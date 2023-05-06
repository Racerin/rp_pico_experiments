#include <Arduino.h>

#define OPTION 6

#if OPTION == 0

#elif OPTION == 1
// #include <shift_register.h>

#elif OPTION == 2

int millis_duration = 200;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(millis_duration);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(millis_duration);                      // wait for a second
}

#elif OPTION == 3

#include <Servo.h>
Servo myservo;
const int SERVO_PIN = 14;
const int SERVO_STEP_ANGLE = 180;
const long SERVO_DURATION = 5*1000/SERVO_STEP_ANGLE;

void setup(){
  // Servo setup
  myservo.attach(SERVO_PIN);

}

void loop() {
  for (int i=0; i<SERVO_STEP_ANGLE; i++){
    myservo.write(i);
    delay(SERVO_DURATION);
  };
};

#elif OPTION == 4

#include "RP2040_PWM.h"

RP2040_PWM* pwm_instance;

const int pin_out = 14;

const int delay_time = 1000;
const float freq = 1000;
float duty_cycle;

void setup(){
  // Assign pin 14 for servo control (1kHz, 1.5ms=0.15 duty cycle)
  pwm_instance = new RP2040_PWM(pin_out, 1000, 1);
}

void loop(){
  for(int i=1; i<8; i++){
    duty_cycle = i * 10;

    pwm_instance->setPWM(pin_out, freq, duty_cycle);

    delay(delay_time);
  }
}

#elif OPTION == 5

const int pin_out = 14;

const int observe_delay = 1000;  // ms
long observe_start;  // ms
long observe_end;  // ms

const int freq = 1000;  // Hz
const long cycle_period = 1e6/freq;  // micro seconds

int _duty_cycle;
int duty_cycle;  // 0 to 100
long duty_duration;  // micro seconds
long remaining_duty_duration; // micro seconds

void set_duty_cycle(int val){
    duty_cycle = _duty_cycle > 100 ? 100 : _duty_cycle;
    duty_cycle = duty_cycle < 0 ? 0 : duty_cycle;
}

void setup(){
  pinMode(pin_out, OUTPUT);
}

void loop(){
  for (int i=1; i<10; i++){
    set_duty_cycle(10 * i);
    // Calculate the duty cycle properties for each phase
    duty_duration = (duty_cycle/100) * cycle_period;
    remaining_duty_duration = cycle_period - duty_duration;

    // Turn ON and OFF according to duty cycle for observation period
    observe_start = millis();
    observe_end = observe_start + observe_delay;
    while(millis() < observe_end){
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      digitalWrite(pin_out, HIGH);
      delayMicroseconds(duty_duration);
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      digitalWrite(pin_out, LOW);
      delayMicroseconds(remaining_duty_duration);
    }
    digitalWrite(pin_out, LOW);

  };
}

#elif OPTION == 6

int pin_out = 14;

void setup(){
  pinMode(pin_out, OUTPUT);
}

void loop(){
  for (int i=0; i<1000; i++){
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin_out, HIGH);
  delayMicroseconds(500);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin_out, LOW);
  delayMicroseconds(500);
  }

  
  for (int i=0; i<1000; i++){
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin_out, HIGH);
  delayMicroseconds(200);
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin_out, LOW);
  delayMicroseconds(800);
  }
}

#endif



