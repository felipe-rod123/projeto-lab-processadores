#include <stdint.h>
#include "bcm.h"

#define GPFSEL4  ((volatile unsigned int*)0x3F200010)
#define GPSET1   ((volatile unsigned int*)0x3F200020)
#define GPCLR1   ((volatile unsigned int*)0x3F20002C)

// Frequência de 50Hz, período de 20ms
#define PWM_PERIOD_US 20000


void configure_gpio47_output(void) {
    // Configura GPIO 47 como saída
    *GPFSEL4 &= ~(0b111 << 21);  // Limpa os bits relevantes (21-23)
    *GPFSEL4 |=  (0b001 << 21);  // Define GPIO 47 como saída (001)
}

// Função de delay em microssegundos   
void delay_us(unsigned int delay) {
    volatile unsigned int count;
    while (delay--) {
        count = 7;  // Ajustar para o valor correto no seu sistema
        while (count--) {
            asm volatile("nop");
        }
    }
}

/*
   Envia um pulso PWM com uma largura especificada em microssegundos. O SG-90 usa pulsos de 500 a 2400 microsegundos para se mover de 0 a 180 graus.
*/
void pwm_pulse(int pulse_width_us) {
    // Envia um pulso PWM de largura definida
    *GPSET1 = (1 << 15);   // Seta GPIO 47 (bit 15 de GPSET1)
    delay_us(pulse_width_us);
    *GPCLR1 = (1 << 15);   // Limpa GPIO 47 (bit 15 de GPCLR1)
    delay_us(PWM_PERIOD_US - pulse_width_us);
}


void set_servo_position(int position) {
    int pulse_width_us;

    // Mapear posição (0-180 graus) para largura de pulso (500-2400us)
    pulse_width_us = 500 + (position * 1900) / 180;

    for (int i = 0; i < 50; i++) {  // Envia 50 pulsos (~1 segundo)
        pwm_pulse(pulse_width_us);
    }
}


void rotate_forward(int current_position, int target_position) {
    for (int pos = current_position; pos <= target_position; pos++) {
        set_servo_position(pos);
    }
}

void rotate_backward(int current_position, int target_position) {
    for (int pos = current_position; pos >= target_position; pos--) {
        set_servo_position(pos);
    }
}




int main(void) {
    configure_gpio47_output();

    // Exemplo de uso:
    set_servo_position(90);  // Posiciona o servo a 90 graus
    delay_us(1000000);        // Aguardar 1 segundo

    rotate_forward(90, 180);  // Gira para 180 graus
    delay_us(1000000);        // Aguardar 1 segundo

    rotate_backward(180, 0);  // Gira para 0 graus
    delay_us(1000000);        // Aguardar 1 segundo

    return 0;
}