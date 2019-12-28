#include 
#include 
#include 
//动态加载的so中尽量不用线程局部存储.
pthread_key_t key;
pthread_once_t once = PTHREAD_ONCE_INIT;

static void destructor(void *ptr)
{
    free(ptr);
}

void init_once(void)
{
    pthread_key_create(&key, destructor);
}

extern "C" void process()
{
    pthread_once(&once, init_once);

    void *ptr;
    if ((ptr = pthread_getspecific(key)) == NULL)
    {
    fprintf(stdout, "malloc 1024 byte\n");
    ptr = malloc(1024);
    pthread_setspecific(key, ptr);
    }
    return;
}




typedef void (*FuncType)(void);
static void *thread_fn(void *arg)
{
    FuncType func = (FuncType)arg;
    func();
    sleep(2);
    return (NULL);
}
int main()
{
    void *handler = dlopen("./libfirst.so", RTLD_NOW);
    if(!handler)
    {
        printf("%s\n", dlerror());
        return -1;
    }
    FuncType func = reinterpret_cast(dlsym(handler, "process"));
    if(NULL == func)
    {
        printf("first func is null\n");
        return -2;
    }
    int i = 0; int n = 10;
    pthread_t tids[10];
    for (i = 0; i < n; i++)
    {
        pthread_create(&tids[i], NULL, thread_fn, (void *)func);
    }
    sleep(1);
    dlclose(handler);
    for (i = 0; i < n; i++)
    {
        pthread_join(tids[i], NULL);
    }
    return 0;
}