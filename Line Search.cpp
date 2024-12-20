#include <iostream>
#include <fstream> // Для работы с файлами
#include <vector>  // Для использования std::vector
#include <chrono>  // Для измерения времени
using namespace std;

// Функция линейного поиска
int linearSearch(const vector<int>& vec, int x) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "RU");

    // Создаем вектор
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }

    // Открываем файл для записи результатов
    ofstream outFile("search_results.txt");
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    // Измеряем время работы алгоритма для каждого элемента
    for (int x = 0; x < vec.size(); x += 10000) {
        int z = vec[x]; // Искомый элемент

        auto start = chrono::high_resolution_clock::now(); // Начало измерения времени
        int result = linearSearch(vec, z);
        auto end = chrono::high_resolution_clock::now();   // Конец измерения времени

        // Вычисляем время выполнения в наносекундах
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // Записываем результат в файл
        outFile << x << " " << duration << endl;
        if (x % 10000 == 0) {
            cout << "Размер " << x << ", Время " << duration << " нс" << endl;
        }
    }

    // Закрываем файл
    outFile.close();

    cout << "Результаты записаны в файл 'search_results.txt'." << endl;
    return 0;
}