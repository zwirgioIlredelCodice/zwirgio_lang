#include <stdio.h>
#include <stdlib.h>
#include "zwm.h"
#include "zwassembly.h"

int main()
{
    /*
    printf("ghe bello\n");
    int program[] =
        {0, 0, 0, 0,
         20, 10, 0, 0,
         15, 0, 22, 0,
         15, 1, 69, 0,
         0, 3, 0, 1,
         19, 3, 0, 0,
         23, 5, 0, 0,
         24, 0, 0, 0};
    run(program);
    return 0;
    */
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
    printf("*DEBUG* progam \n");
    for (int i=0; i<numero_comandi; i++) 
    {
        printf("%d ",program[i]);
    }
    printf("\n");
    
    run(program);
    return 0;
}