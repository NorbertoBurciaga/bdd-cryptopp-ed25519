# bdd-cryptopp-ed25519
## Contents

* [Introduction](#introduction)
* [Project Hierarchy](#project-hierarchy)
* [Getting Started](#getting-started)
* [Support](#support)
* [FAQ](#faq)
* [Development](#development)
* [License](#license)
* [References](#references)

## Introduction

application to test elliptic ed25519 keys messages and signatures

[Contents](#contents)

## Project Hierarchy

```console
.
├── CMakeLists.txt
├── LICENSE
├── README.md
└── tests
    ├── execute_tests.sh
    ├── features
    │   ├── CMakeLists.txt
    │   ├── keys.feature
    │   ├── signatures.feature
    │   ├── step_definitions
    │   │   ├── cucumber.wire
    │   │   ├── KeySteps.cpp
    │   │   ├── KeySteps.h
    │   │   ├── SignatureSteps.cpp
    │   │   └── SignatureSteps.h
    │   └── support
    │       └── env.rb
    ├── myprivatekey.der
```

[Contents](#contents)

## Getting Started

### Requirements
* Cmake
* Boost
* Google Test
* Cucumber
* Ruby
* Crypto++

### Installation

Install the following packages:

```console
$ sudo apt install git-all gcc g++ flex bison make autoconf automake libtool autotools-dev libevent-dev zlib1g-dev pkg-config libssl-dev xbindkeys xautomation libsnappy-dev libbz2-dev liblz4-dev libzstd-dev net-tools tree curl graphviz texlive-latex-base dumpasn1
```

#### Install CMake

Download .._x86_64.sh file from: https://cmake.org/files/LatestRelease/
$ chmod +x the downloaded file:

```console 
$ chmod +x cmake-3.13.0-Linux-x86_64.sh
```
Execute the downloaded sh file:

```console 
$ ./cmake-3.13.0-Linux-x86_64.sh
```

Move the directory created in Dowloads to opt directory: $ sudo mv cmake-3.13.0-Linux-x86_64 /opt
Create links in /usr/local/bin:

```console
$ cd /usr/local/bin
$ sudo ln -s /opt/cmake-3.13.0-Linux-x86_64/bin/cmake
$ sudo ln -s /opt/cmake-3.13.0-Linux-x86_64/bin/ccmake
$ sudo ln -s /opt/cmake-3.13.0-Linux-x86_64/bin/ctest
$ sudo ln -s /opt/cmake-3.13.0-Linux-x86_64/bin/cmake-gui
```

#### Install Boost
Boost is required by cucumbercpp
Download latest version from: https://dl.bintray.com/boostorg/release/

```console
$ wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz
```
Extract package

```console
$ cd boost_1_69_0/
$ sudo ./bootstrap.sh --prefix=/usr/local
```
Set the use of MPI

```console
$ user_configFile=`find $PWD -name user-config.jam`
$ echo $user_configFile
/home/norberto/Downloads/boost_1_69_0/tools/build/example/user-config.jam
$ echo "using mpi;" >> $user_configFile
$ sudo ./b2 install
```

#### Install google test/mock
Tests in cucumber-cpp requires gtest

```console
$ git clone https://github.com/google/googletest.git
$ cd googletest/
$ mkdir build
$ cd build
$ cmake .. && make
$ sudo make install
```

#### Install Ruby
```console
$ sudo apt install ruby-full ruby-dev ruby-rspec rake rubygems bundler
```

#### Cucumber pre-requisites
Install bundler gem:

```console
$ sudo gem install bundler
$ cd /var/lib/gems/2.5.0/gems/bundler-2.0.1/lib/bundler/templates/
/var/lib/gems/2.5.0/gems/bundler-2.0.1/lib/bundler/templates$ bundle install
```

#### Install Cucumber
```console
$ sudo gem install cucumber --version 2.99.0   NOTE: The newest version has conflicts with cucumber-cpp
$ git clone https://github.com/cucumber/cucumber-cpp.git
$ cd cucumber-cpp/
$ git submodule init
$ git submodule update
$ cmake -E make_directory build
$ cmake -E chdir build cmake -DCUKE_ENABLE_EXAMPLES=on ..
```
it sent the following error but it created the Makefiles:
install(EXPORT "CucumberCpp" ...) includes target "cucumber-cpp-nomain" which requires target "json_spirit.header" that is not in the export set.

```console
$ cmake --build build
$ cmake --build build --target test
$ sudo cmake --build build --target install
$ cmake --build build --target features
$ build/examples/Calc/BoostCalculatorSteps >/dev/null &
$ cucumber examples/Calc
```

#### Install Crypto++
```console
$ git clone https://github.com/weidai11/cryptopp.git
$ git clone https://github.com/weidai11/cryptopp.git
$ cd cryptopp
$ git submodule add https://github.com/noloader/cryptopp-cmake.git cmake
$ git submodule update --remote
$ cp "$PWD/cmake/cryptopp-config.cmake" "$PWD"
$ cp "$PWD/cmake/CMakeLists.txt" "$PWD"
```
[Contents](#contents)

### Testing

```console
$ git clone https://github.com/NorbertoBurciaga/bdd-cryptopp-ed25519.git
$ cd bdd-cryptopp-ed25519/tests
$ ./execute_tests.sh
```
[Contents](#contents)

### Documentation

There is no other documentation but you can check Key.feature and Signatures.feature to read case scenarios implemented in this test.

[Contents](#contents)

## Support
Technical support is available in 

[Contents](#contents)

## FAQ

[Contents](#contents)

## Development
If you want to contribute....

[Contents](#contents)

## License

Copyright (c) 2018, Respective Authors all rights reserved.

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

[Contents](#contents)

## References