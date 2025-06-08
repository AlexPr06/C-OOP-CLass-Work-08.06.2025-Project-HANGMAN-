#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <algorithm>
#include <windows.h>


using namespace std;

// ����� ��������
const vector<wstring> HANGMAN_STATES = {
    L"  _______\n"
    L" |/      |\n"
    L" |       \n"
    L" |        \n"
    L" |        \n"
    L" |        \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |        \n"
    L" |        \n"
    L" |        \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |       |\n"
    L" |       |\n"
    L" |        \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |      \\|\n"
    L" |       |\n"
    L" |        \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |      \\|/\n"
    L" |       |\n"
    L" |        \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |      \\|/\n"
    L" |       |\n"
    L" |      / \n"
    L"_|___     \n",

    L"  _______\n"
    L" |/      |\n"
    L" |      (_)\n"
    L" |      \\|/\n"
    L" |       |\n"
    L" |      / \\\n"
    L"_|___     \n"
};

void printWord(const wstring& word, const vector<wchar_t>& guessed) {
    for (wchar_t c : word) {
        if (find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            wcout << c << L" ";
        }
        else {
            wcout << L"_ ";
        }
    }
    wcout << endl;
}

bool isWordGuessed(const wstring& word, const vector<wchar_t>& guessed) {
    for (wchar_t c : word) {
        if (find(guessed.begin(), guessed.end(), c) == guessed.end())
            return false;
    }
    return true;
}

int main() {
    // ������������ ��������� ������
    SetConsoleOutputCP(65001); // UTF-8
    SetConsoleCP(65001);       // UTF-8
    locale::global(locale("uk_UA.utf8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

    wstring word = L"��������";
    vector<wchar_t> guessed;
    int wrongGuesses = 0;
    const int maxWrong = HANGMAN_STATES.size() - 1;

    wcout << L"=== ��� ²Ѳ˲�� ===" << endl;

    while (wrongGuesses < maxWrong) {
        wcout << HANGMAN_STATES[wrongGuesses] << endl;
        printWord(word, guessed);

        wcout << L"����� �����: ";
        wchar_t guess;
        wcin >> guess;

        guess = towupper(guess); // ��� Unicode

        if (!iswalpha(guess)) {
            wcout << L"���� �����, ����� �����!" << endl;
            continue;
        }

        if (find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
            wcout << L"�� ��� ������ �� �����!" << endl;
            continue;
        }

        guessed.push_back(guess);

        if (word.find(guess) != wstring::npos) {
            wcout << L"���������!" << endl;
        }
        else {
            wcout << L"�����������!" << endl;
            wrongGuesses++;
        }

        if (isWordGuessed(word, guessed)) {
            wcout << L"\n�� ������! �����: " << word << endl;
            break;
        }
    }

    if (wrongGuesses == maxWrong) {
        wcout << HANGMAN_STATES[wrongGuesses] << endl;
        wcout << L"\n�� �������. ����� ����: " << word << endl;
    }

    return 0;
}
