CXX_SRC=top.cpp
VERILOG_SRC=gray_code.v
VERILOG_CFLAGS = -Wall -Wno-DECLFILENAME -Wno-UNOPTFLAT -CFLAGS "-std=c++17" --cc --exe

build:
	verilator $(VERILOG_CFLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
