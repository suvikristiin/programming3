#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<double> stringToDouble(string numberString)
{
    vector<double> numbers;

    unsigned int i = 0;
    size_t kohta = 0;
    string tulos = "";

    while(i < numberString.length())
    {
        kohta = numberString.find(" ", i+1);

        if(kohta == string::npos ) {
            tulos = numberString.substr(i);

            try {
                double doubletulos = stod(tulos);
                numbers.push_back(doubletulos);
                return numbers;
            } catch (...) {
                cout << "Not a double";
                exit(EXIT_FAILURE);
            }
        } else {
            tulos = numberString.substr(i, kohta-i);

            try {
                double doubletulos = stod(tulos);
                numbers.push_back(doubletulos);
                i = kohta+1;
            } catch (...) {
                cout << "Not a double";
                exit(EXIT_FAILURE);
            }
        }
    }

    return numbers;
}

int printMedian(vector<double> vector)
{
    int size = vector.size();
    sort(vector.begin(), vector.end());
    int div = size / 2;

    if (size % 2 == 0)
    {
        double median = (vector.at(div - 1) + vector.at(div)) / 2;
        cout << "Median: " << median;
    } else {
        double median = vector.at(div);
        cout << "Median: " << median;
    }

    return EXIT_SUCCESS;
}

int main()
{
    string numbersString = "";
    cout << "Enter numbers: ";
    getline(cin, numbersString);

    if (numbersString.empty()) {
        cout << "No input";
        return EXIT_FAILURE;
    }



    vector<double> vector = stringToDouble(numbersString);
    printMedian(vector);

    return 0;


}
