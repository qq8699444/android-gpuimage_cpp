#ifndef GPU_IMAGE_Color_Matrix_FILTER
#define GPU_IMAGE_Color_Matrix_FILTER

#include "GPUImageFilter.h" 


class GPUImageColorMatrixFilter : public GPUImageFilter
{
public:
    GPUImageColorMatrixFilter(float intensity = 1.0f, float* mat4 = mat4I);
    ~GPUImageColorMatrixFilter() = default;

    void setIntensity(float intensity);
    void setColorMatrix(float* colorMatrix);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    float intensity;
    float* colorMatrix;
    int colorMatrixLocation;
    int intensityLocation;

    static string COLOR_MATRIX_FRAGMENT_SHADER;
    static float  mat4I[16];
};
#endif