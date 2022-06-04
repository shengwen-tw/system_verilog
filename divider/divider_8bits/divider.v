/* 8-bits divider with iterative subtration method */
module divider(a, b, quotient, remainder, div_by_zero);

parameter bit_width = 8;

input  [bit_width-1:0] a;
input  [bit_width-1:0] b;
output [bit_width-1:0] quotient;
output [bit_width-1:0] remainder;
output div_by_zero;

wire   [bit_width-1:0] q;
wire   [bit_width-1:0] r[bit_width+1];

assign div_by_zero = (b == {bit_width{1'b0}}) ? 1'b1 : 1'b0;
assign r[0] = {bit_width{1'b0}};

genvar i;
generate
	for(i=0; i < bit_width; i=i+1) begin
		divider_sub_stage s_i(.a({r[i][bit_width-2:0], a[bit_width-i-1]}),
	                              .b(b[bit_width-1:0]),
	                              .q(q[bit_width-i-1]),
	                              .r(r[i+1]));
	end
endgenerate

assign remainder = r[bit_width];
assign quotient = ~q;

endmodule

module divider_sub_stage(a, b, q, r);

parameter bit_width = 8;

input  [bit_width-1:0] a;
input  [bit_width-1:0] b;
output q;
output [bit_width-1:0] r;

wire   [bit_width-1:0] xor_b; //1's complement
wire   [bit_width-1:0] s;     //subtraction result
wire   [2:0] c;

/* 8-bits subtractor:
   different to the textbook, we use the cla with xor instead of
   using the full-subtractor, therefore the q will be inverted */
assign xor_b = b ^ {bit_width{1'b1}};
assign c[0] = 1'b1;

cla_4bits cla4_1(a[3:0], xor_b[3:0], s[3:0], c[0], c[1]);
cla_4bits cla4_2(a[7:4], xor_b[7:4], s[7:4], c[1], c[2]);

assign q = ~c[2];

/* 2-ways 8-bits mux */
mux m(.sel(q), .in1(a), .in0(s), .out(r));

endmodule

/* 4-bits carry-lookahead adder */
module cla_4bits(a, b, s, cin, cout);

input  [3:0] a;
input  [3:0] b;
output [3:0] s;
input  cin;
output cout;

wire [4:0] c;
wire [3:0] g; //generate
wire [3:0] p; //propagate

assign g = a & b;
assign p = a ^ b;
assign c[0] = cin;
assign c[1] = g[0] | (p[0] & c[0]);
assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & c[0]);
assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) |
              (p[2] & p[1] & p[0] & c[0]);
assign c[4] = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) |
              (p[3] & p[2] & p[1] & g[0]) | (p[3] & p[2] & p[1] & p[0] & c[0]);

assign s = p ^ c[3:0];

assign cout = c[4];

endmodule

/* 2-ways 8-bits mux */
module mux(sel, in0, in1, out);

parameter bit_width = 8;

input  sel;
input  [bit_width-1:0] in0;
input  [bit_width-1:0] in1;
output [bit_width-1:0] out;

assign out = sel ? in1 : in0;

endmodule
