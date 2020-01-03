#include <stdio.h>
#include <vector>
#include <algorithm>
#include <new>
struct foo_t
{
    int size;
};
class cmp_t
{
public:
    //写c++ stl中的比较函数是，bool返回真的时候，一定是“真的”大，或者小，等于的时候只能返回false。
    bool operator()(foo_t *a, foo_t *b)
    {
        return a->size >= b->size; // == true
        //return a->size > b->size; //  == false
    }
    //https://stackoverflow.com/questions/39933036/core-dump-when-using-stdsort
    //https://cloud.tencent.com/developer/article/1336738
};
int main(int argc, char *argv[])
{
    std::vector<foo_t *> vec;
    for (int i = 0; i < 17; i++)
    {
        foo_t *x = new (std::nothrow) foo_t();
        if (NULL == x)
        {
            goto fail;
        }
        else
        {
            x->size = 1;
        }
        vec.push_back(x);
    }
    std::sort(vec.begin(), vec.end(), cmp_t());
fail:
    for (std::vector<foo_t *>::iterator iter = vec.begin(); vec.end() != iter; ++iter)
    {
        delete *iter;
        *iter = NULL;
    }
    return 0;
}