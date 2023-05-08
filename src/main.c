#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUILTIN_LED 0
#define HELLO_WORLD 0
#define PWM_SERVO_EX 1


#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
// const uint led_pin = 25;
#else
const uint led_pin = PICO_DEFAULT_LED_PIN;
#endif

const uint servo_pin = 14;


int main() {
    // SETUP
    #if BUILTIN_LED == 1
    // LED setup
    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    // Initialize chosen serial port
    stdio_init_all();
    #endif

    #if PWM_SERVO_EX == 1
    // https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#pwm_example
    gpio_set_function(servo_pin, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(servo_pin);
    // ChatGPT FTW
    pwm_set_clock_divider(slice_num, 125); // 125 MHz / 125 = 1 MHz (1 us resolution)
    pwm_set_wrap(slice_num, 2000); // 1 MHz / 2000 = 500 Hz (2 ms period)
    pwm_set_chan_level(slice_num, 0, 120); // 2000 / 100 * 3 = 60 (3% duty cycle)   //WTF?

    // Enable PWM on the slice
    pwm_set_enabled(slice_num, true);

    uint i_pwm_counter = 0;
    uint pwm_duty; // 0 to 100
    uint pwm_chan;
    char pwm_str_template[] = "PWM duty cycle %3.0f.";
    char pwm_output_str[100];
    #endif

    #if PWM_SERVO_EX == 2
    gpio_init(servo_pin);
    gpio_set_dir(servo_pin, GPIO_OUT);
    uint i_pwm_counter;
    uint duty;
    uint duty_time;
    char pwm_str_template[] = "PWM duty cycle %3.0f.";
    char pwm_output_str[100];
    #endif

    // LOOP
    while (true){
        
        #if HELLO_WORLD == 1
        // Print to monitor?
        setup_default_uart();
        printf("Hello, world!\n");
        return 0;
        sleep_ms(10e3);
        #endif
    
        // Prevent print spam
        #if BUILTIN_LED == 1
        for (int i=0; i < 10; i++)
        {
            // Blink LED
            printf("Blinking!\r\n");
            gpio_put(led_pin, true);
            sleep_ms(1000);
            gpio_put(led_pin, false);
            sleep_ms(1000);
        }
        #endif

        #if PWM_SERVO_EX == 1
        i_pwm_counter ++;
        i_pwm_counter %= 9;
        pwm_duty = i_pwm_counter * 10;
        pwm_chan = pwm_duty * 20; // pwm_chan is according to 'pwm_set_chan' (20 per 1% duty cycle)
        pwm_set_chan_level(slice_num, 0, pwm_chan * 2);
        sleep_ms(1e3);
        // sprintf(pwm_output_str, pwm_str_template, pwm_duty);
        // printf(pwm_output_str);
        // printf(pwm_str_template);
        printf("PWM duty cycle: " + str())
        #endif

        #if PWM_SERVO_EX == 2
        i_pwm_counter ++;
        i_pwm_counter %= 9;
        duty = i_pwm_counter * 10;
        duty_time = 10 * duty;
        for(int i; i<1e3; i++)  // PWM at one position for 1ms * 1000 = 1s
        {
            gpio_put(servo_pin, true);
            sleep_us(duty_time);
            gpio_put(servo_pin, false);
            sleep_us(1000-duty_time);
        }
        sprintf(pwm_output_str, pwm_str_template, duty);
        printf(pwm_output_str);
        #endif
    }
}