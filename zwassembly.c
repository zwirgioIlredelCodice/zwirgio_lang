#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTION_LEN 50
#define NUM_INSTRUCTION 25

int count_line(char file_name[])
{
    FILE *fp;
    int count = 0; // Line counter (result)
    char c;        // To store a character read from file

    // Get file name from user. The file should be
    // either in current folder or complete path should be provided

    // Open the file
    fp = fopen(file_name, "r");

    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", file_name);
        return (-1);
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    // Close the file
    fclose(fp);
    return (count+1);
}

void zwassembler(char file_name[], int program[])
{
    int instruction_counter = 0;

    FILE *fp;

    char buff[100];
    char instrNum[20];
    char reg1[20];
    char reg2[20];
    char reg3[20];

    int n_instrNum;
    int n_reg1;
    int n_reg2;
    int n_reg3;

    char *token;
    const char delim[] = " ";

    char instruction[NUM_INSTRUCTION][MAX_INSTRUCTION_LEN] = 
    {
    "add",
    "add_immediate",
    "subtract",
    "multiply",
    "divide",
    "and",
    "or",
    "not",
    "equal",
    "greater_than",
    "greater_equal",
    "lower_than",
    "lower_equal",
    "jump",
    "jump_if",
    "set_immediate",
    "set",
    "set_pointer",
    "read",
    "write",
    "memory_alloc_immediate",
    "memory_alloc",
    "memory_free",
    "memory_free_immediate",
    "end",
    };

    int not_found = 0;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Could not open file %s", file_name);
    }

    while (!feof(fp))
    {
        fgets(buff, 100, (FILE *)fp); //leggie una riga del file in buff

        token = strtok(buff, delim); //fa un token quando vede uno spazio
        strcpy(instrNum, token);      //copia la stringa nel instrNum

        int i = 0;
        while (token != NULL) //finchè non sono finiti i token
        {
            if (i == 1)
            {
                strcpy(reg1, token);
            }
            if (i == 2)
            {
                strcpy(reg2, token);
            }
            i++;
            token = strtok(NULL, delim);
        }
        n_reg1 = atoi(reg1);
        n_reg2 = atoi(reg2);
        n_reg3 = atoi(reg3);

        for(int i=0; i<NUM_INSTRUCTION; i++)
        {
            if (strcmp(instrNum,instruction[i])== 0)
            {
                not_found = 0;
                n_instrNum = i;
                break;
            }
        }
        if (not_found) 
        {
            printf("instruction not found");
            return;
        }
        not_found = 0;

        //lo mette nel array
        program[instruction_counter] = n_instrNum;
        instruction_counter++;
        program[instruction_counter] = n_reg1;
        instruction_counter++;
        program[instruction_counter] = n_reg2;
        instruction_counter++;
        program[instruction_counter] = n_reg3;
        instruction_counter++;
    }
    fclose(fp); 
}
