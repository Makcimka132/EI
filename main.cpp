#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>

using namespace std;

map <string,string> vars;

string get_word(string line, int index)
{
    return line.substr(index, line.find(" "));
}
string StringReplacer(const string inputStr, const string src, const string dst)
{
    string result(inputStr);
    size_t pos = result.find(src);
    while(pos != string::npos) {
        result.replace(pos, src.size(), dst);
        pos = result.find(src, pos);
    }
    return result;
}
string trim(string s)
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
int get_words_c(string stri)
{
    const char* str = stri.c_str();
    if(str[0] == NULL) return 0;
    int coun = 0;
    for(int i=0; i<strlen(str); i++)
    {
        if(str[i] != ' ' && str[i] != NULL)
        {
            if(str[i+1] == ' ' && str[i+2] != NULL && str[i+2] != ' ') coun++;
        }
    }
    return coun = coun + 1;
}
string replace_vars(string stri)
{
    stri = trim(stri);
    for(int i=0; i<get_words_c(stri); i++)
    {
        string currword = get_word(stri, i);
        if(currword[0] != '%') continue;
        string var_name = StringReplacer(currword, "%", "");
        stri = StringReplacer(stri, currword, vars[var_name]);
    }
    return stri;
}

int main(int argc, char** argv)
{
    string line;
    string file_name = "";
    if(argv[1] != NULL) file_name = argv[1];
    else getline(cin, file_name);

    ifstream file(file_name); // файл из которого читаем

    while(getline(file, line)){ // пока не достигнут конец файла класть очередную строку в переменную
        string func = get_word(line, 0);
        func = str_tolower(func);
        line = StringReplacer(line, get_word(line, 0), "");
        const char* func_cstr = func.c_str();
        if(func == "print"){
                line = trim(line);
                line = replace_vars(line);
                cout << line << endl;
        }
        else if(func == "var"){
                line = trim(line);
                string var_name = get_word(line, 0);
                vars[var_name] = trim(StringReplacer(line, var_name, ""));
        }
        else {cout << "Unknow command: '" << func << "'!" << endl; return 1;}
    }

    file.close(); // обязательно закрываем файл что бы не повредить его

    return 0;
}
