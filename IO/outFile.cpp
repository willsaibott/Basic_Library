#include "outFile.h"

outFile::outFile() : Files()
{
    cout << "here";
}


outFile::outFile(string filename) : Files(filename)
{

}


outFile::outFile(string filename, ios_base::openmode mode) : Files(filename)
{
    out = open(mode);
}


outFile::~outFile(){
    close();
}



ofstream* outFile::open(string filename, ios_base::openmode mode){
    ofstream *file = new ofstream();
    file->open(filename.data(), ios_base::out | mode);
    if (file->is_open()){
        return file;
    }
    else
        return NULL;

}


ofstream* outFile::open(ios_base::openmode mode){
    out = outFile::open(properties.filename, mode);
    opened = (out!=NULL)? true: false;
    return out;
}


void outFile::erase(){
    opened = false;
    size = 0;
}


void outFile::close(){
    if (out->is_open())
        out->close();

    opened = false;
}


bool outFile::write(byte *output, uint size){
    if (out->is_open()){
        for (uint i = 0; i < size; i ++)
            *out << output[i];
        return true;
    }else
        return false;
}
