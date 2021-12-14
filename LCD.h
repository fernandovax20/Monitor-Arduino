#include <LiquidCrystal.h>
int VO = 9; int RS = 7; int E = 8;
int D4 = 10; int D5 = 11; int D6 = 12; int D7 = 13;
LiquidCrystal lcd (RS, E, D4, D5, D6, D7);

class LCDController{
    private:

    public:
    void iniciar(){
        analogWrite(VO, 120);
        lcd.begin(16, 2);
    }
    
    void showDisplay(String MAX, String MIN, String AVG, String ANEMOMETRO, String TEMPERATURA, String HUMEDAD){
        
        static long last_change = 0;
        long hora = millis();
        
        if(hora - last_change > 8000){
          last_change = hora;
          lcd.setCursor(0, 0);
          lcd.print("Mx: "+MAX+"cm Mn: "+MIN+"cm           ");
          lcd.setCursor(0,1);
          lcd.print("A: "+AVG+"cm                         ");
          
        }else if(hora - last_change > 5000){
          //last_change = hora;
          lcd.setCursor(0, 0);
          lcd.print("An: "+ANEMOMETRO+"Km/h                   ");
          lcd.setCursor(0,1);
          lcd.print("                                    ");
        }
        else if(hora - last_change > 2000){
          lcd.setCursor(0, 0);
          lcd.print("Tm: "+TEMPERATURA+"C                   ");
          lcd.setCursor(0,1);
          lcd.print("Hu: "+HUMEDAD+"%                       ");
          
        }
        
    }
};
