#A Note on std::invoke
If you need to support member function pointers (e.g., &MyClass::method), standard function call syntax func(args...) will fail. You should include <functional> and replace the return line with:

return std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
