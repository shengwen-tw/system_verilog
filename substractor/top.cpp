#include <stdio.h>
#include <limits.h>
#include "Vsubstractor.h"
#include "verilated.h"

using namespace std;

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vsubstractor* sub = new Vsubstractor{contextp};

	/* unit test */

	printf("[substractor] unit test begins.\n\r");

	for(int i = CHAR_MIN; i <= CHAR_MAX; i++) {
		for(int j = CHAR_MIN; j <= CHAR_MAX; j++) {
			sub->a = i;
			sub->b = j;
			sub->eval();

			int8_t result;
			memcpy(&result, &sub->s, sizeof(int8_t));

			int8_t true_ans = i - j;
			if(result == true_ans) {
				printf("[passed] %d - %d = %d\n", i, j, result);
			} else {
				printf("[failed] %d - %d = %d (expect s=%d)\n", i, j, result, true_ans);

				delete sub;
				delete contextp;

				return 0;
			}
		}
	}

	printf("[substractor] unit tests all passed.\n\r");

	delete sub;
	delete contextp;

	return 0;
}

