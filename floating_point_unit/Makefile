IVERILOG_VVP=fpu.vvp

VERILOG_SRC=./verilog/ \
	./verilog/except.v \
	./verilog/fpu.v \
	./verilog/post_norm.v \
	./verilog/pre_norm_fmul.v \
	./verilog/pre_norm.v \
	./verilog/primitives.v \
	./test_bench/test_top.v

build: $(VERILOG_SRC)
	iverilog $^  -o $(IVERILOG_VVP)

run: $(IVERILOG_VVP)
	vvp $^

clean:
	rm -rf $(IVERILOG_VVP)

.PHONY: build run clean
