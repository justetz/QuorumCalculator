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
typedef std::vector<std::vector<std::string> > STR_DOUBLE_VEC; //for the parsing
typedef std::map<std::string, int> STR_INT_MAP; //for the processed data

//definitons
void process_csv(std::istream&, STR_DOUBLE_VEC&); //processes the data provided
void usage(std::ostream&, std::string, std::string=""); //in the event program fails, print usage
void output_data(std::ostream&, const STR_INT_MAP&, int); //output the results

//main
int main(int argc, char* argv[]) {
    if(argc < 3) { //not enough arguments provided
        usage(std::cerr, argv[0]);
        return 1;
    }

    std::ifstream file_stream(argv[1]); //load the file provided

    if(!file_stream.good()) { //if the file is not valid
        usage(std::cerr, argv[0], "Your file is invalid!");
        return 1;
    }

    if(atoi(argv[2]) == 0) { //if the num of meetings is either 0 or NaN
        usage(std::cerr, argv[0], "You haven't specified a valid number of meetings! (> 0)");
        return 1;
    }

    int num_meetings = atoi(argv[2]); //otherwise, set it to that number
    //num to pool is how many attendance lists to count from
    int num_to_pool = (argc >= 4) ? atoi(argv[3]) : num_meetings;
    if(num_to_pool < num_meetings) { //if the number of meetings is unreachable
        usage(std::cerr, argv[0], "Your number to pool from must be greater than the number of needed meetings!");
        return 1;
    }

    STR_DOUBLE_VEC contents; //to store the soon-to-be-parsed data
    STR_INT_MAP attendance_record; //to track attendance record

    process_csv(file_stream, contents); //get the data processed
    
    //figure out where to start in the file
    int x = (contents.size()-num_to_pool <= 0) ? 0 : contents.size()-num_to_pool;
    for(; x<contents.size(); x++) { //crawl the vector and count attendance
        for(int y=0; y<contents[x].size(); y++) {
            attendance_record[contents[x][y]]++;
        }
    }
    
    output_data(std::cout, attendance_record, num_meetings); //output the results, giving 
    
    return 0;
}

//functions
void usage(std::ostream& out, std::string exe_name, std::string custom_error) {
    out << std::endl;
    if(custom_error != "") out << custom_error << std::endl;
    out << "USAGE: " << exe_name << " <file name> <number of meetings> [meetings to pool]" << std::endl;
    out << std::endl;
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

void output_data(std::ostream& out, const STR_INT_MAP& attendance_record, int num_meetings) {
    int count = 0; //counter of total valid voting membership
    //print the results (only those who qualify to vote)
    for(STR_INT_MAP::const_iterator itr = attendance_record.begin(); itr != attendance_record.end(); ++itr) {
        if(itr->second >= num_meetings) {
            //print the member and number of meetings attended in pool range
            out << itr->first <<  " (" << itr->second << ")" << std::endl;
            ++count;
        }
    }

    out << std::endl;

    if(count <= 0){
        out << "No members qualify to vote." << std::endl;
        return;
    }

    int simple_majority     = floor((float)count * (.50)) + 1;
    int two_thirds_majority = ceil((float)count * (2.0/3.0));

    out << "A total of " << count << " members qualify to vote." << std::endl;
    out << std::setw(28) << std::left << "Simple majority (50% + 1)"      << simple_majority << " / " << count << std::endl;
    out << std::setw(28) << std::left <<  "Two-thirds majority (2/3)" << two_thirds_majority << " / " << count << std::endl;
}