
#line 5 "cut.md"

	
#line 22 "cut.md"

	#include <iostream>
	
#line 69 "cut.md"

	
#line 126 "cut.md"

	#include <limits>
	using nli = std::numeric_limits<int>;
	int from { 0 }, to { nli::max() };

#line 70 "cut.md"
;
	bool should_print(int cur) {
		
#line 134 "cut.md"

	return cur >= from && cur <= to;

#line 72 "cut.md"
;
		return true;
	}

#line 92 "cut.md"

	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c',
		byte = 'b'
	} mode { Mode::delim };

#line 24 "cut.md"
;
	bool processed { false };
	void process(std::istream &in) {
		
#line 44 "cut.md"

	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		
#line 57 "cut.md"

	if (ch == '\n') {
		std::cout.put(ch);
		cur = 1;
		continue;
	}

#line 80 "cut.md"

	bool print { should_print(cur) };
	
#line 103 "cut.md"

	if (mode == Mode::delim && ch == delim) {
		++cur;
		if (print && should_print(cur)) {
			std::cout.put(ch);
		}
		continue;
	}

#line 82 "cut.md"
;
	if (print) {
		std::cout.put(ch);
	}
	
#line 115 "cut.md"

	if (mode == Mode::byte) {
		++cur;
	}
	if (mode == Mode::chr && ! (ch & 0x80)) {
		++cur;
	}

#line 86 "cut.md"
;

#line 48 "cut.md"
;
	}
	processed = true;

#line 27 "cut.md"
;
	}

#line 140 "cut.md"

	#include <fstream>

#line 221 "cut.md"

	void reset_list() {
		from = 0;
		to = nli::max();
	}

#line 6 "cut.md"
;
	int main(int argc, char *argv[]) {
		
#line 15 "cut.md"

	
#line 146 "cut.md"

	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			
#line 160 "cut.md"

	switch (arg[1]) {
		
#line 182 "cut.md"

	case '\0':
		process(std::cin);
		break;

#line 190 "cut.md"

	case 'd':
		delim = arg[2];
		break;

#line 198 "cut.md"

	case 'f': case 'b': case 'c': {
		mode = static_cast<Mode>(arg[1]);
		
#line 230 "cut.md"

	const char *s { arg + 2 };
	reset_list();
	
#line 248 "cut.md"

	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	to = from;

#line 233 "cut.md"
;
	if (*s == '-') {
		++s;
		
#line 257 "cut.md"

	to = 0;
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = nli::max();
	}

#line 236 "cut.md"
;
	}
	if (*s) {
		std::cerr <<
			"ignoring wrong list " <<
			arg << '\n';
		reset_list();
	}

#line 201 "cut.md"
;
		break;
	}

#line 162 "cut.md"
;
		default:
			
#line 173 "cut.md"

	if (arg[1] == '-' && arg[2] == '\0') {
		args_parsed = true;
		break;
	}

#line 164 "cut.md"
;
			std::cerr <<
				"ignoring unknown"
				" option " << arg << '\n';
	}

#line 151 "cut.md"
;
		} else {
			
#line 208 "cut.md"

	std::ifstream in { arg };
	if (in) {
		process(in);
	} else {
		std::cerr << "can't open " <<
			arg << '\n';
		processed = true;
	}

#line 153 "cut.md"
;
		}
	}

#line 16 "cut.md"
;

#line 35 "cut.md"

	if (! processed) {
		process(std::cin);
	}

#line 8 "cut.md"
;
	}
