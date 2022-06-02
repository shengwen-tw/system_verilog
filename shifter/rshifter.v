module rshifter(data_in, data_out, bits);

parameter data_width = 8;
parameter shift_len = 3;

input [data_width-1:0] data_in;
input [shift_len-1:0] bits;
output [data_width-1:0] data_out;

wire [data_width-1:0] shifter1, shifter2;

mux2 m1(shifter1, bits[0], data_in,  {1'b0, data_in[data_width-1:1]});
mux2 m2(shifter2, bits[1], shifter1, {2'b0, shifter1[data_width-1:2]});
mux2 m3(data_out, bits[2], shifter2, {4'b0, shifter2[data_width-1:4]});

endmodule
