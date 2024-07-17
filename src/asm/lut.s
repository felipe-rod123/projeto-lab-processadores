.global tabela_senos
.global tabela_cossenos

.data

tabela_senos:
  .word 0b00000000000000000000000000000000
  .word 0b00000110010001111101100101111100
  .word 0b00001100100010111101001101011110
  .word 0b00010010110010000001000001101111
  .word 0b00011000111110001011100000111100
  .word 0b00011111000110011111100101111011
  .word 0b00100101001010000000110001011110
  .word 0b00101011000111110011010011101011
  .word 0b00110000111110111100010101001101
  .word 0b00110110101110100010000000010100
  .word 0b00111100010101101011101001110000
  .word 0b01000001110011100001111001100101
  .word 0b01000111000111001110110011100111
  .word 0b01001100001111111101111111110100
  .word 0b01010001001100111100110010010100
  .word 0b01010101111101011010010011010010
  .word 0b01011010100000100111100110011010
  .word 0b01011110110101110111110010001010
  .word 0b01100010111100100000000110101100
  .word 0b01100110110011111000000100100000
  .word 0b01101010011011011001100010100100
  .word 0b01101101110010100000110100010100
  .word 0b01110000111000101100101111000110
  .word 0b01110011101101011110101111010001
  .word 0b01110110010000011010111100111101
  .word 0b01111000100001001000010000010100
  .word 0b01111010011111010000010101011011
  .word 0b01111100001010011111101111101110
  .word 0b01111101100010100101111101000000
  .word 0b01111110100111010101010111111100
  .word 0b01111111011000100011011010001111
  .word 0b01111111110110001000011110001110
  .word 0b01111111111111111111111111111111
  .word 0b01111111110110001000011110001110
  .word 0b01111111011000100011011010001111
  .word 0b01111110100111010101010111111100
  .word 0b01111101100010100101111101000000
  .word 0b01111100001010011111101111101110
  .word 0b01111010011111010000010101011011
  .word 0b01111000100001001000010000010100
  .word 0b01110110010000011010111100111101
  .word 0b01110011101101011110101111010001
  .word 0b01110000111000101100101111000110
  .word 0b01101101110010100000110100010100
  .word 0b01101010011011011001100010100100
  .word 0b01100110110011111000000100100000
  .word 0b01100010111100100000000110101100
  .word 0b01011110110101110111110010001010
  .word 0b01011010100000100111100110011010
  .word 0b01010101111101011010010011010010
  .word 0b01010001001100111100110010010100
  .word 0b01001100001111111101111111110100
  .word 0b01000111000111001110110011100111
  .word 0b01000001110011100001111001100101
  .word 0b00111100010101101011101001110000
  .word 0b00110110101110100010000000010100
  .word 0b00110000111110111100010101001101
  .word 0b00101011000111110011010011101011
  .word 0b00100101001010000000110001011110
  .word 0b00011111000110011111100101111011
  .word 0b00011000111110001011100000111100
  .word 0b00010010110010000001000001101111
  .word 0b00001100100010111101001101011110
  .word 0b00000110010001111101100101111100
  .word 0b00000000000000000000000000000000
  .word 0b10000110010001111101100101111100
  .word 0b10001100100010111101001101011110
  .word 0b10010010110010000001000001101111
  .word 0b10011000111110001011100000111100
  .word 0b10011111000110011111100101111011
  .word 0b10100101001010000000110001011110
  .word 0b10101011000111110011010011101011
  .word 0b10110000111110111100010101001101
  .word 0b10110110101110100010000000010100
  .word 0b10111100010101101011101001110000
  .word 0b11000001110011100001111001100101
  .word 0b11000111000111001110110011100111
  .word 0b11001100001111111101111111110100
  .word 0b11010001001100111100110010010100
  .word 0b11010101111101011010010011010010
  .word 0b11011010100000100111100110011010
  .word 0b11011110110101110111110010001010
  .word 0b11100010111100100000000110101100
  .word 0b11100110110011111000000100100000
  .word 0b11101010011011011001100010100100
  .word 0b11101101110010100000110100010100
  .word 0b11110000111000101100101111000110
  .word 0b11110011101101011110101111010001
  .word 0b11110110010000011010111100111101
  .word 0b11111000100001001000010000010100
  .word 0b11111010011111010000010101011011
  .word 0b11111100001010011111101111101110
  .word 0b11111101100010100101111101000000
  .word 0b11111110100111010101010111111100
  .word 0b11111111011000100011011010001111
  .word 0b11111111110110001000011110001110
  .word 0b11111111111111111111111111111111
  .word 0b11111111110110001000011110001110
  .word 0b11111111011000100011011010001111
  .word 0b11111110100111010101010111111100
  .word 0b11111101100010100101111101000000
  .word 0b11111100001010011111101111101110
  .word 0b11111010011111010000010101011011
  .word 0b11111000100001001000010000010100
  .word 0b11110110010000011010111100111101
  .word 0b11110011101101011110101111010001
  .word 0b11110000111000101100101111000110
  .word 0b11101101110010100000110100010100
  .word 0b11101010011011011001100010100100
  .word 0b11100110110011111000000100100000
  .word 0b11100010111100100000000110101100
  .word 0b11011110110101110111110010001010
  .word 0b11011010100000100111100110011010
  .word 0b11010101111101011010010011010010
  .word 0b11010001001100111100110010010100
  .word 0b11001100001111111101111111110100
  .word 0b11000111000111001110110011100111
  .word 0b11000001110011100001111001100101
  .word 0b10111100010101101011101001110000
  .word 0b10110110101110100010000000010100
  .word 0b10110000111110111100010101001101
  .word 0b10101011000111110011010011101011
  .word 0b10100101001010000000110001011110
  .word 0b10011111000110011111100101111011
  .word 0b10011000111110001011100000111100
  .word 0b10010010110010000001000001101111
  .word 0b10001100100010111101001101011110
  .word 0b10000110010001111101100101111100

