#include <stdio.h>

int go_rec50(int no);

int main (void) {
   go_rec50(1);
}

int go_rec50(int no) {

    if (no == 51) return 0;
    if (no == 1) puts("The natural numbers up to 50: ");
    
    printf("%d ", no);
   
    no++;
    go_rec50(no);
}
