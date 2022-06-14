CXX_SRC=top.cpp
VERILOG_SRC=syn_fifo.v
VERILOG_CFLAGS = -Wall -Wno-WIDTH -CFLAGS "-std=c++17" --cc --exe

build:
	verilator $(VERILOG_CFLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
