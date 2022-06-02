CXX_SRC=top.cpp
VERILOG_SRC=lshifter.v
VERILATOR_FLAGS = -Wall -Wno-DECLFILENAME -CFLAGS "-std=c++17" --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
