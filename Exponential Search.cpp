#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;

// Вспомогательная функция бинарного поиска
int binarySearch(const vector<int>& vec, int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Если элемент найден, возвращаем его индекс
        if (vec[mid] == x) {
            return mid;
        }

        // Если искомый элемент меньше, ищем в левой половине
        if (vec[mid] > x) {
            right = mid - 1;
        }
        // Иначе ищем в правой половине
        else {
            left = mid + 1;
        }
    }

    // Если элемент не найден, возвращаем -1
    return -1;
}

// Функция экспоненциального поиска
int exponentialSearch(const vector<int>& vec, int n, int x) {
    // Если искомый элемент находится в начале массива
    if (vec[0] == x) {
        return 0;
    }

    // Экспоненциальное увеличение диапазона
    int i = 1;
    while (i < n && vec[i] <= x) {
        i *= 2; // Увеличиваем диапазон вдвое
    }

    // Выполняем бинарный поиск в найденном интервале
    return binarySearch(vec, i / 2, min(i, n - 1), x);
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }
    int n = vec.size(); // Размер вектора

    // Открываем файл для записи результатов
    ofstream outputFile("search_results.txt");
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }

    // Записываем заголовок в файл
    outputFile << "Номер элемента,Время поиска (нс)" << endl;

    // Измеряем время работы алгоритма для каждого элемента
    for (int x = 0; x < n; x += 10000) {
        int z = vec[x]; // Искомый элемент

        auto start = chrono::high_resolution_clock::now(); // Начало измерения времени

        int result = exponentialSearch(vec, n, z); // Вызов функции поиска

        auto end = chrono::high_resolution_clock::now(); // Конец измерения времени
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); // Время в наносекундах

        // Записываем результат в файл
        outputFile << x << " " << duration << endl;

        // Вывод прогресса в консоль
        if (x % 10000 == 0) {
            cout << "Элем " << x << " Врем " << duration << " нс" << endl;
        }
    }

    // Закрываем файл
    outputFile.close();

    cout << "Результаты записаны в файл search_results.txt" << endl;

    return 0;
}