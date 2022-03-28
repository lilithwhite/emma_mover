#include <iostream>
#include <filesystem>
#include <experimental/filesystem>
#include <string>
#include <parallel/find.h>

using namespace std;

int main (int argc, char *argv[]){
    string files [1000];
    string target_file = argv[1];
    string output_file = argv[2];
    string target = argv[3];
    string are_you_sure;
    int file_number = 0;
//    cout << "extension" << '\n';
//    cin >> target;
//    cout << "target folder" << '\n';
//    cin >> target_file;
//    cout << "output folder" << '\n';
//    cin >> output_file;
    cout << "are you sure Y/n" << '\n';
    cin >> are_you_sure;
    if (are_you_sure != "Y") {
        cout << "aborted" << '\n';
        exit(0);
    }
    for (auto const& dir_entry : experimental::filesystem::recursive_directory_iterator(target_file)){
        string dir = experimental::filesystem::path(dir_entry);
            if (dir.find(target) != -1) {
                files [file_number] = dir;
                file_number = file_number + 1;
            }
    }
    file_number = 0;
    do 
    {
        std::size_t found = files [file_number].find_last_of("/\\");
        string test = output_file + files [file_number].substr(found+1);
        if (test == files [file_number]) {
            file_number = file_number + 1;
        }else{
            experimental::filesystem::copy (files [file_number], output_file, experimental::filesystem::copy_options::overwrite_existing);
            file_number = file_number + 1;
        }
    }while (files [file_number].empty() == 0);
}
