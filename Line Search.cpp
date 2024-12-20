#include <iostream>
#include <fstream> // ��� ������ � �������
#include <vector>  // ��� ������������� std::vector
#include <chrono>  // ��� ��������� �������
using namespace std;

// ������� ��������� ������
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

    // ������� ������
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }

    // ��������� ���� ��� ������ �����������
    ofstream outFile("search_results.txt");
    if (!outFile.is_open()) {
        cerr << "������ �������� �����!" << endl;
        return 1;
    }

    // �������� ����� ������ ��������� ��� ������� ��������
    for (int x = 0; x < vec.size(); x += 10000) {
        int z = vec[x]; // ������� �������

        auto start = chrono::high_resolution_clock::now(); // ������ ��������� �������
        int result = linearSearch(vec, z);
        auto end = chrono::high_resolution_clock::now();   // ����� ��������� �������

        // ��������� ����� ���������� � ������������
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // ���������� ��������� � ����
        outFile << x << " " << duration << endl;
        if (x % 10000 == 0) {
            cout << "������ " << x << ", ����� " << duration << " ��" << endl;
        }
    }

    // ��������� ����
    outFile.close();

    cout << "���������� �������� � ���� 'search_results.txt'." << endl;
    return 0;
}