# callstackpp

### A C++ stack trace pretty printer

[![Build Status](https://travis-ci.com/jhurliman/callstackpp.svg?branch=main)](https://travis-ci.com/jhurliman/callstackpp)
[![codecov](https://codecov.io/gh/jhurliman/callstackpp/branch/main/graph/badge.svg)](https://codecov.io/gh/jhurliman/callstackpp)

## Usage

### Install a signal handler that will pretty print a stack trace on segfault

```cpp
#include <iostream>

#include "callstackpp.hpp"

static callstackpp::SignalHandler sh;

int invalid_read() {
  char *ptr = reinterpret_cast<char *>(42);
  int v = *ptr;
  return v;
}

void invalid_write() {
  char *ptr = reinterpret_cast<char *>(42);
  *ptr = 42;
}

void call_abort() {
  std::cout << "Aborting!\n";
  abort();
}

int main() {
  // Try commenting and uncommenting different lines in this method to test
  std::cout << invalid_read() << '\n';
  // invalid_write();
  // call_abort();
}
```

## Test

```shell
# build test binaries
make

# run tests
make test
```

The default test binaries will be built in release mode (with debug info). You
can make Debug test binaries as well:

```shell
make clean
make debug
make test
```

Enable additional sanitizers to catch hard-to-find bugs, for example:

```shell
export LDFLAGS="-fsanitize=address,undefined"
export CXXFLAGS="-fsanitize=address,undefined"

make
```

# License

callstackpp is licensed under [MIT](https://opensource.org/licenses/MIT).
