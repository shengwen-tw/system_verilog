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

	for(int i = 0; i <= UCHAR_MAX; i++) {
		for(int j = 0; j <= UCHAR_MAX; j++) {
			rca->a = i;
			rca->b = j;
			rca->cin = 0;
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

