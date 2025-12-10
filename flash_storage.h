#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#include <stdbool.h>
#include <stdint.h>

#ifndef PWM_TOP_VALUE
#define PWM_TOP_VALUE 255
#endif

bool flash_storage_save_color(uint32_t hue, uint32_t saturation, uint32_t brightness);

bool flash_storage_load_color(uint32_t *hue, uint32_t *saturation, uint32_t *brightness);

#endif