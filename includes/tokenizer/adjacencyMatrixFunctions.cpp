//
// Created by Zachary on 1/19/2023.
//

#include "adjacencyMatrixFunctions.h"

void init_table(int (*_table)[MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; ++i)
        for (int j = 0; j < MAX_COLUMNS; ++j)
            _table[i][j] = -1;
}

void mark_success(int (*_table)[MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

void mark_fail(int (*_table)[MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

bool is_success(int (*_table)[MAX_COLUMNS], int state)
{
    return _table[state][0] == 1;
}

void mark_cells(int row, int (*_table)[MAX_COLUMNS], int from, int to, int state)
{
    for (; from <= to; ++from)
        _table[row][from] = state;
}

void mark_cells(int row, int (*_table)[MAX_COLUMNS], const char *columns, int state)
{
    for (int i = 0; i < strlen(columns); ++i)
        _table[row][columns[i]] = state;
}

void mark_cell(int row, int (*_table)[MAX_COLUMNS], int column, int state)
{
    _table[row][column] = state;
}

void print_table(int (*_table)[MAX_COLUMNS])
{
    for (int i = 0; i < MAX_COLUMNS; ++i)
        std::cout << std::setw(5) << i;
    std::cout << std::endl;
//    for (int i = 0; i < MAX_COLUMNS; ++i)
//        std::cout << std::setw(5) << static_cast<char>(i);
//    std::cout << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < MAX_COLUMNS; ++j)
            std::cout << std::setw(5) << _table[i][j];
        std::cout << std::endl;
    }
}

void show_string(char *s, int _pos)
{
    std::cout << s << '\n' << std::string(_pos, ' ') << '^';
}
