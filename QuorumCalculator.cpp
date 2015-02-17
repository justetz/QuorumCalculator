#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <stdlib.h> 

//typedefs
typedef std::vector<std::vector<std::string> > STR_DOUBLE_VEC;
typedef std::map<std::string, int> STR_INT_MAP;

//definitons
void process_csv(std::istream&, STR_DOUBLE_VEC&);
void usage(std::ostream&,std::string);

//main
int main(int argc, char* argv[]) {
    if(argc != 3) {
        usage(std::cerr, argv[0]);
        return 1;
    }
    

    std::ifstream file_stream(argv[1]);

    if(!file_stream.good()) {
        std::cout << "Your file is invalid!" << std::endl;
        usage(std::cerr, argv[0]);
        return 1;
    }

    if(atoi(argv[2]) == 0) {
        std::cout << "You haven't specified a valid number of meetings! (> 0)" << std::endl;
        usage(std::cerr, argv[0]);
        return 1;
    }

    int num_meetings = argv[2];
    STR_DOUBLE_VEC contents;
    STR_INT_MAP attendance_record;

    process_csv(file_stream, contents);
    for(int x=contents.size()-num_meetings; x<contents.size(); x++) {
        for(int y=0; y<contents[x].size(); y++) {
            attendance_record[contents[x][y]]++;
        }
    }
    int index = 0;
    for(STR_INT_MAP::const_iterator itr = attendance_record.begin(); itr != attendance_record.end(); ++itr) {
        if(itr->second >= num_meetings) {
            std::cout << itr->first <<  " (" << itr->second << ")" << std::endl;
            ++index;
        }
    }
    if(index > 0) std::cout << "A total of " << index;
    else          std::cout << "No";

    std::cout << " members qualify to vote." << std::endl;
    return 0;
}

//functions
void usage(std::ostream& out, std::string exe_name) {
    out << "USAGE: " << std::endl;
    out << exe_name << " <file name> <number of meetings>" << std::endl;
}

void process_csv(std::istream& in_str, STR_DOUBLE_VEC& contents) {
    std::string line, cell;

    while(std::getline(in_str, line)) {
        std::stringstream line_stream(line);
        std::vector<std::string> t;

        while(std::getline(line_stream,cell,','))
            t.push_back(cell);

        contents.push_back(t);
    }
}