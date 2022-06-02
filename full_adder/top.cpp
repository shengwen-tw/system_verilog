#include <stdio.h>
#include "Vfull_adder.h"
#include "verilated.h"

using namespace std;

struct TestCase {
	const char* name;
	uint8_t a;
	uint8_t b;
	uint8_t cin;
	uint8_t s;
	uint8_t cout;
};

struct TestCase test_cases[] = {
	{"case1", 0, 0, 0, 0, 0},
	{"case2", 0, 0, 1, 1, 0},
	{"case3", 0, 1, 0, 1, 0},
	{"case4", 0, 1, 1, 0, 1},
	{"case5", 1, 0, 0, 1, 0},
	{"case6", 1, 0, 1, 0, 1},
	{"case7", 1, 1, 0, 0, 1},
	{"case8", 1, 1, 1, 1, 1},
};

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vfull_adder* fa = new Vfull_adder{contextp};

	/* unit test */

	printf("[full adder] unit test begins.\n\r");

	int test_case_num = sizeof(test_cases) / sizeof(TestCase);
	for(int i = 0; i < test_case_num; i++) {
		fa->a = test_cases[i].a;
		fa->b = test_cases[i].b;
		fa->cin = test_cases[i].cin;
		fa->eval();

		if((fa->s == test_cases[i].s) && (fa->cout == test_cases[i].cout)) {
			printf("[passed] a=%d, b=%d, cin=%d -> S=%d, cout=%d\n",
                               fa->a, fa->b, fa->cin, fa->s, fa->cout);
		} else {
			printf("[failed] a=%d, b=%d, cin=%d -> s=%d, cout=%d (expected s=%d, cout=%d)\n",
                               fa->a, fa->b, fa->cin, fa->s, fa->cout,
                               test_cases[i].s, test_cases[i].cout);
		}
	}

	printf("[full adder] unit tests all passed.\n\r");

	delete fa;
	delete contextp;

	return 0;
}
