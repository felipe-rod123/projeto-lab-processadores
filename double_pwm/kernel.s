.include "gpio.inc"

// este dever ser o endereço 0x8000
.text
.global start

start:
   // inicia stack pointer
   ldr sp, =stack_addr

   // configurar GPIO 21 como saída
   ldr r0, =GPFSEL2
   ldr r1, [r0]
   bic r1, r1, #(0b111 << 3)
   orr r1, r1, #(0b001 << 3)
   str r1, [r0]

   // configurar GPIO 26 como saída
   ldr r0, =GPFSEL2
   ldr r1, [r0]
   bic r1, r1, #(0b111 << 18)
   orr r1, r1, #(0b001 << 18)
   str r1, [r0]

   ldr r3, =#0000600 // tempo em low de pwm tem que ser par !!
   ldr r6, =#0000221 // tempo em low de pwm // !! tem que ser par !!
   ldr r8, =0x3F003010 // endereco do compare register 1
   ldr r7, =0x3F003018 // endereco do compare register 2

   ldr r9, =#0000000 // t da ultima borda de descida


   // inicia timer 1 
   ldr r0, =0x3F003000 
   ldr r1,[r0,#4]
   add r1,r1,r6
   mov r4, #(1 << 1)
   str r4, [r0, #0x00] // limpa flag

   // inicia timer 3 
   ldr r0, =0x3F003000 
   ldr r2,[r0,#4]
   add r2,r2,r3
   mov r4, #(1 << 3)
   str r4, [r0, #0x00] // limpa flag



escuta:


//    condicao: tempo == r1
   str r1, [r8] 
   ldr r0, =0x3F003000 
   ldr r4, [r0]
   tst r4, #(1 << 1) 
   beq nao_tempo_igual_a_r1
   tempo_igual_a_r1:
      bl faz_borda_pwm_e_atualiza_r1 
   nao_tempo_igual_a_r1:



 //condicao: tempo == r2
   str r2, [r7] 
   ldr r0, =0x3F003000 
   ldr r4, [r0]
   tst r4, #(1 << 3) 
   beq nao_tempo_igual_a_r2
   tempo_igual_a_r2:
      bl faz_borda_pwm_e_atualiza_r2
   nao_tempo_igual_a_r2:

b escuta


faz_borda_pwm_e_atualiza_r1:
   push {lr}
   ldr r5, =#0001001 // tempo total de pwm   // !!tem que ser impar!!
   ldr r0, =0x3F003000 
   ldr r1,[r0,#4]
   sub r6, r5, r6
   add r1,r1,r6

   mov r4, #(1 << 1)
   str r4, [r0, #0x00] // limpa flag
   
   tst r6, #1
   beq faz_borda_pwm_e_atualiza_r1_apagar
   bl acende_21
   b faz_borda_pwm_e_atualiza_r1_fim
   faz_borda_pwm_e_atualiza_r1_apagar:
      bl apaga_21
   b faz_borda_pwm_e_atualiza_r1_fim
   faz_borda_pwm_e_atualiza_r1_fim: 
      pop {lr}
      bx lr



faz_borda_pwm_e_atualiza_r2:
   push {lr}
   ldr r5, =#0001001 // tempo total de pwm   // !!tem que ser impar!!
   ldr r0, =0x3F003000 
   ldr r2,[r0,#4]
   sub r3, r5, r3
   add r2,r2,r3

   mov r4, #(1 << 3)
   str r4, [r0, #0x00] // limpa flag
   
   tst r3, #1
   beq faz_borda_pwm_e_atualiza_r2_apagar
   bl acende_26
   b faz_borda_pwm_e_atualiza_r2_fim
   faz_borda_pwm_e_atualiza_r2_apagar:
      bl apaga_26
   b faz_borda_pwm_e_atualiza_r2_fim
   faz_borda_pwm_e_atualiza_r2_fim: 
      pop {lr}
      bx lr

apaga_21:
   push {r0, r1, lr}
   ldr r0, =GPCLR0
   mov r1, #(1 << 21)
   str r1, [r0]
   pop {r0, r1, lr}
   bx lr

acende_21:
   push {r0, r1, lr}
   ldr r0, =GPSET0
   mov r1, #(1 << 21)
   str r1, [r0]
   pop {r0, r1, lr}
   bx lr

apaga_26:
   push {r0, r1, lr}
   ldr r0, =GPCLR0
   mov r1, #(1 << 26)
   str r1, [r0]
   pop {r0, r1, lr}
   bx lr

acende_26:
   push {r0, r1, lr}
   ldr r0, =GPSET0
   mov r1, #(1 << 26)
   str r1, [r0]
   pop {r0, r1, lr}
   bx lr

