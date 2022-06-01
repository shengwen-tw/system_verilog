build:
	@$(MAKE) -C ./pg-src/src -f Makefile
	mv ./pg-src/src/pg ./
	sh ./mkall.sh
	sh ./mkall_fcmp.sh

clean:
	rm -rf pg combo/ fcmp/ rdown/ rtne/ rtzero/ rup/


.PHONY: build clean
