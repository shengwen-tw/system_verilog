CXX_SRC=top.cpp
VERILOG_SRC=hello_world.v

build:
	verilator -Wall --cc --exe --build $(CXX_SRC) $(VERILOG_SRC)

clean:
	rm -rf obj_dir 

.PHONY: build clean
