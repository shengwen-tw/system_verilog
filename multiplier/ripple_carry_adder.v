module ripple_carry_adder(A, B, S, Cout);

parameter bit_width = 8;

input  [bit_width-1:0] A;
input  [bit_width-1:0] B;
output [bit_width-1:0] S = 0;
output Cout = 0;

wire   [bit_width:0] Cin;
assign Cin[0] = 1'b0;

genvar i;
generate
	for(i = 0; i < bit_width; i++) begin
		full_adder fa2(A[i], B[i], Cin[i], S[i], Cin[i+1]);
	end
endgenerate

assign Cout = Cin[bit_width];

endmodule
