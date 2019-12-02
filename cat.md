# Implementation of `cat`

```
@Def(file: cat.cpp)
	@put(main prereqs);
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
@def(main prereqs)
	@put(parse args prereqs);
@end(main prereqs)
```

```
@add(main prereqs)
	#include <iostream>

	bool processed { false };
	void process(std::istream &in) {
		@put(process);
		processed = true;
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
	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}
@end(process)
```

```
@def(parse args)
	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		@put(parse arg);
	}
@end(parse args)
```

```
@def(parse args prereqs)
	#include <fstream>
@end(parse args prereqs)
```

```
@def(parse arg)
	if (! args_parsed && arg[0] == '-') {
		@put(parse option);
	} else {
		std::ifstream in { arg };
		if (in) {
			process(in);
		} else {
			std::cerr << "can't open " <<
				arg << '\n';
			processed = true;
		}
	}
@end(parse arg)
```

```
@def(parse option)
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
@end(parse option)
```

