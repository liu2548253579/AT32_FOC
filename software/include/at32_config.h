#ifndef __AT32_CONFIG_H
#define __AT32_CONFIG_H

#include "Arduino.h"
#include "Wire.h"
#include "stdint.h"
#include "stm32f1xx_hal_rcc.h"


#define IOMUX_MAKE_VALUE(reg_offset, bit_addr ,bit_num, bit_val) \
        (uint32_t)(((reg_offset) << 24) | ((bit_addr) << 16) | ((bit_num) << 8) | (bit_val))
#define I2C1_GMUX_0011                   IOMUX_MAKE_VALUE(0x28, 4, 4, 0x03)  /*!< i2c1_scl(pf6), i2c1_sda(pf7) */
#define IOMUX_BASE                       (APB2PERIPH_BASE + 0x0000)

#define LED_PIN                          PB1
#define KEY_PIN                          PA0
#define BAT_PIN                          PB0

typedef enum {FALSE = 0, TRUE = !FALSE} confirm_state;



extern TwoWire Wire1;

extern void gpio_pin_remap_config(uint32_t gpio_remap, confirm_state new_state);
extern void at32_i2c_clock_config(void);
extern void at32_board_init(void);
extern float at32_battery_voltage_read(void);
extern uint8_t KEY_Read(void);
extern uint8_t KEY_Read_Debounce(void);

#endif /* AT32_CONFIG_H */

