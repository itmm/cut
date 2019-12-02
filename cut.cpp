
#line 5 "cut.md"

	
#line 20 "cut.md"

	#include <iostream>
	
#line 60 "cut.md"

	
#line 114 "cut.md"

	#include <limits>
	using nli = std::numeric_limits<int>;
	int from { 0 }, to { nli::max() };

#line 61 "cut.md"
;
	bool should_print(int cur) {
		
#line 122 "cut.md"

	return cur >= from && cur <= to;

#line 63 "cut.md"
;
		return true;
	}

#line 81 "cut.md"

	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c',
		byte = 'b'
	} mode { Mode::delim };

#line 22 "cut.md"
;
	bool processed { false };
	void process(std::istream &in) {
		
#line 39 "cut.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 50 "cut.md"

	if (ch == '\n') {
		std::cout.put(ch);
		cur = 1;
		continue;
	}

#line 70 "cut.md"

	bool print { should_print(cur) };
	
#line 91 "cut.md"

	if (mode == Mode::delim && ch == delim) {
		++cur;
		if (print && should_print(cur)) {
			std::cout.put(ch);
		}
		continue;
	}

#line 72 "cut.md"
;
	if (print) {
		std::cout.put(ch);
	}
	
#line 103 "cut.md"

	if (mode == Mode::byte) {
		++cur;
	}
	if (mode == Mode::chr && ! (ch & 0x80)) {
		++cur;
	}

#line 76 "cut.md"
;

#line 43 "cut.md"
;
	}
	processed = true;

#line 25 "cut.md"
;
	}

#line 128 "cut.md"

	#include <fstream>

#line 172 "cut.md"

	void reset_list() {
		from = 0;
		to = nli::max();
	}

#line 6 "cut.md"
;
	int main(int argc, char *argv[]) {
		
#line 14 "cut.md"

	
#line 134 "cut.md"

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
					
#line 181 "cut.md"

	const char *s { arg + 2 };
	reset_list();
	
#line 197 "cut.md"

	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	to = from;

#line 184 "cut.md"
;
	if (*s == '-') {
		++s;
		
#line 206 "cut.md"

	to = 0;
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = nli::max();
	}

#line 187 "cut.md"
;
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		reset_list();
	}

#line 148 "cut.md"
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

#line 15 "cut.md"
;

#line 31 "cut.md"

	if (! processed) {
		process(std::cin);
	}

#line 8 "cut.md"
;
	}
