---
layout: page
permalink: /documentation/examples/box2d
---
Example to using box2d libsdlpp

```cpp
#include "libsdlpp/window.hpp"
#include "libsdlpp/box2d.hpp"

int main(int argc, char* argv[]) 
{
    using namespace libsdlpp;

    window w("Hello World", 800, 600);

    auto box = std::make_unique<box2d>(nullptr, 100,100, position(100, 100), color::red());

    w.init();
    w.set_child(box.release());
    w.run();

    return 1;
}
```