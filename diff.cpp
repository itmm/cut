
#line 4 "diff.md"

	#include <fstream>
	#include <iostream>
	#include <vector>

	void process(
		std::istream &o, std::istream &n
	) {
		
#line 28 "diff.md"

	std::string line;
	while (std::getline(o, line)) {
		std::cout << "- " << line << '\n';
	}
	while (std::getline(n, line)) {
		std::cout << "+ " << line << '\n';
	}

#line 12 "diff.md"
;
	}

	int main(int argc, char *argv[]) {
		
#line 22 "diff.md"

	
#line 40 "diff.md"

	bool args_parsed { false };
	std::vector<std::string> paths;
	for (int i = 1; i < argc; ++i) {
		const char *arg = argv[i];
		if (! args_parsed && arg[0] == '-') {
			if (arg[1] == '0') {
				paths.emplace_back(arg);
			} else if (arg[1] == '-' && arg[2] == '\0') {
				args_parsed = true;
				break;
			} else {
				std::cerr << "ignoring unknown option " << arg << '\n';
			}
		} else {
			paths.emplace_back(arg);
		}
	}
	paths.emplace_back("-");
	if (paths.size() == 1) {
		paths.emplace(paths.begin(), "/dev/null");
	}
	if (paths[0] == "-") {
		std::ifstream n { paths[1].c_str() };
		process(std::cin, n);
	} else if (paths[1] == "-") {
		std::ifstream o { paths[0].c_str() };
		process(o, std::cin);
	} else {
		std::ifstream o { paths[0].c_str() };
		std::ifstream n { paths[1].c_str() };
		process(o, n);
	}

#line 23 "diff.md"
;

#line 16 "diff.md"
;
	}