tabela_cossenos:
  .word 0b01111111111111111111111111111111
  .word 0b01111111110110001000011110001110
  .word 0b01111111011000100011011010001111
  .word 0b01111110100111010101010111111100
  .word 0b01111101100010100101111101000000
  .word 0b01111100001010011111101111101110
  .word 0b01111010011111010000010101011011
  .word 0b01111000100001001000010000010100
  .word 0b01110110010000011010111100111101
  .word 0b01110011101101011110101111010001
  .word 0b01110000111000101100101111000110
  .word 0b01101101110010100000110100010100
  .word 0b01101010011011011001100010100100
  .word 0b01100110110011111000000100100000
  .word 0b01100010111100100000000110101100
  .word 0b01011110110101110111110010001010
  .word 0b01011010100000100111100110011010
  .word 0b01010101111101011010010011010010
  .word 0b01010001001100111100110010010100
  .word 0b01001100001111111101111111110100
  .word 0b01000111000111001110110011100111
  .word 0b01000001110011100001111001100101
  .word 0b00111100010101101011101001110000
  .word 0b00110110101110100010000000010100
  .word 0b00110000111110111100010101001101
  .word 0b00101011000111110011010011101011
  .word 0b00100101001010000000110001011110
  .word 0b00011111000110011111100101111011
  .word 0b00011000111110001011100000111100
  .word 0b00010010110010000001000001101111
  .word 0b00001100100010111101001101011110
  .word 0b00000110010001111101100101111100
  .word 0b00000000000000000000000000000000
  .word 0b10000110010001111101100101111100
  .word 0b10001100100010111101001101011110
  .word 0b10010010110010000001000001101111
  .word 0b10011000111110001011100000111100
  .word 0b10011111000110011111100101111011
  .word 0b10100101001010000000110001011110
  .word 0b10101011000111110011010011101011
  .word 0b10110000111110111100010101001101
  .word 0b10110110101110100010000000010100
  .word 0b10111100010101101011101001110000
  .word 0b11000001110011100001111001100101
  .word 0b11000111000111001110110011100111
  .word 0b11001100001111111101111111110100
  .word 0b11010001001100111100110010010100
  .word 0b11010101111101011010010011010010
  .word 0b11011010100000100111100110011010
  .word 0b11011110110101110111110010001010
  .word 0b11100010111100100000000110101100
  .word 0b11100110110011111000000100100000
  .word 0b11101010011011011001100010100100
  .word 0b11101101110010100000110100010100
  .word 0b11110000111000101100101111000110
  .word 0b11110011101101011110101111010001
  .word 0b11110110010000011010111100111101
  .word 0b11111000100001001000010000010100
  .word 0b11111010011111010000010101011011
  .word 0b11111100001010011111101111101110
  .word 0b11111101100010100101111101000000
  .word 0b11111110100111010101010111111100
  .word 0b11111111011000100011011010001111
  .word 0b11111111110110001000011110001110
  .word 0b01111111111111111111111111111111
  .word 0b01111111110110001000011110001110
  .word 0b01111111011000100011011010001111
  .word 0b01111110100111010101010111111100
  .word 0b01111101100010100101111101000000
  .word 0b01111100001010011111101111101110
  .word 0b01111010011111010000010101011011
  .word 0b01111000100001001000010000010100
  .word 0b01110110010000011010111100111101
  .word 0b01110011101101011110101111010001
  .word 0b01110000111000101100101111000110
  .word 0b01101101110010100000110100010100
  .word 0b01101010011011011001100010100100
  .word 0b01100110110011111000000100100000
  .word 0b01100010111100100000000110101100
  .word 0b01011110110101110111110010001010
  .word 0b01011010100000100111100110011010
  .word 0b01010101111101011010010011010010
  .word 0b01010001001100111100110010010100
  .word 0b01001100001111111101111111110100
  .word 0b01000111000111001110110011100111
  .word 0b01000001110011100001111001100101
  .word 0b00111100010101101011101001110000
  .word 0b00110110101110100010000000010100
  .word 0b00110000111110111100010101001101
  .word 0b00101011000111110011010011101011
  .word 0b00100101001010000000110001011110
  .word 0b00011111000110011111100101111011
  .word 0b00011000111110001011100000111100
  .word 0b00010010110010000001000001101111
  .word 0b00001100100010111101001101011110
  .word 0b00000110010001111101100101111100
  .word 0b00000000000000000000000000000000
  .word 0b10000110010001111101100101111100
  .word 0b10001100100010111101001101011110
  .word 0b10010010110010000001000001101111
  .word 0b10011000111110001011100000111100
  .word 0b10011111000110011111100101111011
  .word 0b10100101001010000000110001011110
  .word 0b10101011000111110011010011101011
  .word 0b10110000111110111100010101001101
  .word 0b10110110101110100010000000010100
  .word 0b10111100010101101011101001110000
  .word 0b11000001110011100001111001100101
  .word 0b11000111000111001110110011100111
  .word 0b11001100001111111101111111110100
  .word 0b11010001001100111100110010010100
  .word 0b11010101111101011010010011010010
  .word 0b11011010100000100111100110011010
  .word 0b11011110110101110111110010001010
  .word 0b11100010111100100000000110101100
  .word 0b11100110110011111000000100100000
  .word 0b11101010011011011001100010100100
  .word 0b11101101110010100000110100010100
  .word 0b11110000111000101100101111000110
  .word 0b11110011101101011110101111010001
  .word 0b11110110010000011010111100111101
  .word 0b11111000100001001000010000010100
  .word 0b11111010011111010000010101011011
  .word 0b11111100001010011111101111101110
  .word 0b11111101100010100101111101000000
  .word 0b11111110100111010101010111111100
  .word 0b11111111011000100011011010001111
  .word 0b11111111110110001000011110001110
