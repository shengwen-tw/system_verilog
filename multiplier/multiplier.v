module multiplier(a, b, result);
parameter bit_width = 8;

input [bit_width-1:0] a;
input [bit_width-1:0] b;
output [bit_width-1:0] result;

wire [bit_width-1:0] t[bit_width];

genvar i;
generate
	for(i=0; i<bit_width; i=i+1) begin
		assign t[i] = (b[i] == 1) ? a : 8'h0;
	end
endgenerate

//TODO: implement the details
assign result = t[0] + (t[1] << 1) + (t[2] << 2) +
                (t[3] << 3) + (t[4] << 4) + (t[5] << 5) +
                (t[6] << 6) + (t[7] << 7); 

endmodule
