# CAPACITY

> C++17 capacity/size wrapper classes with one data variable

## Overview

> Currenly 1 class is implemented: son8::capacity::Exponent

- Only tracks capacity and size (using only one variable), does not manage memory.
- Only works with unsigned integral types (default is std::size_t).

## Usage

> simple (not complete) example

```cxx
#include <son8/capacity.hxx>
#include <algorithm>
class Vector {
    using Capacity = son8::capacity::Exponent< >; // default T is std::size_t
    Capacity capsize_{ };
    int *data_{ nullptr };
public:
    Vector() = default;
    Vector(int elems) : capsize_(elems), data_(new int[capsize_.capacity()]) { }
    ~Vector() { delete[] data_; }
    void push_back(int elem) {
        auto update_capacity = capsize_.add(1);
        if (update_capacity) {
            int *new_data = new int[*update_capacity];
            std::copy(data_, data_ + capsize_.last(), new_data);
            delete[] data_;
            data_ = new_data;
        }
        data_[capsize_.last()] = elem;
    }
    int *begin() { return data_; }
    int *end() { return data_ + capsize_.size(); }
};
```

## Reminder

- cannot set needed capacity directly (reserve exact number of elements, as capacity calculated automatically and share same variable with size)
- must check if capacity changes (via checking optional return value after add(), sub() or assign methods)
- currently only c asserts are used for error checking

###### each folder MAY contain README with additional information about project