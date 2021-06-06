#include <stdio.h>
#include "zwm.h"

int main() {
    printf("ghe bello\n");
    int program[] = {set_immediate, 0, 22, 0, set_immediate, 1, 69, 0, add, 0, 1, 2, end, 0,0,0};
    run(program);
    return 0;
}