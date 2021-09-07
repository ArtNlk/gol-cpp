#ifndef GOL_CPP_BOARD_H
#define GOL_CPP_BOARD_H

#include <string>
#include <vector>

class Board {
private:
    int rowCount;
    int colCount;

    bool* data;

public:
    Board();
    Board(int _rowCount, int _colCount);
    explicit Board(const std::vector<bool>& boardState, unsigned int _rowCount, unsigned int _colCount);
    Board(Board&& other) noexcept;
    Board(Board& other);
    ~Board();

    void swap(Board& other);
    int getColCount() const;
    int getRowCount() const;
    std::vector<bool> getState();
    bool& at(unsigned int row, unsigned int col);
    short neighborCountAt(unsigned int row, unsigned int col);
    std::string toCoutString(char aliveChar, char deadChar);

    Board& operator=(Board&& other) noexcept;
};


#endif //GOL_CPP_BOARD_H
