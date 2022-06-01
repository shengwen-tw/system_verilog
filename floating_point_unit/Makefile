IVERILOG_VVP=fpu.vvp

VERILOG_SRC=./verilog/except.v \
	./verilog/fpu.v \
	./verilog/pre_norm_fmul.v \
	./verilog/pre_norm.v \
	./verilog/primitives.v \
	./verilog/post_norm.v


CXX_SRC=top.cpp
VERILATOR_FLAGS=-top-module fpu \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT -Wno-ASSIGNDLY \
		-Wno-EOFNEWLINE -Wno-IMPLICIT \
		-Wno-DECLFILENAME -Wno-UNUSED \
		-Wno-WIDTH -Wno-CASEX \
		--cc --exe

build: build_verilator build_icarus

#to run the simulaion example
build_verilator:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

#to run unit test
build_icarus: $(VERILOG_SRC) ./test_bench/test_top.v
	iverilog $^  -o $(IVERILOG_VVP)

#to generate the dataset for running the unit test
gen_dataset:
	@$(MAKE) -C test_vectors -f Makefile

#to run the unit test
run_icarus: $(IVERILOG_VVP)
	vvp $^

clean:
	rm -rf $(IVERILOG_VVP)

.PHONY: build verilator build_icarus run_icarus clean unit_test
