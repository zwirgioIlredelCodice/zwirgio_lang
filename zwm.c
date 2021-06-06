#include <stdio.h>
#include <stdlib.h>
#include "zwm.h"

/* nunber of initial registers */
int n_regs = 10;
int regs[10];

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
    case add:
        regs[reg1] = regs[reg2] + regs[reg3];
        break;

    case set_immediate:
        regs[reg1] = reg2;
        break;

    case end:
        running  = 0;
        break;

    default:
        printf("instruction not found :(\n");
        running  = 0;
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
  while( running )
  {
    showRegs();
    fetch();
    decode(program);
    eval();
  }
  showRegs();
}