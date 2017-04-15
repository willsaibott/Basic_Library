#ifndef PNG_IMAGE_H
#define PNG_IMAGE_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <png.h>
#include "../Structures/Basic.h"



using namespace std;

#define DATA_OFFSET 30
#define PNG_DEBUG 3

struct PNG_Header{
    byte PNGSignature[8];
    uint nb;
    byte ImageHeader[4];
    uint width;
    uint height;
    byte bitDepth;
    byte colorType;
    byte compressionMethod;
    byte filterMethod;
    byte interlaceMethod;
};


class pngImage{
protected:
    PNG_Header header;
    FILE *image;
    string imageName;
    byte *imageBytes;
    uint  **imageData;
    uint totalBytes;
    int number_of_passes;
    png_structp png_ptr;
    png_infop info_ptr;
    byte ** row_pointers;
    bool alloc;

    void setData();

public:

    pngImage(){alloc = false; row_pointers = NULL; imageBytes = NULL;}
    ~pngImage();

    //getters
    imageSize getSize();
    string getName(){return imageName;}
    PNG_Header getHeader(){return header;}
    byte *getBytes(){return imageBytes;}
    uint getTotalBytes(){return totalBytes;}
    uint **getData(){return imageData;}

    //setters
    void setImageName(string name){this->imageName = name;}

    //others
    static uint changeEndianness(uint val);
    bool isValidPNGFile();
    byte *open(string filename);
    void printHeader();
    void cleanDataPointer();
    void cleanRowPointer();
    static byte *open(string filename, int *size, PNG_Header *PNGheader);
    static bool isValidPNGFile(byte *signature);
};

pngImage::~pngImage(){
    if (alloc){
        delete[] imageBytes;
        for (uint i = 0; i < header.height; i++){
            delete[] imageData[i];
        }
        delete[] imageData;
    }
}

imageSize pngImage::getSize(){
    imageSize size;
    size.height = header.height;
    size.width = header.width;
    return size;
}

uint pngImage::changeEndianness( uint val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}



bool pngImage::isValidPNGFile(){

    if (header.PNGSignature[0] == 0x89 &&  header.PNGSignature[1] == 'P' && header.PNGSignature[2] == 'N' && header.PNGSignature[3] == 'G' && header.PNGSignature[4] == 0x0D && header.PNGSignature[5] == 0x0A && header.PNGSignature[6] == 0x1A && header.PNGSignature[7] == 0x0A)
    {
        return true;
    }
    else {
        return false;
    }

}


bool pngImage::isValidPNGFile(byte *signature){

    if (signature[0] == 0x89 &&  signature[1] == 'P' && signature[2] == 'N' && signature[3] == 'G' && signature[4] == 0x0D && signature[5] == 0x0A && signature[6] == 0x1A && signature[7] == 0x0A)
    {
        return true;
    }
    else {
        return false;
    }

}


byte *pngImage::open(string filename, int *size, PNG_Header *PNGheader){
    ifstream pngFile;
    byte *bytes = 0;

    pngFile.open(filename.data(), ios_base::in |ios_base::binary |ios_base::ate);
    if(!pngFile.is_open())
        return bytes;

    pngFile.seekg(0, ios::end);
    *size = pngFile.tellg();
    pngFile.seekg(0, ios::beg);
    bytes = new byte[*size+1];

    if( !pngFile.read((char *)PNGheader, sizeof(PNG_Header)))
        return bytes;

    PNGheader->nb = changeEndianness(PNGheader->nb);
    PNGheader->width = changeEndianness(PNGheader->width);
    PNGheader->height = changeEndianness(PNGheader->height);

    if (!isValidPNGFile(PNGheader->PNGSignature))
        return bytes;


    pngFile.seekg(0, ios::beg);
    pngFile.read((char*)bytes, *size);
    bytes[*size] = '\0';

    pngFile.close();
    return bytes;

}

byte *pngImage::open(string filename){
    cleanDataPointer();
    /* open file and test for it being a png */
    image = fopen(filename.data(), "rb");
    if (!image)
        return NULL;

    fseek(image, 0, SEEK_SET);
    int result = fread((char*)&header, 1, sizeof(PNG_Header), image);
    if (result!=sizeof(PNG_Header))
        return NULL;
    if (!isValidPNGFile())
        return NULL;

    header.nb = changeEndianness(header.nb);
    header.width = changeEndianness(header.width);
    header.height = changeEndianness(header.height);

    fseek(image, 0, SEEK_END);
    totalBytes = ftell(image);
    fseek(image, 8, SEEK_SET);
    imageBytes = new byte[totalBytes+1];

    /* initialize stuff - Do not try to understand, the following code is not mine */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        return imageBytes;

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        return imageBytes;

    if (setjmp(png_jmpbuf(png_ptr)))
        return imageBytes;


    png_init_io(png_ptr, image);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    //    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        return NULL;

    row_pointers = new byte *[header.height];
    for (uint i=0; i<header.height; i++)
        row_pointers[i] = new byte [png_get_rowbytes(png_ptr,info_ptr)];

    png_read_image(png_ptr, row_pointers);

    setData();
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(image);
    cleanRowPointer();
    return imageBytes;

}



void pngImage::printHeader(){
    cout << "\nPNGSignature: ";
    for(int i = 0; i < 8; i++)
        printf("%d ", header.PNGSignature[i]);

    cout << "\nnbytes: ";
    printf("%d\n", header.nb);

    for(int i = 0; i < 4; i++)
        printf("%d ", header.ImageHeader[i]);

    cout << "\nWidth: ";
    printf("%d\n", header.width );
    printf("Height: %d\n", header.height );
    printf("bitDepth: %d\n", header.bitDepth );
    printf("ColorType: %d\n", header.colorType );
    printf("CompressionMethod: %d\n", header.compressionMethod );
    printf("FilterMethod: %d\n", header.filterMethod );
    printf("InterlaceMethod: %d\n", header.interlaceMethod );

}



void pngImage::setData(){
    alloc = true;
    imageData = new uint*[header.height];
    for (uint i = 0; i < header.height; i++){
        imageData[i] = new uint[header.width];
        for (uint j = 0; j < header.width; j++){
            byte *pixelValue = &row_pointers[i][j*((uint)header.bitDepth/8)];
            imageData[i][j] = 0;
            for (uint k = 0; k < (uint)header.bitDepth/8; k++){
                imageData[i][j] = (imageData[i][j] << 8) | (uint)pixelValue[k];
            }
        }
    }
}

void pngImage::cleanRowPointer(){
    if (row_pointers!=NULL){
        for (uint i=0; i<header.height; i++)
            delete []row_pointers[i];
        delete[] row_pointers;
        row_pointers = NULL;
    }
}

void pngImage::cleanDataPointer(){
    if (alloc){
        for (uint i=0; i<header.height; i++)
            delete []imageData[i];
        delete[] imageData;
        delete[] imageBytes;
    }
}


#endif

