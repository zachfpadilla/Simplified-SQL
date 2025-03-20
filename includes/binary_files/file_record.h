//
// Created by Zachary on 4/2/2023.
//

#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <fstream>
#include "../table/typedefs.h"

class FileRecord{
public:
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    FileRecord();
    FileRecord(int num_of_fields);
    FileRecord(const std::vector<std::string>& items);

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file
    std::vector<std::string> get_record();
    std::string operator[](int field);

    friend ostream& operator<<(ostream& outs, const FileRecord& r);

private:
    int recno, _num_of_fields;
    static const int MAX = 100;
    char _record[100][MAX+1]; //NULL char
};

#endif