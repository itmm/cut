.PHONY: all tests clean

all: tests

cut.cpp: index.md
	@echo HX
	@hx

clean:
	@echo RM
	@rm -f cut cut.cpp

tests: cut
	@echo TESTS
	@mkdir -p build
