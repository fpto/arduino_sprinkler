#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>




/*
# GPIO  pin
water_gpio = 26 # Led light #1
sprinkler_gpio = 19 # Lower sprinkler
l2 = 18 #led light #2
leds_list = [water_gpio, l2, sprinkler_gpio]

# Watering time
watering_time = 60
sprinkler_time = 180

Example of constant definition
#define ledPin 3
// The compiler will replace any mention of ledPin with the value 3 at compile time.

*/
#define watering_time 60000 // 1 minute
#define sprinkler_time 180000 // 3 minutes
#define ledblink 1000 // 1 second
#define ledpin 13 // native led
#define balcony 12
#define sprinkler 7
#define waiting_time 43200 // 24 hours in miliseconds = 86400000
tmElements_t tm;

void setup() {
  // Set up Pins mode
  pinMode(ledpin, OUTPUT);
  pinMode(balcony, OUTPUT);
  pinMode(sprinkler, OUTPUT);
  // Alimentar relay board
  pinMode(2, OUTPUT);

    //Initiate Serial communication.
  Serial.begin(9600);
  // Ensure relay pins are off
  digitalWrite(balcony, HIGH);
  digitalWrite(sprinkler, HIGH);
  digitalWrite(2, HIGH);  // para alimentar relay board
  

}

void ledblinking(int number){
  Serial.println("Blink");
  digitalWrite(ledpin, HIGH);  
  delay(number);              
  digitalWrite(ledpin, LOW);
  delay(number);
  
}
void water_balcony(){
  Serial.println("Balcony starts being watered");
  digitalWrite(balcony, LOW);
  delay(watering_time);
  digitalWrite(balcony, HIGH);
  Serial.println("Balcony stops being watered");
  }
void sprinkling(){
  Serial.println("Sprinkle starts");
  digitalWrite(sprinkler, LOW);
  delay(sprinkler_time);
  digitalWrite(sprinkler, HIGH);
  Serial.println("Sprinkle ends");
} 

void time_printing(){
 

  if (RTC.read(tm)) {
    Serial.print("Ok, la hora es = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Fecha (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    if (tm.Minute == 35){
      Serial.print("!!!! MINUTO 35!!!!!!");
    }
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS3231 has stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS3231 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(5000); // Checar hora cada 5 segundos
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void loop() {
  if (tm.Hour == 06 && tm.Minute == 30){ // TRIGGER TIME
      water_balcony();
      sprinkling();
   }
   ledblinking(ledblink);
  /*  
  //
  for (int i = 0; i < waiting_time; i++) {
    
  } 
    */
  time_printing();
}
