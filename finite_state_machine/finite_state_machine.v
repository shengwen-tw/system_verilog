module finite_state_machine(clk, reset_n, in, out);

parameter IDLE = 2'b00;
parameter S0   = 2'b01;
parameter S1   = 2'b10;

input  clk;
input  reset_n;
input  in;
output reg out;

reg [1:0] curr_state;
reg [1:0] next_state;

/* state transition */
always @(posedge clk or negedge reset_n) begin
	if(~reset_n) curr_state <= IDLE;
	else         curr_state <= next_state;
end

/* next state logic */
always @(*) begin
	case (curr_state)
	IDLE: if(in) next_state = S0;
	      else   next_state = IDLE;
	S0:   if(in) next_state = S1;
              else   next_state = IDLE;
	S1:   if(in) next_state = S1;
              else   next_state = IDLE;
	default:     next_state = IDLE;
	endcase
end

/* output logic */
always @(*) begin
	case (curr_state)
	IDLE:    out = 1'b0;
	S0:      out = 1'b0;
	S1:      out = 1'b1;
	default: out = 1'b0;
	endcase
end

endmodule
