#include "header.h"
#include "fileWork.cpp"

int main() {
//    setlocale(LC_ALL,"Russian");
//    system("chcp 1251");
    std::setlocale(LC_ALL, "Russian_Russia.1251"); //вместо 2-х строк выше

    std::srand(std::time(nullptr));
    std::wstring askAction;

    // Проверяем наличие папок и создаем их, если они отсутствуют
    if(!FS_CLASS::exists(dirData)) FS_CLASS::create_directory(dirData);
    if(!FS_CLASS::exists(dirGen)) FS_CLASS::create_directory(dirGen);

    int numFiles = scanFolder(dirData);
    if (numFiles == -1) {
        std::wcout << L"Произошла ошибка при сканировании папки DATA! Программа будет закрыта." << std::endl;
        system("pause");
        return numFiles;

    } else if (numFiles == 0) {
        std::wcout << L"Папка DATA пустая! Загрузите файлы для обработки и запустите программу снова." << std::endl;
        system("pause");
        return numFiles;
    }

    do{
        system("cls");
        std::wcout << std::endl << L"\t** Программа " ASSISTANT_HEADER_H " **" << std::endl;
        askAction = selectAction();

        // Проверка корректности файлов CSV
        if(askAction == L"1") {

            if (vecFileCSV.size() == 0) {
                std::wcerr << L"Файлов с расширением CVS в папке DATA не обнаружено!" << std::endl;
                std::wcerr << L"Загрузите файлы для обработки и запустите программу снова." << std::endl;
                system("pause");
                return 0;
            }

            if (!makeDirGenPath()){
                std::wcerr << L"Некоторые папки не были созданы!" << std::endl;
            } else {
                std::wcerr << L"Созданы необходимые папки." << std::endl;

                fileWork *fw = new fileWork(vecFileCSV[0]);
//                std::wcout << L"k1 = " << fw->getFreqStart(0) << std::endl;
//                std::wcout << L"___________________" << std::endl;
                fileWork *fs = new fileWork(vecFileDAT[0]);
//                std::wcout << L"k2 = " << fs->getFreqStart(0) << std::endl;
//                delete fw;
//                delete fs;


            };




//            fs::path dd = vecFileCSV[0].relative_path();
//            dd = swapDir(dd);
//            std::wstring tt = dd.generic_wstring();
//            std::ofstream {dd};

//
//            std::wcout  << L"fstart =" << fw.getFreqStart(4) << std::endl;
//            std::wcout  << L"mode = " << fw.templateOne->mode << std::endl;
//            valueFreqStart[0];




            system("pause");

        } else if(askAction == L"10") {      // Проверка корректности и генерирование файлов CSV.

            if (vecFileCSV.size() == 0) {
                std::wcout << L"Файлов с расширением CVS в папке DATA не обнаружено!" << std::endl;
                std::wcout << L"Загрузите файлы для обработки и запустите программу снова." << std::endl;
                system("pause");
                return 0;
            }


//            bool vseOk = makeDirGenPath();
//            if(vseOk) {
//                std::wcout << L"Папки созданы." << std::endl;
//            } else {
//                std::wcout << L"Папки не были созданы!" << std::endl;
//            }







        } else if(askAction == L"2") {       // Проверка корректности файлов DAT.

            if (vecFileDAT.size() == 0) {
                std::wcout << L"Файлов с расширением DAT в папке DATA не обнаружено!" << std::endl;
                std::wcout << L"Загрузите файлы для обработки и запустите программу снова." << std::endl;
                system("pause");
                return 0;
            }





        }
  /*

        else if(askAction == L"20") {      // Проверка корректности и генерирование файлов DAT.




//            bool vseOk = makeDirGenPath();
//            if(vseOk) {
//                std::wcout << L"Папки созданы." << std::endl;
//            } else {
//                std::wcout << L"Папки не были созданы!" << std::endl;
//            }




        } else if(askAction == L"3") {       // Подготовка шаблона СС для одного сектора.




        } else if(askAction == L"4") {       // Подготовка шаблона СС для 12 секторов.




        } else if(askAction == L"5") {       // Переименование файлов.



        }
*/
    } while(askAction != L"6");

    std::wcerr << L"Программа будет закрыта. До встречи." << std::endl;
    system("pause");
    return 0;
}

