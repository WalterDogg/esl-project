#include "flash_storage.h"
#include "nrfx_nvmc.h"
#include "pwm_control.h"
#include <string.h>

#define FLASH_STORAGE_ADDR 0x0007F000

typedef struct {
    uint32_t hue;
    uint32_t saturation;
    uint32_t brightness;
} color_data_t;

bool flash_storage_save_color(uint32_t hue, uint32_t saturation, uint32_t brightness) {
    color_data_t color_data;
    color_data.hue = hue;
    color_data.saturation = saturation;
    color_data.brightness = brightness;
    
    uint32_t first_word = *(uint32_t*)FLASH_STORAGE_ADDR;
    if (first_word != 0xFFFFFFFF) {
        nrfx_nvmc_page_erase(FLASH_STORAGE_ADDR);
    }
    
    while (!nrfx_nvmc_write_done_check());
    
    nrfx_nvmc_words_write(FLASH_STORAGE_ADDR, 
                         (const uint32_t*)&color_data, 
                         sizeof(color_data_t) / sizeof(uint32_t));
    
    while (!nrfx_nvmc_write_done_check());
    
    return true;
}

bool flash_storage_load_color(uint32_t *hue, uint32_t *saturation, uint32_t *brightness) {
    color_data_t *color_data = (color_data_t*)FLASH_STORAGE_ADDR;
    
    if (color_data->hue > 360 || 
        color_data->saturation > PWM_TOP_VALUE || 
        color_data->brightness > PWM_TOP_VALUE) {
        return false;
    }
    
    *hue = color_data->hue;
    *saturation = color_data->saturation;
    *brightness = color_data->brightness;
    
    return true;
}