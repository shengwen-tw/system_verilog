module syn_fifo(clk, rst_n, wr_en, rd_en, wr_data, rd_data, fifo_full, fifo_empty);

parameter data_width = 8;
parameter depth = 8;

input  clk;
input  rst_n;
input  wr_en;
input  rd_en;
input  [data_width-1:0] wr_data;
output reg [data_width-1:0] rd_data;
output fifo_full;
output fifo_empty;

reg [data_width-1:0] fifo[depth];

reg [$clog2(depth):0] cnt = {$clog2(depth)+1{1'b0}};
reg [$clog2(depth)-1:0] wr_ptr = {$clog2(depth){1'b0}};
reg [$clog2(depth)-1:0] rd_ptr = {$clog2(depth){1'b0}};

always @(posedge clk or negedge rst_n) begin
	if(!rst_n) begin
		cnt <= 0;
		rd_data <= 0;
		wr_ptr <= 0;
		rd_ptr <= 0;
	end
	else begin
		/*write data */
		if (wr_en) begin
			fifo[wr_ptr] <= wr_data;
			if(wr_ptr == (depth-1))
				wr_ptr <= 0;
			else
				wr_ptr <= wr_ptr + 1;
		end

		/* read data */
		if (rd_en) begin
			rd_data <= fifo[rd_ptr];
			if(rd_ptr == (depth-1))
				rd_ptr <= 0;
			else
				rd_ptr <= rd_ptr + 1;
		end

		/* counter update */
		if(wr_en && !rd_en)
			cnt <= cnt + 1;
		else if(!wr_en && rd_en)
			cnt <= cnt - 1;
	end
end

assign fifo_full = (cnt == depth) ? 1 : 0;
assign fifo_empty = (cnt == 0) ? 1 : 0;

endmodule
