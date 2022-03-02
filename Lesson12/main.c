#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

#define LED_OFF 0
#define LED_RED (1U << 1)
#define LED_BLU (1U << 2)
#define LED_GRN (1U << 3)


//typedef struct Point Point;
//struct Point {
//  uint16_t x;
//  uint8_t y;
//}; //pa, pb; //Variables could be declared immediately after the struct and
             //then the struct name ("Point" in this instance is optional.

//struct Point pa, pb; //Must use the keyword struct every time you create a
                       //structure variable. UNLESS... you define a MACRO

//Or to make it less tedious you may do this: MISRA C:2012 recommends this.
typedef struct {
  uint16_t x;
  uint8_t y;
} Point;

Point p1, p2;


int main() {

  p1.x = sizeof(Point);
  p1.y = p1.x - 3U;

  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_BLU;
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_OFF;

  while(1) {

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    delay(500000);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_OFF;
    delay(500000);
  }
  //return 0;
}

