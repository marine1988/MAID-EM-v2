# MAID-EM v2 - Energy Monitor

The **MAID-EM v2 - Energy Monitor** is an energy monitor based on a ESP8266 board that uses the SDM120 (or compatible) single phase energy meter to get energy readings. The energy monitor is MQTT enabled and sends readings for all the values measured by the meter.

The **MAID** acronym stands for **M**qtt en**A**bled w**I**fi no**D**e.

### Version
Current version is: _v0.1.2 (21/06/2018)_

### Features
+ Works on ESP8266-based boards.
+ Separate file with all the variables that need to be configured, so you do not have to mess with all the code
+ MQTT enabled with the PubSubClient library
+ Configurable MQTT topics to fit your needs
+ Publishes various information over MQTT:
  + Current Consumption (kWh)
  + Current Power (Watt)
  + Accumulated Consumption (kWh)
  + IP address
  + MAC address
+ Retains the last accumulated consumption value even if the device is rebooted, reset or powered off
+ ESP8266 Webserver to create a web interface
+ Web interface uses Bootstrap framework
+ Information available on the web interface:
  + Current Consumption (kWh)
  + Current Power (Watt)
  + Accumulated Consumption (kWh)
+ A button on the web interface allows to reset the device remotely
+ Debug info via serial interface
+ Information available on the serial interface:
  + IP address
  + MAC address
  + Current Consumption (kWh)
  + Current Power (Watt)
  + Accumulated Consumption (kWh)
+ Telnet server
  + Set CPU speed for ESP8266 (80MHz/160MHz)
  + Remote reset of the device
+ Remote debug via Telnet server with configurable debug level (verbose, debug, info, warning and errors), profiler and filter
+ Information available on the telnet interface
  + Host name
  + IP address
  + MAC address
  + Free Heap RAM
  + Current Consumption (kWh)
  + Current Power (Watt)
  + Accumulated Consumption (kWh)
+ Visual confirmation of operation using the device internal blue LED
