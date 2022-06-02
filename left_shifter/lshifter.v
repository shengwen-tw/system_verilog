/* left shifter */
module lshifter(data_in, data_out, bits);

parameter data_width = 8;
parameter shift_len = 3;

input [data_width-1:0] data_in;
input [shift_len-1:0] bits;
output [data_width-1:0] data_out;

wire [data_width-1:0] shifter1, shifter2;

mux2 m1(shifter1, bits[0], data_in,  {data_in[data_width-2:0], 1'b0});
mux2 m2(shifter2, bits[1], shifter1, {shifter1[data_width-3:0], 2'b0});
mux2 m3(data_out, bits[2], shifter2, {shifter2[data_width-5:0], 4'b0});

endmodule

/* 8-bits 2-ways mux */
module mux2(out, select, in0, in1);

parameter data_width = 8;

output [data_width-1:0] out;
input select;
input [data_width-1:0] in0;
input [data_width-1:0] in1;

assign out = select ? in1 : in0;

endmodule
