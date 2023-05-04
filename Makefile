run: build/movepoint
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib build/movepoint 2>&1 | tee -a log

.PHONY: install list default run run_g
