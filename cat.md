# Implementation of `cat`

```
@Def(file: cat.cpp)
	#include <fstream>
	#include <iostream>
	#include <limits>

	bool processed { false };
	void process(std::istream &in) {
		@put(process);
	}

	int main(int argc, char *argv[]) {
		@put(main);
	}
@End(file: cat.cpp)
```

```
@def(main)
	@put(parse args);
@end(main)
```

```
@def(process)
	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}
	processed = true;
@end(process)
```

```
@def(parse args)
	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			if (arg[1] == '\0') {
				process(std::cin);
			} else if (arg[1] == '-' && arg[2] == '\0') {
				args_parsed = true;
			} else {
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
@add(main)
	if (! processed) {
		process(std::cin);
	}
@end(main)
```
