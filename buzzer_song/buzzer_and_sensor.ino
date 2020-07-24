#define EHCO 3
#define TRIGGER 4
#define BUZZER_PIN 5

#define BUZZER_DELAY 1431 //부저 음 딜레이 - micro 기준

void setup()
{
  pinMode(EHCO, INPUT); //ehco
  pinMode(TRIGGER, OUTPUT); //trigger

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  attachInterrupt(1, myISR, CHANGE);
}

unsigned long c_millis = 0;
unsigned long p_millis_1 = 0;
unsigned long p_millis_2 = 0;
unsigned long c_micros = 0;
unsigned long p_micros = 0;

int isOnBuzzer = 0;
int delays = 1000;
int buzzer_toggle = 0;
unsigned int buzzer_count = 0;

double rising_time = 0;
double falling_time = 0;
int diff_time = 0;
double distance = 51; //시작하자마자 소리를 내지 않도록 소리가 나지 않는 최소점인 51로 설정

void loop()
{
  c_millis = millis();
  if (c_millis - p_millis_1 > 10)
  {
    p_millis_1 = c_millis;
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
  }
  if (distance <= 50)
  {
    if (c_millis - p_millis_2 > delays)
    {
      p_millis_2 = c_millis;
      isOnBuzzer = 1;
    }
  }

  if (isOnBuzzer == 1)
  {
    c_micros = micros();
    if (c_micros - p_micros > BUZZER_DELAY)
    {
      p_micros = c_micros;
      if (buzzer_toggle == 0) {
        buzzer_toggle = 1;
        digitalWrite(BUZZER_PIN, HIGH);
      }
      else {
        buzzer_toggle = 0;
        digitalWrite(BUZZER_PIN, LOW);
      }
      buzzer_count++;
      if (buzzer_count == 1000000 / BUZZER_DELAY / 20) {
        buzzer_count = 0;
        isOnBuzzer = 0;
      }
    }
  }

}

#define ECHO_RISING 1
#define ECHO_FALLING 0


void myISR()
{
  int in_data = digitalRead(EHCO);

  if (in_data == ECHO_RISING) {
    rising_time = micros();
  }
  else if (in_data == ECHO_FALLING) {
    falling_time = micros();

    diff_time = falling_time - rising_time;

    distance = 0.017 * (double)diff_time;

    Serial.println(distance);

    if (distance <= 10)delays = 0;
    else if (distance <= 20)delays = 100;
    else if (distance <= 30)delays = 500;
    else if (distance <= 50)delays = 1000;
  }
}
