#include <iostream>
#include <fstream> // Для работы с файлами
#include <cmath>   // Для функции sqrt
#include <chrono>  // Для измерения времени
#include <vector>  // Для использования векторов
using namespace std;

// Функция прыжкового поиска
int jumpSearch(const vector<int>& vec, int x) {
    int n = vec.size(); // Размер вектора

    // Вычисляем размер прыжка (шаг)
    int step = sqrt(n);
    int prev = 0;

    // Прыгаем по вектору с шагом step
    while (vec[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // Элемент не найден
        }
    }

    // Выполняем линейный поиск в найденном диапазоне
    while (vec[prev] < x) {
        prev++;

        // Если достигли следующего блока или конца вектора
        if (prev == min(step, n)) {
            return -1; // Элемент не найден
        }
    }

    // Если элемент найден
    if (vec[prev] == x) {
        return prev;
    }

    // Если элемент не найден
    return -1;
}

int main() {
    setlocale(LC_ALL, "RU");

    // Создаем вектор и заполняем его значениями
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }

    // Открываем файл для записи результатов
    ofstream outFile("results.txt");
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    // Проходим по каждому элементу вектора
    for (int i = 0; i < vec.size(); i += 10000) {
        int x = vec[i]; // Искомый элемент

        // Засекаем время начала поиска
        auto start = chrono::high_resolution_clock::now();

        // Вызов функции прыжкового поиска
        int result = jumpSearch(vec, x);

        // Засекаем время окончания поиска
        auto end = chrono::high_resolution_clock::now();

        // Вычисляем время выполнения в наносекундах
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // Записываем результат в файл
        outFile << i << " " << duration << endl;

        // Вывод результата в консоль (опционально)
        if (i % 10000 == 0) {
            cout << "Элем " << i << " Врем " << duration << " нс" << endl;
        }
    }

    // Закрываем файл
    outFile.close();

    cout << "Результаты записаны в файл results.txt" << endl;

    return 0;
}