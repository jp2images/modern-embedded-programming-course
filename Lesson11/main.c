#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

#define LED_OFF 0
#define LED_RED (1U << 1)
#define LED_BLU (1U << 2)
#define LED_GRN (1U << 3)

uint8_t  u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t  s8;
int16_t s16;
int32_t s32;

int main() {

  u8a  = sizeof(u8a);
  u16c = sizeof(uint16_t);
  u32e = sizeof(uint32_t);

  u8a  = 0xa1U;
  u16c = 0xc1c2U;
  u32e = 0xe1e2e3e4U;

  u8b  = u8a;
  u16d = u16c;
  u32f = u32e;

  //The C compiler automatically promotes smaller size integer to the built in
  //size int or uint type before performaing any computations
  u16c = 40000U;
  u16d = 30000U;

  //Explicitly cast one of the variables to int32 and this code becomes potable
  //accross 16 and 32-bit processors and doesn't cause a penalty for a native
  //32-bit processor.
  u32e = (uint32_t)u16c + u16d;

  //when mixing signed with unsigned ints, both are promoted to unsigned int.
  //This fails on a 16-bit machine. On this 32-bit machine, the unsigned 16
  //bit is promoted to 32-bit signed. To make this portable, cast to a 16-bit
  //signed. Or 32-bit signed depending on the value.
  u16c = 100U;
  s32 = 10 - (int16_t)u16c;
  s32 = 10 - (int32_t)u16c;

  //the signed and unsigned int conversion can become a problem when comparing
  //integers.
  if(u32e > -1) { //unsigned is always larger than -1.
    //EXCEPT the warning idicates this IF is ALWAYS FALSE.
    //This is because of automatic promotion to unsigned int and a -1 is stored
    //as 0xFFFFFFFF which is the largest UNSIGNED 16-bit value.
    u8a = 1U;
  }
  else {
    u8a = 0U;
  }


  if((int32_t)u32e > -1) { //unsigned is always larger than -1. CAST as UINT
    u8a = 1U;
  }
  else {
    u8a = 0U;
  }


  //binary operation on small integers
  u8a = 0xffU;
  //The compiler knows this can never be TRUE and eliminates it from the
  //compiled code.
  //The ~u8a is promoted to a signed int and the MSB is 0.  When the 1s
  //complement is taken the MSB is changed to 1 and the result can never be 0.
  if ((uint8_t)~u8a == 0x00U) { //to correct, explicitly cast the var as a uint byte.
    u8b = 1U;
  }




  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_BLU;
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_OFF;


  while(1) {

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    //int volatile x = 1000000;
    //delay(x);
    delay(500000);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_OFF;
    //delay(x/4);
    delay(500000);
  }
  //return 0;
}

