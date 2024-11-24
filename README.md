# Python-transpiler-to-Cpp
For transpiling:

g++ main.cpp -o main ; ./main test.py filename transpile

Will produce two files filename.cpp and filename.exe

For interpreting:
Will not produce anything
g++ main.cpp -o main ; ./main test.py filename interpret
