// -*- mode: c++ -*-
// -------------------------------------------------------------------------------------
// Adaptado de https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/adafruitbluefruit
// Autora: Claudia Torres Cruz
// -------------------------------------------------------------------------------------
#include <bluefruit.h>
#include <stdlib.h>
// -------------------------------------------------------------------------------------
// setup
// -------------------------------------------------------------------------------------
void setup() {
   //
   //
   // OJO, hay que tener abierto el serial
   Serial.begin(115200);
   while ( !Serial ) delay(10);

   Serial.println("-----------------------\n");
   Serial.println(" PRUEBAS iBeacon  ");
   Serial.println("-----------------------\n");

   //
   // Initialise the Bluefruit module
   //
   Serial.println("Initialise the Bluefruit nRF52 module");
   Bluefruit.begin();

   //
   // Set the advertised device name (keep it short!)
   //
   Serial.println("Setting Device Name to GTI-CLAUDIA " );

   Bluefruit.setName("GTI-3A-ClaudiaTorresCruz"); //NOMBRE DEL DISPOSITIVO
   Bluefruit.ScanResponse.addName();

   //
   //
   //
   startAdvertising();

   //
   //
   //
   Serial.println("\nAdvertising");

} // setup()
// -------------------------------------------------------------------------------------
/**
 * Diseño:  --> startAdvertising() --> Beacon
**/
// -------------------------------------------------------------------------------------
void startAdvertising() {

   Serial.println( " startAdvertising() " );

   Serial.println( " Bluefruit.Advertising.stop(); ");
   Bluefruit.Advertising.stop(); // ya lo enchufo luego
   //
   // Advertising packet
   //
   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE); //CAMBIAR
   Bluefruit.Advertising.addTxPower();
   //
   //
   //
   // Include Name
   Serial.println( " Bluefruit.Advertising.addName(); " );
   Bluefruit.Advertising.addName();
   uint8_t beaconUUID[16] = {
     'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
     '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
     }; 
   //
   //
   //
   BLEBeacon elBeacon( beaconUUID, 12, 20, 73 ); //CAMBIAR UNO DE LOS 12 Y 34 MAJOR Y MINOR Y PONERLO CON CONTADOR
   elBeacon.setManufacturer( 0x004c ); // aple id
   Serial.println( " Bluefruit.Advertising.setBeacon( elBeacon ); ");
   Bluefruit.Advertising.setBeacon( elBeacon );
   
   Bluefruit.Advertising.restartOnDisconnect(true);
   Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
   Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
   Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

   Serial.println( " Bluefruit.Advertising.start(0);" );

} // startAdvertising ()
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
namespace Loop {
   int cont = 0;
};
// -------------------------------------------------------------------------------------
/**
 * @brief Esta función solo crea un contador infinito que se va mostrando en el serial
 * Diseño:  --> loop() --> 
**/
// -------------------------------------------------------------------------------------
void loop() {

   using namespace Loop;

   cont++;
   

   delay(1000);

   Serial.print( " ** loop cont=" );
   Serial.println( cont );

} // ()
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
