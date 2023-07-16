# Libsdlcpp

This is the first example (Hello World) to using libsdlpp

```cpp
#include "libsdlpp/window.hpp"

int main(int argc, char* argv[]) 
{
    using namespace libsdlpp;

    window w("Hello World", 800, 600);

    w.init();
    w.run();

    return 1;
}
```