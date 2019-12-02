
#line 4 "cat.md"

	
#line 19 "cat.md"

	
#line 65 "cat.md"

	#include <fstream>

#line 20 "cat.md"
;

#line 25 "cat.md"

	#include <iostream>

	bool processed { false };
	void process(std::istream &in) {
		
#line 46 "cat.md"

	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}

#line 30 "cat.md"
;
		processed = true;
	}


#line 5 "cat.md"
;
	int main(int argc, char *argv[]) {
		
#line 13 "cat.md"

	
#line 55 "cat.md"

	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		
#line 71 "cat.md"

	if (! args_parsed && arg[0] == '-') {
		
#line 88 "cat.md"

	if (arg[1] == '\0') {
		process(std::cin);
	} else if (arg[1] == '-' &&
		arg[2] == '\0'
	) {
		args_parsed = true;
	} else {
		std::cerr << "ignoring unknown"
			" option " << arg << '\n';
	}

#line 73 "cat.md"
;
	} else {
		std::ifstream in { arg };
		if (in) {
			process(in);
		} else {
			std::cerr << "can't open " <<
				arg << '\n';
			processed = true;
		}
	}

#line 59 "cat.md"
;
	}

#line 14 "cat.md"
;

#line 38 "cat.md"

	if (! processed) {
		process(std::cin);
	}

#line 7 "cat.md"
;
	}
