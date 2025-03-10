#include "header.h"


static const std::wstring valueFreqStart [] = {L"9100.000000", L"154500.000000", L"30060000.000000", L"1000500000.000000", L"1000200000.000000"};
static const std::wstring valueFreqStop [] = {L"149900.000000", L"29998500.000000", L"999900000.000000", L"5999500000.000000", L"5999400000.000000"};
static const std::wstring valueFreqSpan [] = {L"140800.000000", L"29844000.000000", L"969840000.000000", L"4999000000.000000", L"4999200000.000000"};
static const std::wstring valueFreqRBW [] = {L"200.000000", L"9000.000000", L"120000.000000", L"1000000.000000", L"120000.000000"};
static const std::wstring valueFreqVBW [] = {L"2000.000000", L"100000.000000", L"1000000.000000", L"10000000.000000", L"1000000.000000"};

struct fileTemplateOne {
    std::wstring sep = L",", type, version, date, mode, preamplifier, transducer,
            center_freq, cf_remains, freq_offset, fo_remains , start, start_remains,
            stop, stop_remains, span, span_remains, ref_level, ref_level_remains,
            level_offset, loffset_remains, rf_att, rfatt_remains, el_att,  elatt_remains,
            rbw, rbw_remains, vbw, vbw_remains, swt, swt_remains, sweep_count,
            window = L"1", window_remains = L"Frequency Sweep", ref_position, refpos_remains,
            level_range, levrange_remains, x_axis, y_axis, x_unit, y_unit;
    bool validHeader = true, validData = true, validNum = true;
};

struct trace { // : fileTemplateOne {
    std::wstring trace = L"1", trace_mode= L"AVERAGE",
            detector = L"RMS", values;
};

// *****************************

class fileWork {

