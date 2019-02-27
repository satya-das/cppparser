CppParser
=========

[![Build Status](https://travis-ci.com/satya-das/cppparser.svg?branch=master)](https://travis-ci.com/satya-das/cppparser)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e2a1f6c5c8c149be816f1514ec491c98)](https://www.codacy.com/app/satya-das/cppparser?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=satya-das/cppparser&amp;utm_campaign=Badge_Grade)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

An easy, fast, and robust library to parse C/C++ source.

## Features
- No pre-processing, even preprocessors are part of the ast.
- Even most comments are preserved too and are part of the ast.
- Developed from scratch and uses back-tracking yacc (BtYacc) to write C++ grammer, that means **no dependency on libclang**.
- The result of parsing is the AST where elements of a file are arranged in a tree.
- Minimum dependency. Only external dependency is a [lexer](https://github.com/westes/flex) which is by default available on unix like platforms and can be easily get on Windows.

## Motivation 
CppParser can be used to build tools that need parsing of C/C++ files.
I am using it to develop [cib](https://github.com/satya-das/cib/) which implements ABI stable SDK architecture for C++ library.

## Example

To begin with we will see an example of parsing a hellp-world program and see what is the AST that `cppparser` creates:
```c++
#include <iostream>

int main()
{
  std::cout << "Hello World!\n";

  return 0;
}

```

For the above hello-world program we can expect that when it is parsed the generated AST should look like following:
![AST for Hello World program](https://github.com/satya-das/cppparser/blob/master/src/readme-assets/HelloWorldAST.svg "AST for Hello World program")

So, how we are going to access these elements of AST using `cppparser`?
Below is the program written as unit-test for validating the correctness of generated AST:

```c++
#include <catch/catch.hpp>

#include "cppparser.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

TEST_CASE(" Parsing hello world program")
{
  CppParser parser;
  auto      testFilePath = fs::path(__FILE__).parent_path() / "test-files/hello-world.cpp";
  auto      ast          = parser.parseFile(testFilePath.string());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppIncludeEPtr hashInclude = members[0];
  REQUIRE(hashInclude);
  CHECK(hashInclude->name_ == "<iostream>");

  CppFunctionEPtr func = members[1];
  REQUIRE(func);
  CHECK(func->name_ == "main");

  REQUIRE(func->defn());
  const auto& mainBodyMembers = func->defn()->members();
  REQUIRE(mainBodyMembers.size() == 2);

  CppExprEPtr coutHelloWorld = mainBodyMembers[0];
  REQUIRE(coutHelloWorld);
  CHECK(coutHelloWorld->oper_ == CppOperator::kLeftShift);
}

```

This is example is a real one and is part of actual unit test of cppparser.

## Building CppParser

### Get the source

```sh
git clone https://github.com/satya-das/common.git
git clone https://github.com/satya-das/cppparser.git
```

## Configure and build

```sh
cd cppparser
mkdir builds
cd builds
cmake ..
make && make test
```

*Alternatively, if you prefer `Ninja` instead of `make`*:

```sh
cd cppparser
mkdir builds
cd builds
cmake -G Ninja ..
ninja && ninja test
```

