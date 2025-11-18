#ifndef TEXTBUFFER_HPP
#define TEXTBUFFER_HPP

#include <string>

class TextBuffer {
private:
    std::string data;

public:
    // Constructor
    TextBuffer(const std::string& text);

    // Non-const version (Read/Write)
    std::string& get();

    // Const version (Read-Only)
    const std::string& get() const;
};

#endif