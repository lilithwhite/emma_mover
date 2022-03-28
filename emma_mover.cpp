#include <iostream>
#include <filesystem>
#include <experimental/filesystem>
#include <string>
#include <parallel/find.h>

using namespace std;

int main (int argc, char *argv[]){
    if (argc != 4) {
        cout << "this is not how you use it, it should be like \"./emma_mover \"file you want to move stuff from\" \"file you want to move stuff to\" \"the extention you want\"\"" << '\n';
        cout << "aborted" << '\n';
        exit(0);
    }
    string target_file = argv[1];
    string output_file = argv[2];
    string target = argv[3];
    string are_you_sure;
    cout << "are you sure Y/n" << '\n';
    cin >> are_you_sure;
    if (are_you_sure != "Y") {
        cout << "aborted" << '\n';
        exit(0);
    }
    for (auto const& dir_entry : experimental::filesystem::recursive_directory_iterator(target_file)){
        string dir = experimental::filesystem::path(dir_entry);    
            if (dir.find(target) != -1) {
                std::size_t found = dir.find_last_of("/\\");
                string test = output_file + dir.substr(found+1);
                if(test != dir){
                    experimental::filesystem::copy (dir, output_file, experimental::filesystem::copy_options::overwrite_existing |  experimental::filesystem::copy_options::recursive);
                }

            }
    }
}
