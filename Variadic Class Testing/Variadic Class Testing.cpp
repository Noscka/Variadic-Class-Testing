#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <thread>
#include <functional>

template <typename F, typename ... ArgsT>
void StartThread(F&& callable, ArgsT&& ... args)
{
    (*callable)(this, std::forward<ArgsT>(args)...);
}

class Foo
{
public:
    std::wstring String;

    template <typename F>
    Foo(F* callable)
    {
        std::thread(callable, L"abc");
    }

    //template <typename F, typename ... ArgsT>
    //Foo(F&& callable, ArgsT&& ... args)
    //{
    //    
    //    //std::thread([](typename std::decay<F>::type&& callable, typename std::decay<ArgsT>::type&&... args)
    //    //{
    //    //    try
    //    //    {
    //    //        std::bind(callable, args...)();
    //    //    }
    //    //    catch (...)
    //    //    {
    //    //
    //    //    }
    //    //    //(*callable)(std::forward<ArgsT>(args)...);
    //    //}, std::forward<F>(callable), std::forward<ArgsT>(args)...);
    //}
};

void function(std::wstring input, int SomeTing)
{
    std::wcout << L"Running" << std::endl;
    std::wcout << L"Number: " << SomeTing << std::endl;
    //param->String = input;
}

template <typename F>
void ThreadTemplateFunction(F&& callable)
{
    std::thread([&](F&& Fuction) 
    {
        std::bind(callable, L"abc");
    }, callable);
}

void SimplePrint(std::wstring input)
{
    std::wcout << L"Some Print: " << input << std::endl;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    ThreadTemplateFunction(&SimplePrint);

    //Foo FooTing(&SimplePrint);
    //wprintf(FooTing.String.c_str());
    return 0;
}