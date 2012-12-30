
int reading = 0;

int ON = 1;
int OFF = 0;

long lastDebounceTime = 0;
int debounceDelay = 250; // m
int previousState = OFF;

int SECOND = 1000; // ms

int SWITCH_PIN = 2;
int GREEN_LED = 3;
int RED_LED_1 = 4;
int RED_LED_2 = 5;
int RED_LED_3 = 6;

void setup() {
  
  pinMode(SWITCH_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
  pinMode(RED_LED_3, OUTPUT);  
  
  killRedLeds();
  kill(GREEN_LED);
}

void loop () {
  reading = digitalRead(SWITCH_PIN);

  if( reading == HIGH ) {
    if( previousState == OFF ) { 
      if( enoughDebounce() ) {
        previousState = ON;
        performCountdown();
        lastDebounceTime = millis();
      }
    } else {
      if( enoughDebounce() ) {
        previousState = OFF;
        lightLed(RED_LED_2);
        engineOff();
        lastDebounceTime = millis();
      }
    }
  }
}

boolean enoughDebounce() {
  if( (millis() - lastDebounceTime) > debounceDelay ) {
    return true;
  } 
  return false;
}

void engineOff() {
  lightAllRedLeds();
  kill(GREEN_LED); 
}

void performCountdown() {
  killRedLeds();
  kill(GREEN_LED); 

  waitFor(SECOND);
  lightLed(RED_LED_1);
  waitFor(SECOND);
  lightLed(RED_LED_2);
  waitFor(SECOND);
  lightLed(RED_LED_3);
  waitFor(SECOND);
  lightLed(GREEN_LED);
  
  killRedLeds();
}

void kill(int ledId) {
  digitalWrite(ledId, LOW);
}

void lightLed(int ledId) {
  digitalWrite(ledId, HIGH);
}

void lightAllRedLeds() {
  lightLed(RED_LED_1);
  lightLed(RED_LED_2);
  lightLed(RED_LED_3);
}

void killRedLeds() {
  kill(RED_LED_1);
  kill(RED_LED_2);
  kill(RED_LED_3);
}

void waitFor(int amount) {
 delay(amount); 
}
