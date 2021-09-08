#include "board.h"

#include <stdexcept>

Board::Board() :
        rowCount(1),
        colCount(1)
{
    data = new bool[rowCount * colCount];
}

Board::Board(int _rowCount, int _colCount) :
        rowCount(_rowCount),
        colCount(_colCount)
{
    data = new bool[rowCount * colCount];
}

Board::Board(const std::vector<bool> &boardState, unsigned int _rowCount, unsigned int _colCount):
        rowCount(_rowCount),
        colCount(_colCount)
{
    if(boardState.size() != rowCount * colCount)
    {
        throw std::invalid_argument("Board: invalid board state or row/col count: boardState.size() != rowCount*columnCount");
    }

    data = new bool[rowCount * colCount];

    for(int i = 0; i < boardState.size(); i++)
    {
        data[i] = boardState.at(i);
    }
}

Board::Board(Board &&other) noexcept:
        rowCount(other.rowCount),
        colCount(other.colCount),
        data(other.data)
{
    this->data = other.data;
    other.data = nullptr;
}

Board::Board(Board &other):
        rowCount(other.rowCount),
        colCount(other.colCount)
{
    data = new bool[rowCount * colCount];
    for(int i = 0; i < rowCount*colCount; i++)
    {
        data[i] = other.data[i];
    }
}

Board::~Board() {
    delete[] data;
}

void Board::swap(Board &other) {
    bool* temp = other.data;
    other.data = data;
    data = temp;
}

int Board::getColCount() const{
    return colCount;
}

int Board::getRowCount() const {
    return rowCount;
}

std::vector<bool> Board::getState() {
    std::vector<bool> temp = std::vector<bool>();

    for(int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for(int colIndex = 0; colIndex < colCount; colIndex++)
        {
            temp.push_back(this->at(rowIndex,colIndex));
        }
    }

    return temp;
}

bool &Board::at(unsigned int row, unsigned int col) {
    if(row >= rowCount || col >= colCount)
    {
        throw std::out_of_range("Board::at indexing out of range");
    }

    return data[colCount*row + col];
}

short Board::neighborCountAt(unsigned int row, unsigned int col) {
    if(row >= rowCount || col >= colCount)
    {
        throw std::out_of_range("Board::neighborCountAt indexing out of range");
    }

    short neighborCount = 0;

    int rowIndex = 0;
    int colIndex = 0;

    for(int rowOffset = -1; rowOffset < 2; rowOffset++)
    {
        rowIndex = row + rowOffset;
        if(rowIndex < 0 || rowIndex >= rowCount) {continue;}
        for(int colOffset = -1; colOffset < 2; colOffset++)
        {
            if(colOffset == 0 && rowOffset == 0){continue;}
            colIndex = col+colOffset;
            if(colIndex < 0 || colIndex >= colCount) {continue;}
            if(this->at(rowIndex,colIndex)){neighborCount++;}
        }
    }

    return neighborCount;
}

std::string Board::toCoutString(char aliveChar, char deadChar) {
    std::string output(rowCount*colCount + rowCount,deadChar);
    for(int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for(int colIndex = 0; colIndex < colCount; colIndex++)
        {
            if(data[rowIndex*colCount + colIndex]){output[rowIndex*colCount+colIndex + rowIndex] = aliveChar;}
        }
        output[rowIndex*colCount + colCount +rowIndex] = '\n';
    }

    return output;
}

Board &Board::operator=(Board &&other) noexcept {
    this->colCount = other.colCount;
    this->rowCount = other.rowCount;
    delete data;
    this->data = other.data;
    other.data = nullptr;

    return *this;
}
