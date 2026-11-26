cmake -S <source dir> -B <build dir> 

make 

make -j 

ctest --test-dir <build dir> <-- runs all tests 
ctest -R <test name> <-- run specific test
