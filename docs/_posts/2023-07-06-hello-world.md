---
layout: post
title: "Getting Started"
date: 2023-07-06 18:37:54 -0300
categories: sdl libsdlpp hello example
description: Getting Started
---
This is the first example to using libsdlpp

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

