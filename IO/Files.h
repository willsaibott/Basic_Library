#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <sys/stat.h>


using namespace std;

struct fileProperties{
    string filename;
    string extension;
    bool isFile;
    struct stat sb;
};


class Files{
protected:
    fileProperties properties;
public:

    Files(){
        setFilename("");
    }
    Files(string name){
        setFilename(name);
    }

    //getters
    string getExtension(){
        return properties.extension;
    }
    string getName(){
        return properties.filename;
    }
    fileProperties getFileProperties(){
        stat(properties.filename.c_str(), &properties.sb);
        properties.isFile = isRegularFile();
        return properties;
    }


    //setters
    void setFilename(string name){
        int fSize = name.size();
        this->properties.filename = string(name);
        this->properties.extension = "";
        if (properties.filename != "")
            for (int i = fSize - 1; i >= 0; i--){
                if (properties.filename[i]=='.') break;
                else if (properties.filename[i]=='/'){
                    properties.extension = "";
                    break;
                }
                properties.extension = string(properties.filename[i] + properties.extension);
                if (i - 1 < 0)
                    properties.extension = "";
            }

        properties.isFile = isRegularFile();
    }


    //others
    bool isRegularFile(){
        return (stat(properties.filename.c_str(), &properties.sb) == 0 && S_ISREG(properties.sb.st_mode));
    }

    static bool isRegularFile(string filename){
        struct stat sb;
        return (stat(filename.c_str(), &sb) == 0 && S_ISREG(sb.st_mode));
    }

};

#endif // FILES_H