// ***************************************************

// Сканирование каталога, разделение по папкам файлов
int scanFolder(FS_PATH &inDir) {
    int num = 0;

    if(FS_CLASS::recursive_directory_iterator(dirData) != end(FS_CLASS::recursive_directory_iterator(dirData))) {

        for (auto const& dir_entry : FS_CLASS::recursive_directory_iterator(dirData)) {

            if (dir_entry.is_directory()) {
                vecDirData.push_back(dir_entry.path());

            } else if (dir_entry.path().extension() == ".CSV"){
                vecFileCSV.push_back(dir_entry.path());
                num++;

            } else if (dir_entry.path().extension() == ".DAT") {
                vecFileDAT.push_back(dir_entry.path());
                num++;

            }
        }

    } else {

        return -1;
    }

    return num;
}

// Выбор действия
std::wstring selectAction() {
    std::wstring resTxt;
    std::wstring action[]{L"1",L"2",L"3",L"4",L"5",L"6",L"10",L"20"};
    bool valid = true;

    do {
        std::wcout << std::endl << L"Расположите файлы в папке Data и выберите действие." << std::endl;
        std::wcout << L"1. Проверка корректности файлов CSV." << std::endl;
//        std::wcout << L"2. Проверка корректности файлов DAT." << std::endl;
//        std::wcout << L"3. Подготовка шаблона СС для одного сектора." << std::endl;
//        std::wcout << L"4. Подготовка шаблона СС для 12 секторов." << std::endl;
//        std::wcout << L"5. Переименование файлов." << std::endl;
        std::wcout << L"6. Выход из программы." << std::endl;
        std::wcout << "**************************************" << std::endl;
        std::wcout << L"Ваш выбор: ";
        std::getline(std::wcin, resTxt);

        resTxt = truncSpaces(resTxt);               // Обрежем "случайные" пробелы до и после слова
        valid = std::find(begin(action), end(action), resTxt) != end(action);

        if (resTxt.empty()) {
            std::wcerr << std::endl << L"Вы забыли сделать выбор! Попробуйте снова." << std::endl;
        } else if (!valid) {
            std::wcerr << std::endl << L"Выбирайте действия из указанных выше." << std::endl;
        }

    } while (!valid);

    return resTxt;
}

// Отсечение пробелов в строке с двух сторон
std::wstring truncSpaces(std::wstring inTxt) {
    inTxt = std::regex_replace(inTxt, std::wregex(L"^\\s+"), L"");
    inTxt = std::regex_replace(inTxt, std::wregex(L"\\s+$"), L"");
    return inTxt;
}
//
//// Проверка числа
//bool validNum (std::wstring inTxt) {
//    bool res = (inTxt.empty()) ? false: true;
//    int point = 0;
//
//    for(int i = 0; i < (int)inTxt.length(); i++){
//        if(i == 0 && inTxt[i] == '-'){
//            res &= true;
//            continue;
//        } else if(point == 0 && inTxt[i] == '.'){
//            res &= true;
//            point++;
//            continue;
//        }
//        res &= inTxt[i] >= '0' && inTxt[i] <= '9';
//    }
//
//    return res;
//}

// Генерируем случайное число в диапазоне
int randNum(int &&inStart, int &&inStop) {
    return inStart + std::rand() % (inStart - inStop + 1);
}

// Формируем адрес папки для генерированных файлов из адреса исходного файла
bool makeDirGenPath () {
    bool res = true;

    for (FS_PATH rr : vecDirData) {
        if (!exists(swapDir(rr))) {
            res &= FS_CLASS::create_directory(swapDir(rr));
        }
    }

    return res;
}

// Заменим Data на Generated
FS_PATH swapDir(FS_PATH &inDir) {
    std::wstring pp =  inDir.generic_wstring();
    int ind = pp.find(L'/') + 1;
    pp = dirGen.generic_wstring() + L"/" + pp.substr(ind, pp.length() - ind);

    return (FS_PATH) pp;
}