class Singleton
{
   public:
       static Singleton* getInstance( );
       ~Singleton( );
   private:
       Singleton( );
       static Singleton* instance;
};

//设计一个类不能被继承
class sealedClass1
{
public:
    static sealedClass1* Getinst()
    {
        return  new sealedClass1();

    }

    static void destory(sealedClass1* p)
    {
        if (p)
        {
            delete p;
            p = NULL;
        }
    }

private:
    int _a;
    sealedClass1()
        :_a(0)
    {}
    ~sealedClass1()
    {}
};
class sealedClass;

class Tmp
{
public:
    friend sealedClass;
private:
    Tmp()
        :_a(0)
    {}
    ~Tmp()
    {}
    int _a;
};

class sealedClass : virtual public Tmp
{
public:
    sealedClass()
        :_b(1)
    {}

    ~sealedClass()
    {}
private:
    int _b;
};

class C :public sealedClass
{
public:
    C()
        :_c(3)//出现编译错误
    {}
private:
    int _c;
};
class A
{
public:
    A(int x = 0)
        :_a(x)
    {}

    void destory()
    {
        delete this;
    }

private:
    ~A()
    {}
    int _a;
};

Class A
{
public:
    static A* Getinst()
    {
        return new A();
    }

    void destory()
    {
        delete this;
    }

protected:
    A(int x = 0)
        :_a(x)
    {}

    ~A()
    {}
    int _a;
}

class A
{
public:
    A(int x = 0)
        :_a(x)
    {}

    ~A()
    {}

private:
    void* operator new(size_t N)
    {
        return NULL;
    }

    void operator delete(void* p)
    {}

    int _a;
};

