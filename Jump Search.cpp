#include <iostream>
#include <fstream> // ��� ������ � �������
#include <cmath>   // ��� ������� sqrt
#include <chrono>  // ��� ��������� �������
#include <vector>  // ��� ������������� ��������
using namespace std;

// ������� ���������� ������
int jumpSearch(const vector<int>& vec, int x) {
    int n = vec.size(); // ������ �������

    // ��������� ������ ������ (���)
    int step = sqrt(n);
    int prev = 0;

    // ������� �� ������� � ����� step
    while (vec[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // ������� �� ������
        }
    }

    // ��������� �������� ����� � ��������� ���������
    while (vec[prev] < x) {
        prev++;

        // ���� �������� ���������� ����� ��� ����� �������
        if (prev == min(step, n)) {
            return -1; // ������� �� ������
        }
    }

    // ���� ������� ������
    if (vec[prev] == x) {
        return prev;
    }

    // ���� ������� �� ������
    return -1;
}

int main() {
    setlocale(LC_ALL, "RU");

    // ������� ������ � ��������� ��� ����������
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }

    // ��������� ���� ��� ������ �����������
    ofstream outFile("results.txt");
    if (!outFile.is_open()) {
        cerr << "������ �������� �����!" << endl;
        return 1;
    }

    // �������� �� ������� �������� �������
    for (int i = 0; i < vec.size(); i += 10000) {
        int x = vec[i]; // ������� �������

        // �������� ����� ������ ������
        auto start = chrono::high_resolution_clock::now();

        // ����� ������� ���������� ������
        int result = jumpSearch(vec, x);

        // �������� ����� ��������� ������
        auto end = chrono::high_resolution_clock::now();

        // ��������� ����� ���������� � ������������
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // ���������� ��������� � ����
        outFile << i << " " << duration << endl;

        // ����� ���������� � ������� (�����������)
        if (i % 10000 == 0) {
            cout << "���� " << i << " ���� " << duration << " ��" << endl;
        }
    }

    // ��������� ����
    outFile.close();

    cout << "���������� �������� � ���� results.txt" << endl;

    return 0;
}