# Implementation of `cut`
* printing only special fields of each line

```
@Def(file: cut.cpp)
	@put(main prereqs);
	int main(int argc, char *argv[]) {
		@put(main);
	}
@End(file: cut.cpp)
```
* starting with a `@f(main)` function

```
@def(main)
	@put(parse args);
@end(main)
```
* parsing command line arguments

```
@def(main prereqs)
	#include <iostream>
	@put(process prereqs);
	bool processed { false };
	void process(std::istream &in) {
		@put(process);
	}
@end(main prereqs)
```
* function to process each file
* the flag `processed` indicates if some files were processed already

```
@add(main)
	if (! processed) {
		process(std::cin);
	}
@end(main)
```
* use standard input if no other files were processed

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
* process all characters
* `cur` keeps track of current item number (starting at `1`)

```
@def(process ch)
	if (ch == '\n') {
		std::cout.put(ch);
		cur = 1;
		continue;
	}
@end(process ch)
```
* reset `cur` on newline
* and print the newline

```
@def(process prereqs)
	@put(should print prereqs);
	bool should_print(int cur) {
		@put(should print);
		return true;
	}
@end(process prereqs)
```
* function indicates if the current item should be printed

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
* copy the character if it should be printed

```
@add(process prereqs)
	char delim { '\t' };
	enum class Mode : char {
		delim = 'f', chr = 'c',
		byte = 'b'
	} mode { Mode::delim };
@end(process prereqs)
```
* tabulator is the default delimiter

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
@def(should print prereqs)
	#include <limits>
	using nli = std::numeric_limits<int>;
	int from { 0 }, to { nli::max() };
@end(should print prereqs)
```

```
@def(should print)
	return cur >= from && cur <= to;
@end(should print)
```

```
@add(main prereqs)
	#include <fstream>
@end(main prereqs)
```

```
@def(parse args)
	bool args_parsed { false };
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			@put(parse arg);
		} else {
			@put(process file);
		}
	}
@end(parse args)
```

```
@def(parse arg)
	switch (arg[1]) {
		@put(arg switch);
		default:
			@put(end of options);
			std::cerr <<
				"ignoring unknown"
				" option " << arg << '\n';
	}
@end(parse arg)
```

```
@def(end of options)
	if (arg[1] == '-' && arg[2] == '\0') {
		args_parsed = true;
		break;
	}
@end(end of options)
```

```
@def(arg switch)
	case '\0':
		process(std::cin);
		break;
@end(arg switch)
```

```
@add(arg switch)
	case 'd':
		delim = arg[2];
		break;
@end(arg switch)
```

```
@add(arg switch)
	case 'f': case 'b': case 'c': {
		mode = static_cast<Mode>(arg[1]);
		@put(parse list);
		break;
	}
@end(arg switch)
```

```
@def(process file)
	std::ifstream in { arg };
	if (in) {
		process(in);
	} else {
		std::cerr << "can't open " <<
			arg << '\n';
		processed = true;
	}
@end(process file)
```

```
@add(main prereqs)
	void reset_list() {
		from = 0;
		to = nli::max();
	}
@end(main prereqs)
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
		std::cerr <<
			"ignoring wrong list " <<
			arg << '\n';
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

