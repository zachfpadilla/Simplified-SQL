//
// Created by Zachary on 4/2/2023.
//

#include "utilities.h"

bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists(): File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists(): File DOES exist: "<<filename<<endl;
    ff.close();
    return true;
}

void open_fileRW(fstream& f, const char filename[]) {
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)) {
        //create the file
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()) {
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else {
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    } else {
        f.open (filename,
            std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()) {
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }
}

void open_fileW(fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }
}

void read_info(const char filename[], vectorstr& fields) {
    fstream file;
    open_fileRW(file, filename);
    FileRecord f;
    f.read(file, 0);
    fields = f.get_record();
    file.close();
}

void write_info(const char filename[], const vectorstr& fields) {
    fstream file;
    open_fileW(file, filename);
    FileRecord f(fields);
    f.write(file);
    file.close();
}