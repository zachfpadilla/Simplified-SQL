//
// Created by Zachary on 4/12/2023.
//

#ifndef INC_99_TABLE_RZ187_TYPEDEFS_H
#define INC_99_TABLE_RZ187_TYPEDEFS_H
#include <string>
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../queue/MyQueue.h"

//MAJOR qol addition
using namespace std;
typedef Map<string, string> map_ss;
typedef MMap<string, string> mmap_ss;

typedef Map<string, long> map_sl;
typedef MMap<string, long> mmap_sl;

typedef vector<string> vectorstr;
typedef vector<long> vectorlong;
typedef Queue<string> queuestr;

#endif //INC_99_TABLE_RZ187_TYPEDEFS_H
