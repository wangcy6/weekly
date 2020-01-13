#include <iostream>


int main()
{
    weak_ptr<int> test;
    {
        shared_ptr<int> tmp(new int(2));
        test = tmp;
        if (test.lock().get()) {
            cout << "test: " << *test.lock() << endl;
        }
    }

    if (test.lock().get()) {
        cout << "test: " << *test.lock() << endl;
    } else {
        cout << "test: null" << endl;
    }

    return 0;
}