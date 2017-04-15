#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../../Library/Structures/List.h"
#include "Files.h"
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

struct directoryProperties{
    bool isDir;
    List<string> filesList;
};

class Directory : public Files{
protected:
    directoryProperties *dProperties;

public:
    Directory() : Files(){
        dProperties = new directoryProperties;
        dProperties->isDir = false;
    }
    Directory(string name) : Files(name){
        dProperties = new directoryProperties;
        if(isDirectory()){
            makeFileList();
        }
    }

    //getters
    directoryProperties* getDirProperties(){
        return dProperties;
    }

    bool isDirectory(){
        dProperties->isDir = (stat(properties.filename.c_str(), &properties.sb) == 0 && S_ISDIR(properties.sb.st_mode));
        return dProperties->isDir;
    }

    static bool isDirectory(string filename){
        struct stat sb;
        return (stat(filename.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
    }

    List<string> getSubDir(){
        return dProperties->filesList;
    }



    //others
    static void copy(dirent *d1, dirent* d2){
        d1->d_ino = d2->d_ino;
        strcpy(d1->d_name, d2->d_name);
        d1->d_off = d2->d_off;
        d1->d_reclen = d2->d_reclen;
        d1->d_type = d2->d_type;
    }

    void makeFileList(){
        DIR *dir = opendir(properties.filename.c_str());
        dProperties->filesList.erase();
        if (dProperties!=NULL){
            dirent* file = readdir(dir);
            while(file!=NULL){
                string filename = string(file->d_name);
                dProperties->filesList.insert(filename);
                file = readdir(dir);
            }
            closedir(dir);
            dProperties->filesList.sortList(true, QUICK_SORT);
        }


    }

    void changeDir(string dirname){
        this->setFilename(dirname);
        update();
    }

    void update(){
        if(isDirectory()){
            makeFileList();
        }
    }

    bool makeDir(){
       return makeDir(0775);
    }

    bool makeDir(mode_t mode){
        string dirname = string(properties.filename);
        string subdir, path = string("");
        uint offset = 1, pre = 0;

        if (dirname[dirname.length()-1]!='/')
            dirname += '/';

        offset = dirname.find_first_of('/', offset);

        while (true){
           subdir = dirname.substr(pre, offset-pre+1);
           path += subdir;
           if (!isDirectory(path)){
                if (mkdir(path.data(), mode)!=0 && errno!=EEXIST)
                    return false;
           }
           pre = ++offset;
           offset = dirname.find_first_of('/', offset);
           if (offset>dirname.length()) break;
        }
        return true;
    }


    static int removeDir(string path)
    {
       DIR *d = opendir(path.data());
       size_t path_len = path.length();
       int r = -1;

       if (d)
       {
          struct dirent *p;

          r = 0;

          while (!r && (p=readdir(d)))
          {
              int r2 = -1;
              char *buf;
              size_t len;

              if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
              {
                 continue;
              }

              len = path_len + strlen(p->d_name) + 2;
              buf = (char*)malloc(len);

              if (buf)
              {
                 struct stat statbuf;

                 snprintf(buf, len, "%s/%s", path.data(), p->d_name);

                 if (!stat(buf, &statbuf))
                 {
                    if (S_ISDIR(statbuf.st_mode))
                    {
                       r2 = removeDir(buf);
                    }
                    else
                    {
                       r2 = unlink(buf);
                    }
                 }

                 free(buf);
              }

              r = r2;
          }

          closedir(d);
       }

       if (!r)
       {
          r = rmdir(path.data());
       }

       return r;
    }
};

#endif // DIRECTORY_H
