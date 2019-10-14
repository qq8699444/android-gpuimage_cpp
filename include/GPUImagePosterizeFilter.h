#ifndef GPU_IMAGE_Posterize_FILTER
#define GPU_IMAGE_Posterize_FILTER

#include "GPUImageFilter.h" 
class GPUImagePosterizeFilter:public GPUImageFilter
{
public:
    GPUImagePosterizeFilter();
    GPUImagePosterizeFilter(int colorLevels);
    ~GPUImagePosterizeFilter();

    void setColorLevels(int colorLevels);
protected:

    virtual void onInit() override;
    virtual void onInitialized() override;

private:
    int glUniformColorLevels;
    int colorLevels;
    static string POSTERIZE_FRAGMENT_SHADER; 
};

#endif