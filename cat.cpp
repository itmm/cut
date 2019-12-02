
#line 4 "cat.md"

	#include <fstream>
	#include <iostream>
	#include <limits>

	bool processed { false };
	void process(std::istream &in) {
		
#line 27 "cat.md"

	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}
	processed = true;

#line 11 "cat.md"
;
	}

	int main(int argc, char *argv[]) {
		
#line 21 "cat.md"

	
#line 37 "cat.md"

	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			if (arg[1] == '\0') {
				process(std::cin);
			} else if (arg[1] == '-' && arg[2] == '\0') {
				args_parsed = true;
			} else {
				std::cerr << "ignoring unknown option " << arg << '\n';
			}
		} else {
			std::ifstream in { arg };
			process(in);
		}
	}

#line 22 "cat.md"
;

#line 58 "cat.md"

	if (! processed) {
		process(std::cin);
	}

#line 15 "cat.md"
;
	}
