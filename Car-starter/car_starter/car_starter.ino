
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include "ESP8266WiFi.h"
#endif
#include "fauxmoESP.h"

// Rename the credentials.sample.h file to credentials.h and
// edit it according to your router configuration

#include "credentials.sample.h" //TO-DO
fauxmoESP fauxmo;

bool open_var;

// -----------------------------------------------------------------------------

#define SERIAL_BAUDRATE     115200

#define UNLOCK              2
#define LOCK                4
#define TRUNK               7
#define IGNITION            8
#define PANIC               12
#define STANDARD_TIME       250

// "Alexa, turn yellow lamp on"
// "Alexa, turn on yellow lamp
#define ID_UNLOCK           "unlock button"
#define ID_LOCK             "lock button"
#define ID_TRUNK            "trunk button"
#define ID_IGNITION         "ignition button"
#define ID_PANIC            "panic button"

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {

  // Init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // Buttons
  pinMode(UNLOCK, OUTPUT); //Unlock button on FOB
  pinMode(LOCK, OUTPUT); //Lock button on FOB
  pinMode(TRUNK, OUTPUT); //Trunk button on FOB
  pinMode(IGNITION, OUTPUT); //Ignition button on FOB
  pinMode(PANIC, OUTPUT); //Panic button on FOB
  open_var = false; //State of the Trunk

  digitalWrite(UNLOCK, LOW);
  digitalWrite(LOCK, LOW);
  digitalWrite(TRUNK, LOW);
  digitalWrite(IGNITION, LOW);
  digitalWrite(PANIC, LOW);

  // Wifi
  wifiSetup();

  // By default, fauxmoESP creates it's own webserver on the defined port
  // The TCP port must be 80 for gen3 devices (default is 1901)
  // This has to be done before the call to enable()
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices

  // You have to call enable(true) once you have a WiFi connection
  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);

  // You can use different ways to invoke alexa to modify the devices state:
  // "Alexa, turn yellow lamp on"
  // "Alexa, turn on yellow lamp

  // Add virtual devices
  fauxmo.addDevice(ID_UNLOCK);
  fauxmo.addDevice(ID_LOCK);
  fauxmo.addDevice(ID_TRUNK);
  fauxmo.addDevice(ID_IGNITION);
  fauxmo.addDevice(ID_PANIC);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    // Callback when a command from Alexa is received.
    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
    // If you have to do something more involved here set a flag and process it in your main loop.

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
    // Otherwise comparing the device_name is safer.

    if (strcmp(device_name, ID_UNLOCK) == 0) {
      Unlock();
    } else if (strcmp(device_name, ID_LOCK) == 0) {
      Lock();
    } else if (strcmp(device_name, ID_TRUNK) == 0) {
      Trunk();
    } else if (strcmp(device_name, ID_IGNITION) == 0) {
      Ignition();
    } else if (strcmp(device_name, ID_PANIC) == 0) {
      Panic();
    }

  });

}

void loop() {

  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

  // This is a sample code to output free heap every 5 seconds
  // This is a cheap way to detect memory leaks
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }

  // If your device state is changed by any other means (MQTT, physical button,...)
  // you can instruct the library to report the new state to Alexa on next request:
  // fauxmo.setState(ID_YELLOW, true, 255);

}

void Unlock() //function for unlock 2 clicks
{
  digitalWrite(UNLOCK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(UNLOCK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(UNLOCK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(UNLOCK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
}

void Lock() //function for lock 2 clicks
{
  digitalWrite(LOCK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(LOCK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(LOCK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(LOCK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
}

void Trunk() //function for trunk 2 clicks
{
  digitalWrite(TRUNK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(TRUNK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(TRUNK, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(TRUNK, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
}

void Ignition() //function for ignition 2 clicks
{
  digitalWrite(IGNITION, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(IGNITION, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(IGNITION, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(IGNITION, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
}

void Panic() //function for panic 1 click
{
  digitalWrite(PANIC, HIGH);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
  digitalWrite(PANIC, LOW);
  delay(STANDARD_TIME); // Wait for STANDARD_TIME millisecond(s)
}

//Open Trunk
//------------------------------------------------------------------
/*Logic:
   First we must lock the car doors and then open the trunk door
*/
//------------------------------------------------------------------

void Open_Trunk()
{
  Lock();
  Trunk();
}

//Close Trunk
//------------------------------------------------------------------
/*Logic:
   Press the trunk button again. This function will only run if trunk
   is actually open
*/
//------------------------------------------------------------------
void Close_Trunk()
{
  Trunk();
}

//Start Car
//------------------------------------------------------------------
/*Logic:
   First we must lock the car doors and then Press the car ignition
*/
//------------------------------------------------------------------
void Start_Car()
{
  Lock();
  Ignition();
}
