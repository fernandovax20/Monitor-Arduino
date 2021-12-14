class Anemometro
{
    private:
        float lectura;
        float volt;
        float kmh;
        float MAX=0;
    public:
    
        void inicio(){
            pinMode(A0,INPUT);
        }
        
        String getData(){
          static long last_change = 0;
          long hora = millis();  
          
          if(hora - last_change > 500){
            last_change = hora;
                
            lectura = analogRead(A0);
            volt = lectura /1023 * 5.0;
            if(volt!=0 && volt>0.02 ){
              kmh=(10*volt-0.1011)/0.1027;
              if(MAX<kmh){
                MAX = kmh;
              }
            }else{
              kmh = 0;
            }
            static long last_change2 = 0;
              long hora2 = millis();  
              if(hora2 - last_change2 > 60000){
                last_change2 = hora2;
                MAX = 0;
              }
          }
          return String(MAX);
        }
};
