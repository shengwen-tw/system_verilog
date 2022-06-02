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
			rca->a = i;
			rca->b = j;
			rca->eval();

			uint8_t true_ans = i + j;
			if(rca->s == true_ans) {
				printf("[passed] %d + %d = %d\n",
                                       rca->a, rca->b, rca->s);
			} else {
				printf("[failed] %d + B=%d = %d (expect s=%d)\n",
                                       rca->a, rca->b, rca->s, true_ans);

				delete rca;
				delete contextp;

				return 0;
			}
		}
	}

	printf("[ripple carry adder] unit tests all passed.\n\r");

	delete rca;
	delete contextp;

	return 0;
}

