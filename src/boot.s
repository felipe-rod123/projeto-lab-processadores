.text
.global start
start:
   /*
    * Inicia pilha
    */
   mov r0, #0xd3     // Modo SVC
   msr cpsr_c,r0
   ldr sp, =inicio_stack

   /*
    * Zera segmento BSS
    */
   ldr r0, =fim_bss
   ldr r1, =inicio_bss
   mov r2, #0
   
loop_bss:
   cmp r0, r1
   bge done_bss
   strb r2, [r0], #1
   b loop_bss

done_bss:
  /*
   * Executa a função main
   */
  b main
