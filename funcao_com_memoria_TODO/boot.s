
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

  mov r0, #0xD0     // Modo usuario
  msr cpsr_c,r0
  ldr sp, =inicio_stack

  // Continua executando no modo supervisor (SVC), interrupções desabilitadas
   /*
    * Zera segmento BSS
    */
   ldr r0, =bss_begin
   ldr r1, =bss_end
   mov r2, #0
   
loop_bss:
   cmp r0, r1
   bge done_bss
   strb r2, [r0], #1
   b loop_bss

done_bss:
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
  mov r0, #90 // le 90
  push {r1-r11, lr}  
  bl media_de_d
  pop {r1-r11, lr}
  mov r9 , r0 // valor esperado media_de_d(90) =  (0 + 0 +90)/3 = 30  
  //...0
  mov r0, #15000
  bl delay
  mov r0, r9
  bl uart_putc 

  mov r0, #60 // le 60
  push {r1-r11, lr}  
  bl media_de_d
  pop {r1-r11, lr}

  mov r9 , r0 // valor esperado media_de_d(90) =  (0 + 60 +90)/3 = 50

  mov r0, #15000
  bl delay
  mov r0, r9
  bl uart_putc

  mov r0, #75 // le 75
  push {r1-r11, lr}  
  bl media_de_d
  pop {r1-r11, lr}

  mov r9 , r0 // valor esperado media_de_d(90) =  (75 + 60 +90)/3 = 75

  mov r0, #15000
  bl delay
  mov r0, r9
  bl uart_putc

