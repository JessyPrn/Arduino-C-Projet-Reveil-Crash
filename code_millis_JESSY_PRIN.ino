#include <LiquidCrystal.h>
#include "math.h" =

int z_in = A2;
double AcZ = 0;
double gacz=0.0;
int toggle=0;
const int buzzer = 3; //buzzer to arduino pin 3

void Affichage();

unsigned long time;
unsigned long nextTime;
int heures,minutes,secondes,disec;
char message[16] = "";


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
lcd.begin(16, 2);
lcd.print("Reveil Crash");
delay(2000);
lcd.clear();
time = millis();
nextTime = time +100;

heures = 7;
minutes = 59;
secondes = 50;
disec = 0;
}

void loop(){
// Tout les 100 millis aller dans la routine
AcZ = analogRead(z_in);

gacz= ((0.00488759*(AcZ)-1.65)/0.8)*9.8;

if((gacz<=-15.0))
{
  toggle=!toggle;
  delay(300);
}
if(toggle>0)
{
  digitalWrite(buzzer, LOW);
}
if (millis() > nextTime) {
   nextTime += 100;
   Affichage();
   }

if (heures==8 & minutes==0)
  tone(buzzer, 1000);
}

void Affichage()
{
disec++;

if(disec == 10){
  disec = 0;
  secondes++;
  }
if(secondes == 60)
  {
  secondes = 0;
  minutes++;
  }
if(minutes == 60)
  {
  minutes = 0;
  heures++;
  }
if (heures == 24)
  {
  heures = 0;
  }


sprintf(message,"%d,%d,%d,%d",heures,minutes,secondes,disec);

lcd.home();
lcd.write(message);
}
