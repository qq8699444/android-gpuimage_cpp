#ifndef GPU_IMAGE_Gamma_FILTER
#define GPU_IMAGE_Gamma_FILTER

#include "GPUImageFilter.h" 


class GPUImageGammaFilter : public GPUImageFilter
{
public:
    GPUImageGammaFilter(float gamma= 1.2f);
    ~GPUImageGammaFilter() = default;

    void setGamma(float b);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int gammaLocation;
    float gamma;

    static string GAMMA_FRAGMENT_SHADER;
};
#endif