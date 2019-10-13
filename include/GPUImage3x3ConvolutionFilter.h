#ifndef GPU_IMAGE_3x3Convolution_FILTER
#define GPU_IMAGE_3x3Convolution_FILTER


#include "GPUImageFilter.h" 
#include "GPUImage3x3TextureSamplingFilter.h"

class  GPUImage3x3ConvolutionFilter:public GPUImage3x3TextureSamplingFilter
{
public:
    GPUImage3x3ConvolutionFilter();
    GPUImage3x3ConvolutionFilter(float* kernel);
    ~GPUImage3x3ConvolutionFilter();

    void setConvolutionKernel(float* kernel);
protected:

    static string THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER;
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    float* convolutionKernel;
    int uniformConvolutionMatrix;
};
#endif