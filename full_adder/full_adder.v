module full_adder(
	input A, 
	input B,
	input Cin,
	output S,
	output Cout
);

wire xor1_out, and1_out, and2_out;

xor xor1(xor1_out, A, B);
xor xor2(S, xor1_out, Cin);
and and1(and1_out, Cin, xor1_out);
and and2(and2_out, A, B);
or or1(Cout, and1_out, and2_out);

endmodule
