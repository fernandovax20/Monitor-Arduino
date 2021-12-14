#include "LCD.h"
#include "Anemometro.h"
#include "HC.h"
#include "MonitorESP.h"
#include <DHT.h>  

//------Variable ESP8266----------------------
MonitorESP esp;

//------Variables LCD-------------------------
LCDController lcdc;

//------Variables DHT-------------------------
int SENSOR = 4;     // pin DATA de DHT22
String TEMPERATURA;
String HUMEDAD;
DHT dht(SENSOR, DHT22);

//------Variables Anemometro------------------
Anemometro anemometro;

//------Variables HC -------------------------
HC hc;

void setup(){
  Serial.println("Entra");
  //Inicializacion de monitor serial
  Serial.begin(9600);   

  //Setup ESP8266
  esp.inicio();

  //Setup LCD
  lcdc.iniciar();

  //Setup DHT
  dht.begin(); 

  //Setup Anemometro
  //anemometro.inicio();

  //Setup HC
  hc.inicio();
}

void loop(){
    
    String dist = hc.getDistancia();
    
    TEMPERATURA = String(dht.readTemperature());  // obtencion de valor de temperatura
    HUMEDAD = String(dht.readHumidity());   // obtencion de valor de humedad
    
    lcdc.showDisplay(hc.getMAX() ,hc.getMIN() ,hc.getAVG(), String(anemometro.getData()), TEMPERATURA, HUMEDAD);
    esp.sendData(hc.getMAX() ,hc.getMIN() ,hc.getAVG(), String(anemometro.getData()), TEMPERATURA, HUMEDAD); 
    Serial.println("MAX: "+hc.getMAX()+" MIN: "+hc.getMIN()+" AVG: "+hc.getAVG()+" ANEM: "+String(anemometro.getData())+" TEMP: "+TEMPERATURA+" HUM: "+HUMEDAD+" Dist: "+dist);
   
    
}
