#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Удаляет пробелы из строки
string deleteprobels(string str) {
    int startPos = str.find_first_not_of(" \t");
    if (startPos != string::npos) {
        return str.substr(startPos);
    }
    return "";
}

void processWords(const string &filename) {
    ifstream inputFile(filename); // открываем исходный файл

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла '" << filename << "'." << endl;
        return;
    }

    string word;
    string oneSimbolWord; // Временная строка для хранения слов на одну букву

    char lastFirstBukva = '\0'; // Последняя обработанная буква

    while (getline(inputFile, word)) {
        // Убираем пробелы
        word = deleteprobels(word);

        if (word.empty()) continue; // пропускаем пустые строки

        char firstBukva = toupper(word[0]); // получаем первую заглавную букву слова

        // Если сменилась первая буква, записываем предыдущие слова в файл
        if (lastFirstBukva != firstBukva) {
            if (lastFirstBukva != '\0') { // если уже была какая-то буква
                string outputFilename = string(1, lastFirstBukva) + ".txt";
                ofstream fileWrite(outputFilename, ios::trunc); // открываем файл в режиме очистки
                
                if (!fileWrite.is_open()) {
                    cerr << "Ошибка записи в файл '" << outputFilename << "'." << endl;
                    continue;
                }

                fileWrite << oneSimbolWord; // записываем слова в файл
                fileWrite.close(); // закрываем файл
            }

            oneSimbolWord.clear(); // очищаем временную строку
            lastFirstBukva = firstBukva; // устанавливаем новую букву
        }

        // Добавляем слово в текущую группу
        oneSimbolWord += word + "\n";
    }

    // Обработка последней группы слов
    if (!oneSimbolWord.empty()) {
        string outputFilename = string(1, lastFirstBukva) + ".txt";
        ofstream fileWrite(outputFilename, ios::trunc); // открываем файл в режиме очистки
        
        if (!fileWrite.is_open()) {
            cerr << "Ошибка записи в файл '" << outputFilename << "'." << endl;
            return;
        }

        fileWrite << oneSimbolWord; // записываем оставшиеся слова
        fileWrite.close(); // закрываем файл
    }

    inputFile.close(); // закрываем исходный файл
}

int main() {
    const string fileName = "words.txt"; // имя исходного файла

    processWords(fileName);
    cout << "Файлы созданы успешно." << endl;

    return 0;
}