#include <stdio.h>
#include "Vsyn_fifo.h"
#include "verilated.h"

using namespace std;

void fifo_push(Vsyn_fifo* fifo, uint8_t data)
{
	if(fifo->fifo_full == 0) {
		fifo->wr_en = 1;
		fifo->rd_en = 0;
		fifo->wr_data = data;
		fifo->clk = !fifo->clk;
		fifo->eval();
		printf("[push] data=%d.\n", fifo->wr_data);
	} else {
		fifo->wr_en = 0;
		fifo->rd_en = 0;
		fifo->clk = !fifo->clk;
		fifo->eval();	
		printf("[push] data=%d. failed, the fifo is full.\n", data);
	}

	fifo->clk = !fifo->clk;
	fifo->eval();
}

void fifo_pop(Vsyn_fifo* fifo)
{
	if(fifo->fifo_empty == 0) {
		fifo->wr_en = 0;
		fifo->rd_en = 1;
		fifo->clk = !fifo->clk;
		fifo->eval();
		printf("[pop] data=%d.\n", fifo->rd_data);
	} else {
		fifo->wr_en = 0;
		fifo->rd_en = 0;
		fifo->clk = !fifo->clk;
		fifo->eval();
		printf("[pop] failed, the fifo is empty.\n");
	}

	fifo->clk = !fifo->clk;
	fifo->eval();
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vsyn_fifo* fifo = new Vsyn_fifo{contextp};

	fifo->rst_n = 0;
	fifo->clk = 0;
	fifo->eval();

	fifo->rst_n = 1;

	printf("[synchronous fifo] depth=8\n");

	for(int i = 0; i < 8; i++) {
		fifo_push(fifo, i);
	}

	for(int i = 0; i < 12; i++) {
		fifo_pop(fifo);
	}

	for(int i = 0; i < 8; i++) {
		fifo_push(fifo, i);
	}

	for(int i = 0; i < 12; i++) {
		fifo_pop(fifo);
	}

	delete fifo;
	delete contextp;

	return 0;
}
