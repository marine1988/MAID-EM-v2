/**
 * File contents of "userdata_devel.h" for MAID-EM v2
 *
 * This file is used to change the userdata to meet your needs
 */

 //************* PROJECT AND VERSION **********************************************************************
 //********************************************************************************************************
 const char* PROJ_VER = "MAID-EM v2 v0.1.2 (21/06/2018)";                       // Project name and version

//************ CONFIG WIFI *******************************************************************************
// Configurations of your wifi network - Fixed IP is used because it's quicker than DHCP. IP address and
// and Hostname must be unique inside your network
//********************************************************************************************************
  #ifndef WIFI_CONFIG_H
  #define YOUR_WIFI_SSID "rD_domotic"                                            // Wifi SSID
  #define YOUR_WIFI_PASSWD "9645077188"                                      // Wifi password
  #endif // !WIFI_CONFIG_H

// If you want to use a fixed IP address, open "wifiConfig.h" and edit lines 123, 124 and 125

  #define DEVICE_HOSTNAME "maid_em_v2"                                          // Hostname

//************ CONFIG NTP ********************************************************************************
// Configurations for the NTP server - Use the address of the server closer to your location
//********************************************************************************************************
  static const char ntpServerName[] = "ntp02.oal.ul.pt";                        // NTP server address
  const int timeZone = 0;                                                       // Timezone (0 = UTC)

//************ CONFIG ACCESS TO UPDATE PAGE **************************************************************
// Configurations for OTA page - When you access "http://<device-ip>/firmware" the page will ask for a
// username and password. For your security, please change both or at least the password!
//********************************************************************************************************
  const char* ACCESS_USERNAME = "admin";                                        // Username to the web update page
  const char* ACCESS_PASSWORD = "1a2b3c";                                       // Password to the web update page
  const char* UPDATE_PATH = "/firmware";                                        // Path to update page

//************* CONFIG MQTT ******************************************************************************
// Configurations of your MQTT server -
//********************************************************************************************************
  const char* MQTT_SERVER = "192.168.1.6";                                  // MQTT server IP ou URL
  int MQTT_PORT = 1883;                                                         // MQTT port
  const char* MQTT_USERNAME = "marine88";                                  // MQTT user
  const char* MQTT_PASSWORD = "impresora";                                  // MQTT password

//************ MQTT LWT **********************************************************************************
// Configurations of your MQTT LWT - Define here the Last Will and Testment of your device. the MQTT broker and the
// payload for door open and closed
//********************************************************************************************************
  const char* MQTT_WILL_TOPIC = "home/indoor/sensor/MAID-EM-01/status";// MQTT last will topic
  const char* MQTT_WILL_MESSAGE_ON = "Online";                                  // MQTT last will message on
  const char* MQTT_WILL_MESSAGE_OFF = "Offline";                                // MQTT last will message off
  int MQTT_WILL_QOS = 1;                                                        // MQTT last will QoS (0,1 or 2)
  int MQTT_WILL_RETAIN = 0;                                                     // MQTT last will retain (0 or 1)

//************ MQTT TOPICS *******************************************************************************
// Configurations of your MQTT topics - Enter the topic you want to publish to the MQTT broker and the
// payload for door open and closed
//********************************************************************************************************
  const char* MQTT_TOPIC_VOLT = "home/indoor/sensor/MAID-EM-01/volt";           // MQTT topic - Volt
  const char* MQTT_TOPIC_AMP = "home/indoor/sensor/MAID-EM-01/amp";             // MQTT topic - Amp
  const char* MQTT_TOPIC_WATT = "home/indoor/sensor/MAID-EM-01/watt";           // MQTT topic - Watt
  const char* MQTT_TOPIC_AAP = "home/indoor/sensor/MAID-EM-01/aap";             // MQTT topic - Active Apparent Power
  const char* MQTT_TOPIC_RAP = "home/indoor/sensor/MAID-EM-01/rap";             // MQTT topic - Reactive Apparent Power
  const char* MQTT_TOPIC_PF = "home/indoor/sensor/MAID-EM-01/pf";               // MQTT topic - Power Factor
  const char* MQTT_TOPIC_FREQ = "home/indoor/sensor/MAID-EM-01/freq";           // MQTT topic - Frequency
  const char* MQTT_TOPIC_TAE = "home/indoor/sensor/MAID-EM-01/tae";             // MQTT topic - Total Active Energy (*)
  const char* MQTT_TOPIC_IAE = "home/indoor/sensor/MAID-EM-01/iae";             // MQTT topic - Import Active Energy
  const char* MQTT_TOPIC_EAE = "home/indoor/sensor/MAID-EM-01/eae";             // MQTT topic - Export Active Energy

  const char* MQTT_TOPIC_ip = "home/indoor/sensor/MAID-EM-01/ip";               // MQTT topic - ip
  const char* MQTT_TOPIC_mac = "home/indoor/sensor/MAID-EM-01/mac";             // MQTT topic - mac

//************* CONFIG PINS ******************************************************************************
// Configurations of the device pins - This is where you configure which pins should be used. You can
// change them to fit your needs. The pins refer to Arduino-like pins and not the ones marked on the board
//********************************************************************************************************
  #define ONBOARD_LED 2                                                         // WEMOS D1 mini internal LED
  #define DHTPIN 4                                                              // DHT pin
  #define DHTTYPE DHT22                                                         // DHT type

// END
//********************************************************************************************************
