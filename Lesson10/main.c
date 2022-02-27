#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

#define LED_OFF 0
#define LED_RED (1U << 1)
#define LED_BLU (1U << 2)
#define LED_GRN (1U << 3)


//unsigned fact(unsigned n);

/*
//This can not work because the paramters are based by value and not by reference.
void swap(int x, int y);
void swap(int x, int y){
  int temp = x;
  x = y;
  y = temp;
}


//This one will work since we are using pointers
void swap(int* x, int* y);
void swap(int* x, int* y){
  int temp = *x;
  *x = *y;
  *y = temp;
}
*/

int* swap(int* x, int* y);
int* swap(int* x, int* y){
  static int temp[2];
  temp[0] = *x;
  temp[1] = *y;

  *x = temp[1];
  *y = temp[0];

  return temp;
}


int main() {
/*
  unsigned volatile x;
  x = fact(0U);
  x = 2U + 3U * fact(1U);
  (void)fact(7U);
*/

  //int x = 1;
  //int y = 2;
  //swap(x, y);
  //swap(&x,& y);

  SYSCTL_RCGCGPIO_R |= (1U << 5); /* Enable clock for GPIOF = 0x20 */
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* Enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R  |= (LED_RED | LED_BLU | LED_GRN); /* Set port F pins 1, 2, and 3 as output */
  GPIO_PORTF_AHB_DEN_R  |= (LED_RED | LED_BLU | LED_GRN); /*  */

  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_BLU;
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLU] = LED_OFF;

  int x = 1000000;
  int y = 1000000/5;

  while(1) {

    int* p = swap(&x, &y);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Cleanest looking of the 3 versions
    //int volatile x = 1000000;
    //delay(x);
    delay(p[0]);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_OFF;
    //delay(x/4);
    delay(p[0]);
  }
  //return 0;
}

/*
unsigned fact(unsigned n) {
  // 0! = 1
  // n! = n * (n - 1)! for n > 0

  unsigned foo[6]; //with this array set to 6 and the input set to 7 we are creatng an overflow
  foo[n] = n;

  if (n == 0U) {
    return 1U;
  }
  else {
    return foo[n] * fact(n -1U);
  }
}
*/