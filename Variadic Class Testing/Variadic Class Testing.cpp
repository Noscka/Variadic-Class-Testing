#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <functional>

/*
TODO:
- Make the constructor run the loading screen (later make it the StartLoading) if possible
*/

class Foo
{
    std::function<void(Foo*)> callback;

public:
    std::wstring String;

    template <typename F, typename ... ArgsT>
    Foo(F&& callable, ArgsT&& ... args) : callback([=](Foo* var) { callable(var, args...); })
    {}

    void RunFoo()
    {
        callback(this, L"Innit");
    }
};

void function(Foo* param, std::wstring input)
{
    std::wcout << L"Running" << std::endl;
    param->String = input;
}

void SomeFunction(std::wstring ArgInput)
{
    std::wcout << ArgInput << std::endl;
}

template<typename ... VariadicArgs>
void PassToFunction(void (*Function)(VariadicArgs&& ...), VariadicArgs ... Args)
{
    return (Args + ...);
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    Foo FooTing(&function, L"Input");
    wprintf(FooTing.String.c_str());
    FooTing.RunFoo();
    return 0;
}