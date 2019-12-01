.PHONY: all clean

all: cut

cut.cpp: index.md
	@echo HX
	@hx

clean:
	@echo RM
	@rm -f cut cut.cpp
