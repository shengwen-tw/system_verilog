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

/* 8-bits carry-lookahead adder */
module carry_lookahead_adder(a, b, s, cout);

input  [7:0] a;
input  [7:0] b;
output [7:0] s;
output cout;

wire c[2:0];

assign c[0] = 1'b0;

/* cascade 2 4-bits cla with ripple carry adder scheme */
cla_4bits cla4_1(a[3:0], b[3:0], s[3:0], c[0], c[1]);
cla_4bits cla4_2(a[7:4], b[7:4], s[7:4], c[1], c[2]);

assign cout = c[2];

endmodule
