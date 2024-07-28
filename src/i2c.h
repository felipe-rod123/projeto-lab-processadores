#ifndef __I2C_H__
#define __I2C_H__
#include <stdbool.h>
#include <stdint.h>
#define IDENTIFICATION_MODEL_ID 0xC0
#define PERIPH_BASE 0x3f000000
#define SENSOR_ADRESS 0x29

void i2c_init(void);
bool i2c_write(uint8_t addr, uint8_t *ptr, unsigned size);
bool i2c_read(uint8_t addr, uint8_t *ptr, unsigned size);
bool smbus_write_byte(uint8_t addr, uint8_t reg, uint8_t val);
bool smbus_write_word(uint8_t addr, uint8_t reg, uint16_t val);
int smbus_read_byte(uint8_t addr, uint8_t reg);
int smbus_read_word(uint8_t addr, uint8_t reg);

#endif

