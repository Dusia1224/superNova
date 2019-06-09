#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"

// Rename the credentials.sample.h file to credentials.h and
// edit it according to your router configuration

#include "credentials.h" //TO-DO
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
    open_var=false; //State of the Trunk

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
    // "Alexa, set yellow lamp to fifty" (50 means 50% of brightness, note, this example does not use this functionality)

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

        if (strcmp(device_name, ID_YELLOW)==0) {
            digitalWrite(LED_YELLOW, state ? HIGH : LOW);
        } else if (strcmp(device_name, ID_GREEN)==0) {
            digitalWrite(LED_GREEN, state ? HIGH : LOW);
        } else if (strcmp(device_name, ID_BLUE)==0) {
            digitalWrite(LED_BLUE, state ? HIGH : LOW);
        } else if (strcmp(device_name, ID_PINK)==0) {
            digitalWrite(LED_PINK, state ? HIGH : LOW);
        } else if (strcmp(device_name, ID_WHITE)==0) {
            digitalWrite(LED_WHITE, state ? HIGH : LOW);
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
    Unlock();
    Open_Trunk();
    Close_Trunk();
    Start_Car();
    Panic();
}

void Unlock() //function for unlock 2 clicks
{
digitalWrite(unlock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(unlock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Lock() //function for lock 2 clicks
{
digitalWrite(lock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(lock, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Trunk() //function for trunk 2 clicks
{
digitalWrite(trunk, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(trunk, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Ignition() //function for ignition 2 clicks
{
digitalWrite(ignition, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(ignition, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

void Panic() //function for panic 1 click
{
digitalWrite(panic, HIGH);
delay(standard_time); // Wait for standard_time millisecond(s)
digitalWrite(panic, LOW);
delay(standard_time); // Wait for standard_time millisecond(s)
}

//Open Trunk
//------------------------------------------------------------------
/*Logic:
 * First we must lock the car doors and then open the trunk door
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
 * Press the trunk button again. This function will only run if trunk
 * is actually open
 */
//------------------------------------------------------------------
void Close_Trunk()
{
Trunk();
}

//Start Car
//------------------------------------------------------------------
/*Logic:
 * First we must lock the car doors and then Press the car ignition
 */
//------------------------------------------------------------------
void Start_Car()
{
Lock();
Ignition();
}
