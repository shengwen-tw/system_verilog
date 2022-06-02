module multiplier(a, b, result);

parameter bit_width = 8;

input [bit_width-1:0] a;
input [bit_width-1:0] b;
output [bit_width-1:0] result;

/* shift accumulator */
wire [bit_width-1:0] t[bit_width];
wire [bit_width-1:0] shift_t[bit_width];
wire [bit_width-1:0] adder_stage1[4];
wire [bit_width-1:0] adder_stage2[2];
reg [6:0] carry_out;

genvar i;
generate
	for(i=0; i<bit_width; i=i+1) begin
		assign t[i] = (b[i] == 1) ? a : 8'h0;
	end
endgenerate

/* parallel shift accumulator: result = shift_t[0] + ... + shift_t[7]*/

/* shift[t] = t[i] << i */
assign shift_t[0] = t[0];
generate
	for(i = 1; i < bit_width; i++) begin
		lshifter ls(t[i], shift_t[i], i);
	end
endgenerate

//stage1 adder
ripple_carry_adder rca1_1(shift_t[0], shift_t[1], adder_stage1[0], carry_out[0]);
ripple_carry_adder rca1_2(shift_t[2], shift_t[3], adder_stage1[1], carry_out[1]);
ripple_carry_adder rca1_3(shift_t[4], shift_t[5], adder_stage1[2], carry_out[2]);
ripple_carry_adder rca1_4(shift_t[6], shift_t[7], adder_stage1[3], carry_out[3]);

//stage2 adder
ripple_carry_adder rca2_1(adder_stage1[0], adder_stage1[1], adder_stage2[0], carry_out[4]);
ripple_carry_adder rca2_2(adder_stage1[2], adder_stage1[3], adder_stage2[1], carry_out[5]);

//stage3 adder
ripple_carry_adder rca3_1(adder_stage2[0], adder_stage2[1], result, carry_out[6]);

/* alternatively: */
//assign result = t[0] + (t[1] << 1) + (t[2] << 2) +
//                (t[3] << 3) + (t[4] << 4) + (t[5] << 5) +
//                (t[6] << 6) + (t[7] << 7); 

endmodule
