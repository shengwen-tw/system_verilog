/* 4-bits divider with iterative subtration method */
module divider_4_bits(a, b, quotient, remainder, div_by_zero);

input  [3:0] a;
input  [3:0] b;
output [3:0] quotient;
output [3:0] remainder;
output div_by_zero;

wire   [3:0] q;
wire   [3:0] r0, r1, r2, r3;

assign div_by_zero = (b == 4'b0000) ? 1'b1 : 1'b0;

divider_sub_stage s1({3'b000, a[3]},  b[3:0], q[3], r1);
divider_sub_stage s2({r1[2:0], a[2]}, b[3:0], q[2], r2);
divider_sub_stage s3({r2[2:0], a[1]}, b[3:0], q[1], r3);
divider_sub_stage s4({r3[2:0], a[0]}, b[3:0], q[0], remainder[3:0]);

assign quotient = ~q;

endmodule

module divider_sub_stage(a, b, q, r);

input  [3:0] a;
input  [3:0] b;
output q;
output [3:0] r;

wire   [3:0] xor_b; //1's complement
wire   [3:0] s;     //substraction result

wire carry_out;

/* 4-bits subtractor:
   different to the textbook, we use the cla with xor instead of
   using the full-subtractor, therefore the q will be inverted */
assign xor_b = b ^ 4'b1111;
cla_4bits cla(.a(a), .b(xor_b), .s(s), .cin(1'b1), .cout(carry_out));
assign q = ~carry_out;

/* 2-ways 4-bits mux */
mux2_4 m(.sel(q), .in1(a), .in0(s), .out(r));

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

/* 2-ways 4-bits mux */
module mux2_4(sel, in0, in1, out);

input  sel;
input  [3:0] in0;
input  [3:0] in1;
output [3:0] out;

assign out = sel ? in1 : in0;

endmodule
