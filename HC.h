class HC{
    private:
        int TRIG = 6;      // trigger en pin 10
        int ECO = 5;      // echo en pin 9
        int DURACION;
        int DISTANCIA;
        int DistMAX = 19;
        
        int MAX = 0;
        int MIN = 9999;
        int RMAX = 0;
        int RMIN = 0;
        int AMP = 0;
        int AVG = 0;

    public:
        
        void inicio(){            
            pinMode(TRIG, OUTPUT);  // trigger como salida
            pinMode(ECO, INPUT);    // echo como entrada
        }

        String getDistancia(){
            static long last_change = 0;
            long hora = millis();
            
            digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
            
            if(hora - last_change > 1){
              last_change = hora;
              
              digitalWrite(TRIG, LOW);    // al pin conectado al trigger del sensor
              DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso alto en Echo
              DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros   

              if(MAX<DISTANCIA){
                MAX = DISTANCIA;
                RMIN = DistMAX-MAX; 
              }
              if(MIN>DISTANCIA){
                MIN = DISTANCIA;
                RMAX = DistMAX-MIN;
              }
              
              AMP = (RMAX-RMIN)/2;
              AVG = AMP+RMIN; 

              static long last_change2 = 0;
              long hora2 = millis();  
              if(hora2 - last_change2 > 60000){
                last_change2 = hora2;
                MAX = 0;
                MIN = 9999;
                AMP = 0;
                AVG = 0;
              }
            }
            return String(DISTANCIA);
        }
        
        String getMIN(){
          return String(RMIN);
        }
        String getMAX(){
          return String(RMAX);
        }
        String getAVG(){
          return String(AVG);
        }
};
