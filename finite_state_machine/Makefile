CXX_SRC=top.cpp
VERILOG_SRC=finite_state_machine.v 

VCD=wave.vcd

VERILATOR_FLAGS=-top-module finite_state_machine \
		-CFLAGS "-std=c++17" \
		-Wall -Wno-UNOPTFLAT -Wno-DECLFILENAME \
                --trace --cc --exe

build:
	verilator $(VERILATOR_FLAGS) --build $(CXX_SRC) $(VERILOG_SRC)

plot: $(VCD)
	gtkwave $^

clean:
	rm -rf obj_dir $(VCD)

.PHONY: build plot clean
