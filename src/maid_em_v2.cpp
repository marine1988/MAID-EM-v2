/**
 *        _____  ____    ____  _______          _
 *       |_   _||_   \  /   _||_   __ \        / \
 *         | |    |   \/   |    | |__) |      / _ \
 *     _   | |    | |\  /| |    |  __ /      / ___ \
 *    | |__' |   _| |_\/_| |_  _| |  \ \_  _/ /   \ \_
 *    `.____.'  |_____||_____||____| |___||____| |____|
 *
 * ESP Energy Monitor by Jorge Assunção
 *
 * Remote Debug over Telnet by JoaoLopesF @ https://github.com/JoaoLopesF/ESP8266-RemoteDebug-Telnet
 *
 * See Github for instructions on how to use this code: https://github.com/jorgeassuncao/ESP8266-Energy-Monitor
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License version 2 as published by the Free Software Foundation.
 *
 * You can change your personal user data (wifi access, MQTT server, etc) in the "config/userdata.h" file
 */

//************* INCLUDE LIBRARIES ************************************************************************
//********************************************************************************************************
#include "userdata_devel.h"																											// Load external configuration file
#include "WifiConfig.h"                                               					// Load wifi configuration file
#include <Arduino.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoOTA.h>
#include <RemoteDebug.h>
//#define USE_HARDWARESERIAL
#include <SDM.h>

//************* GLOBAL VARIABLES *************************************************************************
//********************************************************************************************************
unsigned long SEND_FREQUENCY = 14350;                                           // Minimum time between send in milliseconds
unsigned long lastSend;                                                         // Variable -

byte mac[6];                                                                    // Variable - MAC address
char myBuffer[15];                                                              // Variable - MAC string buffer

double ampe;                                                                    // Variable -
//double reading_power;                                                           // Variable -
double kwhTAEaccum;                                                             // Variable -
double kwhTGEaccum;                                                             // Variable -
double voltage;                                                                 // Variable -
double frequency;                                                               // Variable -
double pfactor;                                                                 // Variable -

char voltString[7];                                                             // Variable -
char ampString[7];                                                              // Variable -
char powerString[7];                                                            // Variable -
char aapString[7];                                                              // Variable -
char rapString[7];                                                              // Variable -
char pfString[7];                                                               // Variable -
char freqString[7];                                                             // Variable -
char iaeString[7];                                                              // Variable -
char eaeString[7];                                                              // Variable -
char taeString[7];                                                              // Variable -

double reading_volt;                                                           // Variable -
double reading_amp;                                                            // Variable -
double reading_power;                                                          // Variable -
double reading_aap;                                                            // Variable -
double reading_rap;                                                            // Variable -
double reading_pf;                                                             // Variable -
double reading_freq;                                                           // Variable -
double reading_iae;                                                            // Variable -
double reading_eae;                                                            // Variable -
double reading_tae;                                                            // Variable -

long lastMsg = 0;                                                               // Variable -
char msg[50];                                                                   // Variable -
int value = 0;                                                                  // Variable -

//************* CONFIG SDM120 ****************************************************************************
//********************************************************************************************************
SDM<2400, 12, 13, 4> sdm;                                                       //SDM <baud, rx pin, tx pin, dere>
//SDM<4800, 12, false> sdm;
float m = 0;
char charBuf[50];
String s;
String ss;

//************* CREATE DEBUG *****************************************************************************
//********************************************************************************************************
RemoteDebug Debug;                                                              // Create remote debug

//************* CREATE BREATHE ***************************************************************************
//********************************************************************************************************
int LED_pin = 2;                                                                // Internal LED in NodeMCU
#define BRIGHT 150                                                              // Maximum LED intensity (1-500)
#define INHALE 1500                                                             // Breathe-in time in milliseconds
#define PULSE INHALE*1000/BRIGHT                                                // Pulse
#define REST 1000                                                               // Pause between breathes

//************* CREATE MQTT CLIENT ***********************************************************************
//********************************************************************************************************
WiFiClient espClient;                                                           // Create wifi
PubSubClient client(espClient);                                                 // Create MQTT client

//************* CONFIG WEBSERVER *************************************************************************
//********************************************************************************************************
ESP8266WebServer server(80);                                                    // Config webserver port

#include "webpages.h"																														// Include webpages file

//************* CONFIG OTA *******************************************************************************
//********************************************************************************************************
ESP8266HTTPUpdateServer httpUpdater;

