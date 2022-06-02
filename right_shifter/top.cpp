#include <stdio.h>
#include "Vrshifter.h"
#include "verilated.h"

using namespace std;

bool test_right_shifter(Vrshifter* rsh, uint8_t data, uint8_t bits)
{
	rsh->data_in = data;
	rsh->bits = bits;
	rsh->eval();

	uint8_t true_ans = data >> bits;

	if(rsh->data_out == true_ans) {
		printf("[right shifter] %d >> %d = %d\n",
                       rsh->data_in, rsh->bits, rsh->data_out);
		return true;
	} else {
		printf("[error] %d >> %d = %d (expect %d)\n",
                       rsh->data_in, rsh->bits, rsh->data_out, true_ans);
		return false;
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vrshifter* rsh = new Vrshifter{contextp};

	/* unit test */

	printf("[right shifter] unit test begins.\n\r");

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 8; j++) {
			bool correct = test_right_shifter(rsh, i, j);
			if(correct == false) {
				delete rsh;
				delete contextp;
				return 0;
			}
		}
	}

	printf("[right shifter] unit tests all passed.\n\r");

	delete rsh;
	delete contextp;

	return 0;
}
