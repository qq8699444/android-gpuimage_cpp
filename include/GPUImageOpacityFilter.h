#ifndef GPU_IMAGE_OPACITY_FILTER
#define GPU_IMAGE_OPACITY_FILTER

#include "GPUImageFilter.h"

class GPUImageOpacityFilter:public GPUImageFilter
{
public:
    GPUImageOpacityFilter(float opacity);
    void setOpacity(float opacity);
protected:
    static string OPACITY_FRAGMENT_SHADER;
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int opacityLocation;
    float opacity;
};

#endif