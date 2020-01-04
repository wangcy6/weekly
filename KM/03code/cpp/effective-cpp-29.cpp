// Item 29: Strive for exception-safe code.
// Effective C++ 29：追求异常安全的代码

#include <iostream>

using namespace std;

class Menu
{
    Mutex m;
    Image *bg;
    shared_ptr<Image> bg1;
    int changeCount;

public:
    void changeBg(istream &sr);
};
//From the perspective of exception safety,
void Menu::changeBg(istream &src)
{
    lock(&mutex);

    delete bg;
    ++changeCount; //Menu数据一致性被破坏。首先bg变成了空，然后changeCount也错误地自增了 Don't allow data structures to become corrupted

    bg = new Image(src); //throw

    unlock(&mutex); //mutex资源被泄露了。没有被unlock Leak no resources.
}

void Menu::changeBg1(istream &src)
{
    Lock m1(&m); // shared_ptr

    bg1.reset(new Image(src)); //shared_ptr

    ++changeCont;
}

struct PMImpl
{                                        // PMImpl = "PrettyMenu
    shared_ptr<Image> bgImage; // Impl."; see below for
    int imageChanges;                    // why it's a struct
} 


class PrettyMenu {

private:
    Mutex mutex;
    shared_ptr<PMImpl> pImpl;
};
// copy-and-swap
void PrettyMenu::changeBackground(std::istream &imgSrc)
{
    using std::swap; // see Item 25
    Lock ml(&mutex); // acquire the mutex

    std::shared_ptr<PMImpl> // copy obj. data
        pNew(new PMImpl(*pImpl));
    pNew->bgImage.reset(new Image(imgSrc)); // modify the copy

    ++pNew->imageChanges;
    swap(pImpl, pNew); // swap the new// data into place
} // release the mute

////https://harttle.land/2015/08/27/effective-cpp-29.html