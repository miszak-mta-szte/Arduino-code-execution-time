inline void clearAndStartTimer(void) __attribute__((always_inline));
inline void stopTimer(void) __attribute__((always_inline));

void setup() {
  analogReference(DEFAULT);
  Serial.begin(57600);
}

void loop()
{
  uint8_t i;

  clearAndStartTimer();
  __asm__("nop");
  stopTimer();
  Serial.print("'nop' instruction system clock ticks: ");
  Serial.print(getTimer());
  Serial.print(", execution time [us]: ");
  Serial.println(getTimer()/16.0);

  for(i=1; i<=3; i+=2)
  {
    clearAndStartTimer();
    delayMicroseconds(i);
    stopTimer();
    Serial.print("delayMicroseconds(");
    Serial.print(i);
    Serial.print(") system clock ticks: ");
    Serial.print(getTimer());
    Serial.print(", execution time [us]: ");
    Serial.println(getTimer()/16.0);
  }

  clearAndStartTimer();
  digitalRead(9);
  stopTimer();
  Serial.print("digitalRead system clock ticks: ");
  Serial.print(getTimer());
  Serial.print(", execution time [us]: ");
  Serial.println(getTimer()/16.0);

  clearAndStartTimer();
  analogRead(A0);
  stopTimer();
  Serial.print("analogRead system clock ticks: ");
  Serial.print(getTimer());
  Serial.print(", execution time [us]: ");
  Serial.println(getTimer()/16.0);

  Serial.println("-------------------------------");

  delay(1000);
}

inline void clearAndStartTimer(void)
{
  TCCR1A = 0;    // set timer1 mode: normal
  TCCR1B = 0;    // disable timer1 clock to be sure it is not running
  TCNT1  = 0;    // clear timer1 value
  TCCR1B = 1;    // start timer1 with input clock 16MHz
}

inline void stopTimer(void)
{
  TCCR1B = 0;    // stop timer1
}

uint16_t getTimer(void)
{
  return TCNT1 - 2; // remove overhead clocks
}

