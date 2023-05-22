
int counter = 0;

int main() {
    int* p_int;
    p_int = &counter;

    //while(counter < 21) {
    while(*p_int < 21) {
        //++counter;
        ++(*p_int);
    }

    p_int = (int*)0x20000024U;
    *p_int = 0xDEADBEEF;
    return 0;
}
