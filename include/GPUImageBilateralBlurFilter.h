#ifndef GPU_IMAGE_BilateralBlur_FILTER
#define GPU_IMAGE_BilateralBlur_FILTER

#include "GPUImageFilter.h" 

class GPUImageBilateralBlurFilter: public GPUImageFilter
{
public:
    GPUImageBilateralBlurFilter();
    GPUImageBilateralBlurFilter(float distanceNormalizationFactor);
    ~GPUImageBilateralBlurFilter();

    void setDistanceNormalizationFactor(float newValue);
    void setTexelSize(float w, float h);
    virtual void onOutputSizeChanged(int width, int height) override;
protected:

    virtual void onInit() override;
    virtual void onInitialized() override;


private:
    float distanceNormalizationFactor;
    int disFactorLocation;
    int singleStepOffsetLocation;

    static string BILATERAL_VERTEX_SHADER;
    static string BILATERAL_FRAGMENT_SHADER;

};
#endif