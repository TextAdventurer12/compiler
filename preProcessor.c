#include "preProcessor.h"

char* pushActive(int regs)
{
    char regNames[14][10] = {"push rax\n", "push rbx\n", "push rcx\n", "push rdx\n", "push rsi\n", "push rdi\n", "push r8\n", "push r9\n", "push r10\n", "push r11\n", "push r12\n", "push r13\n", "push r14\n", "push r15\n"};
    char* out = malloc(getBitCount(regs) * 9);
    for (int i = 0; i < 14; i++)
    {
        if (regs & 0x01)
            strcat(out, regNames[i]);
        regs = regs >> 1;
    }
    return out;
}

char* popActive(int regs)
{
    char regNames[14][9] = {"pop rax\n", "pop rbx\n", "pop rcx\n", "pop rdx\n", "pop rsi\n", "pop rdi\n", "pop r8\n", "pop r9\n", "pop r10\n", "pop r11\n", "pop r12\n", "pop r13\n", "pop r14\n", "pop r15\n"};
    char* out = malloc(getBitCount(regs) * 8);
    for (int i = 0; i < 14; i++)
    {
        if (regs & 0x01)
           strcat(out, regNames[i]);
        regs = regs >> 1;
    }
    return out;
}

int getActiveRegs(char* line)
{
    char regNames[14][4] = {"r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8", "rdi", "rsi", "rdx", "rcx", "rbx", "rax"};
    int regs = 0;
    for (int i = 0; i < 14; i++)
    {
        if (containsString(line, regNames[i]))
            regs++;
        regs = regs << 1;
    }
    regs = regs >> 1;
    return regs;
}

void writePrologue(FILE* rdi, int allocSize, int regs)
{
    fprintf(rdi, "push rbp\n mov rbp, rsp \n sub rsp, %d \n", allocSize);
    char* psh = pushActive(regs);
    fprintf(rdi, "%s", psh);
    free (psh);
}

void writeEpilogue(FILE* rdi, int regs)
{
    char* pop = popActive(regs);
    fprintf( rdi, "%s", pop);
    free (pop);
    fprintf(rdi, "mov rsp, rbp\n pop rbp\nret");
}

void preProcessor(FILE* rdi, char* line)
{
    char digits[10] = "0123456789";
    if (contains(line, 'P'))
    {
        int j = 0;
        for (; j < strlen(line) && !contains(digits, line[j]); j++);
        int k = j;
        for (; k < strlen(line) && contains(digits, line[k]); k++);
        char* numStr = strcpybtwn(line, j, k);
        writePrologue(rdi, atoi(numStr), getActiveRegs(line));
    }
    else if (contains(line, 'E'))
        writeEpilogue(rdi, getActiveRegs(line));
}
