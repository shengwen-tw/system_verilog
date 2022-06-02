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
