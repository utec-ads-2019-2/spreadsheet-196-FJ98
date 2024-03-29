#include<bits/stdc++.h>

using namespace std;

#define vecOfStrVec std::vector< std::vector<std::string> >
#define vecOfIntVec std::vector< std::vector<int> >
#define vecOfIntIntPair std::vector<std::pair<int,int>>

vecOfStrVec enterMatrix(int rows, int columns);
void printMatrix(int, int, vecOfIntVec&);

int columnToInteger(const std::string&);
void parseFormulas(const std::string&, vecOfIntIntPair*);
int evaluateFormulas(vecOfStrVec& sheet, vecOfIntVec& mem, int rows, int columns);
vecOfIntVec solveSpreadSheet(vecOfStrVec sheet, int rows, int columns);

int main() {

    int numOfSpreadSheets = 0;
    std::cin >> numOfSpreadSheets;

    for (int i = 0; i < numOfSpreadSheets; ++i)
    {
        int columns = 0; int rows = 0;
        std::cin >> columns >> rows;

        auto matrixInput = enterMatrix(rows, columns);
        auto resultMatrix = solveSpreadSheet(matrixInput, rows, columns);

        printMatrix(rows, columns, resultMatrix);
    }

	return 0;
}


vecOfStrVec enterMatrix(int rows, int columns)
{
    vecOfStrVec matrixInput(rows, std::vector<std::string>(columns));
    for (int j = 0; j < rows; ++j)
    {
        for (int k = 0; k < columns; ++k)
        {
            std::cin >> matrixInput[j][k];
        }
    }
    return matrixInput;
}


int columnToInteger(const std::string& col)
{
    int ret = 0;
    int m = 1;
    for (int i = static_cast<int>(col.size()) - 1; i >= 0; --i)
    {
        ret += (std::toupper(col[i]) - 'A' + 1) * m;
        m *= 26;
    }

    return ret;
}


void parseFormulas(const std::string& formula, vecOfIntIntPair* parsed)
{
    for (int i = 1; i < static_cast<int>(formula.size()); ++i)
    {
        std::string col, row;
        while (i < static_cast<int>(formula.size()) && formula[i] != '+')
        {
            if (std::isalpha(formula[i]))
                col += formula[i];
            else
                row += formula[i];

            ++i;
        }
        parsed->push_back( std::make_pair(std::stoi(row) - 1, columnToInteger(col) - 1) );
    }
}


int evaluateFormulas(vecOfStrVec& sheet, vecOfIntVec& mem, int rows, int columns)
{
    if (mem[rows][columns] != -1)
        return mem[rows][columns];

    if (sheet[rows][columns][0] != '=')
        return mem[rows][columns] = std::stoi(sheet[rows][columns]);

    vecOfIntIntPair parsed;
    parseFormulas(sheet[rows][columns], &parsed);
    int ret = 0;
    for (auto & k : parsed)
    {
        ret += evaluateFormulas(sheet, mem, k.first, k.second);
    }

    return mem[rows][columns] = ret;
}


vecOfIntVec solveSpreadSheet(vecOfStrVec sheet, int rows, int columns)
{
    vecOfIntVec result(rows, std::vector<int>(columns, -1));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (sheet[i][j][0] != '=') {
                result[i][j] = std::stoi(sheet[i][j]);
            } else {
                result[i][j] = evaluateFormulas(sheet, result, i, j);
            }
        }
    }

    return result;
}


void printMatrix(int rows,int columns, vecOfIntVec& matrix)
{
    for (int l = 0; l < rows; ++l) {
        for (int m = 0; m < columns; ++m)
        {
            if (m > 0) std::cout << " ";
            std::cout << matrix[l][m];
        }
        std::cout << "\n";
    }
}