    private:
    const std::wstring *freqStart = valueFreqStart;
    const std::wstring *freqStop = valueFreqStop;
    const std::wstring *freqSpan = valueFreqSpan;
    const std::wstring *freqRBW = valueFreqRBW;
    const std::wstring *freqVBW = valueFreqVBW;
    fileTemplateOne *templateOne = new fileTemplateOne;
    trace *valueTrace = new trace;
    bool validData;

// Функция разбиения прочитанной строки на слова
    std::vector <std::wstring> parsingWstring (std::wstring inText) {
        std::vector <std::wstring> res;
        int indF;

        do {
            indF = inText.find(separ);
            res.push_back(inText.substr(0, indF));
            inText = inText.substr(indF + 1);

        } while (inText.find(separ) != std::wstring::npos);

        if(!inText.empty()) {
            res.push_back(inText);
        }

        return res;
    }

// Проверка числа целого, дробного и отрицательного
    bool validNum (std::wstring &inTxt) {
        bool res = (inTxt.empty()) ? false: true;
        int point = 0;

        for(int i = 0; i < (int)inTxt.length(); i++){
            if(i == 0 && inTxt[i] == '-'){
                res &= true;
                continue;
            } else if(point == 0 && inTxt[i] == '.'){
                res &= true;
                point++;
                continue;
            }
            res &= inTxt[i] >= '0' && inTxt[i] <= '9';
        }

        return res;
    }

// Проверка числа натурального
    bool validNumNature (std::wstring &inTxt) {
        bool res = (inTxt.empty()) ? false: true;

        for(wchar_t intX : inTxt){
            res &= intX >= '0' && intX <= '9';
        }

        return res;
    }

// Функция загрузки содержимого в объект
    void textLoad (const std::wstring &inTxt) {
        std::wstring firstWord, secondWord, remains;

        std::vector<std::wstring> words = parsingWstring(inTxt);
        firstWord = words[0];
        secondWord = words[1];
        if (words.size() > 2) remains = words[2];

//        std::wcout << L"fw = " << firstWord << L"\tsw = " << secondWord << std::endl;

        // Обработка Type
        if (firstWord == L"Type") {
            templateOne->type = secondWord;
        }

        // Обработка Version
        if (firstWord == L"Version") {
            templateOne->version = secondWord;
        }

        // Обработка Date
        if (firstWord == L"Date") {
            std::time_t curTime = time(0);
            std::string tt = ctime(&curTime);
            secondWord = convWStr.from_bytes(tt.substr(8, 2)) + L"." +
                         convWStr.from_bytes(tt.substr(4, 3)) + L" " +
                         convWStr.from_bytes(tt.substr(20, 4));
            templateOne->date = secondWord;
        }

        // Обработка Mode
        if (firstWord == L"Mode") {
            templateOne->mode = secondWord;
        }

        // Обработка Preamplifier
        if (firstWord == L"Preamplifier") {
            templateOne->preamplifier = secondWord;
        }

        // Обработка Transducer
        if (firstWord == L"Transducer") {
            templateOne->transducer = secondWord;
        }

        // Обработка Center Freq
        if (firstWord == L"Center Freq") {
            templateOne->center_freq = secondWord;
            templateOne->cf_remains = remains;
        }

        // Обработка Freq Offset
        if (firstWord == L"Freq Offset") {
            templateOne->freq_offset = secondWord;
            templateOne->fo_remains = remains;
        }

        // Обработка Start
        if (firstWord == L"Start") {
            templateOne->start = secondWord;
            templateOne->start_remains = remains;
        }

        // Обработка Stop
        if (firstWord == L"Stop") {
            templateOne->stop = secondWord;
            templateOne->stop_remains = remains;
        }

        // Обработка Span
        if (firstWord == L"Span") {
            templateOne->span = secondWord;
            templateOne->span_remains = remains;
        }

        // Обработка Ref Level
        if (firstWord == L"Ref Level") {
            templateOne->ref_level = secondWord;
            templateOne->ref_level_remains = remains;
        }

        // Обработка Level Offset
        if (firstWord == L"Level Offset") {
            templateOne->level_offset = secondWord;
            templateOne->loffset_remains = remains;
        }

        // Обработка Rf Att
        if (firstWord == L"Rf Att") {
            templateOne->rf_att = secondWord;
            templateOne->rfatt_remains = remains;
        }

        // Обработка El Att
        if (firstWord == L"El Att") {
            templateOne->el_att = secondWord;
            templateOne->elatt_remains = remains;
        }

        // Обработка RBW
        if (firstWord == L"RBW") {
            templateOne->rbw = secondWord;
            templateOne->rbw_remains = remains;
        }

        // Обработка VBW
        if (firstWord == L"VBW") {
            templateOne->vbw = secondWord;
            templateOne->vbw_remains = remains;
        }

        // Обработка SWT
        if (firstWord == L"SWT") {
            templateOne->swt = secondWord;
            templateOne->swt_remains = remains;
        }

        // Обработка Sweep Count
        if (firstWord == L"Sweep Count") {
            templateOne->sweep_count = secondWord;
        }

        // Обработка Window
        if (firstWord == L"Window") {
            templateOne->window = secondWord;
            templateOne->window_remains = remains;
        }

        // Обработка Ref Position
        if (firstWord == L"Ref Position") {
            templateOne->ref_position = secondWord;
            templateOne->refpos_remains = remains;
        }

        // Обработка Level Range
        if (firstWord == L"Level Range") {
            templateOne->level_range = secondWord;
            templateOne->levrange_remains = remains;
        }

        // Обработка x-Axis
        if (firstWord == L"x-Axis") {
            templateOne->x_axis = secondWord;
        }

        // Обработка y-Axis
        if (firstWord == L"y-Axis") {
            templateOne->y_axis = secondWord;
        }

        // Обработка x-Unit
        if (firstWord == L"x-Unit") {
            templateOne->x_unit = secondWord;
        }

        // Обработка y-Unit
        if (firstWord == L"y-Unit") {
            templateOne->y_unit = secondWord;
        }

        // Обработка значений вида 10e-06   27.3e-23
        if (secondWord.find(L"e-") != std::wstring::npos) {
            int indF = secondWord.find(L"e-");
            std::wstring swOne = secondWord.substr(0, indF);
            std::wstring swTwo = secondWord.substr(indF + 2);
            std::wstring tmpTxt;

            if (validNum(swOne) && validNumNature(swTwo)) {
                int numDig = swOne.substr(0,swOne.find(L'.')).length();
                int swPow = std::stoi(swTwo) + numDig;
                secondWord = (std::stoi(swOne) < 0) ? L"-0." : L"0.";

                for (int i = 0; i < swPow; i++) {
                    secondWord.push_back(L'0');
                }

                for (int i = 0; i < swOne.length(); i++) {
                    if (swOne[i] != L'.') {
                        secondWord.push_back(swOne[i]);
                    }
                }
                validData &= true;
            } else {
                validData = false;
            }
        }

    }

//        double tempNum = 0;
//        int numAftePoint = 0;
//        // Заполняем частоты
//        if (firstWord == L"Start" || firstWord == L"Stop" || firstWord == L"Span") {
//            freqStart = (firstWord == L"Start" && validNum(secondWord)) ? std::stoll(secondWord) : freqStart;
//            freqStop = (firstWord == L"Stop" && validNum(secondWord)) ? std::stoll(secondWord) : freqStop;
//            freqSpan = (firstWord == L"Span" && validNum(secondWord)) ? std::stoll(secondWord) : freqSpan;
//        }
//
//        // Значение RBW, VBW
//        if (firstWord == "RBW" || firstWord == "VBW") {
//            valueRBW = (firstWord == "RBW" && validNum(secondWord)) ? std::stoi(secondWord) : valueRBW;
//            valueVBW = (firstWord == "VBW" && validNum(secondWord)) ? std::stoi(secondWord) : valueVBW;
//        }
//
//        // Проверим начальные установки
//        if (firstWord == "y-Unit") {
//            bool valid = true;
//
//            if (freqStart == 9100) {
//                valid &= (freqStop == 149900);
//                valid &= (freqSpan == freqStop - freqStart);
//                valid &= (valueRBW == 200);
//                valid &= (valueVBW == 2000);
//
//            } else if (freqStart == 154500) {
//                valid &= (freqStop == 29998500);
//                valid &= (freqSpan == freqStop - freqStart);
//                valid &= (valueRBW == 9000);
//                valid &= (valueVBW == 100000);
//
//            } else if (freqStart == 30060000) {
//                valid &= (freqStop == 999900000);
//                valid &= (freqSpan == freqStop - freqStart);
//                valid &= (valueRBW == 120000);
//                valid &= (valueVBW == 1000000);
//
//            } else if (freqStart == 1000200000) {
//                valid &= (freqStop == 5999400000);
//                valid &= (freqSpan == freqStop - freqStart);
//                valid &= (valueRBW == 1000000);
//                valid &= (valueVBW == 10000000);
//
//            } else if (freqStart == 1000500000) {
//                valid &= (freqStop == 5999500000);
//                valid &= (freqSpan == freqStop - freqStart);
//                valid &= (valueRBW == 1000000);
//                valid &= (valueVBW == 10000000);
//            } else {
//                valid = false;
//            }
//            // Выводим сообщение если данные не верны
//            if (!valid) {
//                return "error:Check the initial settings!";
//            }
//        }
//
//        if (firstWord == "Trace" && validNum(secondWord)) {
//            valuePoint = 0;
//            numPoint = 0;
//            numTrace = std::stoi(secondWord);
//        }
//
//        if (firstWord == "Values") {
//            valuePoint = (validNum(secondWord)) ? std::stoi(secondWord) : valuePoint;
//        }
//
//        if (validNum(firstWord)) {
//
//
//
//            // Подсчитываем количество записей в Trace
//            if (validNum(secondWord)) {
//
//                std::istringstream doublef(secondWord);
//                doublef >> tempNum;
//                doublef.str("");                                   // Обнуление потока
//
//                tempNum *= (rand() % 5 + 98) * 0.01;              // Изменяем значение (rand() % (102 - 98 + 1) + 98) * 0.01;
//
//                secondWord = doubleToString(tempNum, numAftePoint);
//
//            } else {
//                return "error:Error in reading amplitude values at frequencies " + firstWord + "! \nFile: " + fileNew.string();
//            }
//            numPoint++;
//            // Проверяем правильность заполнения трейсов
//            if (numPoint == 0 && firstWord != std::to_string(freqStart)) {                   // Проверяем точку начала
//                return "error:Check the starting frequency value! Trace " + std::to_string(numTrace) + "! \nFile: " + fileNew.string();
//
//            } else if (numPoint == valuePoint && firstWord != std::to_string(freqStop)) {     // Проверяем точку останова
//                return "error:Check the value of the final frequency! Trace " + std::to_string(numTrace) + "!\n" + fileNew.string();
//
//            } else if (numPoint != valuePoint && firstWord == std::to_string(freqStop)) {     // Проверяем количество строк в трейсе
//                return "error:The number of calculation points differs from the number of lines in Trace " + std::to_string(numTrace) + "!\n" + fileNew.string();
//            }
//        }
//
//        if (inTxt == "") {
//            return inTxt;
//        }
//
//        return (remains == "") ? firstWord + "," + secondWord + "," : firstWord + "," + secondWord + "," + remains;
//    }


