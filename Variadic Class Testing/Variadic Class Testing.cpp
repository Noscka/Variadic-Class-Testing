#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <thread>
#include <functional>

/* For calling in class */
class Foo
{
public:
  /* just function, compiling error */
    template <typename F>
    Foo(F& callable)
    {
        /* First try */
        std::thread namedThread(callable, 2);
        namedThread.join();

        /* Second try (both aren't here at once btw) */
        //std::thread namedThread([&](F&& Fuction) { std::bind(callable, 2); }, callable);
        //namedThread.detach();
    }

    /* Trying both typename callable with Variadic parameters */
    template <typename F, typename ... ArgsT>
    Foo(F&& callable, ArgsT&& ... args)
    {
        //std::thread namedThread([&](typename std::decay<F>::type&& Fuction, typename std::decay<ArgsT>::type&&... args) { std::bind(Fuction, args...); }, std::forward<F>(callable), std::forward<ArgsT>(args)...);
        std::thread namedThread(callable, std::forward<ArgsT>(args)...);
        namedThread.join();
    }
};

void functionToThread(int SomeTing)
{
    std::wcout << L"Running" << std::endl;
    std::wcout << L"Number: " << SomeTing << std::endl;
    return;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    //Foo FooTing1(functionToThread);
    Foo FooTing2(&functionToThread, 3);
    return 0;
}


//template <typename F, typename ... ArgsT>
//void StartThread(F&& callable, ArgsT&& ... args)
//{
//    (*callable)(this, std::forward<ArgsT>(args)...);
//}