#include <stdio.h>
#include <limits.h>
#include "Vfinite_state_machine.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

using namespace std;

struct FSM_Step {
	const char* name;
	uint8_t in;
};

struct FSM_Step fsm_step_list[] = {
	{"step1", 1},
	{"step2", 1},
	{"step3", 0},
	{"step4", 1},
	{"step5", 0},
	{"step6", 0},
	{"step7", 1},
	{"step8", 0},
	{"step9", 0},
	{"step10", 0}
};

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vfinite_state_machine* fsm = new Vfinite_state_machine{contextp};
	fsm->reset_n = 1;

	/* vcd logger */
	VerilatedVcdC* tfp = new VerilatedVcdC;
	contextp->traceEverOn(true);
	fsm->trace(tfp, 0);
	tfp->open("wave.vcd");

	int test_num = sizeof(fsm_step_list) / sizeof(FSM_Step);

	/* run simulation and record with vcd logger */
	for(int i = 0; i < 50; i++) {
		fsm->clk = !fsm->clk;
		fsm->in = fsm_step_list[i % test_num].in;
		fsm->eval();

		printf("[%d] clk=%d, in=%d, out=%d, reset_n=%d\n",
                       i, fsm->clk, fsm->in, fsm->out, fsm->reset_n);

		tfp->dump(contextp->time());
		contextp->timeInc(1);
	}
	printf("[verilator] end of simulation\n"
               "type `make plot` to observe the signal change with gtkwave.\n");

	delete fsm;
	tfp->close();
	delete contextp;

	return 0;
}

