# Implementation of `cat`
* print content of files

```
@Def(file: cat.cpp)
	@put(main prereqs);
	int main(int argc, char *argv[]) {
		@put(main);
	}
@End(file: cat.cpp)
```
* start with `@f(main)` function

```
@def(main)
	@put(parse args);
@end(main)
```
* parse command line arguments

```
@def(main prereqs)
	@put(parse args prereqs);
@end(main prereqs)
```
* stuff needed for parsing arguments

```
@add(main prereqs)
	#include <iostream>
@end(main prereqs)
```
* needs `std::istream`, `std::cout` and `std::cerr`

```
@add(main prereqs)
	bool processed { false };
@end(main prereqs)
```
* flag that indicates if some file was printed
* if no files are specified in the command line arguments, standard
  input will be used

```
@add(main prereqs)
	void process(std::istream &in) {
		@put(process);
		processed = true;
	}

@end(main prereqs)
```
* process file
* and indicate that some file was printed

```
@add(main)
	if (! processed) {
		process(std::cin);
	}
@end(main)
```
* if no files are specified in the command line arguments, standard
  input will be used

```
@def(process)
	char ch;
	while (in.get(ch)) {
		std::cout.put(ch);
	}
@end(process)
```
* copy each `char` to standard output

```
@def(parse args)
	bool args_parsed { false };
@end(parse args)
```
* flag to indicate if additional options should be parsed
* options start with `-`
* every other argument is treated as a file name
* after the option `--` all arguments are treated as file names

```
@add(parse args)
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		@put(parse arg);
	}
@end(parse args)
```
* handle each argument

```
@def(parse arg)
	if (! args_parsed && arg[0] == '-') {
		@put(parse option);
	} else {
		@put(process file);
	}
@end(parse arg)
```
* treat argument as option or file name

```
@def(parse args prereqs)
	#include <fstream>
@end(parse args prereqs)
```
* needs `std::ifstream`

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
* process file
* print message if file cannot be opened
* a unreadable file counts as processed
* so standard input is not processed afterwards

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
* only the options `-` and `--` are processed:
* `-` is the file name for standard input
* `--` marks the end of options section

