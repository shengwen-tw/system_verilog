#include <stdio.h>
#include "Vmultiplier.h"
#include "verilated.h"

using namespace std;

bool test_multiplier(Vmultiplier* mul, uint8_t a, uint8_t b)
{
	mul->a = a;
	mul->b = b;
	mul->eval();

	uint8_t true_ans = a * b;

	if(mul->result == true_ans) {
		printf("[multiplier] %d * %d = %d\n", a, b, mul->result);
		return true;
	} else {
		printf("[error] %d * %d = %d\n (expect: %d)",
                       a, b, mul->result, true_ans);
		return false;
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vmultiplier* mul = new Vmultiplier{contextp};

	/* unit test */

	printf("[multiplier] unit test begins.\n\r");

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			bool correct = test_multiplier(mul, i, j);
			if(correct == false) {
				delete mul;
				delete contextp;
				return 0;
			}
		}
	}

	printf("[multiplier] unit tests all passed.\n\r");

	delete mul;
	delete contextp;

	return 0;
}
