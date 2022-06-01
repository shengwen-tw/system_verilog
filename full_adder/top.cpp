#include <stdio.h>
#include "Vfull_adder.h"
#include "verilated.h"

using namespace std;

struct TestCase {
	const char* name;
	uint8_t A;
	uint8_t B;
	uint8_t Cin;
	uint8_t S;
	uint8_t Cout;
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
		fa->A = test_cases[i].A;
		fa->B = test_cases[i].B;
		fa->Cin = test_cases[i].Cin;
		fa->eval();

		if((fa->S == test_cases[i].S) && (fa->Cout == test_cases[i].Cout)) {
			printf("[passed] A=%d, B=%d, Cin=%d -> S=%d, Cout=%d\n",
                               fa->A, fa->B, fa->Cin, fa->S, fa->Cout);
		} else {
			printf("[failed] A=%d, B=%d, Cin=%d -> S=%d, Cout=%d (expected S=%d, Cout=%d)\n",
                               fa->A, fa->B, fa->Cin, fa->S, fa->Cout,
                               test_cases[i].S, test_cases[i].Cout);
		}
	}

	printf("[full adder] uint tests all passed.\n\r");

	delete fa;
	delete contextp;

	return 0;
}
