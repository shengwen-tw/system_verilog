#include <stdio.h>
#include <limits.h>
#include "Vgray_code.h"
#include "verilated.h"

#define BIN_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BIN(byte)  \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0') 

using namespace std;

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	Vgray_code* gc = new Vgray_code{contextp};

	uint8_t gray_code;

	printf("[unit test start]\n");

	/* convert binray to gray code */
	gc->mode = 0;
	for(uint8_t i = 0; i < UCHAR_MAX; i++) {
		/* convert binray to gray code */
		gc->mode = 0;
		gc->data_in = i;
		gc->eval();

		gray_code = gc->data_out;

		printf("[binary to gray code] decimal=%d, binray=" BIN_PATTERN ", gray code=" BIN_PATTERN "\n",
                       i, BYTE_TO_BIN(gc->data_in), BYTE_TO_BIN(gc->data_out));

		/* convert gray code back to binary */
		gc->mode = 1;
		gc->data_in = gray_code;
		gc->eval();

		printf("[gray code to binray] decimal=%d, binray=" BIN_PATTERN ", gray code=" BIN_PATTERN "\n",
                       gc->data_out, BYTE_TO_BIN(gc->data_out), BYTE_TO_BIN(gc->data_in));

		if(i != gc->data_out) {
			printf("[error] unexpected conversion result.\n");
			delete gc;
			delete contextp;
			return 0;
		}
	}

	printf("[unit test all complete]\n");

	delete gc;
	delete contextp;

	return 0;
}
