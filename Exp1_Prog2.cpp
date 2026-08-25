#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string s;

    cout << "Enter a word: " << endl;
    cin >> s;


    cout << "Length: " << s.length() << endl;

    for(char &c : s)
    {
        c = toupper(c);
    }

    cout << "Upper: " << s << endl;

    bool pal = true;

    for (size_t i = 0, j = s.size() - 1; i < j; ++i, --j)
    {
        if (s[i] != s[j])
        {
            pal = false;
            break;
        }
    }

    cout << s << (pal ? " is": " is not") << " a palindrome" << endl;

    size_t pos = s.find("AN");

    if (pos != string :: npos)
    cout<<"'AN' found at index " << pos << endl;
    else
    cout << "'AN' not found" << endl;

    return 0;
}