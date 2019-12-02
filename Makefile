MDs := $(shell hx-srcs.sh)
SRCs := $(shell hx-files.sh $(MDs))
EXEs := $(SRCs:.cpp=)

.PHONY: all tests clean

all: hx-run

$(SRCs): hx-run

hx-run: $(MDs)
	@echo HX
	@hx
	@date >hx-run
	@make --no-print-directory tests

clean:
	@echo RM
	@rm -f $(SRCs) $(EXEs)

tests: $(EXEs)
	@echo TESTS
	@./tests/run.sh

