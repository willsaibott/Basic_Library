#ifndef INFILE_H
#define INFILE_H

#include "Files.h"
#include <fstream>
#include "../../Library/Structures/Basic.h"

class inFile : public Files{
protected:
    uint size = 0;
    bool opened = false;
    ifstream *in;
    byte *bytes;

public :
    inFile();
    inFile(string filename);
    inFile(string filename, ios_base::openmode mode);
    ~inFile();

    //getters
    uint getSize(){return size;}
    byte *getBytes(){return bytes;}
    ifstream *getFile(){return in;}
    bool isOpened(){return opened;}
    string getLine(uint bufferSize);

    //others
    static ifstream* open(string filename, ios_base::openmode mode, byte* bytes, uint *size);
    ifstream* open(ios_base::openmode mode);
    void close();
    void erase();

};


#endif // INFILE_H
