#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    ofstream inputFile("input.txt");
    for (int i = 0; i < 100; ++i) {
        inputFile << rand() % 101 - 50 << endl;
    }
    inputFile.close();

    ifstream input("input.txt");
    ofstream output("output.txt");
    int sum = 0, count = 0, num;

    while (input >> num) {
        sum += num;
        count++;
    }
    double avg = sum / static_cast<double>(count);

    input.clear();
    input.seekg(0, ios::beg);

    while (input >> num) {
        if (num % 2 != 0) {
            num /= avg;
        }
        output << num << endl;
    }

    input.close();
    output.close();
    return 0;
}