
#line 4 "cut.md"

	#include <fstream>
	#include <iostream>
	#include <limits>
	using nli = std::numeric_limits<int>;

	int from, to;

	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c', byte = 'b'
	} mode { Mode::delim };
	bool processed { false };

	void process(std::istream &in) {
		
#line 41 "cut.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 52 "cut.md"

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

#line 45 "cut.md"
;
	}
	processed = true;

#line 19 "cut.md"
;
	}

	void reset_list() {
		from = 0;
		to = nli::max();
	}

	int main(int argc, char *argv[]) {
		
#line 34 "cut.md"

	reset_list();
	
#line 78 "cut.md"

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
					
#line 116 "cut.md"

	const char *s { arg + 2 };
	reset_list();
	
#line 132 "cut.md"

	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	to = from;

#line 119 "cut.md"
;
	if (*s == '-') {
		++s;
		
#line 141 "cut.md"

	to = 0;
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = nli::max();
	}

#line 122 "cut.md"
;
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		reset_list();
	}

#line 92 "cut.md"
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

#line 36 "cut.md"
;

#line 154 "cut.md"

	if (! processed) {
		process(std::cin);
	}

#line 28 "cut.md"
;
	}
