

int main() {
  *((unsigned int*)0x400FE608U) = 0x20U; //Enable Memory block P4 scanning with bit 5 high
  *((unsigned int*)0x40025400U) = 0x0EU; //Enable GPIO Pin direction for Port F bits 1, 2, and 3
  *((unsigned int*)0x4002551CU) = 0x0EU; //Enable GPIO Digital Function Port F bits 1, 2, and 3

  int counter = 0;
  int loopCount = 1000000;

  while(1) {
    *((unsigned int*)0x400253FCU) = 0x02U; //Turn ON bit 1 (Red LED)
    counter = 0;
    while (counter < loopCount){
      ++counter;
    }
    *((unsigned int*)0x400253FCU) = 0x00U; //Turn OFF bit 1 (Red LED)
    counter = 0;
    while (counter < loopCount){
      ++counter;
    }

    *((unsigned int*)0x400253FCU) = 0x04U; //Turn ON bit 2 (Blue LED)
    counter = 0;
    while (counter < loopCount){
      ++counter;
    }
    *((unsigned int*)0x400253FCU) = 0x00U; //Turn OFF bit 2 (Blue LED)
    counter = 0;
    while (counter < loopCount){
      ++counter;
    }

    *((unsigned int*)0x400253FCU) = 0x08U; //Turn ON bit 3 (Breen LED)
    counter = 0;
    while (counter < loopCount){
      ++counter;
    }
    *((unsigned int*)0x400253FCU) = 0x00U; //Turn OFF bit 3 (Breen LED)
        counter = 0;
    while (counter < loopCount){
      ++counter;
    }
  }

  return 0;
}
