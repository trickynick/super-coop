//TMP36 Pin Variables
int tempPin = A0; //temp sensor
int timePin = A2; //pot pin to adjust time since
int lightPin = A1; //light sensor
int closePin = 2;  //close relay
int openPin = 4;   // open relay




void setup()
{
  pinMode(tempPin, INPUT);
  pinMode(timePin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(closePin, INPUT);
  pinMode(openPin, INPUT);
  Serial.begin(9600);
}

unsigned long motionTime; //Start the clock
unsigned long now;

// POSSIBLE STATES
enum STATE_T {
  STATE_OPEN,
  STATE_WAITING,
  STATE_CLOSED,
  STATE_HOTDOG,
  STATE_YUMM,
  STATE_YUCK
};


int state = STATE_OPEN; // which state do we start in???
int nextState; // don't initialize


void loop()
{
  // START STATE MACHINE
  // these are outside the state machine and always update

  // take new data
  float tempValue = analogRead(tempPin);
  float lightValue = analogRead(lightPin);
  now = millis();
  //  Serial.print(lightValue); Serial.println(" units of photo-sensor");
  int closePinValue = digitalRead(closePin);
  int openPinValue = digitalRead(openPin);



  nextState = state;
  switch (state)
  {
    case STATE_OPEN:
      Serial.println("OPEN");
      if (lightValue < 330) // higher is brighter
      {
        motionTime = now; // save "now" into cubbyhole
        nextState = STATE_WAITING;
      }
      break;
    case STATE_WAITING:
      Serial.println("WAITING");
      if ((now - motionTime) >= 2000)
      {
        nextState = STATE_CLOSED;
      }
      break;
    case STATE_CLOSED:
      Serial.println("CLOSED");
      if (lightValue > 400) // highet is brither
      {
        nextState = STATE_HOTDOG;
      }
      break;
    case STATE_HOTDOG:
      Serial.println("HOTDOG");
      if (closePinValue == HIGH)
      {
        nextState = STATE_YUMM;
        motionTime = now;
      }
      if (openPinValue == HIGH)
      {
        nextState = STATE_YUCK;
        motionTime = now;
      }
      if(openPinValue == HIGH && closePinValue == HIGH)
      {
        nextState = STATE_HOTDOG;
      }
      break;
    case STATE_YUMM:
      Serial.println("YUMM");
      if ((now - motionTime) >= 2000)
      {
        //motionTime = now;
        nextState = STATE_HOTDOG;
      }
      break;
    case STATE_YUCK:
      Serial.println("YUCK");
      if ((now - motionTime) >= 2000)
      {
        // motionTime = now;
        nextState = STATE_HOTDOG;
      }
      break;
    default:
      Serial.println("SOMETHING WRONG");
      break;
  }

  state = nextState;

  delay(500);

  // END STATE MACHINE






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


