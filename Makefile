default: run

run-clang: build-clang/movepoint
	$(MAKE) -C build-clang/
	build-clang/movepoint 2>&1 | tee -a log

run: build/movepoint
	build/movepoint 2>&1 | tee -a log

build/movepoint:
	$(MAKE) -C build/ movepoint

.PHONY: build/movepoint install list default run run_g run-clang default

# vim: noet
