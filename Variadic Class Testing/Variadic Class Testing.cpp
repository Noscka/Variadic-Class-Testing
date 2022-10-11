#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <thread>

template <typename F, typename ... ArgsT>
void StartThread(F&& callable, ArgsT&& ... args)
{
    (*callable)(this, std::forward<ArgsT>(args)...);
}

void function(Foo* param, std::wstring input, int SomeTing)
{
    std::wcout << L"Running" << std::endl;
    std::wcout << L"Number: " << SomeTing << std::endl;
    param->String = input;
}

class Foo
{
public:
    std::wstring String;

    template <typename F, typename ... ArgsT>
    Foo(F&& callable, ArgsT&& ... args)
    {
        std::thread(function, std::forward<ArgsT>(args)...);
    }
};



int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    Foo FooTing(&function, L"Input", 2);
    wprintf(FooTing.String.c_str());
    return 0;
}