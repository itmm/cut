# Implementation of `cut`
* printing only special fields of each line

```
@Def(file: cut.cpp)
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

	@put(main prereqs);
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
@def(main prereqs)
	#include <iostream>
	bool processed { false };
	void process(std::istream &in) {
		@put(process);
	}
@end(main prereqs)
```

```
@add(main)
	if (! processed) {
		process(std::cin);
	}
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
@end(process ch)
```

```
@add(process ch)
	bool print { should_print(cur) };
	@put(process pre);
	if (print) {
		std::cout.put(ch);
	}
	@put(process post);
@end(process ch)
```

```
@def(process pre)
	if (mode == Mode::delim && ch == delim) {
		++cur;
		if (print && should_print(cur)) {
			std::cout.put(ch);
		}
		continue;
	}
@end(process pre)
```

```
@def(process post)
	if (mode == Mode::byte) {
		++cur;
	}
	if (mode == Mode::chr && ! (ch & 0x80)) {
		++cur;
	}
@end(process post)
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
			if (in) {
				process(in);
			} else {
				std::cerr << "can't open " << arg << '\n';
				processed = true;
			}
		}
	}
@end(parse args)
```

```
@def(parse list)
	const char *s { arg + 2 };
	reset_list();
	@put(parse from);
	if (*s == '-') {
		++s;
		@put(parse to);
	}
	if (*s) {
		std::cerr << "ignoring wrong list " << arg << '\n';
		reset_list();
	}
@end(parse list)
```

```
@def(parse from)
	for (; isdigit(*s); ++s) {
		from = from * 10 + (*s - '0');
	}
	to = from;
@end(parse from)
```

```
@def(parse to)
	to = 0;
	if (isdigit(*s)) {
		for (; isdigit(*s); ++s) {
			to = to * 10 + (*s - '0');
		}
	} else {
		to = nli::max();
	}
@end(parse to)
```

