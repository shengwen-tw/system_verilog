## Prerequisites

```
sudo apt install iverilog libgoogle-perftools-dev numactl perl-doc \
                 libfl2 libfl-dev zlibc zlib1g zlib1g-dev

git clone https://github.com/verilator/verilator

unset VERILATOR_ROOT
cd verilator
git checkout stable
git pull origin stable

autoconf
./configure
make -j `nproc`
sudo make install
```
