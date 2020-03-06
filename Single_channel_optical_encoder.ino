// Single Channel Optical Encoder with DC motor
   
#define encoder 2
volatile int count = 0;

void setup() {
  Serial.begin(38400);
  pinMode(encoder, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder), pulse, RISING);
}

void loop() {
  //Serial.println(digitalRead(encoder));    //uncomment to see squarewave output
  Serial.println(count);
}

void pulse(){  
  count += 1 ;
}
