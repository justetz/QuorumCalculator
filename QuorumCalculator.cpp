
//definitons
void get_next_line(std::istream& in_str, std::vector<std::string>& contents);

//main
int main(int argc, char* argc[]) {
	if
}

//functions
void get_next_line(std::istream& in_str, std::vector<std::string>& contents) {
    std::string line, cell;
    std::getline(in_str, line);

    std::stringstream line_stream(line);

    while(std::getline(lineStream,cell,','))
        contents.push_back(cell);
}