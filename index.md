# Implementation of `cut`

```
@Def(file: cut.cpp)
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
		@put(process);
	}

	int main(int argc, char *argv[]) {
		@put(main);
	}
@End(file: cut.cpp)
```

```
@def(main)
	@put(parse args);
@end(main)
```

```
@def(process)
	int cur { 1 };
	char ch;
	while (in.get(ch)) {
		@put(process ch);
	}
	processed = true;
@end(process)
```

```
@def(process ch)
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
@end(process ch)
```

```
@def(parse args)
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
					@put(parse list);
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
@end(parse args)
```

```
@def(parse list)
	const char *s { arg + 2 };
	from = to = 0;
	@put(parse from);
	if (*s == '-') {
		++s;
		@put(parse to);
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		from = to = 0;
	}
@end(parse list)
```

```
@def(parse from)
	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
@end(parse from)
```

```
@def(parse to)
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = std::numeric_limits<int>::max();
	}
@end(parse to)
```

```
@add(main)
	if (! processed) {
		process(std::cin);
	}
@end(main)
```