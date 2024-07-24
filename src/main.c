#include "uart.h"
#include "rpi-i2c.h"
#include "defines.h"

#include <stdio.h>
#define SENSOR_ENDERECO 0x29>>1

void main(void) {

    i2c_init();
    while(1){
    enable_int_TX(); 
    int valores[] = {1,2,3};
    write_bytes(SENSOR_ENDERECO, valores, 3);
           } 
}
