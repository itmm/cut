
#line 4 "index.md"

	#include <cassert>
	#include <fstream>
	#include <iostream>
	#include <limits>

	int from { 0 }, to { 0 };
	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c', byte = 'b'
	} mode { Mode::delim };
	bool processed { false };

	void process(std::istream &in) {
		
#line 34 "index.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 45 "index.md"

	if (ch == '\n') {
		std::cout.put(ch);
		cur = 1;
		continue;
	}
	if (mode == Mode::delim && ch == delim) {
		++cur;
		if (cur > from && cur <= to) {
			std::cout.put(ch);
		}
		continue;
	}
	if (cur >= from  && cur <= to) {
		std::cout.put(ch);
	}
	if (mode == Mode::byte) {
		++cur;
	}
	if (mode == Mode::chr && ! (ch & 0x80)) {
		++cur;
	}

#line 38 "index.md"
;
	}
	processed = true;

#line 18 "index.md"
;
	}

	int main(int argc, char *argv[]) {
		
#line 28 "index.md"

	
#line 71 "index.md"

	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			switch (arg[1]) {
				case '\0':
					process(std::cin);
					break;
				case 'd':
					delim = arg[2];
					break;
				case 'f': case 'b': case 'c': {
					mode = static_cast<Mode>(arg[1]);
					
#line 104 "index.md"

	const char *s { arg + 2 };
	from = to = 0;
	
#line 120 "index.md"

	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}

#line 107 "index.md"
;
	if (*s == '-') {
		++s;
		
#line 128 "index.md"

	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = std::numeric_limits<int>::max();
	}

#line 110 "index.md"
;
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		from = to = 0;
	}

#line 85 "index.md"
;
					break;
				}
				default:
					if (arg[1] == '-' && arg[2] == '\0') {
						args_parsed = true;
						break;
					}
					std::cerr << "ignoring unknown option " << arg << '\n';
			}
		} else {
			std::ifstream in { arg };
			process(in);
		}
	}

#line 29 "index.md"
;

#line 140 "index.md"

	if (! processed) {
		process(std::cin);
	}

#line 22 "index.md"
;
	}