//************* CONNECT TO WIFI AND NTP ******************************************************************
//********************************************************************************************************
void onSTAGotIP(WiFiEventStationModeGotIP ipInfo) {															// Start NTP only after IP network is connected
	Serial.printf("IP address is  %s\r\n", ipInfo.ip.toString().c_str());
	NTP.begin(ntpServerName, timeZone, true);
	NTP.setInterval(86400000); 																										// resync after 86400000 milliseconds (24 hours)
}

void onSTADisconnected(WiFiEventStationModeDisconnected event_info) {						// Manage network disconnection
	Serial.printf("Disconnected from %s\n", event_info.ssid.c_str());
	Serial.printf("Reason: %d\n", event_info.reason);
	digitalWrite(ONBOARD_LED, HIGH); 																							// Turn off internal LED
	//NTP.stop(); // NTP sync disabled to avoid sync errors if no wifi
}

void processSyncEvent(NTPSyncEvent_t ntpEvent) {																// Manage NTP disconnection
	if (ntpEvent) {
		Serial.print("Time Sync error: ");
		if (ntpEvent == noResponse)
			Serial.println("NTP server not reachable");
		else if (ntpEvent == invalidAddress)
			Serial.println("Invalid NTP server address");
	}
	else {
		Serial.print("Got NTP time: ");
		Serial.println(NTP.getTimeDateString(NTP.getLastNTPSync()));
	}
}

boolean syncEventTriggered = false;																							// True if time event has been triggered
NTPSyncEvent_t ntpEvent;																												// Last triggered event

//************* RECONNECT MQTT ***************************************************************************
//********************************************************************************************************
void mqttConnect() {

  while (!client.connected()) {                                                 // Loop until reconnected
    Serial.print("Starting MQTT Client... ");                   								// Send text to serial interface
    Debug.printf("Starting MQTT Client... ");                   								// Send text to telnet debug interface
    if (client.connect(
			DEVICE_HOSTNAME, MQTT_USERNAME, MQTT_PASSWORD,
			MQTT_WILL_TOPIC, MQTT_WILL_QOS, MQTT_WILL_RETAIN, MQTT_WILL_MESSAGE_OFF)) {		// Connect to MQTT broker
			delay(1000);																															// Wait 1 second
			digitalWrite(ONBOARD_LED, LOW); delay(250);																// Blink internal LED
			digitalWrite(ONBOARD_LED, HIGH);																					// ...
			delay(1000);																															// Wait 1 second
      Serial.println(" Started!");                                              // Send text to serial interface
      Debug.println(" Started!");                                               // Send text to telnet debug interface
			Serial.println();                                                         // Block space to serial interface
		  Debug.println();                                                          // Block space to telnet debug interface
			digitalWrite(ONBOARD_LED, LOW); 																					// Turn on internal LED
    } else {
      Serial.print("failed, rc=");                                              // Send text to serial interface
      Debug.printf("failed, rc=");                                              // Send text to telnet debug interface
      Serial.print(client.state());                                             // Send failure state to serial interface
      //Debug.printf(client.state());                                           // Send failure state to telnet debug interface
      Serial.println(" try again in 5 seconds");                                // Send text to serial interface
      Debug.println(" try again in 5 seconds!");                                // Send text to telnet debug interface
      delay(5000);                                                              // Wait 5 seconds before retrying
    }
  }
}

