#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

#define LED_OFF 0
#define LED_RED (1U << 1)
#define LED_BLU (1U << 2)
#define LED_GRN (1U << 3)


unsigned fact(unsigned n);


int main() {

  unsigned volatile x;
  x = fact(0U);
  x = 2U + 3U * fact(1U);
  (void)fact(5U);


  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  GPIO_PORTF_DATA_BITS_R[LED_BLU] = LED_BLU;

  while(1) {
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    delayLoop(1000000);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_OFF;
    delayLoop(250000);
  }
  //return 0;
}

unsigned fact(unsigned n) {
  // 0! = 1
  // n! = n * (n - 1)! for n > 0

  if (n == 0U) {
    return 1U;
  }
  else {
    return n * fact(n -1U);
  }
}