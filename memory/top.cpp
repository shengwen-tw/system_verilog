#include <stdio.h>
#include "Vmemory.h"
#include "verilated.h"

using namespace std;

enum {
	MEMORY_READ = 0,
	MEMORY_WRITE = 1
} MemoryMode;

void mem_generate_clk(Vmemory* mem, int cycles)
{
        for(int i = 0; i < (cycles * 2); i++) {
                mem->clk = !mem->clk;
                mem->eval();
        }
}

void mem_write(Vmemory* mem, uint8_t addr, uint8_t data)
{
	mem->cs = 1;
	mem->rw = MEMORY_WRITE;
	mem->addr = addr;
	mem->data = data;
	mem_generate_clk(mem, 1);
	printf("[write] address:%d, data=%d\n", addr, data);
}

uint8_t mem_read(Vmemory* mem, uint8_t addr)
{
	mem->cs = 1;
	mem->rw = MEMORY_READ;
	mem->addr = addr;
	mem->data = 0;
	mem_generate_clk(mem, 1);
	printf("[read] address:%d, data=%d\n", addr, mem->data);

	return mem->data;
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vmemory* mem = new Vmemory{contextp};
	mem->clk = 1;
	mem->reset = 0;
	mem->eval();

	printf("[memory] unit test begins.\n\r");

	for(uint8_t i = 0; i < 255; i++) {
		mem_write(mem, i, i);
		uint8_t retval = mem_read(mem, i);

		if(retval != i) {
			printf("[Error] inconsistent memory read/write. (expect: %d)\n", i);
			delete mem;
			delete contextp;

			return 0;
		}
	}

	printf("[memory] uint tests all passed.\n\r");

	delete mem;
	delete contextp;

	return 0;
}
