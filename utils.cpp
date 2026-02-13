#include "../include/utils.hpp"

std::string removeTrailingZeros(long double number) {
    /*
    Your implementation goes here
    */
    std::string str = std::to_string(number);

    // Remove trailing zeros
    while (str.back() == '0') //while last character is 0:
        str.pop_back();       //remove last character

    // Remove trailing decimal point
    if (str.back() == '.') //if last character is a decimal pt
        str.pop_back();

    return str;
}

std::vector<std::string> str_split(std::string line) {
    /*
    Your implementation goes here
    */
    std::vector<std::string> result;
    std::string current = "";

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ' || 
            line[i] == '\t' || 
            line[i] == '\n') {
            if (current != "") { //save current to result upon encountering whitespace
                result.push_back(current);
                current = "";
            }
        } else {
            current += line[i];
        }
    }

    if (current != "") { //add last token to result
        result.push_back(current);
    }

    return result;
}