    public:
    fileWork(){}

    fileWork(FS_PATH &inPathFile) {
        FILE_IN fileSourse;

        fileSourse.exceptions(FILE_IN::badbit);// | FILE_IN::failbit);
        try {
            fileSourse.open(inPathFile, std::ios::in);
            std::wstring readTxt;
            int k = 1;

//            while(std::getline(fileSourse, readTxt)) {
            while(std::getline(fileSourse, readTxt)) { // && readTxt.find(L"Values") == std::wstring::npos) {
                if (readTxt.find(L"sep") != std::wstring::npos) {
                    // Определяем разделитель sep
                    separ = readTxt.substr(4, 1);

                } else {
                    if (inPathFile.extension().generic_wstring() == L".DAT") {
                        separ = L";";
                    }

                    textLoad(readTxt);



                }



            }


//            std::wcout << L"read = " << templateOne->date << L"\tsep = " << separ << std::endl;

            system("pause");

            fileSourse.close();

        } catch (const std::exception& e) {
            std::wcout << L"Произошла ошибка чтения файла " << inPathFile.wstring() << L"!" << std::endl;
            std::wcout << L"err = " << e.what() << std::endl;
            fileSourse.close();
            system("pause");
        }


    }


    int ddd = 123;


    std::wstring getFreqStart(int ind) {
        return freqStart[ind];
    }






    ~fileWork(){}
};





