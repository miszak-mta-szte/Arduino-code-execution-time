inline void clearAndStartTimer(void) __attribute__((always_inline));
inline void stopTimer(void) __attribute__((always_inline));

bool firstCycle = true;

void setup() {
  analogReference(DEFAULT);
  Serial.begin(57600);
}

void loop()
{
  stopTimer();
  if (firstCycle)
  {
    firstCycle = false;
  }
  else
  {
    Serial.print("'loop' overhead system clock ticks: ");
    Serial.print(getTimer());
    Serial.print(", execution time [us]: ");
    Serial.println(getTimer()/16.0);
    delay(1000);
  }
  clearAndStartTimer();
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

