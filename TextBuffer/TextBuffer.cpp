#include "TextBuffer.hpp"
#include <iostream>

// Constructor implementation
TextBuffer::TextBuffer(const std::string& text) : data(text) {}

// 1. Non-const version implementation
std::string& TextBuffer::get() {
    std::cout << "[Log] Non-const accessor called.\n";
    return data;
}

// 2. Const version implementation
// Note: 'const' must be included here in the signature
const std::string& TextBuffer::get() const {
    std::cout << "[Log] Const accessor called.\n";
    return data;
}