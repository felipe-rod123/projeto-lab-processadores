# Projeto do Laboratório de Processadores

## Descrição do Projeto

Este projeto consiste na criação de um controlador utilizando um Raspberry Pi 3 e programação bare metal para controlar um servomotor PWM, que por sua vez está ligado a um sensor ultrassônico. O objetivo do sistema é manter o equilíbrio de uma bolinha posicionada em um braço, formando um sistema de equilíbrio de um único eixo.

## Componentes Utilizados

- Raspberry Pi 3
- Servomotor PWM
- Sensor Ultrassônico
- Braço mecânico para sustentar a bolinha

## Funcionamento do Sistema

O sistema funciona da seguinte maneira:

1. O sensor ultrassônico mede a distância entre a bolinha e o sensor.
2. Com base na distância medida, o Raspberry Pi 3 calcula a velocidade necessária para manter o equilíbrio da bolinha.
3. O Raspberry Pi 3 envia o sinal de controle para o servomotor PWM, ajustando a posição do braço para manter a bolinha equilibrada.
4. O processo se repete continuamente, garantindo o equilíbrio da bolinha em tempo real.

## Instruções de Instalação

Para reproduzir este projeto, siga as instruções abaixo:

1. Conecte o sensor ultrassônico e o servomotor PWM ao Raspberry Pi 3, seguindo as especificações do fabricante.
2. Clone o repositório do projeto em seu Raspberry Pi 3.
3. Compile e execute o código bare metal fornecido na pasta MAIN_controlador_regulado_configuravel repositório.
4. Ajuste as configurações do sistema, se necessário, para otimizar o equilíbrio da bolinha.
5. Teste o sistema, verificando se a bolinha se mantém equilibrada no braço.

## Integrantes
- Angela Colas
- Felipe Rodrigues
- Ian Ribeiro
