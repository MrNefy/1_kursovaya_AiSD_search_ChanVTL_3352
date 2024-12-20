#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

// ������� ����������������� ������
// � �������������� ����������������� ������
int interpolationSearch(const vector<int>& arr, int lo, int hi, int x)
{
    int pos;

    // ���������, ��� ������� ��������� � �������� �������
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {

        // ��������� ������� � ������ ������������ �������������
        pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        // ���� ������� ������
        if (arr[pos] == x)
            return pos;

        // ���� x ������, ���� � ������ ����������
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, hi, x);

        // ���� x ������, ���� � ����� ����������
        if (arr[pos] > x)
            return interpolationSearch(arr, lo, pos - 1, x);
    }
    return -1; // ������� �� ������
}
int main() {
    setlocale(LC_ALL, "RU");
    vector<int> vec(100000000);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = i;
    }
    int n = vec.size(); // ������ �������

    // ��������� ���� ��� ������ �����������
    ofstream outFile("search_results.txt");
    if (!outFile.is_open()) {
        cerr << "������ �������� ����� ��� ������!" << endl;
        return 1;
    }

    // �������� �� ���� ��������� ������� � �������� ����� ������
    for (int i = 0; i < n; i += 10000) {
        int x = vec[i]; // ������� �������

        // �������� ����� ����� ����������� ������
        auto start = chrono::high_resolution_clock::now();

        // ����� ������� ����������������� ������
        int result = interpolationSearch(vec, 0, n - 1, x);

        // �������� ����� ����� ���������� ������
        auto end = chrono::high_resolution_clock::now();

        // ��������� ����� ���������� � ������������
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // ���������� ��������� � ����
        outFile << i << " " << duration << endl;

        // ����� ���������� � ������� (�����������)
        if (i % 10000 == 0) {
            cout << "���� " << x << " ���� " << duration << " ��" << endl;
        }
    }

    // ��������� ����
    outFile.close();

    cout << "���������� �������� � ���� search_results.txt" << endl;

    return 0;
}