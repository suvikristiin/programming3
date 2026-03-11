#ifndef SUDOKU_HH
#define SUDOKU_HH
#include <vector>

using namespace std;

// Sizes of a block and the whole sudoku
const unsigned int BLOCK_SIZE = 3;
const unsigned int SIZE = 3 * BLOCK_SIZE;

class Sudoku
{
public:
    Sudoku();
    void print();
    void set(int i, int j, char c);
    bool check();
private:
    vector< vector< char > > sudokuVector;
};

#endif // SUDOKU_HH
