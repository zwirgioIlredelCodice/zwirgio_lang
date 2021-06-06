#include <stdio.h>
#include <stdlib.h>
#include "zwm.h"

/* nunber of initial registers */
int n_regs = 0;
int *regs;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;

/* the VM runs until this flag becomes 0 */
int running = 1;

/* program counter */
unsigned int pc = 0;

void fetch()
{
    pc += NUM_ARGS;
}

void decode(int program[])
{
    instrNum = program[pc];
    reg1 = program[pc + 1];
    reg2 = program[pc + 2];
    reg3 = program[pc + 3];
}

void eval()
{
    switch (instrNum)
    {
    //Arithmetic
    case add:
        regs[reg1] = regs[reg2] + regs[reg3];
        break;

    case add_immediate:
        regs[reg1] = regs[reg2] + reg3;
        break;

    case subtract:
        regs[reg1] = regs[reg2] - reg3;
        break;

    case multiply:
        regs[reg1] = regs[reg2] * reg3;
        break;

    case divide:
        regs[reg1] = regs[reg2] / regs[reg3];
        break;

    //Logical
    case and:
        regs[reg1] = regs[reg2] && regs[reg3];
        break;

    case or:
        regs[reg1] = regs[reg2] || regs[reg3];
        break;

    case not:
        regs[reg1] = !regs[reg2];
        break;

    //comparison
    case equal:
        regs[reg1] = regs[reg2] == regs[reg3];
        break;

    case greater_than:
        regs[reg1] = regs[reg2] > regs[reg3];
        break;

    case greater_equal:
        regs[reg1] = regs[reg2] >= regs[reg3];
        break;

    case lower_than:
        regs[reg1] = regs[reg2] < regs[reg3];
        break;

    case lower_equal:
        regs[reg1] = regs[reg2] <= regs[reg3];
        break;

    //jumps
    case jump:
        pc = reg2;
        break;

    case jump_if:
        if (regs[reg1])
        {
            pc = reg2;
        }
        break;

    //data transfer
    case set_immediate:
        regs[reg1] = reg2;
        break;

    case set:
        regs[reg1] = regs[reg2];
        break;

    case set_pointer:
        regs[reg1] = regs[regs[reg2]];
        break;

    //system
    case read:
        scanf("%d", &regs[reg1]);
        break;

    case write:
        printf("%d", regs[reg1]);
        break;

    case memory_alloc_immediate:
        n_regs += reg1;
        regs = realloc(regs, n_regs);
        if (regs == NULL)
        {
            fprintf(stderr, "Error - unable to allocate required memory\n");
            running = 0;
        }
        break;

    case memory_alloc:
        n_regs += regs[reg1];
        regs = realloc(regs, n_regs);
        if (regs == NULL)
        {
            fprintf(stderr, "Error - unable to allocate required memory\n");
            running = 0;
        }
        break;

    case memory_free_immediate:
        n_regs -= reg1;
        regs = realloc(regs, n_regs);
        if (regs == NULL)
        {
            fprintf(stderr, "Error - unable to allocate required memory\n");
            running = 0;
        }
        break;

    case memory_free:
        n_regs -= regs[reg1];
        regs = realloc(regs, n_regs);
        if (regs == NULL)
        {
            fprintf(stderr, "Error - unable to allocate required memory\n");
            running = 0;
        }
        break;

    case end:
        running = 0;
        break;

    default:
        printf("instruction not found :(\n");
        running = 0;
        break;
    }
}

void showRegs()
{
    int i;
    printf("regs = ");
    for (i = 0; i < n_regs; i++)
        printf("%d ", regs[i]);
    printf("\n");
}

void run(int program[])
{
    while (running)
    {
        showRegs();
        fetch();
        decode(program);
        eval();
    }
    showRegs();
    free(regs); //free regs
}