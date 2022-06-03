#include <stdio.h>
#include <limits.h>
#include "Vcarry_lookahead_adder.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vcarry_lookahead_adder* cla = new Vcarry_lookahead_adder{contextp};

	/* unit test */

	printf("[carry-lookahead adder] unit test begins.\n\r");

	int test_range = UCHAR_MAX;

	for(int i = 0; i < test_range; i++) {
		for(int j = 0; j < test_range; j++) {
			cla->a = i;
			cla->b = j;
			cla->cin = 0;
			cla->eval();

			uint8_t true_ans = i + j;
			if(cla->s == true_ans) {
				printf("[passed] %d + %d = %d\n",
                                       cla->a, cla->b, cla->s);
			} else {
				printf("[failed] %d + %d = %d (expect s=%d)\n",
                                       cla->a, cla->b, cla->s, true_ans);

				delete cla;
				delete contextp;

				return 0;
			}
		}
	}

	printf("[carry-lookahead adder] unit tests all passed.\n\r");

	delete cla;
	delete contextp;

	return 0;
}

