
#line 5 "cat.md"

	
#line 22 "cat.md"

	
#line 108 "cat.md"

	#include <fstream>

#line 23 "cat.md"
;

#line 29 "cat.md"

	#include <iostream>

#line 36 "cat.md"

	bool processed { false };

#line 45 "cat.md"

	void process(std::istream &in) {
		
#line 67 "cat.md"

	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}

#line 47 "cat.md"
;
		processed = true;
	}


#line 6 "cat.md"
;
	int main(int argc, char *argv[]) {
		
#line 15 "cat.md"

	
#line 77 "cat.md"

	bool args_parsed { false };

#line 87 "cat.md"

	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		
#line 97 "cat.md"

	if (! args_parsed && arg[0] == '-') {
		
#line 132 "cat.md"

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

#line 99 "cat.md"
;
	} else {
		
#line 115 "cat.md"

	std::ifstream in { arg };
	if (in) {
		process(in);
	} else {
		std::cerr << "can't open " <<
			arg << '\n';
		processed = true;
	}

#line 101 "cat.md"
;
	}

#line 90 "cat.md"
;
	}

#line 16 "cat.md"
;

#line 57 "cat.md"

	if (! processed) {
		process(std::cin);
	}

#line 8 "cat.md"
;
	}
