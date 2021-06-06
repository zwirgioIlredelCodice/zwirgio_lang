#pragma once

#define NUM_ARGS 4

extern int regs[];
extern unsigned int pc;

extern int running;

extern int instrNum;
extern int reg1;
extern int reg2;
extern int reg3;

enum instruction
{
    //Arithmetic
    add,
    subtract,
    Multiply,
    Divide,

    //Logical
    and,
    or,
    not,

    //Comparison
    equal,
    greater_than,
    greater_of_equal,
    lower_than,
    lower_equal,

    //Jumps
    jump,
    jump_if,

    //Data Transfer
    set_immediate,
    set,
    set_pointer,

    //System
    read,
    write,
    memory_alloc_immediate,
    memory_alloc,
    memory_free_immediate,
    end,
};

void fetch();

void decode(int program[]);

void eval();

void showRegs();

void run(int program[]);