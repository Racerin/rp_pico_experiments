#include <stdio.h>
#include "pico/stdlib.h"

#define BUILTIN_LED 1
#define HELLO_WORLD 0


int main() {

    #if BUILTIN_LED == 1
    // LED setup
    const uint led_pin = 25;
    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    // Initialize chosen serial port
    stdio_init_all();
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
    }
}