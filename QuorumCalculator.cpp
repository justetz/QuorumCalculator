#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

typedef std::vector<std::vector<std::string> > STR_DOUBLE_VEC;

//definitons
void get_next_line(std::istream& in_str, std::vector<std::string>& contents);

//main
int main(int argc, char* argv[]) {
	STR_DOUBLE_VEC contents;
}

//functions
void get_next_line(std::istream& in_str, STR_DOUBLE_VEC& contents) {
    std::string line, cell;
    std::getline(in_str, line);

    std::stringstream line_stream(line);
    std::vector<std::string> t;

    while(std::getline(line_stream,cell,','))
        t.push_back(cell);

	contents.push_back(t);
}