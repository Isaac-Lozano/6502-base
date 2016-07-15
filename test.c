#include <stdio.h>
#include "6502.h"

uint8_t mem[CPU6502_MEM_SIZE];

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    size_t len = fread(mem, 1, CPU6502_MEM_SIZE, f);
    printf("Read %zd bytes.\n", len);
    mem[CPU6502_RESET] = 0x00;
    mem[CPU6502_RESET+1] = 0x10;

    CPU_6502 cpu;
    cpu6502_init(&cpu, mem);
    cpu6502_reset(&cpu);

    printf("Press Enter to step one opcode.\n");
    for(;;)
    {
        getchar();
        cpu6502_run(&cpu, 1);
        cpu6502_print_status(&cpu);
    }

    printf("ps is 0x%x\n", cpu.ps.ps);
    printf("s %d, v %d, U %d, b %d, d %d, i %d, z %d, c %d\n",
            cpu.ps.flags.s,
            cpu.ps.flags.v,
            cpu.ps.flags.UNUSED,
            cpu.ps.flags.b,
            cpu.ps.flags.d,
            cpu.ps.flags.i,
            cpu.ps.flags.z,
            cpu.ps.flags.c);
    printf("mem[3]: 0x%x\n", cpu.memory[3]);

    return 0;
}
