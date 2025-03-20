//
// Created by Zachary on 4/2/2023.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "file_record.h"
#include "../table/typedefs.h"

using namespace std;

bool file_exists(const char filename[]);

void open_fileRW(fstream& f, const char filename[]);
void open_fileW(fstream& f, const char filename[]);
void read_info(const char filename[], vectorstr& fields);
void write_info(const char filename[], const vectorstr& fields);

#endif