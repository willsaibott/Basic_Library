#include "inFile.h"
inFile::inFile() : Files()
{
    cout << "here";
}

inFile::inFile(string filename) : Files(filename)
{
}

inFile::inFile(string filename, ios_base::openmode mode) : Files(filename)
{
    in = open(mode);
}

inFile::~inFile(){
    close();
}

ifstream *inFile::open(string filename, ios_base::openmode mode, byte *bytes, uint *size){
    ifstream *file = new ifstream();

    file->open(filename.data(), ios_base::in | mode);
    if (file->is_open()){
        int pos = file->tellg();
        file->seekg(0, ios_base::beg);
        file->seekg(0, ios_base::end);
        *size = file->tellg();
        file->seekg(pos, ios_base::beg);
        bytes = new byte[*size];
        file->read((char*)bytes, *size);
        file->seekg(pos, ios_base::beg);
    }
    else
        return NULL;


    return file;

}

ifstream *inFile::open(ios_base::openmode mode){
    in = open(properties.filename, mode, bytes, &size);
    opened = (in!=NULL)? true: false;
    return in;
}

void inFile::erase(){
    opened = false;
    size = 0;
    delete bytes;
}

void inFile::close(){
    if (in->is_open())
        in->close();
}

string inFile::getLine(uint bufferSize){
    char buffer[bufferSize];
    if (in->is_open()){
        in->getline(buffer, bufferSize);
        return string(buffer);
    }
    return string('\0');
}
