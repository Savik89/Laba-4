#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void rFile(string& s){
    ifstream File("text.txt");
    if (!File.is_open())
    {
        cout << "Файл не открыт\n";
        exit(1);
    }
    while (!File.eof())
        getline(File, s);
    File.close();
}

void readString(string& s) {
    int choice;
    cout << "Считать из файла или ввести вручную?" << endl;
    cout << "1 - файл / 2 - ввести вручную;" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        rFile(s);
        break;
    case 2:
        system("cls");
        cout << "Введите строку: ";
        cin.ignore();
        getline(cin, s);
        break;
    default:
        cout << "Что-то пошло не так" << endl;
        exit(1);
        break;
    }
}

void removeSpaces(string& s) {
    while (s[0] == ' ')
        s.erase(0, 1);
    int len = s.length();
    int i = 0;
    while (i < len - 1) {
        if (s[i] == ' ' && s[i + 1] == ' ') {
            s.erase(i, 1);
            len -= 1;
        }
        else
            i++;
    }
}

void editMarks(string& s) {
    int len, count = 0;
    while (s[0] == ',' || s[0] == '!' || s[0] == '?' || s[0] == ';' || s[0] == ':' || s[0] == '-' || s[0] == '.')
        s.erase(0, 1);
    len = s.length();
    for (int i = 1; i < len; ++i) {
        if (s[i - 1] == ' ' && (s[i] == ',' || s[i] == '!' || s[i] == '?' || s[i] == ';' || s[i] == ':' || s[i] == '-'))
            s.erase(i - 1, 1);
        if (s[i - 1] == ',' || s[i - 1] == '!' || s[i - 1] == '?' || s[i - 1] == ';' || s[i - 1] == ':' || s[i - 1] == '-')
            if ((s[i] <= 90 && s[i] >= 65) || (s[i] <= 122 && s[i] >= 97))
                    s.insert(i, " ");
        if (s[i] == ',' || s[i] == '!' || s[i] == '?' || s[i] == ';' || s[i] == ':' || s[i] == '-')
            count++;
        else {
            if (count > 1) {
                s.erase(i - count + 1, count - 1);
                len -= count - 1;
            }
            count = 0;
        }
    }
    for (int i = 1; i < len; i++) {
        if (s[i - 1] == ',' || s[i - 1] == '!' || s[i - 1] == '?' || s[i - 1] == ';' || s[i - 1] == ':' || s[i - 1] == '-')
            if (s[i] == ',' || s[i] == '!' || s[i] == '?' || s[i] == ';' || s[i] == ':' || s[i] == '-')
                s.erase(i, 1);
    }
}

void editLetters(string& s) {
    int len = s.length();
    if (s[0] <= 122 && s[0] >= 97)
        s[0] -= 32;
    for (int i = 2; i < len; i++)
    {
        if ((s[i] <= 90 && s[i] >= 65) && (s[i - 2] != '.' && s[i - 2] != '!' && s[i - 2] != '?'))
            s[i] += 32;
        else 
            if ((s[i] <= 122 && s[i] >= 97) && ((s[i - 2] == '.') || (s[i - 2] == '!') || (s[i - 2] == '?')))
                s[i] -= 32;
    }
}

void editString(string& s) {
    removeSpaces(s);
    editMarks(s);
    removeSpaces(s);
    editLetters(s);
}

void printWords(string& s) {
    char s1[14];
    int count = 0;
    bool flag = false;
    s.append(" ");
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        if (s[i] != ' ') {
            s1[count] = s[i];
            count++;
        }
        else {
            if (s1[count-1] == ',' || s1[count-1] == '!' || s1[count-1] == '?' || s1[count-1] == ';' || s1[count-1] == ':' || s1[count-1] == '-' || s1[count-1] == '.')
                count--;
            s1[count+1] = '\0';
            for (int j = 0; j < count; j++) {
                for (int k = j; k < count; ++k) {
                    if (s1[j] == s1[k])
                        if ((s1[j] >= 97 && s1[j] <= 122) || (s1[j] >= 65 && s1[j] <= 90)) {
                            flag = true;
                            break;
                        }
                }
            }
            if (flag) {
                for (int a = 0; a < count; a++) {
                    cout << s1[a];
                }
                cout << " ";
            }
            flag = false;
            count = 0;
        }
    }
}

void replaceNumbers(string& s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] >= 48 && s[i] <= 57)
            s[i] += 49;
    }
    editLetters(s);
}

int findSubstring(string& s, string& subs) {
    int lenS = s.length();
    int lenSubs = subs.length();
    if (lenSubs > lenS)
        return -1;
    for (int i = 0; i < lenS - lenSubs; i++) {
        int j;
        for (j = 0; j < lenSubs; j++) {
            if (s[i + j] != subs[j])
                break;
        }
        if (j == lenSubs)
            return i;
    }
    return -2;
}

int main() {
    setlocale(0, "");
    string s, subs;
    int result;
    readString(s);
    cout << "\n1. Строка без изменений:\n" << s << endl;
    editString(s);
    cout << "2. Отформатированная строка:\n" << s << endl;
    cout << "3. Слова последовательности, в которых встречаются одинаковые буквы:\n";
    printWords(s);
    replaceNumbers(s);
    cout << "\n4. Последовательность с заменёнными цифрами на буквы латинского алфавита:\n" << s << endl;
    cout << "5. Введите подстроку, которую нужно найти:" << endl;
    cin.ignore();
    getline(cin, subs);
    result = findSubstring(s, subs);
    switch (result) {
    case -1:
        cout << "Подстрока длиннее самой строки! Так не бывает!";
        exit(0);
        break;
    case -2:
        cout << "Подстрока не найдена!";
        break;
    default:
        cout << "Подстрока найдена в позиции: " << result;
        break;
    }
}