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

int16_t y = -1;
uint32_t x = LED_RED | LED_GRN;

int16_t sqr[] = {
  1*1,
  2*2,
  3*3,
  4*5
  //Missing elements are initialized to ZERO if array size is larger than supplied initial values.
};

typedef struct {
  uint8_t y;
  uint16_t x;
} Point;

Point p1 = {
  123U,
  0x1234U
};
Point p2;

typedef struct {
  Point top_left;
  Point bottom_right;
} Window;

typedef struct {
  Point corners[3];
} Triangle;

Window w = {
  { 123U, 0x1234U },
  { 234U, 0x6789U }
};

Window w2;
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

