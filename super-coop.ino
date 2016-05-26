//TMP36 Pin Variables
int tempknobPin = A0; //temp control knob
int timeknobPin = A2; //time control knob
int lightPin = A1; //light sensor
int closePin = 2;  //close relay
int openPin = 4;   // open relay
int tempPin = A3;//temp sensor
int heatlampPin = 6; // heatlamp relay
int open1 = 0;

void setup()
{
  pinMode(tempknobPin, INPUT);
  pinMode(timeknobPin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(closePin, OUTPUT);
  pinMode(openPin, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(heatlampPin, OUTPUT);
  Serial.begin(9600);
}

unsigned long motionTime; //Start the clock
unsigned long now;

// POSSIBLE STATES
enum STATE_T {
  STATE_OPEN,
  STATE_WAITING,
  STATE_CLOSED,
  STATE_OPENING
};


int state = STATE_OPEN; // which state do we start in???
int nextState; // don't initialize


void loop()
{

  // START STATE MACHINE
  // these are outside the state machine and always update

  // take new data
  float tempreture = analogRead(tempPin);
  float brightness = analogRead(lightPin);
  int temprange = analogRead(tempknobPin);
  int knob = analogRead(timeknobPin);
  unsigned long rerangetime = map(knob, 13, 1020L, (long)(10) * 60, (long)(4) * 60 * 60);
  rerangetime = rerangetime * 1;// 1000 = real time
  now = millis();
  //  Serial.print(lightValue); Serial.println(" units of photo-sensor");
  Serial.print("\n\n\n__________\n");
  Serial.print("Time: ");
  Serial.print(rerangetime);
  Serial.print("\n");
  //  Serial.print("Temp: ");
  //  Serial.print(tempreture);
  //  Serial.print("\n");
  Serial.print("knob: ");
  Serial.print(knob);
  Serial.print("\n");


  nextState = state;
  switch (state)
  {
    case STATE_OPEN:
      Serial.println("OPEN");
      if (brightness < 330) // higher is brighter
      {
        motionTime = now; // save "now" into cubbyhole
        nextState = STATE_WAITING;
      }
      break;
    case STATE_WAITING:
      Serial.println("WAITING");
      if ((now - motionTime) >= rerangetime)
      {
        nextState = STATE_CLOSED;
      }
      break;
    case STATE_CLOSED:
      Serial.println("CLOSED");
      if (brightness > 330) // higher is brighter
      {
        motionTime = now; // save "now" into cubbyhole
        nextState = STATE_OPENING;
      }
      break;
    case STATE_OPENING:
      Serial.println("OPENING");
      Serial.print("do worak here\n");
      nextState = STATE_OPEN;
      break;

  }


  state = nextState;

  delay(500);

  // END STATE MACHINE
  if (analogRead(tempPin) <= temprange)
  {
    digitalWrite(heatlampPin, LOW);
  }
  else
  {
    digitalWrite(heatlampPin, HIGH);
  }




  //  int reading = analogRead(tempPin);
  //
  //
  //  float voltage = reading * 5.0;
  //  voltage /= 1024.0;
  //
  //
  //  Serial.print(voltage); Serial.println(" volts");
  //
  //  float temperatureC = (voltage - 0.5) * 100 ;
  //
  //  Serial.print(temperatureC); Serial.println(" degrees C");
  //
  //
  //  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  //  Serial.print(temperatureF); Serial.println(" degrees F");
  //  Serial.println(motionTime);
  //  delay(1000);


}


