#pragma once
#ifndef ASSISTANT_HEADER_H
#define ASSISTANT_HEADER_H "\"Ассистент инженера ЛабСИ\""
#endif //ASSISTANT_HEADER_H

#define FS_CLASS std::filesystem
#define FS_PATH std::filesystem::path
#define FILE_OUT std::wofstream
#define FILE_IN std::wifstream


#include <iostream>
#include <regex>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <ctime>
#include <map>
#include <codecvt>  // Для конвертации строк в wstring

// Глобальные переменные
FS_PATH dirData {"Data"};
FS_PATH dirGen {"Generated"};
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convWStr; // Для конвертации строк в wstring
std::vector <FS_PATH> vecDirData, vecFileDAT, vecFileCSV;
std::wstring separ;
//wchar_t sep = ',';


std::wstring freqStart, freqStop, freqSpan, valueRBW, valueVBW;
FS_PATH projectPath = FS_CLASS::current_path();





// Функции
int scanFolder(FS_PATH &);                  // Сканирование каталога, разделение по папкам файлов
std::wstring selectAction();                // Выбор действия
std::wstring truncSpaces(std::wstring);     // Отсечение пробелов в строке с двух сторон
FS_PATH swapDir(FS_PATH &);                 // Заменим Data на Generated
bool makeDirGenPath ();                     // Создаем папки в Generated как в Data


//bool validNum (std::wstring);             // Проверка числа
int randNum(int &&, int &&);                // Генерируем случайное число в диапазоне




