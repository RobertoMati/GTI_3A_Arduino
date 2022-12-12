

#include <bluefruit.h>
#include <math.h>
//Pines para lectura
int Vgas = A5;
int Vref = A4;
int Vtmp = A3;

double offset=0;

int Vgas_value = 0;
int Vref_value = 0;
int Vtmp_value = 0;

double M = 0;
double Cx = 0;

//funcion promedirar
float promediar(){
  //media entre 10000 valores
  for (int i=0; i<10000; i++){
    Vgas_value += analogRead(Vgas);
   /* Serial.println(i);
    Serial.println(Vgas_value);*/
  }
  Vgas_value = Vgas_value/10000;
  Serial.println("El valor promediado es");
  Serial.println(Vgas_value);
  return Vgas_value;
}

//aplicación de la formular para la conenctracion en ppm
void medidasVref(){
  
  float M = 34.33 * 499 *pow(10,-9) * pow(10,3);
  //Serial.print(M);
  /*double s = ((3,3/4096)*Vgas_value);
  Serial.println(s);*/

  /*Serial.print("Valor vgas");
  Serial.println(vgasa);*/

  float t = 1/M;
  /*Serial.println(t);*/
  //Llamada a la función promediar
  float promedio = promediar();
  float vgasa = promedio* 0.806 * pow(10,-3);
  Serial.print("Valor vgas normal");
  Serial.println(vgasa);
  float vgas0 = analogRead(Vref)* 0.806 * pow(10,-3);
  Serial.print("Valor vgas");
  Serial.println(vgas0);

  Cx = t* (abs(vgasa-vgas0));


  Serial.print("Valor calibrado");
  Serial.println(Cx, 6);
  
} 


void setup() {
   Serial.begin(115200);
   while ( !Serial ) delay(10);
   Serial.println("-----------------------------------------------\n");
   Serial.println(" Iniciamos la operación de envío de iBeacons  ");
   Serial.println("-----------------------------------------------\n");
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   //Inicializamos el módule Bluefruit nRF52
   Serial.println("Iniciamos el módule Bluefruit nRF52");
   Bluefruit.begin();
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   // Elegimos el nombre del dispositivo
   Serial.println("Nombro al dispositivo como GTI-3ARoberto" );
   Bluefruit.setName("GTI-3ARoberto");
   Bluefruit.ScanResponse.addName();
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   // Llamamos a la función que envía el iBeacon
   ComienzoEnvioBeacons();
   Serial.println("\nAdvertising");
   //-------------------------------------------------------------
}




void ComienzoEnvioBeacons() {
   medidasVref();

   //-------------------------------------------------------------
   Serial.println( " ComienzoEnvioBeacons() " );
   Serial.println( " Bluefruit.Advertising.stop(); ");
   //Detenemos la publicidad. Se inicia al final de la función
   Bluefruit.Advertising.stop();
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   // Paquete de publicidad
   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
   Bluefruit.Advertising.addTxPower();
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   // Incluimos el nombre del dispositivo
   Serial.println( " Bluefruit.Advertising.addName(); " );
   Bluefruit.Advertising.addName();
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   Serial.println( " Bluefruit.Advertising.setBeacon( elBeacon ); ");

   //-------------------------------------------------------------
   //Creamos el identificador del iBeacon
   uint8_t beaconUUID[16] = {'E', 'P', 'S', 'G', '-', 'R', 'O', 'B','E', 'R', 'T', 'O', '-', 'P', 'R', 'O' };
    /* Creamos el iBeacon. Este consta de 4 partes: 
       1. Identificador del iBeacon
       2. Major
       3. Minor
       4. Potencia de transmisión (TxPower)
   */
   BLEBeacon elBeacon( beaconUUID, 12,Cx*10000, 73 );
   elBeacon.setManufacturer( 0x004c ); // Apple ID
   // Se añade el iBeacon al paquete de publicidad
   Bluefruit.Advertising.setBeacon( elBeacon );
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   //Iniciamos la publicidad
   Bluefruit.Advertising.restartOnDisconnect(true);
   Bluefruit.Advertising.setInterval(32, 244);    // En unidad de 0.625 ms
   Bluefruit.Advertising.setFastTimeout(30);      // Número de segundos en modo rápido
   Bluefruit.Advertising.start(0);                // 0 = No parar de transmitir después de un número de segundos
   Serial.println( " Bluefruit.Advertising.start(0);" );
   //-------------------------------------------------------------
}

/*
* @brief  Esta función (loop) se inicia un contador.
*/namespace Loop {
    //Iniciamos el contador a 0
   int cont = 0;
};

/*
* @brief  Esta función (loop) se encarga contar las veces que se ha producido la transmisión del iBeacon.
*/
void loop() {
   
   //-------------------------------------------------------------
   using namespace Loop;
   //-------------------------------------------------------------
   medidasVref();
   ComienzoEnvioBeacons();

   //-------------------------------------------------------------
   // Vamos aumentando el contador
   cont++;
   //Añadimos un retardo de 1 segundo
   delay(1000);
   Serial.print( " ** loop cont=" );
   Serial.println( cont );
   //-------------------------------------------------------------
} 

// ----------------------------------------------------
// Fin Proceso loop()
// ----------------------------------------------------
