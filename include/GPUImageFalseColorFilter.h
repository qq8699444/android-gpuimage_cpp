#ifndef GPU_IMAGE_False_Color_FILTER
#define GPU_IMAGE_False_Color_FILTER

#include "GPUImageFilter.h" 


class GPUImageFalseColorFilter : public GPUImageFilter
{
public:
    GPUImageFalseColorFilter(float firstRed = 0.0f, float firstGreen = 0.0f, float firstBlue = 0.5f,
                            float secondRed = 1.f, float secondGreen = 0.0f, float secondBlue = 0.0f);
    ~GPUImageFalseColorFilter() = default;

    void setFirstColor(float* fc);
    void setSecondColor(float* sc);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    float firstColor[3];
    int firstColorLocation;

    float secondColor[3];
    int secondColorLocation;

    static string FALSECOLOR_FRAGMENT_SHADER;
};
#endif