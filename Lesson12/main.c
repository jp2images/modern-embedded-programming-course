#include <stdint.h>
#include <stdbool.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "../driverlib/sysctl.h"
#include "../driverlib/gpio.h"
#include "tm4c123ge6pm.h"


#include "tm4c_cmsis.h"
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
typedef /*__packed*/ struct { //The __packed is a IAR extension to remove the
                          //padding that the compiler would include to keep all
                          //variables placed on even addresses.
  //WARNING packed instructions use more instructions to get the data back out.
  //so it is much slower on lower end processors/
  uint8_t y;
  uint16_t x;
} Point;

Point p1, p2;

typedef struct {
  Point top_left;
  Point bottom_right;
} Window;

typedef struct {
  Point corners[3];
} Triangle;

Window w, w2;
Triangle t;


int main() {

  Point* pp;
  Window* wp;

  p1.x = sizeof(Point);
  p1.y = p1.x - 0xAAU;

  w.top_left.x = 1U;
  w.bottom_right.y =2U;

  t.corners[0].x = 1U;
  t.corners[2].y = 2U;

  p2 = p1;
  w2 = w;

  pp = &p1;
  wp = &w2;

  (*pp).x =1U; // to use the dot operator
  (*wp).top_left = *pp;

  pp->x = 1U;
  wp->bottom_right = *pp;

  /*
    SYSCTL->RCGC2 |= (1U << 5);
    SYSCTL->GPIOHSCTL |= (1U << 5);
    SYSCTL->DIR |= (LED_RED | LED_BLU | LED_GRN);
    SYSCTL->DEN |= (LED_RED | LED_BLU | LED_GRN);

    GPIOF_HS->DATA_BITS[LED_BLU] = LED_OFF;
  */


  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_BLU;
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_OFF;

  while(1) {

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    //GPIOF_HS->DATA_BITS[LED_RED] = LED_RED;
    delay(500000);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_OFF;
    //GPIOF_HS->DATA_BITS[LED_RED] = LED_OFF;
    delay(500000);
  }
  //return 0;
}

