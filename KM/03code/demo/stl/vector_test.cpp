#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class myclass {
        public:
        myclass(int a, int b):first(a), second(b){}
        int first;
        int second;
        bool operator < (const myclass &m)const {
                return first < m.first;
        }
};

bool less_second(const myclass & m1, const myclass & m2) {
        return m1.second < m2.second;
}

int main() {
        
        vector< myclass > vect;
        for(int i = 0 ; i < 10 ; i ++)
        {
                myclass my(i, i);
                vect.push_back(my);
        }
        for(int i = 0 ; i < vect.size(); i ++) 
        {
            cout<<"("<<vect[i].first<<","<<vect[i].second<<")\n";
        }
        
        sort(vect.begin(), vect.end());

        cout<<"after sorted by first:"<<endl;
        for(int i = 0 ; i < vect.size(); i ++) 
        { 
            cout<<"("<<vect[i].first<<","<<vect[i].second<<")\n";
        }
        // cout<<"after sorted by second:"<<endl;
        // sort(vect.begin(), vect.end(), less_second);
        // for(int i = 0 ; i < vect.size(); i ++) 
        // cout<<"("<<vect[i].first<<","<<vect[i].second<<")\n";
        
        return 0 ;
}

//http://feihu.me/blog/2014/sgi-std-sort/