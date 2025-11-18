#include <iostream>
#include "TextBuffer.hpp"

int main() {
    // --- Case 1: Mutable Object ---
    TextBuffer mutableBuf("Hello");
    
    std::cout << "--- Mutable Object ---\n";
    // Calls non-const get(), returns mutable reference
    mutableBuf.get() += " World"; 
    std::cout << "Value: " << mutableBuf.get() << "\n\n";


    // --- Case 2: Const Object ---
    const TextBuffer constBuf("Immutable");

    std::cout << "--- Const Object ---\n";
    // Calls const get(), returns const reference
    std::cout << "Value: " << constBuf.get() << "\n";

    // The following line would fail to compile:
    // constBuf.get() = "Change me"; 
    
    return 0;
}