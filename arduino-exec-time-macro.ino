#define CLEAR_AND_START_TIMER { TCCR1A = 0; TCCR1B = 0; TCNT1 = 0; TCCR1B = 1; }
#define STOP_TIMER  { TCCR1B = 0; }
#define GET_TIMER   (TCNT1-2)

void setup() {
  analogReference(DEFAULT);
  Serial.begin(57600);
}

void loop()
{
  uint8_t i;

  CLEAR_AND_START_TIMER;
  __asm__("nop");
  STOP_TIMER;
  Serial.print("'nop' instruction system clock ticks: ");
  Serial.print(GET_TIMER);
  Serial.print(", execution time [us]: ");
  Serial.println(GET_TIMER/16.0);

  for(i=1; i<=3; i+=2)
  {
    CLEAR_AND_START_TIMER;
    delayMicroseconds(i);
    STOP_TIMER;
    Serial.print("delayMicroseconds(");
    Serial.print(i);
    Serial.print(") system clock ticks: ");
    Serial.print(GET_TIMER);
    Serial.print(", execution time [us]: ");
    Serial.println(GET_TIMER/16.0);
  }

  CLEAR_AND_START_TIMER;
  digitalRead(9);
  STOP_TIMER;
  Serial.print("digitalRead system clock ticks: ");
  Serial.print(GET_TIMER);
  Serial.print(", execution time [us]: ");
  Serial.println(GET_TIMER/16.0);

  CLEAR_AND_START_TIMER;
  analogRead(A0);
  STOP_TIMER;
  Serial.print("analogRead system clock ticks: ");
  Serial.print(GET_TIMER);
  Serial.print(", execution time [us]: ");
  Serial.println(GET_TIMER/16.0);

  Serial.println("-------------------------------");

  delay(1000);
}


