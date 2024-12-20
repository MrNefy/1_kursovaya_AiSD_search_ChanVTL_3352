#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

// Функция интерполяционного поиска
// с использованием интерполяционного поиска
int interpolationSearch(const vector<int>& arr, int lo, int hi, int x)
{
    int pos;

    // Проверяем, что элемент находится в пределах массива
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {

        // Вычисляем позицию с учетом равномерного распределения
        pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        // Если элемент найден
        if (arr[pos] == x)
            return pos;

        // Если x больше, ищем в правой подмассиве
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, hi, x);

        // Если x меньше, ищем в левой подмассиве
        if (arr[pos] > x)
            return interpolationSearch(arr, lo, pos - 1, x);
    }
    return -1; // Элемент не найден
}
int main() {
    setlocale(LC_ALL, "RU");
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }
    int n = vec.size(); // Размер вектора

    // Открываем файл для записи результатов
    ofstream outFile("search_results.txt");
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }

    // Проходим по всем элементам вектора и измеряем время поиска
    for (int i = 0; i < n; i += 10000) {
        int x = vec[i]; // Искомый элемент

        // Засекаем время перед выполнением поиска
        auto start = chrono::high_resolution_clock::now();

        // Вызов функции интерполяционного поиска
        int result = interpolationSearch(vec, 0, n - 1, x);

        // Засекаем время после выполнения поиска
        auto end = chrono::high_resolution_clock::now();

        // Вычисляем время выполнения в наносекундах
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // Записываем результат в файл
        outFile << i << " " << duration << endl;

        // Вывод результата в консоль (опционально)
        if (i % 10000 == 0) {
            cout << "Элем " << x << " Врем " << duration << " нс" << endl;
        }
    }

    // Закрываем файл
    outFile.close();

    cout << "Результаты записаны в файл search_results.txt" << endl;

    return 0;
}