/* full adder for 1-bit addition */
module full_adder(a, b, cin, s, cout);
  
input a;
input b;
input cin;
output s;
output cout;

wire xor1_out, and1_out, and2_out;

xor xor1(xor1_out, a, b);
xor xor2(s, xor1_out, cin);
and and1(and1_out, cin, xor1_out);
and and2(and2_out, a, b);
or or1(cout, and1_out, and2_out);

endmodule

/* ripple carry adder for 8-bits addition */
module ripple_carry_adder(a, b, s, cin, cout);

parameter bit_width = 8;

input  [bit_width-1:0] a;
input  [bit_width-1:0] b;
input  cin;
output [bit_width-1:0] s = 0;
output cout = 0;

wire   [bit_width:0] c;
assign c[0] = cin;

genvar i;
generate
	for(i = 0; i < bit_width; i++) begin
		full_adder fa(a[i], b[i], c[i], s[i], c[i+1]);
	end
endgenerate

assign cout = c[bit_width];

endmodule
