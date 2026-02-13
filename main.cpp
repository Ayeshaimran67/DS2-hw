#include <iostream>
#include <string>
#include "include/PostScriptFileSimplifier.hpp"

int main() { 
    std::string input_files[] = {
        "input/file-1.ps",
        "input/file-2.eps",
        "input/file-3.eps",
        "input/file-4.eps",
        "input/file-5.eps",
        "input/file-6.eps",
        "input/file-7.eps"
    };

    std::string output_files[] = {
        "test-output/file-1-simplified.ps",
        "test-output/file-2-simplified.eps",
        "test-output/file-3-simplified.eps",
        "test-output/file-4-simplified.eps",
        "test-output/file-5-simplified.eps",
        "test-output/file-6-simplified.eps",
        "test-output/file-7-simplified.eps"
    };

    for (int i = 0; i < 7; i++) {
        // Create simplifier
        PostScriptFileSimplifier simplifier(input_files[i]);
        
        // Simplify definitions
        simplifier.simplify_definitions();
        
        // Evaluate operations
        simplifier.evaluate_operations();

        simplifier.writefile(output_files[i]);
        }
    return 0;
}
