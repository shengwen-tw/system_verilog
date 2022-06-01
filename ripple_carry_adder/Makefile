CXX_SRC=top.cpp
VERILOG_SRC=full_adder.v ripple_carry_adder.v 

VERILATOR_FLAGS=-top-module ripple_carry_adder \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
