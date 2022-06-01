#include <stdio.h>
#include <limits.h>
#include "Vfpu.h"
#include "verilated.h"

using namespace std;

enum {
	FPU_ADD = 0,
	FPU_SUB = 1,
	FPU_MUL = 2,
	FPU_DIV = 3
} FPU_OP;

enum {
	FPU_ROUND_NEAR_EAST_EVEN = 0,
	FPU_ROUND_ZERO = 1,
	FPU_ROUND_PLUS_INF = 2,
	FPU_ROUND_NEG_INF = 3	
} FPU_RoundingMode;

void fpu_setup(Vfpu* fpu, uint8_t operation, float op_a, float op_b, uint8_t round_mode)
{
	fpu->fpu_op = operation;
	memcpy(&fpu->opa, &op_a, sizeof(float));
	memcpy(&fpu->opb, &op_b, sizeof(float));
	fpu->rmode = round_mode;
}

void fpu_print_result(Vfpu* fpu)
{
	char op;
	switch(fpu->fpu_op) {
	case FPU_ADD:
		op = '+';
		break;
	case FPU_SUB:
		op = '-';
		break;
	case FPU_MUL:
		op = '*';
		break;
	case FPU_DIV:
		op = '/';
		break;
	}

	float fpu_op_a, fpu_op_b, fpu_out;
	memcpy(&fpu_op_a, &fpu->opa, sizeof(float));
	memcpy(&fpu_op_b, &fpu->opb, sizeof(float));
	memcpy(&fpu_out, &fpu->out, sizeof(float));
	printf("[FPU] %f %c %f = %f\n", fpu_op_a, op, fpu_op_b, fpu_out);
}

void fpu_check_flags(Vfpu* fpu)
{
	if(fpu->zero == 1) printf("[FPU] zero flags is set.\n");
	if(fpu->snan == 1) printf("[FPU] snan flags is set.\n");
	if(fpu->qnan == 1) printf("[FPU] qnan flags is set.\n");
	if(fpu->inf == 1) printf("[FPU] inf flags is set.\n");
	if(fpu->ine == 1) printf("[FPU] ine flags is set.\n");
	if(fpu->div_by_zero == 1) printf("[FPU] div_by_zero flags is set.\n");
}

void fpu_generate_clk(Vfpu* fpu, int cycles)
{
	for(int i = 0; i < (cycles * 2); i++) {
		fpu->clk = !fpu->clk;
		fpu->eval();
	}
}

int main(int argc, char** argv, char** env)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);

	/* reset FPU state */
	Vfpu* fpu = new Vfpu{contextp};
	fpu->clk = 1; 
	fpu->eval();

	/* FPU requires 4 clock cycles to deliver the result */

	/* test float addition */
	fpu_setup(fpu, FPU_ADD, 1.5f, 2.5f, FPU_ROUND_NEAR_EAST_EVEN);
	fpu_generate_clk(fpu, 4);
	fpu_print_result(fpu);
	fpu_check_flags(fpu);

	/* test float substraction */
	fpu_setup(fpu, FPU_SUB, 1.5f, 2.5f, FPU_ROUND_NEAR_EAST_EVEN);
	fpu_generate_clk(fpu, 4);
	fpu_print_result(fpu);
	fpu_check_flags(fpu);

	/* test float multiplication */
	fpu_setup(fpu, FPU_MUL, 1.5f, 1.5f, FPU_ROUND_NEAR_EAST_EVEN);
	fpu_generate_clk(fpu, 4);
	fpu_print_result(fpu);
	fpu_check_flags(fpu);

	/* test float multiplication */
	fpu_setup(fpu, FPU_DIV, 1.30f, 0.5f, FPU_ROUND_NEAR_EAST_EVEN);
	fpu_generate_clk(fpu, 4);
	fpu_print_result(fpu);
	fpu_check_flags(fpu);

	/* test float divide by zero */
	fpu_setup(fpu, FPU_DIV, 1.30f, 0.0f, FPU_ROUND_NEAR_EAST_EVEN);
	fpu_generate_clk(fpu, 4);
	fpu_print_result(fpu);
	fpu_check_flags(fpu);


	delete fpu;
	delete contextp;

	return 0;
}

