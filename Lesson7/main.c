#include <stdint.h>
#include "tm4c123gh6pm.h"

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
  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */

  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */

  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  int loopCount = 1000000;

  //GPIO_PORTF_DATA_BITS_R[LED_BLU] = LED_BLU;

  while(1) {
    //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED;
    //GPIO_PORTF_DATA_R |= LED_RED; //To work this register must have R/W permission

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    //equiv.
    //*((unsigned volatile long*)(0x40025000 + (LED_RED << 2U))) = LED_RED;
    //equiv.
    //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
    delayLoop(loopCount);

    //GPIO_PORTF_DATA_R &= ~LED_RED; //Clear the bit (Turn OFF the LED)
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;

    delayLoop(loopCount);

    /*
    GPIO_PORTF_AHB_DATA_R |= LED_BLU;
    delayLoop(loopCount);

    GPIO_PORTF_AHB_DATA_R &= ~LED_BLU;
    delayLoop(loopCount);

    GPIO_PORTF_AHB_DATA_R |= LED_GRN;
    delayLoop(loopCount);

    GPIO_PORTF_AHB_DATA_R &= ~LED_GRN;
    delayLoop(loopCount);
*/
  }

  return 0;
}
