#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;

// ��������������� ������� ��������� ������
int binarySearch(const vector<int>& vec, int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // ���� ������� ������, ���������� ��� ������
        if (vec[mid] == x) {
            return mid;
        }

        // ���� ������� ������� ������, ���� � ����� ��������
        if (vec[mid] > x) {
            right = mid - 1;
        }
        // ����� ���� � ������ ��������
        else {
            left = mid + 1;
        }
    }

    // ���� ������� �� ������, ���������� -1
    return -1;
}

// ������� ����������������� ������
int exponentialSearch(const vector<int>& vec, int n, int x) {
    // ���� ������� ������� ��������� � ������ �������
    if (vec[0] == x) {
        return 0;
    }

    // ���������������� ���������� ���������
    int i = 1;
    while (i < n && vec[i] <= x) {
        i *= 2; // ����������� �������� �����
    }

    // ��������� �������� ����� � ��������� ���������
    return binarySearch(vec, i / 2, min(i, n - 1), x);
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }
    int n = vec.size(); // ������ �������

    // ��������� ���� ��� ������ �����������
    ofstream outputFile("search_results.txt");
    if (!outputFile.is_open()) {
        cerr << "������ �������� ����� ��� ������!" << endl;
        return 1;
    }

    // ���������� ��������� � ����
    outputFile << "����� ��������,����� ������ (��)" << endl;

    // �������� ����� ������ ��������� ��� ������� ��������
    for (int x = 0; x < n; x += 10000) {
        int z = vec[x]; // ������� �������

        auto start = chrono::high_resolution_clock::now(); // ������ ��������� �������

        int result = exponentialSearch(vec, n, z); // ����� ������� ������

        auto end = chrono::high_resolution_clock::now(); // ����� ��������� �������
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); // ����� � ������������

        // ���������� ��������� � ����
        outputFile << x << " " << duration << endl;

        // ����� ��������� � �������
        if (x % 10000 == 0) {
            cout << "���� " << x << " ���� " << duration << " ��" << endl;
        }
    }

    // ��������� ����
    outputFile.close();

    cout << "���������� �������� � ���� search_results.txt" << endl;

    return 0;
}