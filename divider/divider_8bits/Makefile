CXX_SRC=top.cpp
VERILOG_SRC=divider.v 

VERILATOR_FLAGS=-top-module divider \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT -Wno-DECLFILENAME -Wno-UNUSED \
                --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
