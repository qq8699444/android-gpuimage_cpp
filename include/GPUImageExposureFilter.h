#ifndef GPU_IMAGE_Exposure_FILTER
#define GPU_IMAGE_Exposure_FILTER

#include "GPUImageFilter.h" 

class GPUImageExposureFilter: public GPUImageFilter
{
public:
    GPUImageExposureFilter();
    GPUImageExposureFilter(float exposure);
    ~GPUImageExposureFilter();

    void setExposure(float exposure);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int exposureLocation;
    float exposure;

    static string EXPOSURE_FRAGMENT_SHADER;
};
#endif