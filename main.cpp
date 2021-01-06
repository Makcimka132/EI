#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

string get_word(string line, string delimiter, int index)
{
    return line.substr(index, line.find(delimiter));
}
string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
{
    std::string result(inputStr);
    size_t pos = result.find(src);
    while(pos != std::string::npos) {
        result.replace(pos, src.size(), dst);
        pos = result.find(src, pos);
    }
    return result;
}
string trim(string& s)
{
    const string& delimiters = " \f\n\r\t\v";
    return s.erase( s.find_last_not_of( delimiters ) + 1 ).erase( 0, s.erase( s.find_last_not_of( delimiters ) + 1 ).find_first_not_of( delimiters ) );
}
string str_tolower(string s) {
    transform(s.begin(), s.end(), s.begin(),
                // static_cast<int(*)(int)>(std::tolower)         // wrong
                // [](int c){ return std::tolower(c); }           // wrong
                // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

int main(int argc, char** argv)
{
    string line;
    string file_name = "";
    if(argv[1] != NULL) file_name = argv[1];
    else getline(cin, file_name);

    ifstream file(file_name); // файл из которого читаем (для линукс путь будет выглядеть по другому)

    while(getline(file, line)){ // пока не достигнут конец файла класть очередную строку в переменную
        string func = get_word(line, " ", 0);
        func = str_tolower(func);
        if(func == "print"){
                line = StringReplacer(line, get_word(line, " ", 0), "");
                line = trim(line);
                cout << line << endl;
                break;
        }
    }

    file.close(); // обязательно закрываем файл что бы не повредить его

    return 0;
}
