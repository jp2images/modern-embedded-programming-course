
int main() {
  int counter = 0;

    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    
    while (counter < 21){
      ++counter;
    }
          
    if((counter & 1) != 0) {
      /* Do something when the counter is odd */
      //Test the last bit of the counter by ANDing it with a 1.
      // 0001 0010 == 18
      // 0000 0001 ==  1
      // ---------------
      // 0000 0000 ==  0  EQUALS an even number
      
    }
    else {
      /* Do something when the counter is even */
      //Test the last bit of the counter by ANDing it with a 1.
      // 0001 0101 == 21
      // 0000 0001 ==  1
      // ---------------
      // 0000 0000 ==  1  EQUALS an odd number
    }
  
  return 0;
}
