#include <iostream>
#include <memory>
//基于Boost库, C++11加入了shared_ptr和weak_pt
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "use_count == " << gw.use_count() << ": ";
    if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
	std::cout << *spt << "\n";
    }
    else {
        std::cout << "gw is expired\n";
    }
}
 
int main()
{
    {
		auto sp = std::make_shared<int>(42);
		gw = sp;
		observe(); 
    }//消失了
 
    observe();
}

//use_count == 1: 42
//use_count == 0: gw is expired