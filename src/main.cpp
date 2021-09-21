
#include <Arduino.h>
#include <Ps3Controller.h>
#include <stdlib.h>


#define sig_pwm_tracao 2
#define sig_frente     4
#define sig_re         5

#define sig_dir_esq    18
#define sig_dir_dir    19
#define sig_pwm_dir    21

#define sig_farol      13

int player = 0;
int battery = 0;

void notify()
{
        if (Ps3.data.analog.stick.lx>10)
       { 
           digitalWrite(sig_dir_dir,1);
           digitalWrite(sig_dir_esq,0);

       }
       else if (Ps3.data.analog.stick.lx<-10)
       {
           digitalWrite(sig_dir_dir,0);
           digitalWrite(sig_dir_esq,1);
       }

    int8_t aux= Ps3.data.analog.stick.lx;
    if(aux<0)
        aux=aux*-1;

    uint8_t aux2=(uint8_t)aux;

    if(aux2>10)
        ledcWrite(1,aux2*2);
    else    
        ledcWrite(1, 0);

    //--- Digital cross/square/triangle/circle button events ---


    if( Ps3.event.button_down.triangle )
    {
        Serial.println("Started pressing the triangle button");
        digitalWrite(sig_farol,!digitalRead(sig_farol));
    }
    if( Ps3.event.button_up.triangle )
        Serial.println("Released the triangle button");

    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 )
    {
        Serial.println("Started pressing the left trigger button");
        digitalWrite(sig_re,1);
    }
        
    if( Ps3.event.button_up.l2 )
    {
        Serial.println("Released the left trigger button");
        digitalWrite(sig_re,0);
    }
        

    if( Ps3.event.button_down.r2 )
    {
        Serial.println("Started pressing the right trigger button");
        digitalWrite(sig_frente,1);
    }
        
    if( Ps3.event.button_up.r2 )
    {
        Serial.println("Released the right trigger button");
        digitalWrite(sig_frente,0);
    }



    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print("Moved the left stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);

       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }
  //  else 
    //    ledcWrite(1,0);

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
       Serial.print("Moved the right stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
       Serial.println();
   }


   

   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("98:83:89:8d:74:b6");

    pinMode(sig_frente,OUTPUT);
    pinMode(sig_re,OUTPUT);
    pinMode(sig_dir_esq,OUTPUT);
    pinMode(sig_dir_dir,OUTPUT);
    pinMode(sig_farol,OUTPUT);

    ledcSetup(0, 2500, 8);
    ledcAttachPin(sig_pwm_tracao, 0);
    ledcSetup(1, 2500, 8);
    ledcAttachPin(sig_pwm_dir, 1);
    Serial.println("Ready.");
}

void loop()
{
    if(!Ps3.isConnected())
        return;

    
    delay(2000);
}