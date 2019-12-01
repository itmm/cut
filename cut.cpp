
#line 4 "index.md"

	#include <cassert>
	#include <fstream>
	#include <iostream>
	#include <limits>

	int from { 0 }, to { 0 };
	char delim { '\t' };
	enum class Mode {
		delim, chr, byte
	} mode { Mode::delim };
	bool processed { false };

	void process(std::istream &in) {
		
#line 38 "index.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 49 "index.md"

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

#line 42 "index.md"
;
	}
	processed = true;

#line 18 "index.md"
;
	}

	void parse_list(const char *src) {
		
#line 75 "index.md"

	const char *s { src };
	from = to = 0;
	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	if (*s == '-') {
		++s;
		if (isdigit(*s)) {
			for (; isdigit(*s); ++s) {
				to = to * 10 + (*s - '0');
			}
		} else {
			to = std::numeric_limits<int>::max();
		}
	}
	if (*s) {
		std::cerr << "wrong list argument " << src << '\n';
		from = to = 0;
	}

#line 22 "index.md"
;
	}

	int main(int argc, char *argv[]) {
		
#line 32 "index.md"

	
#line 99 "index.md"

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
				case 'f':
					mode = Mode::delim;
					parse_list(arg + 2);
					break;
				case 'b':
					mode = Mode::byte;
					parse_list(arg + 2);
					break;
				case 'c':
					mode = Mode::chr;
					parse_list(arg + 2);
					break;
				default:
					if (arg[1] == '-' && arg[2] == '\0') {
						args_parsed = true;
						break;
					}
					std::cerr << "ignoring option " << arg << '\n';
			}
		} else {
			std::ifstream in { arg };
			process(in);
		}
	}
	if (! processed) {
		process(std::cin);
	}

#line 33 "index.md"
;

#line 26 "index.md"
;
	}
