#include <stdio.h>
#include "Vlshifter.h"
#include "verilated.h"

using namespace std;

bool test_left_shifter(Vlshifter* lsh, uint8_t data, uint8_t bits)
{
	lsh->data_in = data;
	lsh->bits = bits;
	lsh->eval();

	uint8_t true_ans = data << bits;

	if(lsh->data_out == true_ans) {
		printf("[left shifter] %d << %d = %d\n",
                       lsh->data_in, lsh->bits, lsh->data_out);
		return true;
	} else {
		printf("[error] %d MM %d = %d (expect %d)\n",
                       lsh->data_in, lsh->bits, lsh->data_out, true_ans);
		return false;
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vlshifter* lsh = new Vlshifter{contextp};

	/* unit test */

	printf("[left shifter] unit test begins.\n\r");

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 8; j++) {
			bool correct = test_left_shifter(lsh, i, j);
			if(correct == false) {
				delete lsh;
				delete contextp;
				return 0;
			}
		}
	}

	printf("[left shifter] unit tests all passed.\n\r");

	delete lsh;
	delete contextp;

	return 0;
}
