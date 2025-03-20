//
// Created by Zachary on 1/18/2023.
//

#ifndef BARKESHLI_S22_CONSTANTS_H
#define BARKESHLI_S22_CONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200; //default 200

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "*><=!+-%&|";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "?.,:;'`~!_";
const char QUOTE[] = "\"";
const char L_PAREN[] = "(";
const char R_PAREN[] = ")";

const int STATE_DOUBLE = 2; //START_DOUBLE = 0;
const int STATE_SPACES = 6; //START_SPACES = 4;
const int STATE_ALPHA = 1; //START_ALPHA = 6;
const int STATE_OPERATOR = 5; //START_OPERATOR = 20;
const int STATE_PUNC = 7; //START_PUNC = 10;
const int STATE_MIXED_STRING = 9;

//keywords
const int STATE_MAKE = 1;
const int STATE_SELECT = 6;
const int STATE_INSERT = 13;
const int STATE_DROP = 18;
const int STATE_BATCH = 21;
const int STATE_EXIT = 23;
const int STATE_HELP = 24;
const int STATE_LIST = 25;

const int STATE_FIELDS_1 = 5;
const int STATE_FIELDS_2 = 8;
const int STATE_FIELDS_3 = 7;

const int STATE_TABLE_1 = 3;
const int STATE_TABLE_2 = 10;
const int STATE_TABLE_3 = 15;
const int STATE_TABLE_4 = 20;

const int STATE_CONDITIONS = 12;

const int STATE_FILE_NAME = 22;

const int STATE_WHERE = 11;
const int STATE_VALUES = 17;

#endif //BARKESHLI_S22_CONSTANTS_H
