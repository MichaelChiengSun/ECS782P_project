#include <dht11.h>
#include <LiquidCrystal_I2C.h>
#define DHT11PIN 7
dht11 DHT11;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  //PIR
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  // Temperature DHT11
  Serial.begin(9600);

  lcd.backlight();// turn on lcd backlight
  lcd.init();// initialize lcd
}


void loop(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    display_temp();            // Display temp on screen
    if ((float(DHT11.temperature)<23.00) || (float(DHT11.humidity)<50.00)) {
      digitalWrite(led, HIGH);   // turn LED ON (On/Off switch for heater)
      delay(500);                // delay 500 milliseconds 
    }
    else {
      digitalWrite(led, LOW);
      delay(500);
    }
  if (state == LOW) {
    Serial.println("Motion detected!"); 
    state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
    lcd.clear();
    digitalWrite(led, LOW); // turn LED OFF
    delay(1000);             // delay 500 milliseconds 
    if (state == HIGH){
      Serial.println("Motion stopped!");
      state = LOW;       // update variable state to LOW
    }
  }
}

void display_temp() {
  //LCD display temperature
  int cha = DHT11.read(DHT11PIN);
  float temp = DHT11.temperature;
  float humid = DHT11.humidity;

  lcd.setCursor(0,0);// set the cursor on the first row and column
  lcd.print("Humidity=");
  lcd.print(humid);//print the humidity
  lcd.print("%");
  lcd.setCursor(0,1);//set the cursor on the second row and first column
  lcd.print("Temperature=");
  lcd.print(temp);//print the temperature
  lcd.print("C");
}
