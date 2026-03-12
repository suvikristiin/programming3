#include <iostream>
#include <vector>

using namespace std;

// Splits the given string into several strings, by using the given delimiter
// as a separator.
// Returns the splitted string as a vector such that each string part is an
// element of the vector.
vector<string> split(const string& str, const char delimiter)
{
    vector<string> result;
    string tmp = str;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not word.empty())
        {
            result.push_back(word);
        }

    }
    if(not tmp.empty())
    {
        result.push_back(tmp);
    }
    return result;
}

// Converts the words, found from the input string, to double values and
// counts the mean of these values.
double mean(const string& input)  // Don't change the function definition!
{
    // TODO: Write the functionality for counting mean here.
    // Must throw invalid_argument and domain_error on applicaple errors
    char delimeter = ' ';
    vector<string> splitNumbers = split(input, delimeter);
    double sum = 0;

    if(splitNumbers.empty()) {
        throw domain_error("No numbers");
    }

    for (const string& s : splitNumbers) {
        try {
            sum += stod(s);
        }
        catch (...) {
            throw invalid_argument("stod");
        }
    }

    double result = sum / splitNumbers.size();

    return result;
}


// Don't remove! Needed for tests.
#ifndef MEAN_TEST
// Don't remove! Needed for tests.
// Main function
int main()
{

    // TODO: Write main function code here
    //       (including try-catch block to catch the thrown exceptions)

    string inputNumbers = "";
    cout << "Enter numbers: ";
    getline(cin, inputNumbers);

    try {
        double result = mean(inputNumbers);
        cout << "Mean: "<< result << endl;

    } catch (std::invalid_argument& error) {
        std::cout << "invalid_argument: " << error.what();
    } catch(std::domain_error& error) {
        std::cout << "domain_error: " << error.what()<< endl;
    }


    return 0;
}
// Don't remove! Needed for tests.
#endif // MEAN_TEST
// Don't remove! Needed for tests.
