CXX_SRC=top.cpp
VERILOG_SRC=carry_lookahead_adder.v 

VERILATOR_FLAGS=-top-module carry_lookahead_adder \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT -Wno-DECLFILENAME \
                --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
