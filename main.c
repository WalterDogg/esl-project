#include "led_control.h"
#include "pwm_control.h"
#include "button_handler.h"
#include "flash_storage.h"
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_clock.h"

void lfclk_request(void) {
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);
}

void blinky_on_button_click(void) {
    
}

void blinky_on_button_double_click(void) {
    set_current_mode();
}

void blinky_on_button_long_press(void) {
    update_duty_cycle_RGB();
}

void init_helper(void) {
    load_color_from_storage();
    
    button_pin_init();
    button_timers_init();
    button_event_init(blinky_on_button_click, 
                     blinky_on_button_double_click, 
                     blinky_on_button_long_press);

    pwm_timer_init();
    pwm_controller_init();

}

int main(void) {
    lfclk_request();
    init_helper();
    turn_off_all_leds();
    pwm_start_playback();
    pwm_timer_start();

    while (true) {
 
    }
}