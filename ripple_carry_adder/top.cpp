#include <stdio.h>
#include <limits.h>
#include "Vripple_carry_adder.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vripple_carry_adder* rca = new Vripple_carry_adder{contextp};

	/* unit test */

	printf("[ripple carry adder] unit test begins.\n\r");

	int test_range = UCHAR_MAX;

	for(int i = 0; i < test_range; i++) {
		for(int j = 0; j < test_range; j++) {
			rca->A = i;
			rca->B = j;
			rca->eval();

			uint8_t true_ans = i + j;
			if(rca->S == true_ans) {
				printf("[passed] A=%d, B=%d => S=%d\n",
                                       rca->A, rca->B, rca->S);
			} else {
				printf("[failed] A=%d, B=%d => S=%d (expect S=%d)\n",
                                       rca->A, rca->B, rca->S, true_ans);

				delete rca;
				delete contextp;

				return 0;
			}
		}
	}

	printf("[ripple carry adder] uint tests all passed.\n\r");

	delete rca;
	delete contextp;

	return 0;
}

