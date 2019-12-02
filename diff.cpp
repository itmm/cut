
#line 4 "diff.md"

	#include <fstream>
	#include <iostream>

	void process(
		std::istream &o, std::istream &n
	) {
		
#line 27 "diff.md"

	std::string line;
	while (std::getline(o, line)) {
		std::cout << "- " << line << '\n';
	}
	while (std::getline(n, line)) {
		std::cout << "+ " << line << '\n';
	}

#line 11 "diff.md"
;
	}

	int main(int argc, char *argv[]) {
		
#line 21 "diff.md"

	
#line 39 "diff.md"

	bool args_parsed { false };
	const char *old_path = nullptr;
	const char *new_path = nullptr;
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			if (arg[1] == '0') {
				if (! old_path) {
					old_path = arg;
				} else if (! new_path) {
					new_path = arg;
				} else {
					std::cerr << "ignoring additional path " << arg << '\n';
				}
			} else if (arg[1] == '-' && arg[2] == '\0') {
				args_parsed = true;
				break;
			} else {
				std::cerr << "ignoring unknown option " << arg << '\n';
			}
		} else {
			if (! old_path) {
				old_path = arg;
			} else if (! new_path) {
				new_path = arg;
			} else {
				std::cerr << "ignoring additional path " << arg << '\n';
			}
		}
	}
	if (! old_path) {
		old_path = "/dev/null";
	}
	if (! new_path) {
		new_path = "-";
	}
	if (old_path == "-") {
		std::ifstream n { new_path };
		if (n) {
			process(std::cin, n);
		} else {
			std::cerr << "can't open " << new_path << '\n';
		}
	} else if (new_path == "-") {
		std::ifstream o { old_path };
		if (o) {
			process(o, std::cin);
		} else {
			std::cerr << "can't open " << old_path << '\n';
		}
	} else {
		std::ifstream o { old_path };
		std::ifstream n { new_path };
		if (o && n) {
			process(o, n);
		} else {
			if (! o) {
				std::cerr << "can't open " << old_path << '\n';
			}
			if (! n) {
				std::cerr << "can't open " << new_path << '\n';
			}
		}
	}

#line 22 "diff.md"
;

#line 15 "diff.md"
;
	}
