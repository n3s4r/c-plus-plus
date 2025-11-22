#include <iostream>
#include <utility>   // for std::forward
#include <typeinfo>  // for typeid
#include <string>
#include <memory>


#ifdef __GNUG__
#include <cxxabi.h>
std::string demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}
#else
// MSVC produces readable names by default
std::string demangle(const char* name) {
    return name;
}
#endif

// --- The Generic Wrapper ---

template <typename Func, typename... Args>
decltype(auto) logAndCall(Func&& func, Args&&... args) {

    std::cout << "[LOG] Calling function with types: ";

    ((std::cout << demangle(typeid(Args).name()) << " "), ...);

    std::cout << "\n";


    return std::forward<Func>(func)(std::forward<Args>(args)...);
}

// --- Usage Examples ---

void voidFunc(int x, double y) {
    std::cout << "    -> Inside voidFunc: " << x << ", " << y << "\n";
}

int sum(int a, int b) {
    std::cout << "    -> Inside sum: " << a + b << "\n";
    return a + b;
}

struct Foo {
    void operator()(std::string s) {
        std::cout << "    -> Inside functor: " << s << "\n";
    }
};

int main() {

    logAndCall(voidFunc, 10, 3.14);

    std::cout << "-------------------\n";


    int result = logAndCall(sum, 50, 100);
    std::cout << "    -> Result in main: " << result << "\n";

    std::cout << "-------------------\n";


    logAndCall([](const char* msg) {
        std::cout << "    -> Inside lambda: " << msg << "\n";
    }, "Hello Lambda");

    std::cout << "-------------------\n";


    Foo myFoo;
    logAndCall(myFoo, std::string("Hello Functor"));

    return 0;
}
