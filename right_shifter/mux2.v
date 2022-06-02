module mux2(out, select, in0, in1);

parameter data_width = 8;

output [data_width-1:0] out;
input select;
input [data_width-1:0] in0;
input [data_width-1:0] in1;

assign out = select ? in1 : in0;

endmodule
