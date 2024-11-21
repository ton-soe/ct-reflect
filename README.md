# ct-reflect
Compile Time Reflection

# Usage
Supports Clang, GCC (Untested). Does not support MSVC.\
Requires C++20 or above.

# Example
```
#include "ct-refl.h"

struct Foo
{
    int a;
    float b;
    char c;    
};
REFLECT(Foo, a, b, c)

int main()
{
    Foo f{ 100, 3.14f, 'T'};
    auto field = std::get<1>(ctr::Reflect<Foo>::Fields());
    printf("%s = %f\n", field.name, f.*field.ptr);
}
```
Produces
```
b = 3.14
```

# References
[The Map Macro](https://github.com/swansontec/map-macro)
