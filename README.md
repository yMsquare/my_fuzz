# my_fuzz
a test repository of several tests using google/fuzztest

# How to use
```shell

git clone https://github.com/yMsquare/my_fuzz.git
cd my_fuzz

#create dir build
mkdir build && cd build

#generating CMakeLists
CC=clang CXX=clang++ cmake -DCMAKE_BUIlD_TYPE=RelWithDebug -DFUZZTEST_FUZZING_MODE=on ..myArray+=(item)

#compile
cmake --build .

#run the tests
#./my_fuzz --fuzz=<TestSuiteName>.<TestName>
./my_fuzz --fuzz=StringTest.TestCatString
```
