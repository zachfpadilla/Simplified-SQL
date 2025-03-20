//
// Created by Zachary on 4/2/2023.
//

#include "file_record.h"

FileRecord::FileRecord()
: _num_of_fields(0) {
    for (auto &i : _record)
        i[0] = '\0';
    recno = -1;
}

FileRecord::FileRecord(int num_of_fields)
: _num_of_fields(num_of_fields) {
    for (auto &i : _record)
        i[0] = '\0';
    recno = -1;
}

FileRecord::FileRecord(const std::vector<std::string>& items)
: recno(0), _num_of_fields(items.size()) {
    for (int i = 0; i < items.size(); ++i)
        strncpy(&_record[i][0], items[i].c_str(), MAX);
    for (int i = items.size(); i < MAX; ++i)
        _record[i][0] = '\0';
}

long FileRecord::write(fstream &outs){
    outs.seekg(0, std::ostream::end);

    long pos = outs.tellp();

//    int num_fields = 0;
//    for (; _record[num_fields][0] != '\0'; ++num_fields) {
//        outs.write(_record[num_fields], sizeof(_record[num_fields]));
//    } return pos/(sizeof(_record[0]) * num_fields);
    for (int i = 0; i < _num_of_fields; ++i) {
        outs.write(_record[i], sizeof(_record[i]));
    } int field_size = sizeof(_record[0]) * _num_of_fields;
    return field_size? pos/(sizeof(_record[0]) * _num_of_fields) : 0;
}

long FileRecord::read(fstream &ins, long recnum){
    long pos= recnum * sizeof(_record[0]) * _num_of_fields;
    ins.seekg(pos, ios_base::beg);
    ++recno;

    for (int i = 0; !ins.eof(); ++i) {
        ins.read(_record[i], sizeof(_record[i]));
        _record[i][ins.gcount()] = '\0';
        if (_num_of_fields && i >= _num_of_fields - 1)
            break;
        if (_record[i][0] == '\0') {
            if (!_num_of_fields)
                _num_of_fields = i;
            break;
        }
    } return ins.gcount();
}

ostream& operator<<(ostream& outs,
                    const FileRecord& r){
    for (int i = 0; i < r._num_of_fields; ++i)
        outs<< r._record[i]<<setw(20);
    return outs;
}

std::vector<std::string> FileRecord::get_record() {
    std::vector<std::string> record(_num_of_fields);
    for (int i = 0; i < _num_of_fields; ++i) {
        record[i] = _record[i];
    } return record;
}

std::string FileRecord::operator[](int field) {
    return _record[field];
}