#include <stdio.h>
#include <stdlib.h>
#include "zwm.h"
#include "zwassembly.h"

int main()
{
    printf("ghe bello\n");
    int program[] =
        {0, 0, 0, 0,
         memory_alloc_immediate, 10, 0, 0,
         set_immediate, 0, 22, 0,
         set_immediate, 1, 69, 0,
         add, 3, 0, 1,
         write, 3, 0, 0,
         memory_free_immediate, 5, 0, 0,
         end, 0, 0, 0};
    run(program);
    return 0;
    /*
   char file_name[] = "example.txt";
   printf("eseguzione file %s\n", file_name);

    int numero_righe = count_line(file_name);
    int numero_comandi = numero_righe * 4;

    int *program;
    program = calloc(numero_comandi, sizeof(int)); //crea un array di int per tnenere tutti i comandi
    if (program == NULL)
    {
        printf("error not able to allocate memory for program[]\n");
        return 1;
    }

    zwassembler(file_name, program);
    run(program);
    return 0;*/
}