#include <vector>
#include <iostream>
using namespace std;


int main()
{
    vector<int> ivec;
   
    int* p = NULL;

    for (int ix = 0; ix < 500; ++ix)
    {
        ivec.push_back(ix);
        p = ivec.data();
        //A pointer to the first element in the array used internally by the vector.
        cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << p<< endl;

        
    }

    return 0;
}