module gray_code(mode, data_in, data_out);
	parameter bit_width = 8;

	input  mode; //input  mode; //0: binary to gray code, 1: gray code to binray
	input  [bit_width-1:0] data_in;
	output [bit_width-1:0] data_out;
	wire   [bit_width-1:0] b2g_result;
	wire   [bit_width-1:0] g2b_result;

	bin2gray b2g(data_in, b2g_result);
	gray2bin g2b(data_in, g2b_result);

	assign data_out = (mode == 0) ? b2g_result : g2b_result;
endmodule

module bin2gray(bin, gray);
	parameter bit_width = 8;

	input  [bit_width-1:0] bin;
	output [bit_width-1:0] gray;

	genvar i;
	generate
		assign gray[bit_width-1] = bin[bit_width-1];
		for(i=0; i<=(bit_width-2); i=i+1) begin
			assign gray[i] = bin[i+1] ^ bin[i];
		end
	endgenerate
endmodule

module gray2bin(gray, bin);
	parameter bit_width = 8;

	input  [bit_width-1:0] gray;
	output [bit_width-1:0] bin;

	genvar i;
	generate
		assign bin[bit_width-1] = gray[bit_width-1];
		for(i=(bit_width-2); i>=0; i=i-1) begin
			assign bin[i] = bin[i+1] ^ gray[i];
		end
	endgenerate
endmodule
