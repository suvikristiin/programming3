#include "sudoku.hh"
#include <iostream>
#include <vector>

using namespace std;

Sudoku::Sudoku() : sudokuVector(9, vector<char>(9, ' ')) {}

void Sudoku::print() {

    int i = 0;
    int j = 0;
    string hashchar = "#";
    string space = "|";
    cout << "#####################################"<< endl;
    for (vector<char> row : sudokuVector) {
        for (char c: row) {
            if (i== 0) {
                cout<< hashchar << " " << c << " " << space ;
            }
            else if (i == 2 or i==5 or i==8) {
                cout<< " " << c << " " << hashchar ;

            } else {

                cout<< " " << c << " " << space ;

            }
            i++;
        }
        cout<< endl;
        if (j == 2 or j== 5 or j==8) {
            cout << "#####################################"<< endl;
        } else {
            cout << "#---+---+---#---+---+---#---+---+---#"<< endl;
        }
        i = 0;
        j++;

    }

}

void Sudoku::set(int rowi, int colj, char sudokuc) {

    int i = 0;

    if (rowi < 0 || rowi>8 || colj < 0 || colj>8) {
        cout << "Trying to access illegal cell (" << rowi << ", " <<  colj << ")!"<<endl;
    }

    for (vector<char> row : sudokuVector) {

        try {

            if (i == rowi) {

                int rowSize = sudokuVector.at(i).size();
                for (int j = 0; j < rowSize; j++) {

                    if (j == colj) {

                        if (sudokuc == ' ' || (sudokuc >= '1' && sudokuc <= '9')) {
                            sudokuVector.at(i).at(j) = sudokuc;
                        }
                        else {
                            cout << "Trying to set illegal character " << sudokuc
                                 << " to (" << i << ", " << j << ")!" << endl;
                        }

                    }

                }
            }

            i++;

        } catch (...) {

            cout << "error"<<endl;
        }


    }
}

bool Sudoku::check() {

    char founded = '0';
    bool duplikate = false;

    for (size_t row = 0; row < 9; ++row) {
        bool found[9] = {false};

        for (size_t col = 0; col < 9; ++col) {
            char c = sudokuVector[row][col];

            if (c == ' ') {
                continue;
            }

            int index = c - '1';

            if (found[index]) {
                duplikate = true;

                if (founded > c or founded == '0') {
                    founded = c;
                }

            }

            found[index] = true;
        }

        if (duplikate) {
            cout << "Row " << row <<  " has multiple " << founded << "'s!"<<endl;
            return false;
        }
    }


    for (size_t col = 0; col < 9; ++col) {
        bool found[9] = {false};
        bool duplikate = false;
        char founded = '0';


        for (size_t row = 0; row < 9; ++row) {
            char c = sudokuVector[row][col];

            if (c == ' ') {
                continue;
            }

            int index = c - '1';

            if (found[index]) {
                duplikate = true;

                if (founded > c or founded == '0') {
                    founded = c;
                }
            }

            found[index] = true;
        }

        if (duplikate) {
            cout << "Column " << col <<  " has multiple " << founded << "'s!"<<endl;
            return false;
        }
    }


    for (size_t blockRow = 0; blockRow < 9; blockRow += 3) {

        bool duplikate = false;
        char founded = '0';

        for (size_t blockCol = 0; blockCol < 9; blockCol += 3) {
            bool found[9] = {false};

            for (size_t row = blockRow; row < blockRow + 3; ++row) {
                for (size_t col = blockCol; col < blockCol + 3; ++col) {
                    char c = sudokuVector[row][col];

                    if (c == ' ') {
                        continue;
                    }

                    int index = c - '1';

                    if (found[index]) {
                        duplikate = true;

                        if (founded > c or founded == '0') {
                            founded = c;
                        }
                    }

                    found[index] = true;
                }
            }

            if (duplikate) {
                cout << "Block at (" << blockRow <<", " << blockCol << ") has multiple " << founded <<"'s!"<<endl;
                return false;
            }
        }
    }

    return true;

}

