#include <stdio.h>
#include <limits.h>
#include "Vdivider_4_bits.h"
#include "verilated.h"

using namespace std;

bool test_divider(Vdivider_4_bits* div, uint8_t a, uint8_t b)
{
	div->a = a;
	div->b = b;
	div->eval();

	uint8_t true_q = (a / b) << 4 >> 4;
	uint8_t true_r = (a % b);

	if(div->quotient == true_q && div->remainder == true_r) {
		printf("[passed] a=%d, b=%d => q=%d, r:%d\n",
                       a, b, div->quotient, div->remainder);
		return true;
	} else {
		printf("[failed] a=%d, b=%d => q=%d, r:%d (expect: q=%d, r=)\n",
                       a, b, div->quotient, div->remainder, true_q, true_r);
		return false;
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vdivider_4_bits* div = new Vdivider_4_bits{contextp};

	/* unit test */

	printf("[4-bits divider] unit test begins.\n\r");

	test_divider(div, 15, 7);

	int test_range = 15;

	for(int i = 1; i < test_range; i++) {
		for(int j = 1; j < test_range; j++) {
			bool correct = test_divider(div, i, j);
			if(correct == false) {
				delete div;
				delete contextp;
				return 0;
			}
		}
	}


	printf("[4-bits divider] unit tests all passed.\n\r");

	delete div;
	delete contextp;

	return 0;
}

