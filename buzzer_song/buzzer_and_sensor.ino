#define EHCO 2
#define TRIGGER 3
#define BUZZER_PIN 4

#define DISTANCE 30 // 1초마다 소리 나는 기준 거리
#define BUZZER_DELAY 1911 //부저 음 딜레이 - micro 기준


void setup()
{
  pinMode(EHCO, INPUT); //ehco
  pinMode(TRIGGER, OUTPUT); //trigger

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  attachInterrupt(0, myISR, CHANGE);
}

unsigned long c_millis = 0;
unsigned long p_millis_1 = 0;
unsigned long p_millis_2 = 0;

int delays = 1000;

void loop()
{
  c_millis = millis();
  if (c_millis - p_millis_1 > 1000)
  {
    p_millis_1 = c_millis;
    digitalWrite(3, HIGH);
    delayMicroseconds(10);
    digitalWrite(3, LOW);
  }
  if (c_millis - p_millis_2 > delays)
  {
    p_millis_2 = c_millis;
    for (int i = 0; i < 1000000 / BUZZER_DELAY / 10; i++)
    {
      digitalWrite(4, HIGH);
      delayMicroseconds(BUZZER_DELAY);
      digitalWrite(4, LOW);
      delayMicroseconds(BUZZER_DELAY);
    }
  }
}

#define ECHO_RISING 1
#define ECHO_FALLING 0

double rising_time = 0;
double falling_time = 0;
int diff_time = 0;
double distance = 0;

void myISR()
{
  int in_data = digitalRead(2);

  if (in_data == ECHO_RISING) {
    //Serial.println("Up!!");

    rising_time = micros();
  }
  else if (in_data == ECHO_FALLING) {
    //Serial.println("Down...");

    falling_time = micros();

    diff_time = falling_time - rising_time;

    distance = 0.017 * (double)diff_time;

    Serial.println(distance);
    if (distance > DISTANCE)delays = 1000;
    else if(distance < 0)delays = 0;
    else delays = (int)((double)1000 * (distance / DISTANCE));
  }
}
