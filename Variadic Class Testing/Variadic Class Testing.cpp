#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <thread>
#include <functional>

/*
Project for testing Variadic Templates, Callable Templates, passing template variables and threading with template variables
It isn't made for effiency as I made it to test different functions and etc for another project (Console Loading Screen)
which doesn't just use the constructor
*/

class Foo
{
public:
    template <typename F, typename ... ArgsT>
    Foo(F&& callable, ArgsT&& ... args)
    {
        StartThreadFunction(std::forward<F>(callable), std::forward<ArgsT>(args)...);
    }

    template <typename F, typename ... ArgsT>
    void StartThreadFunction(F&& callable, ArgsT&& ... args)
    {
        std::thread([this](F&& callable, ArgsT&& ... args) { this->StartThread(callable, std::forward<ArgsT>(args)...); }, callable, std::forward<ArgsT>(args)...).join();
        
    }

    template <typename F, typename ... ArgsT>
    void StartThread(F&& callable, ArgsT&& ... args)
    {
        (*callable)(this, std::forward<ArgsT>(args)...);
    }
};

void functionToThread(Foo* pointerObject, int SomeTing)
{
    std::wcout << L"Running" << std::endl;
    std::wcout << L"Number: " << SomeTing << std::endl;
    return;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    Foo FooTest(&functionToThread, 3);
    return 0;
}