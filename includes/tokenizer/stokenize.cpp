//
// Created by Zachary on 1/18/2023.
//

#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() {
    make_table();
}

STokenizer::STokenizer(char *str) {
    make_table();
    set_string(str);
}

bool STokenizer::done() {
    return _pos > strlen(_buffer);
}

bool STokenizer::more() {
    return _pos <= strlen(_buffer);
}

void STokenizer::set_string(char *str) {
    assert(MAX_BUFFER >= strlen(str)); //eventually try commenting out
    _pos = 0;
    for (char &i : _buffer)
        i = 0;
    for (int i = 0; i < strlen(str) && i < MAX_BUFFER - 1; ++i)
        _buffer[i] = str[i];

    //unknown characters take up 3 indexes
//    for (char i : _buffer)
//        std::cout << i;
//    std::cout << std::endl;
}

void STokenizer::make_table() {
    init_table(_table);

    //state 0
    mark_fail(_table, 0);
    mark_cells(0, _table, ALFA, 1);
    mark_cells(0, _table, DIGITS, 2);
    mark_cells(0, _table, OPERATORS, 5);
    mark_cells(0, _table, SPACES, 6);
    mark_cells(0, _table, PUNC, 7);
    mark_cells(0, _table, QUOTE, 8);
    mark_cells(0, _table, L_PAREN, 10);
    mark_cells(0, _table, R_PAREN, 11);

    //state 1 (Token = ALPHA)
    mark_success(_table, 1);
    mark_cells(1, _table, ALFA, 1);

    //state 2-5 (Token = DIGITS)
    mark_success(_table, 2);
    mark_cells(2, _table, DIGITS, 2);
    mark_cells(2, _table, ".", 3);
    mark_fail(_table, 3);
    mark_cells(3, _table, DIGITS, 4); //state 3 should be fail
    mark_success(_table, 4);
    mark_cells(4, _table, DIGITS, 4);

    //state 5 (Token = OPERATORS)
    mark_success(_table, 5);
    mark_cells(5, _table, OPERATORS, 5);

    //state 6 (Token = SPACES)
    mark_success(_table, 6);
    mark_cells(6, _table, SPACES, 6);

    //state 7 (Token = PUNC)
    mark_success(_table, 7);
    mark_cells(7, _table, PUNC, 7);

    //state 8 (Token = QUOTE aka MIXED STRING)
    mark_fail(_table, 8);
    mark_cells(8, _table, ALFA, 8);
    mark_cells(8, _table, DIGITS, 8);
    mark_cells(8, _table, OPERATORS, 8);
    mark_cells(8, _table, SPACES, 8);
    mark_cells(8, _table, PUNC, 8);
    mark_cells(8, _table, L_PAREN, 8);
    mark_cells(8, _table, R_PAREN, 8);
    mark_cells(8, _table, QUOTE, 9);
    mark_success(_table, 9);

    //state 10 (Token = " or LPAREN)
    mark_success(_table, 10);
    mark_cells(10, _table, L_PAREN, 12);
    mark_fail(_table, 12);

    //state 11 (Token = " or RPAREN)
    mark_success(_table, 11);
    mark_cells(11, _table, R_PAREN, 12);
    mark_fail(_table, 12);
//    print_table(_table);
}

bool STokenizer::get_token(int &state, std::string &token) {
    if (_buffer[_pos] == '\0')
        ++_pos;
    if (done())
        return false;
    int lastSuccessPos = _pos, temp_state = state;
    while(true) {
        temp_state = _table[temp_state][_buffer[_pos]];
        if (temp_state == TOKEN_UNKNOWN || _buffer[_pos] <= 0) {
//            std::cout << "token failed at pos " << _pos << ", char " << _buffer[_pos] << std::endl;
            for (int i = 0; !token.empty() && i < _pos - lastSuccessPos; ++i) {
                token.pop_back();
                --_pos;
//                std::cout << "clearing chars...\n";
            }
            if (token.empty())
                token += _buffer[_pos++];
            return true;
        } state = temp_state;
//        std::cout << "pos: " << _pos << "; char at pos: " << _buffer[_pos] << "; ascii value of read character: " << static_cast<int>(_buffer[_pos]) << std::endl;
        token += _buffer[_pos++];
        if (is_success(_table, state))
            lastSuccessPos = _pos;
    }
}

STokenizer &operator>>(STokenizer &s, Token &t)
{
//    if (!s.more())
//        int wow = 5/0;
    assert(s.more());
    int type, state = 0;
    std::string token;

    if (!s.get_token(state, token)) {
        t = Token({}, TOKEN_UNKNOWN);
        return s;
    }
    if (token[0] == '\0')
        type = TOKEN_END;
    else
        switch (state) {
        case STATE_ALPHA: type = TOKEN_ALPHA; break;
        case STATE_DOUBLE: type = TOKEN_NUMBER; break;
        case STATE_OPERATOR: type = TOKEN_OPERATOR; break;
        case STATE_SPACES: type = TOKEN_SPACE; break;
        case STATE_PUNC: type = TOKEN_PUNC; break;
        case STATE_MIXED_STRING:
            type = TOKEN_MIXED_STRING;
            token = token.substr(1, token.size() - 2);
        break;
        default: type = TOKEN_UNKNOWN;
        }
    t = Token(token, type);
    return s;
}
