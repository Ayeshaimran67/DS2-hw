#include "../include/PostScriptFileSimplifier.hpp"

#include <string>

#include "../include/stackPostScript.hpp"
#include "../include/utils.hpp"

PostScriptFileSimplifier::PostScriptFileSimplifier(std::string file) {
    std::ifstream inFile(file);
    if(!inFile.is_open()) {
        std::cout<<"Error opening file: "<<file<<std::endl;
        return;
    }
    std::string line;
    while(std::getline(inFile, line)) {
        fileContents.push_back(line);
    }
    inFile.close();
}

std::unordered_map<std::string, std::string> PostScriptFileSimplifier::get_tokens() const {
    std::unordered_map<std::string, std::string> tokens;
    for(const auto& line : fileContents) {
        auto words = str_split(line);  
        if(words.size() >= 3 && words[0][0] == '/' && words[2] == "def") {
            std::string varName = words[0].substr(1); 
            std::string value = words[1];
            tokens[varName] = value;
        }
    }
    return tokens;
}

void PostScriptFileSimplifier::simplify_definitions() {
    auto tokens= get_tokens();
    replace_tokens(tokens);
}

void PostScriptFileSimplifier::display_file() const {
    for(auto& line:fileContents) {
        std::cout<<line<<std::endl;
    }
}

void PostScriptFileSimplifier::writefile(std::string file) const {
    std::ofstream outFile(file);
    if(!outFile) {
        std::cout<<"Error: Cannot write to file "<<file <<std::endl;
        return;
    }
    for(auto& line: fileContents) {
        outFile<<line<<std::endl;
    }
    outFile.close();
}

void PostScriptFileSimplifier::evaluate_operations() {
    StackPostScript stack;
    for(auto& line :fileContents) {
        auto tokens =str_split(line);
        std::string Line1 = "";
        for(size_t t=0; t<tokens.size();t++) {
            std::string token= tokens[t];
            bool isNum =true;
            if(token.empty()) {
                isNum = false;
            }
            for(size_t i =0; i<token.size();i++) {
                if(i==0 && (token[i] =='-'||token[i] == '+')) {
                    continue;
                }
                if(token[i] == '.') {continue;}
                if(token[i] < '0'|| token[i] > '9') { isNum = false; break; }
            }
            if(isNum) {
                long double val = std::stold(token);
                stack.push(val);
                Line1+=removeTrailingZeros(val);
            } 
            else if (token == "add") stack.add();
            else if (token == "sub") stack.subtract();
            else if (token == "mul") stack.multiply();
            else if (token == "div") stack.divide();
            else if (token == "mod") stack.mod();
            else if (token == "sqrt") stack.sqrt();
            else if (token == "sin") stack.sin();
            else if (token == "cos") stack.cos();
            else if (token == "atan") stack.atan();
            else if (token == "dup") stack.dup();
            else if (token == "exch") stack.exch();
            else if (token == "roll") {
                if(stack.is_empty()) {continue;}
                long double j = stack.pop();
                long double n = stack.pop();
                stack.roll(n, j);
            }
            else if (keywords.find(token) != keywords.end()) {
                Line1 += token;
            }
            if (t != tokens.size() - 1) Line1 += " ";
        }
        line = Line1;
    }
}

void PostScriptFileSimplifier::replace_tokens(
    std::unordered_map<std::string, std::string>& tokens) {
    for(auto& line :fileContents) {
        auto words= str_split(line); 
        for(auto& word: words) {
            if(tokens.find(word)!=tokens.end()) {
                word= tokens[word];
            }
        }
        std::string newLine = "";
        for(size_t i=0; i<words.size();i++) {
            newLine+= words[i];
            if(i!= words.size()-1) {
                newLine += " ";
            }
        }
        line = newLine;
    }
}