//************* SETUP ************************************************************************************
//********************************************************************************************************
void setup() {

	static WiFiEventHandler e1, e2;																								// Variable -

	server.on("/", handleRoot);                                                   // Serve root page
  server.on("/reset", handleReset);                                             // Serve root page
  server.onNotFound(handleNotFound);                                            // Serve page not found

	pinMode(ONBOARD_LED, OUTPUT); 																								// Set internal LED as output
	digitalWrite(ONBOARD_LED, HIGH); 																							// Switch off LED

	NTP.onNTPSyncEvent([](NTPSyncEvent_t event) {         												// When NTP syncs...
		ntpEvent = event; 																													// ...mark as triggered
		syncEventTriggered = true; 																									// False if time event has been triggered
	});

	e1 = WiFi.onStationModeGotIP(onSTAGotIP);																			// Start NTP only after IP network is connected
	e2 = WiFi.onStationModeDisconnected(onSTADisconnected);												// Manage network disconnection

	Serial.begin(115200);                                                         // Start serial interface
	Serial.println();                                                             // Send space to serial interface
  Debug.println();                                                              // Send space to telnet debug interface

	Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");  // Block separator to serial interface
  Debug.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");   // Block separator to telnet debug interface
  Serial.println(PROJ_VER);                                                     // Send project name and version to serial interface
  Debug.println(PROJ_VER);                                                      // Send project name and version to telnet debug interface
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");  // Block separator to serial interface
  Debug.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");   // Block separator to telnet debug interface
  Serial.println();                                                             // Send space to serial interface
  Debug.println();                                                              // Send space to telnet debug interface

  Serial.print("Connecting to "); Serial.println(ssid);                         // Send network name to serial interface
  Debug.printf("Connecting to "); Debug.println(ssid);                          // Send network name to telnet debug interface

	WiFi.mode(WIFI_STA);                                                          // Switch to STA mode
	WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);                         				// Start wifi connection
	WiFi.macAddress(mac);                                                         // Get MAC address of the device

	delay(10000);																																	// Give time for wifi to connect

  Serial.println("WiFi connected!");                                            // Send successful connection to serial interface
  Debug.println("WiFi connected!");                                             // Send successful connection to telnet debug interface
	delay(1000);
	digitalWrite(ONBOARD_LED, LOW); delay(250); digitalWrite(ONBOARD_LED, HIGH);		// Blink internal LED
	Serial.println();                                                             // Block space to serial interface
  Debug.println();                                                              // Block space to telnet debug interface

  sprintf(myBuffer,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);    // Get MAC address

  Serial.print("MAC address is "); Serial.println(myBuffer);                    // Send MAC address to serial interface
  Debug.printf("MAC address is "); Debug.println(myBuffer);                     // Send MAC address to telnet debug interface
	Serial.println();                                                             // Block space to serial interface
  Debug.println();                                                              // Block space to telnet debug interface

	Serial.print("Starting HTTP server... ");                                     // Block space to serial interface
  Debug.print("Starting HTTP server... ");                                      // Block space to telnet debug interface
	server.begin();                                                               // Start Web server
	delay(1000);																																	// Wait 1 second
	digitalWrite(ONBOARD_LED, LOW); delay(250); digitalWrite(ONBOARD_LED, HIGH);	// Blink internal LED
  Serial.println(" Started!");                                                  // Send text to serial interface
  Debug.println(" Started!");                                                   // Send text to telnet debug interface

	Serial.print("Starting Telnet server... ");                                   // Block space to serial interface
  Debug.print("Starting telnet server... ");                                    // Block space to telnet debug interface
	Debug.begin(DEVICE_HOSTNAME);                                                 // Start Telnet server
	delay(1000);																																	// Wait 1 second
	digitalWrite(ONBOARD_LED, LOW); delay(250); digitalWrite(ONBOARD_LED, HIGH);	// Blink internal LED
	Serial.println(" Started!");                                                  // Send text to serial interface
  Debug.println(" Started!");                                                   // Send text to telnet debug interface
	Debug.setResetCmdEnabled(true);                                               // Enable/disable (true/false) the reset command (true/false)
  Debug.showTime(false);                                                        // Enable/disable (true/false) timestamps
	Debug.showProfiler(false);                                                    // Enable/disable (true/false) Profiler - time between messages of Debug
  Debug.showDebugLevel(false);                                                  // Enable/disable (true/false) debug levels
  Debug.showColors(true);                                                       // Enable/disable (true/false) colors

	Serial.print("Starting mDNS server... ");                                     // Block space to serial interface
  Debug.print("Starting mDNS server... ");                                      // Block space to telnet debug interface
	MDNS.begin(DEVICE_HOSTNAME);                                                  // Start mDNS service
	MDNS.addService("http", "tcp", 80);                                           // Open por 80 for HTTP and TCP
	delay(1000);																																	// Wait 1 second
	digitalWrite(ONBOARD_LED, LOW); delay(250); digitalWrite(ONBOARD_LED, HIGH);	// Blink internal LED
	Serial.println(" Started!");                                                  // Send text to serial interface
	Debug.println(" Started!");                                                   // Send text to telnet debug interface

	Serial.print("Starting OTA Updater... ");                                     // Block space to serial interface
  Debug.print("Starting OTA Updater... ");                                      // Block space to telnet debug interface
	httpUpdater.setup(&server, UPDATE_PATH, ACCESS_USERNAME, ACCESS_PASSWORD);		// Start HTTP Updater
	delay(1000);																																	// Wait 1 second
	digitalWrite(ONBOARD_LED, LOW); delay(250); digitalWrite(ONBOARD_LED, HIGH);	// Blink internal LED
	Serial.println(" Started!");                                                  // Send text to serial interface
	Debug.println(" Started!");                                                   // Send text to telnet debug interface
	Serial.println();                                                             // Block space to serial interface
  Debug.println();                                                              // Block space to telnet debug interface
	Serial.print("Open http://"); Serial.print(WiFi.localIP());										// Send text to serial interface
	Debug.print("Open http://"); Debug.print(WiFi.localIP());											// Send text to telnet debug interface
	Serial.println(" for web interface");																					// Send text to serial interface
	Debug.println(" for web interface");																					// Send text to telnet debug interface
	Serial.print("Open http://"); Serial.print(WiFi.localIP());										// Send text to serial interface
	Debug.print("Open http://"); Debug.print(WiFi.localIP());											// Send text to telnet debug interface
	Serial.print(UPDATE_PATH); Serial.print(" for OTA. Login with username '");		// Send text to serial interface
	Debug.print(UPDATE_PATH); Debug.print(" for OTA. Login with username '");			// Send text to telnet debug interface
	Serial.print(ACCESS_USERNAME); Serial.print("' and password '");							// Send text to serial interface
	Debug.print(ACCESS_USERNAME); Debug.print("' and password '");								// Send text to telnet debug interface
	Serial.print(ACCESS_PASSWORD); Serial.print("'");															// Send text to serial interface
	Debug.print(ACCESS_PASSWORD); Debug.print("'");																// Send text to telnet debug interface
	Serial.println();                                                             // Block space to serial interface
  Debug.println();                                                              // Block space to telnet debug interface

	ArduinoOTA.begin();																														// Start OTA over wifi
	#include "ota.h"																															// Include OTA file

	client.setServer(MQTT_SERVER, MQTT_PORT);                                     // Start MQTT client

  sdm.begin();                                                                  // Initalize SDM120 communication

	delay(2000);																																	// Wait 2 seconds
	Serial.print("Daylight Saving period is ");                                   // Send text to serial interface
	Serial.println(NTP.isSummerTime() ? "Summer Time" : "Winter Time");						// Send text to serial interface

}

