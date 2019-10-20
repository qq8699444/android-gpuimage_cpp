#ifndef GPU_IMAGE_ColorInvert_FILTER
#define GPU_IMAGE_ColorInvert_FILTER

#include "GPUImageFilter.h" 


class GPUImageColorInvertFilter : public GPUImageFilter
{
public:
    GPUImageColorInvertFilter();
    ~GPUImageColorInvertFilter() = default;

protected:
    //virtual void onInit() override;
    //virtual void onInitialized() override;
private:
   
    static string COLOR_INVERT_FRAGMENT_SHADER;
};
#endif