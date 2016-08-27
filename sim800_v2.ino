//proyecto en pruba

#include <SoftwareSerial.h>

SoftwareSerial sim800l(10,11); //RX - TX  
bool res_at(char *buf,char *patern){ 
  char *ptr;

   ptr = strstr(buf, patern);
   if (ptr !=0){
   return true;
   }else{
   return false;
   }
}

char *debug()
{
int i=0;
char cad[255]="\0";
char c='\0';
        
        strcpy(cad,"");
        while(sim800l.available()>0)
        {
        c=sim800l.read();
        cad[i]=c;
        i++;
        }
      
return cad;
}


void env_sms()
{
 sim800l.println(F("AT+CMGF=1"));
 delay(500);
if (res_at(debug(),"OK")){
 sim800l.println(F("AT+CMGS=\"+542996321848\""));//
delay(500); 
  if(res_at(debug(),">")){
    sim800l.println(F("ardu rack"));
    delay(500);
    sim800l.println();
    delay(500);
    sim800l.write(0x1A);
    delay(500);
    }
  }
}

void hac_llam(){
 sim800l.println(F("ATD+542996321848;"));
 delay(500);
Serial.println(debug());
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
sim800l.begin(9600);

Serial.println("sim800...........");

sim800l.println(F("AT"));
delay(500);
Serial.println(debug());
sim800l.println(F("AT+CBC"));
delay(500);
Serial.println(debug());

sim800l.println(F("AT+CSQ"));
delay(500);

//env_sms();
hac_llam();

}

void loop() {
  // put your main code here, to run repeatedly:

}