//************* LOOP *************************************************************************************
//********************************************************************************************************
void loop() {

	server.handleClient();                                                        // Handle http requests

  for (int ii=1;ii<BRIGHT;ii++){                                              // Breath in
    digitalWrite(LED_pin, LOW);                                               // LED on
    delayMicroseconds(ii*10);                                                 // Wait
    digitalWrite(LED_pin, HIGH);                                              // LED off
    delayMicroseconds(PULSE-ii*10);                                           // Wait
    delay(0);                                                                 // Prevent watchdog firing
  }
  for (int ii=BRIGHT-1;ii>0;ii--){                                            // Breath out
    digitalWrite(LED_pin, LOW);                                               // LED on
    delayMicroseconds(ii*10);                                                 // Wait
    digitalWrite(LED_pin, HIGH);                                              // LED off
    delayMicroseconds(PULSE-ii*10);                                           // Wait
    ii--;
    delay(0);                                                                 // Prevent watchdog firing
  }
    delay(REST);                                                              // Pause before repeat

	ArduinoOTA.handle();	// Handle OTA requests via wifi

	if (syncEventTriggered) {																											// If NTP not sync'ed...
		processSyncEvent(ntpEvent);                                                 // ...sync it again
		syncEventTriggered = false;																									// True if time event has been triggered
	}

	if (!client.connected()) {                                                    // If MQTT client disconnects...
    mqttConnect();                                                              // ...connect again
  }

  client.loop();

  unsigned long now = millis();
	bool sendTime = now - lastSend > SEND_FREQUENCY;                              // Only send values at a maximum frequency

  if (sendTime) {                                                               // Only send values at a maximum frequency

    lastSend = now;                                                             // Update the send time

    s = String(sdm.readVal(SDM120C_VOLTAGE));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_VOLT, charBuf);
      Serial.print("Volts: ");
      Serial.print(s); Serial.println(" V");
      reading_volt = sdm.readVal(SDM120C_VOLTAGE);
      Debug.println("voltage read");
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_CURRENT));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_AMP, charBuf);
      Serial.print("Amps: ");
      Serial.print(s); Serial.println(" A");
      reading_amp = sdm.readVal(SDM120C_CURRENT);
    }

    delay(50);

    s = abs(sdm.readVal(SDM120C_POWER));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_WATT, charBuf);
      Serial.print("Watt: ");
      Serial.print(s); Serial.println(" W");
      reading_power = abs(sdm.readVal(SDM120C_POWER));
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_ACTIVE_APPARENT_POWER));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_AAP, charBuf);
      Serial.print("Active Apparent Power: ");
      Serial.print(s); Serial.println(" VA");
			reading_aap = sdm.readVal(SDM120C_ACTIVE_APPARENT_POWER);
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_REACTIVE_APPARENT_POWER));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_RAP, charBuf);
      Serial.print("Reactive Apparent Power: ");
      Serial.print(s); Serial.println(" VAR");
			reading_rap = sdm.readVal(SDM120C_REACTIVE_APPARENT_POWER);
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_POWER_FACTOR));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_PF, charBuf);
      Serial.print("Power Factor: ");
      Serial.print(s); Serial.println(" pf");
      reading_pf = sdm.readVal(SDM120C_POWER_FACTOR);
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_FREQUENCY));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_FREQ, charBuf);
      Serial.print("Frequency: ");
      Serial.print(s); Serial.println(" Hz");
      reading_freq = sdm.readVal(SDM120C_FREQUENCY);
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_IMPORT_ACTIVE_ENERGY));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_IAE, charBuf);
      Serial.print("Import Active Energy: ");
      Serial.print(s); Serial.println(" Wh");
			reading_iae = sdm.readVal(SDM120C_IMPORT_ACTIVE_ENERGY);
    }

    delay(50);

    s = String(sdm.readVal(SDM120C_EXPORT_ACTIVE_ENERGY));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_EAE, charBuf);
      Serial.print("Export Active Energy: ");
      Serial.print(s); Serial.println(" Wh");
			reading_eae = sdm.readVal(SDM120C_EXPORT_ACTIVE_ENERGY);
    }

    delay(50);

		s = String(sdm.readVal(SDM120C_TOTAL_ACTIVE_ENERGY));
    if (s != "nan") {
      s.toCharArray(charBuf, 50);
      client.publish(MQTT_TOPIC_TAE, charBuf);
      Serial.print("Total Active Energy: ");
      Serial.print(s); Serial.println(" Wh");
      reading_tae = sdm.readVal(SDM120C_TOTAL_ACTIVE_ENERGY);
    }

    delay(50);

		dtostrf(reading_volt, 5, 2, voltString);                                    // Convert to string
		dtostrf(reading_amp, 5, 2, ampString);                                      // Convert to string
    dtostrf(reading_power, 5, 2, powerString);                                  // Convert to string
		dtostrf(reading_aap, 5, 2, aapString);                                      // Convert to string
		dtostrf(reading_rap, 5, 2, rapString);                                      // Convert to string
    dtostrf(reading_pf, 5, 2, pfString);                                        // Convert to string
		dtostrf(reading_freq, 5, 2, freqString);                                    // Convert to string
    dtostrf(reading_iae, 5, 2, iaeString);                                      // Convert to string
		dtostrf(reading_eae, 5, 2, eaeString);                                      // Convert to string
    dtostrf(reading_tae, 5, 2, taeString);                                      // Convert to string

    Debug.println("Volt"); Debug.println(voltString);
		Debug.println("Amp"); Debug.println(ampString);
    Debug.println("Watt"); Debug.println(powerString);
		Debug.println("Active Apparent Power"); Debug.println(aapString);
		Debug.println("Reactive Apparent Power"); Debug.println(rapString);
		Debug.println("Power Factor"); Debug.println(pfString);
    Debug.println("Frequency"); Debug.println(freqString);
		Debug.println("Import Active Energy"); Debug.println(iaeString);
		Debug.println("Export Active Energy"); Debug.println(eaeString);
    Debug.println("Total Active Energy"); Debug.println(taeString);


    Debug.handle();                                                             // Remote debug over telnet

    Serial.println("----------------------------------------");

  }

  yield();                                                                      // Yielding

}

// END
//********************************************************************************************************
