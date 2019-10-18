#ifndef GPU_IMAGE_Contrast_FILTER
#define GPU_IMAGE_Contrast_FILTER

#include "GPUImageFilter.h" 

class GPUImageContrastFilter: public GPUImageFilter
{
public:
    GPUImageContrastFilter();
    GPUImageContrastFilter(float contrast);
    ~GPUImageContrastFilter();

    void setContrast(float contrast);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int contrastLocation;
    float contrast;

    static string CONTRAST_FRAGMENT_SHADER;
};
#endif