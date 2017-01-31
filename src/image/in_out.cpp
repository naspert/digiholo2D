#include "image/in_out.h"
#include <cstdio>
#include "debug/debug_out.h"


bool read_float_image(char *inputfile, float_image * img)
{
    int imsize = img->get_width()*img->get_height();
    
    FILE *pFile;
    pFile = fopen(inputfile,"rb");
    if(pFile == nullptr)
    {
        return false;
    }
    size_t len = fread(img->get_data_pointer(),sizeof(float),imsize,pFile);
    fclose(pFile);
        
    return (len != 0 && !ferror(pFile) && !feof(pFile));
}


bool write_image(char *outputfile, float_image * img)
{
    long imsize = img->get_width()*img->get_height();
    
    DEBUG_PRINTLN("Writing image to disk (" << outputfile << ")");
    
    FILE *pFile;
    pFile = fopen(outputfile,"wb");
    if(pFile == nullptr)
    {
        return false;
    }
    fwrite(img->get_data_pointer(),sizeof(float),imsize,pFile);
    fclose(pFile);
        
    if(ferror(pFile))
    {
        DEBUG_PRINTLN("Error writing image to disk!");
        return false;
    }
    return true;
}

bool write_image(char *outputfile, sharedptr<row_major_float_image> img)
{
    long imsize = img->get_width()*img->get_height();

    FILE *pFile;
    pFile = fopen(outputfile,"wb");
    if(pFile == nullptr)
    {
        return false;
    }
    fwrite(img->get_data_pointer(),sizeof(float),imsize,pFile);
    fclose(pFile);
        
    if(ferror(pFile))
    {
        return false;
    }
    return true;
}