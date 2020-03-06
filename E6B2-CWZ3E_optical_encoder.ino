/* YUMO E6B2-CWZ3E OPTICAL ENCODER 
 * 
 * Outputs A & B: quadrature encoder
 * Output Z: homing reference point
 * 
 * Both outputs A and B have 1024 (2^10) rising edge pulses per revolution
 * Change the variable 'pulsesPerRev' to reflect the specifications of your encoder
 * Reference output Z has 1 rising edge pulse per revolution
 * 
 * Wiring:
 * Brown -> 5V
 * Blue -> GND
 * Exposed -> GND
 * Black -> D2 (OUTPUT A)
 * White -> D3 (OUTPUT B)
 * Orange -> D4 (OUTPUT Z)
 * 
 * Libraries used in this program
 * https://github.com/GreyGnome/EnableInterrupt
 * https://github.com/NicksonYap/digitalWriteFast
 */
 
#include <EnableInterrupt.h>          //insufficient number of standard Interrupt pins on the Arduino Uno
#include <digitalWriteFast.h>         

#define encoderA 2
#define encoderB 3
#define encoderZ 4

volatile int countA = 0;
volatile int countB = 0;
volatile int cumulativeCountA = 0;
volatile int cumulativeCountB = 0;
int pulsesPerRev = 1024;     //This variable will is unique to the type of encoder
int Dir = 0;  // 1 = CW
              // 0 = Stationary
              // -1 = CCW

void setup() {
  Serial.begin(9600);
  pinMode(encoderA, INPUT);
  pinModeFast(encoderB, INPUT);
  pinMode(encoderZ, INPUT);  
  enableInterrupt(encoderA, pulseA, RISING);
  enableInterrupt(encoderB, pulseB, RISING);
  enableInterrupt(encoderZ, pulseZ, RISING);
}

void loop() {
  //Serial.print(countA);
  Serial.print('\t');
  //Serial.print(countB);
  Serial.print('\t');
  //Serial.print(cumulativeCountA);
  Serial.print('\t');
  //Serial.print(cumulativeCountB);
  Serial.print('\t');
  Serial.println(Dir);  
}

void checkDirection(){
  if((bool) digitalReadFast(encoderB) ==  HIGH){                             //digitalReadFast() is faster than digitalRead()
    Dir = 1;  
  }
  else{
    Dir = -1;
  }
}

void pulseA(){  
  checkDirection();
  countA += Dir;
  cumulativeCountA += Dir;
}

void pulseB(){  
  countB += Dir;
  cumulativeCountB += Dir;  
}

void pulseZ(){
  countA = 0;   //reset counters at "home" reference point
  countB = 0;
}
