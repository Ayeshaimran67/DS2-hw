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
    for(auto& line : fileContents) {
        std::vector<std::string> tokens;
        std::string current = "";
        for(char ch :line) {
            if(ch == ' '||ch == '\t'||ch=='\n') {
                if(!current.empty()) {
                    tokens.push_back(current);
                    current = "";
                }
            } 
            else {
                current += ch;
            }
        }
        if(!current.empty())
            tokens.push_back(current);
        std::string newLine = "";
        for(size_t t = 0; t < tokens.size(); t++) {
            std::string token = tokens[t];
            bool isNum = true;
            if(token.empty()) {
                isNum = false;
            }
            for(size_t i = 0; i < token.size(); i++) {
                if(i == 0 && (token[i] == '-' || token[i] == '+')) {continue;}
                if(token[i] == '.') {continue;}
                if(token[i] < '0'||token[i]>'9') {isNum = false; break;}
            }
            if(isNum) {
                long double val = std::stold(token);
                stack.push(val);
                newLine += removeTrailingZeros(val);
            } 
            else if(token == "add") {
                long double res = stack.add();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "sub") {
                long double res = stack.subtract();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "mul") {
                long double res = stack.multiply();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "div") {
                long double res = stack.divide();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "mod") {
                long double res = stack.mod();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "sqrt") {
                long double res = stack.sqrt();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "sin") {
                long double res = stack.sin();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "cos") {
                long double res = stack.cos();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "atan") {
                long double res = stack.atan();
                newLine += removeTrailingZeros(res);
            } 
            else if(token == "dup") {
                stack.dup();
                newLine += removeTrailingZeros(stack.peek());
            } 
            else if(token == "exch") {
                stack.exch();
            } 
            else if(token == "roll") {
                long double j = stack.pop();
                long double n = stack.pop();
                stack.roll(n, j);
            }
            else if (keywords.find(token) != keywords.end()) {
                if (!newLine.empty()) {newLine += " ";}
                newLine += token;
                continue;
            }
            if (t != tokens.size() - 1) {newLine += " ";}
        }
        line = newLine;
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
