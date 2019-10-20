#ifndef GPU_IMAGE_Sepia_Tone_FILTER
#define GPU_IMAGE_Sepia_Tone_FILTER

#include "GPUImageColorMatrixFilter.h"
class GPUImageSepiaToneFilter : public GPUImageColorMatrixFilter
{
public:
    GPUImageSepiaToneFilter() :
        GPUImageSepiaToneFilter(1.0f)
    {

    }

    GPUImageSepiaToneFilter(float intensity) :
        GPUImageColorMatrixFilter(intensity, sepiaToneMat4) {

    }
protected:
private:

    static float sepiaToneMat4[16];
};
#endif