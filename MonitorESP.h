#include <SoftwareSerial.h>
#define RX 2
#define TX 3
SoftwareSerial esp8266(RX,TX); 

class MonitorESP{
    private:
        String AP = "TP-Link_77DE_2.4";       // AP NAME
        String PASS = "LecpU162534"; // AP PASSWORD
        String API = "C49E07XSQX97HMW8";   // Write API KEY
        String HOST = "api.thingspeak.com";
        String PORT = "80";
        int countTrueCommand;
        int countTimeCommand; 
        boolean found = false; 
        int valSensor = 1;
    public:
    
        void inicio(){
            esp8266.begin(115200);
            sendCommand("AT",5,"OK");
            sendCommand("AT+CWMODE=1",5,"OK");
            sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
        }

        void sendData(String MAX, String MIN, String AVG, String ANEM, String TEMP, String HUM){
          static long last_change = 0;
          long hora = millis();

          if(hora - last_change > 46000){
            last_change = hora;
                
            String getData = "GET /update?api_key="+ API +"&field1="+MAX+"&field2="+MIN+
            "&field3="+AVG+"&field4="+ANEM+"&field5="+TEMP+"&field6="+HUM;
            
            sendCommand("AT+CIPMUX=1",5,"OK");
            sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
            sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
            esp8266.println(getData);
            countTrueCommand++;
            sendCommand("AT+CIPCLOSE=0",5,"OK");
          }  
        }
        void sendCommand(String command, int maxTime, char readReplay[]) {
          //Serial.print(countTrueCommand);
          //Serial.print(". at command => ");
          //Serial.print(command);
          //Serial.print(" ");
          while(countTimeCommand < (maxTime*1))
          {
            esp8266.println(command);//at+cipsend
            if(esp8266.find(readReplay))//ok
            {
              found = true;
              break;
            }
          
            countTimeCommand++;
          }
          
          if(found == true)
          {
            //Serial.println("OYI");
            countTrueCommand++;
            countTimeCommand = 0;
          }
          
          if(found == false)
          {
            //Serial.println("Fail");
            countTrueCommand = 0;
            countTimeCommand = 0;
          }
          
          found = false;
        }
        
        
};
