const int i = 100;
const int j = 100;
const int k = 100;
// g++ -x c -S c0801.cpp -o c0801_c.s
//  4:5: error: variably modified ‘array’ at file scope
// int array[i + j + k];
int array[i + j + k];
