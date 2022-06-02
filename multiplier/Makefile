CXX_SRC=top.cpp
VERILOG_SRC=multiplier.v mux2.v lshifter.v full_adder.v ripple_carry_adder.v
VERILATOR_FLAGS=-top-module multiplier \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNUSED -Wno-UNOPTFLAT \
		--cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
