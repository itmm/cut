
#line 5 "cut.md"

	#include <fstream>
	#include <limits>
	using nli = std::numeric_limits<int>;

	int from { 0 }, to { nli::max() };

	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c', byte = 'b'
	} mode { Mode::delim };

	bool should_print(int cur) {
		return cur >= from && cur <= to;
	}

	void reset_list() {
		from = 0;
		to = nli::max();
	}

	
#line 40 "cut.md"

	#include <iostream>
	bool processed { false };
	void process(std::istream &in) {
		
#line 58 "cut.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 69 "cut.md"

	if (ch == '\n') {
		std::cout.put(ch);
		cur = 1;
		continue;
	}

#line 79 "cut.md"

	bool print { should_print(cur) };
	
#line 90 "cut.md"

	if (mode == Mode::delim && ch == delim) {
		++cur;
		if (print && should_print(cur)) {
			std::cout.put(ch);
		}
		continue;
	}

#line 81 "cut.md"
;
	if (print) {
		std::cout.put(ch);
	}
	
#line 102 "cut.md"

	if (mode == Mode::byte) {
		++cur;
	}
	if (mode == Mode::chr && ! (ch & 0x80)) {
		++cur;
	}

#line 85 "cut.md"
;

#line 62 "cut.md"
;
	}
	processed = true;

#line 44 "cut.md"
;
	}

#line 26 "cut.md"
;
	int main(int argc, char *argv[]) {
		
#line 34 "cut.md"

	
#line 113 "cut.md"

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
					
#line 151 "cut.md"

	const char *s { arg + 2 };
	reset_list();
	
#line 167 "cut.md"

	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	to = from;

#line 154 "cut.md"
;
	if (*s == '-') {
		++s;
		
#line 176 "cut.md"

	to = 0;
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = nli::max();
	}

#line 157 "cut.md"
;
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		reset_list();
	}

#line 127 "cut.md"
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
			if (in) {
				process(in);
			} else {
				std::cerr << "can't open " << arg << '\n';
				processed = true;
			}
		}
	}

#line 35 "cut.md"
;

#line 50 "cut.md"

	if (! processed) {
		process(std::cin);
	}

#line 28 "cut.md"
;
	}
