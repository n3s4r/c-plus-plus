#include <iostream>
#include <string>
#include <unordered_map>

bool areAnagrams(std::string s1, std::string s2) {
    if (s1.length() != s2.length()) return false;

    std::unordered_map<char, int> counts;

    for (int i = 0; i < s1.length(); i++) {
        counts[s1[i]]++;
        counts[s2[i]]--;
    }

    for (auto const& [key, val] : counts) {
        if (val != 0) return false;
    }
    return true;
}

int main() {
    std::string s1 = "anagram";
    std::string s2 = "nagaram";

    if (areAnagrams(s1, s2)) {
        std::cout << "These are anagrams!" << std::endl;
    } else {
        std::cout << "Not anagrams." << std::endl;
    }

    return 0;
}
