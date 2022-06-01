CXX_SRC=top.cpp
VERILOG_SRC=full_adder.v

build:
	verilator -Wall -CFLAGS "-std=c++17" --cc --exe --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
