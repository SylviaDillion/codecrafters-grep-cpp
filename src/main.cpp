#include <iostream>
#include <string>
#include<cmath>

bool match_pattern(const std::string& input_line, const std::string& pattern);

bool match_character_group(const std::string& input_line, const std::string& pattern);

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    else if(pattern == "\\d"){//查找数字
        for(char c:input_line){
            if(std::isdigit(c)){
                return true;
            }
        }
        return false;
    }
    else if(pattern == "\\w"){//查找数字和字母
        for(char c:input_line){
            if(std::isalpha(c) || isdigit(c) || c == '_'){
                return true;
            }
        }
        return false;
    }
    else if(pattern[0] == '[' && pattern[pattern.length()-1] == ']'){
        return match_character_group(input_line, pattern);
    }
    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

bool match_character_group(const std::string& input_line, const std::string& pattern){
    std::string subpattern = pattern.substr(1,pattern.length()-1);
    size_t pos = input_line.find(subpattern);
    if(pos != std::string::npos){
        return true;
    }
    else{
        return false;
    }
}

int main(int argc, char* argv[]) {
    
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin,input_line);

    try{
        if(match_pattern(input_line,pattern)){
            // std::cout<<"Matched\n";
            return 0;
        }else{
            // std::cout<<"Not matched\n";
            return 1;
        }
    }catch (const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
}
