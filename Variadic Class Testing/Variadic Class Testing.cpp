#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>

void SomeFunction(std::wstring ArgInput)
{
    std::wcout << ArgInput << std::endl;
}

template<typename ... VariadicArgs>
void PassToFunction(void (*Function)(VariadicArgs&& ...), VariadicArgs ... Args)
{
    return (Args + ...);
}

bool has_dups(int a[], int n)
{
    //assume no duplicates in the array
    int has_duplicates = 0;

    for (int i = 0; i < n; i++)
    {
        //variable to track the number of occurences of the current i element in a[]
        int number_of_occurences = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[i] == a[j] && i != j)
            {
                has_duplicates = 1;
                return has_duplicates;
            }
        }
    }
    return has_duplicates;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    int abc[]{1, 2, 2, 4, 5};

    std::wcout << (has_dups(abc, 5) ? L"Has Dupes" : L"Hasn't dupes") << std::endl;

    return 0;
}