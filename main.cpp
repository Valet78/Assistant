#include "header.h"

int main() {
    std::string askAction = "";
    setlocale(LC_ALL,"Russian");

    do{
        std::wcout << L"\t** Программа \"Ассистент\" **" << std::endl;
        askAction = selectAction();

        if(askAction == "1") {              // Проверка корректности файлов CSV




        } else if(askAction == "10") {      // Проверка корректности и генерирование файлов CSV.




        } else if(askAction == "2") {       // Проверка корректности файлов DAT.




        } else if(askAction == "20") {      // Проверка корректности и генерирование файлов DAT.




        } else if(askAction == "3") {       // Подготовка шаблона СС для одного сектора.




        } else if(askAction == "4") {       // Подготовка шаблона СС для 12 секторов.




        } else if(askAction == "5") {       // Переименование файлов.



        }

    } while(askAction != "6");

    std::wcerr << L"Программа будет закрыта. До встречи." << std::endl;
    system("pause");
    return 0;
}

// ***************************************************

// Выбор действия
std::string selectAction() {
    std::string resTxt = "";
    std::string action[]{"1","2","3","4","5","6","10","20"};
    bool valid = true;

    do {
        std::wcout << std::endl << L"Расположите файлы в папке Data и выберите действие." << std::endl;
        std::wcout << L"1. Проверка корректности файлов CSV." << std::endl;
        std::wcout << L"2. Проверка корректности файлов DAT." << std::endl;
        std::wcout << L"3. Подготовка шаблона СС для одного сектора." << std::endl;
        std::wcout << L"4. Подготовка шаблона СС для 12 секторов." << std::endl;
        std::wcout << L"5. Переименование файлов." << std::endl;
        std::wcout << L"6. Выход из программы." << std::endl;
        std::wcout << "**************************************" << std::endl;
        std::wcout << L"Ваш выбор: ";
        std::getline(std::cin, resTxt);
        // Обрежем "случайные" пробелы до и после слова
        resTxt = truncSpaces(resTxt);
        valid = std::find(begin(action), end(action), resTxt) != end(action);

        if (resTxt.empty()) {
            std::wcerr << std::endl << L"Вы забыли сделать выбор! Полпробуйте снова." << std::endl;
        } else if (!valid) {
            std::wcerr << std::endl << L"Выбирайте действия из указанных выше." << std::endl;
        }

    } while (!valid);

    return resTxt;
}

// Отсечение пробелов в строке с двух сторон
std::string truncSpaces(std::string inTxt) {
    inTxt = std::regex_replace(inTxt, std::regex("^\\s+"), "");
    inTxt = std::regex_replace(inTxt, std::regex("\\s+$"), "");
    return inTxt;
}
