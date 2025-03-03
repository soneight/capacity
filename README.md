# CAPACITY

> C++17 capacity/size wrapper classes with one data variable

## Overview

> Currenly 1 class is implemented: son8::capacity::Exponent

Only tracks capacity and size (using only one variable), does not manage memory.

## Usage

> simple (not complete) example

```cxx
#include <son8/capacity.hpp>
#include <algorithm>
class Vector {
    using Capacity = son8::capacity::Exponent< std::size_t >;
    Capacity capacity{};
    int *data{nullptr};
public:
    Vector() = default;
    Vector(int elems) : capacity(elems), data(new int[capacity.capacity()]) {}
    ~Vector() { delete[] data; }
    void push_back(int elem) {
        auto update_capacity = capacity.add(1);
        if (update_capacity) {
            int *new_data = new int[*update_capacity];
            std::copy(data, data + capacity.last(), new_data);
            delete[] data;
            data = new_data;
        }
        data[capacity.last()] = elem;
    }
    int *begin() { return data; }
    int *end() { return data + capacity.size(); }
};
```

## Reminder

- cannot set needed capacity directly (reserve exact number of elements, as capacity calculated automatically and share same variable with size)
- must check if capacity changes (via checking optional return value after add() and sub() methods)
- currently only c asserts are used for error checking

###### each folder MAY contain README with additional information about project