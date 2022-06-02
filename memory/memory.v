module memory(clk, reset, addr, data, cs, rw);

parameter data_width = 8;
parameter addr_width = 8;
parameter mem_size = 256;

input clk;
input reset;
input [addr_width-1:0] addr;
inout [data_width-1:0] data;
input cs; //chip selection
input rw; //read/write mode

reg [data_width-1:0] mem [mem_size];
reg [data_width-1:0] buffer;

always @(posedge clk) begin
	if(reset == 1) begin
		integer i;
		for(i=0; i<mem_size; i=i+1) begin
			assign mem[i] = 8'h0;
		end
	end
	else if(cs == 1 && rw == 1) begin //rw == 0: write mode
		mem[addr] <= data;
		buffer <= 8'h0;
	end
	else if(cs == 1 && rw == 0) begin //rw == 1: read mode
		buffer <= mem[addr];
	end
end

assign data = buffer;

endmodule
