#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

//typedefs
typedef std::vector<std::vector<std::string> > STR_DOUBLE_VEC;
typedef std::map<std::string, int> STR_INT_MAP;

//definitons
void process_csv(std::istream&, STR_DOUBLE_VEC&);
void usage(std::ostream&,std::string);
void output_data(int);

//main
int main(int argc, char* argv[]) {
    if(argc < 3) {
        usage(std::cerr, argv[0]);
        return 1;
    }

    std::ifstream file_stream(argv[1]);

    if(!file_stream.good()) {
        std::cerr << "Your file is invalid!" << std::endl;
        usage(std::cerr, argv[0]);
        return 1;
    }

    if(atoi(argv[2]) == 0) {
        std::cerr << "You haven't specified a valid number of meetings! (> 0)" << std::endl;
        usage(std::cerr, argv[0]);
        return 1;
    }

    int num_meetings = atoi(argv[2]);
    int num_to_pool = (argc >= 4) ? atoi(argv[3]) : num_meetings;
    if(num_to_pool < num_meetings) {
        std::cerr << "Your number to pool from must be greater than the number of needed meetings!" << std::endl;
        usage(std::cerr, argv[0]);
        return 1;
    }

    STR_DOUBLE_VEC contents;
    STR_INT_MAP attendance_record;

    process_csv(file_stream, contents);
    
    int x = (contents.size()-num_to_pool <= 0) ? 0 : contents.size()-num_to_pool;
    for(; x<contents.size(); x++) {
        for(int y=0; y<contents[x].size(); y++) {
            attendance_record[contents[x][y]]++;
        }
    }
    int count = 0;
    for(STR_INT_MAP::const_iterator itr = attendance_record.begin(); itr != attendance_record.end(); ++itr) {
        if(itr->second >= num_meetings) {
            std::cout << itr->first <<  " (" << itr->second << ")" << std::endl;
            ++count;
        }
    }
    
    output_data(count);
    
    return 0;
}

//functions
void usage(std::ostream& out, std::string exe_name) {
    out << "USAGE: " << std::endl;
    out << exe_name << " <file name> <number of meetings> [meetings to pool]" << std::endl;
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

void output_data(int count) {
    std::cout << std::endl;

    if(count > 0) {
        std::cout << "A total of " << count << " members qualify to vote." << std::endl;
        std::cout << std::setw(28) << std::left << "Simple majority (.51)"     << ceil((float)count*.51) << " / " << count << std::endl;
        std::cout << std::setw(28) << std::left <<  "Two-thirds majority (2/3)" << ceil((float)count*(2/(float)3)) << " / " << count << std::endl;
    } else {
        std::cout << "No members qualify to vote." << std::endl;
    }
}