#ifndef OUTFILE_H
#define OUTFILE_H

#include "Files.h"
#include <fstream>
#include "../../Library/Structures/Basic.h"

class outFile : public Files{
protected:
    uint size;
    bool opened;
    ofstream *out;


public :
    outFile();
    outFile(string filename);
    outFile(string filename, ios_base::openmode mode);
    ~outFile();

    //getters
    ofstream *getFile(){return out;}
    bool isOpened(){return opened;}


    //others
    static ofstream* open(string filename, ios_base::openmode mode);
    ofstream* open(ios_base::openmode mode);
    bool write(byte *output, uint size);
    void close();
    void erase();

};




#endif // OUTFILE_H

