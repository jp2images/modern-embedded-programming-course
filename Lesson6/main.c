#include <stdint.h>
#include "tm4c123gh6pm.h"

/*
GPIO_PORTF_DATA_R   XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX
LED_RED             0000 0000 0000 0000 0000 0000 0000 0010
------------------------------------------------------------
GPIO ... | LED_RED  XXXX XXXX XXXX XXXX XXXX XXXX XXXX XX1X // OR the 2 words together

GPIO_PORTF_DATA_R   XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX
~LED_RED            1111 1111 1111 1111 1111 1111 1111 1101
------------------------------------------------------------
GPIO ... & ~LED_RED XXXX XXXX XXXX XXXX XXXX XXXX XXXX XX0X // AND the 2 words together

 LED_BLU             0000 0000 0000 0000 0000 0000 0000 0100
~LED_BLU             1111 1111 1111 1111 1111 1111 1111 1011

 LED_GRN             0000 0000 0000 0000 0000 0000 0000 1000
~LED_GRN             1111 1111 1111 1111 1111 1111 1111 0111
*/

#define LED_OFF 0
#define LED_RED (1U << 1)
#define LED_BLU (1U << 2)
#define LED_GRN (1U << 3)

void delayLoop(int loopCount){
  int volatile counter = 0;
  while (counter < loopCount){
    ++counter;
  }
}

int main() {
  /*
  unsigned int a = 0x5A5A5A5A;
  unsigned int b = 0xDEADBEEF;
  unsigned int c;

  c = a | b;  // OR
  c = a & b;  // AND
  c = a ^ b;  // XOR
  c = ~b;     // NOT
  c = b >> 1; // Right Shift
  c = b << 3; // Left Shift

  int x = 1024;
  int y = -1024;
  int z;

  z = x >> 3;
  z = y << 3;
  */

  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  GPIO_PORTF_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  int loopCount = 1000000;

  while(1) {
    //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED;
    GPIO_PORTF_DATA_R = LED_RED; //To work this register must have R/W permission
    delayLoop(loopCount);

    GPIO_PORTF_DATA_R &= ~LED_RED; //Clear the bit (Turn OFF the LED)
    delayLoop(loopCount);

    GPIO_PORTF_DATA_R = LED_BLU;
    delayLoop(loopCount);

    GPIO_PORTF_DATA_R &= ~LED_BLU;
    delayLoop(loopCount);

    GPIO_PORTF_DATA_R = LED_GRN;
    delayLoop(loopCount);

    GPIO_PORTF_DATA_R &= ~LED_GRN;
    delayLoop(loopCount);
  }

  return 0;
}
