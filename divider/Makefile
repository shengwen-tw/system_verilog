CXX_SRC=top.cpp
VERILOG_SRC=divider_4_bits.v 

VERILATOR_FLAGS=-top-module divider_4_bits \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT -Wno-DECLFILENAME -Wno-UNUSED \
                --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
