module subtractor(a, b, s, cout);

parameter bit_width = 8;

input  [bit_width-1:0] a;
input  [bit_width-1:0] b;
output [bit_width-1:0] s;
output cout;

wire   [bit_width-1:0] xor_b;

assign xor_b = b ^ {bit_width{1'b1}};

carry_lookahead_adder cla(a, xor_b, s, 1'b1, cout);

endmodule
