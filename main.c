#include <stdio.h>
#include "zwm.h"

int main() {
    printf("ghe bello\n");
    int program[] = {0,0,0,0,set_immediate, 0, 22, 0, set_immediate, 1, 69, 0, add, 3, 0, 1, end, 0,0,0};
    run(program);
    return 0;
}