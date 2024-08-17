.include "gpio.inc"
.section .init
.global start
start:

  /*
   * Verifica priviégio de execução EL2 (HYP) ou EL1 (SVC)
   */
  mrs r0, cpsr
  and r0, r0, #0x1f
  cmp r0, #0x1a
  bne continua

  /*
   * Sai do modo EL2 (HYP)
   */
  mrs r0, cpsr
  bic r0, r0, #0x1f
  orr r0, r0, #0x13
  msr spsr_cxsf, r0
  add lr, pc, #4       // aponta o rótulo 'continua'
  msr ELR_hyp, lr
  eret                 // 'retorna' do privilégio EL2 para o EL1

continua:
  /*
   * Verifica o índice das CPUs
   */
  mrc p15,0,r0,c0,c0,5    // registrador MPIDR
  ands r0, r0, #0xff
  beq core0

// Núcleos #1, #2 e #3 vão executar a partir daqui

trava:
  wfe
  b trava

// Execução do núcleo #0
core0:
  /*
   * configura os stack pointers
   */
  mov r0, #0xD2     // Modo IRQ
  msr cpsr_c,r0
  mov sp, #0x4000

  mov r0, #0xD3     // Modo SVC
  msr cpsr_c,r0
  mov sp, #0x8000

  // Continua executando no modo supervisor (SVC), interrupções desabilitadas

  /*
   * Executa o sistema
   */
  b main_codigo

/*
 * Suspende o processamento por um número de ciclos
 * param r0 Número de ciclos.
 */
 .text
.globl delay
delay:
  subs r0, r0, #1
  bne delay
  mov pc, lr

/*
 * Habilita ou desabilita interrupções
 * param r0 0 = desabilita, diferente de zero = habilita
 */
.globl enable_irq
enable_irq:
  movs r0, r0
  beq disable
  mrs r0, cpsr
  bic r0, r0, #0x80
  msr cpsr_c, r0
  mov pc, lr
disable:
  mrs r0, cpsr
  orr r0, r0, #0x80
  msr cpsr_c, r0
  mov pc, lr

/*
 * Lê o valor atual do CPSR
 */
.globl get_cpsr
get_cpsr:
  mrs r0, cpsr
  mov pc, lr


main_codigo:

   bl uart_init 
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

   // configurar GPIO 20 como entrada
   ldr r0, =GPFSEL2
   ldr r1, [r0]
   bic r1, r1, #(0b111 << 0)
   str r1, [r0]


   ldr r3, =#0000011 // tempo em low de pwm tem que ser par !! // em cima do gnd 
   ldr r6, =#1000011 // tempo em low de pwm // !! tem que ser par !!  
   ldr r8, =0x3F003010 // endereco do compare register 1
   ldr r7, =0x3F003018 // endereco do compare register 2

   ldr r9, =#0000000 // t da ultima borda de descida

   //bl faz_borda_pwm_e_atualiza_r1

   // r1: hora de subir o sinal de pwm | hora de descer o sinal de pwm
   // r2: hora de ativar timer | 

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
//bl printa_oi

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

   cmp r9, #0
   bne nao_ativou_20 // (nao ativou agora) ja ativou antes
   
   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   beq nao_ativou_20
   bl delay_igor

   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   beq nao_ativou_20
   bl delay_igor

   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   beq nao_ativou_20
   bl delay_igor

   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   beq nao_ativou_20
   bl delay_igor

   ativou_20: 

     push {r0-r11, lr}
     mov r0, #10
     bl printa_oi
     pop {r0-r11, lr}
      ldr r0, =0x3F003000
      ldr r9,[r0,#4] // r9 = t
      ands r0, r6, #1
      bne tem_1_
   
      tem_0_:
         //LSR r9, r9, #1
         //LSL r9, r9, #1         
         //add r6, r9, #0
         //ldr r6, =#2500000
         //bl apaga_21 
         
         b nao_ativou_20
      tem_1_:
         //LSR r9, r9, #1
         //LSL r9, r9, #1
         //add r6, r9, #1
         //ldr r6, =#0500001
         //bl apaga_21 
         
   nao_ativou_20:



   cmp r9, #0
   beq nao_desativou_20 // nao ativou ainda, nao tem como desativar  


   // condicao:  pino desativou  
   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   bne nao_desativou_20
   bl delay_igor


   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   bne nao_desativou_20
   bl delay_igor


   ldr r0, =GPLEV0
   mov r4, #(1 << 20)
   ldr r4, [r0]
   ands r4, r4, #(1 << 20)
   CMP r4, #0 
   bne nao_desativou_20


   desativou_20: 

     push {r0-r11, lr}
     mov r0, #10
     bl printa_oi
     pop {r0-r11, lr}
      
      ldr r0, =0x3F003000 
      ldr r4,[r0,#4] // R4 = T 

      sub r9, r4, r9 // R9 = dT

      cmp r9 , #0000000
      blt nao_desativou_20
     
     push {r0-r11, lr}
     mov r0, r9
     bl printa_1_o_por_ms
     pop {r0-r11, lr}

      ldr r0, =#3000001
      LSR r9, r9, #1
      LSL r9, r9, #1 
      cmp r0, r9
      bpl sem_bo
      com_bo: 
         ldr r9 ,=#2999990
      sem_bo:

      push {r0}
      ldr r0, =0x3F003000 
      ldr r4,[r0,#4] // R4 = T
      pop {r0}
      
      sub r4, r0, r9
      ands r0, r6, #1
      bne tem_1
   
      tem_0:     
         add r6, r9, #0
         
         //ldr r6, =#0500000 
         //bl acende_21
         ldr r9, =#0000000 
         
         b nao_desativou_20
      tem_1:
         add r6, r4, #0
         //ldr r6, =#2500001 
         //bl acende_21
         ldr r9, =#0000000    
   nao_desativou_20: 
b escuta


faz_borda_pwm_e_atualiza_r1:
   push {lr}
   ldr r5, =#3000001 // tempo total de pwm   // !!tem que ser impar!!
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
   //ldr r5, =#2000001 // tempo total de pwm   // !!tem que ser impar!!
   ldr r5, =#500001 // tempo total de pwm   // !!tem que ser impar!!
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

//   push {r0-r11, lr}
//   mov r0, #10
//   bl printa_oi
//   pop {r0-r11, lr}
   
   
   ldr r0, =GPSET0
   mov r1, #(1 << 26)
   str r1, [r0]
   pop {r0, r1, lr}
   bx lr



// creditos Igor
delay_igor:
    push {r0, lr}     @ preserva r0 e lr
    mov r0, #100       @ define o valor do delay
delay_loop:
    subs r0, r0, #1   @ decrementa r0
    bne delay_loop    @ se não zero, continua no loop
    pop {r0, lr}      @ restaura r0 e lr
    bx lr
