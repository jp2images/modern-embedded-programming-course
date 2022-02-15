#include "tm4c123gh6pm.h"

#define GPIO_BASE 0x40025000U

/// 0x20U; //Enable Memory block P4 scanning with bit 5 high (Clock)
#define RCGCGPIO  (*((unsigned int*)0x400FE608U))

/// 0x0EU; //Enable GPIO Pin direction for Port F bits 1, 2, and 3
#define GPIOF_DIR  (*((unsigned int*)(GPIO_BASE + 0x400U)))

/// 0x0EU; //Enable GPIO Digital Function Port F bits 1, 2, and 3
#define GPIOF_DEN  (*((unsigned int*)(GPIO_BASE + 0x51CU)))


#define GPIOF_DATA (*((unsigned int*)(GPIO_BASE + 0x3FCU)))

void delayLoop(int loopCount){
  int counter = 0;
  while (counter < loopCount){
    ++counter;
  }
}

int main() {
  RCGCGPIO = 0x20U;  //Enable Memory block P4 scanning with bit 5 high (Clock)
  GPIOF_DIR = 0x0EU; //Enable GPIO Pin direction for Port F bits 1, 2, and 3 as OUTPUT
  GPIOF_DEN= 0x0EU;  //Enable GPIO Digital Function Port F bits 1, 2, and 3

  int counter = 0;
  int loopCount = 1000000;

  while(1) {
    GPIOF_DATA = 0x02U; //Turn ON bit 1 (Red LED)
    delayLoop(loopCount);

    GPIOF_DATA = 0x00U; //Turn OFF bit 1 (Red LED)
    delayLoop(loopCount);

    GPIOF_DATA = 0x04U; //Turn ON bit 2 (Blue LED)
    delayLoop(loopCount);

    GPIOF_DATA = 0x00U; //Turn OFF bit 2 (Blue LED)
    delayLoop(loopCount);

    GPIOF_DATA = 0x08U; //Turn ON bit 3 (Breen LED)
    delayLoop(loopCount);

    GPIOF_DATA = 0x00U; //Turn OFF bit 3 (Breen LED)
    delayLoop(loopCount);
  }

  return 0;
}
