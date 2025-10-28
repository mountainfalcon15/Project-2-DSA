#include <iostream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
    std::string input;
    while(true) {
        std::cout << "------------------------------" << std::endl;
        std::cout << "Welcome to the Steamler! This is a program that helps you pick out games for you based on the genre(s) you select!" << std::endl;
        std::cout << "1. See all genres based on popularity" << std::endl;
        std::cout << "2. Enter genres to search" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "Please enter a number to begin: " ;
        std::cin >> input;
        if (input == "1") {

        }
        if (input == "2") {
            std::cout << "Separate genres using commas (ie. Action, Single-Player)" << std::endl;

        }
        if (input == "3") {
            return 0;
        }
    }
    return 0;
}