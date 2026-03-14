#include <iostream>
#include <vector>
#include <algorithm> // Required for std::rotate

void printVector(const std::vector<int>& vec) {
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n, d;

    std::cout << "Enter number of elements: ";
    if (!(std::cin >> n)) return 1;

    std::vector<int> vec(n);
    std::cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    std::cout << "Enter number of positions to rotate: ";
    std::cin >> d;

    // Handle rotations larger than vector size
    d = d % n;

    // std::rotate(first, middle, last) 
    // It takes the element at 'middle' and makes it the new 'first'
    std::rotate(vec.begin(), vec.begin() + d, vec.end());

    std::cout << "Rotated vector: ";
    printVector(vec);

    return 0;
}
