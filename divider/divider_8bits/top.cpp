#include <stdio.h>
#include <limits.h>
#include "Vdivider.h"
#include "verilated.h"

using namespace std;

bool test_divider(Vdivider* div, uint8_t a, uint8_t b)
{
	div->a = a;
	div->b = b;
	div->eval();

	/* test divide by zero */
	if(b == 0) {
		if(div->div_by_zero == 1) {
			printf("[passed] a=%d, b=%d, div_by_zero=%d\n", a, b, div->div_by_zero);
			return true;
		} else {
			printf("[passed] a=%d, b=%d, div_by_zero=%d (expect div_by_zero=1)\n",
                               a, b, div->div_by_zero);
			return false;
		}
	}

	/* test proper values */
	uint8_t true_q = (a / b) << 4 >> 4;
	uint8_t true_r = (a % b);

	if(div->quotient == true_q && div->remainder == true_r) {
		printf("[passed] a=%d, b=%d => q=%d, r:%d\n",
                       a, b, div->quotient, div->remainder);
		return true;
	} else {
		printf("[failed] a=%d, b=%d => q=%d, r:%d (expect: q=%d, r=%d)\n",
                       a, b, div->quotient, div->remainder, true_q, true_r);
		return false;
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vdivider* div = new Vdivider{contextp};

	/* unit test */

	printf("[8-bits divider] unit test begins.\n\r");

	int range_min = 0;
	int range_max = UCHAR_MAX;
	for(int i = range_min; i < range_max; i++) {
		for(int j = range_min; j < range_max; j++) {
			bool correct = test_divider(div, i, j);
			if(correct == false) {
				delete div;
				delete contextp;
				return 0;
			}
		}
	}

	printf("[8-bits divider] unit tests all passed.\n\r");

	delete div;
	delete contextp;

	return 0;
}

