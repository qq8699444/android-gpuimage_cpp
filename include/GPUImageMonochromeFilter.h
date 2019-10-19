#ifndef GPU_IMAGE_Monochrome_FILTER
#define GPU_IMAGE_Monochrome_FILTER

#include "GPUImageFilter.h" 


class GPUImageMonochromeFilter : public GPUImageFilter
{
public:
    GPUImageMonochromeFilter(float intensity= 1.0f, float* color= defaultcolor);
    ~GPUImageMonochromeFilter() = default;

    void setIntensity(float intensity);
    void setColor(float* color);
    //void setColor(float red, float green, float blue) {
    //    setFloatVec3(filterColorLocation, new float[] {red, green, blue});
    //}
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int intensityLocation;
    float intensity;
    int filterColorLocation;
    float* color;


    static string MONOCHROME_FRAGMENT_SHADER;
    static float defaultcolor[3];
};
#endif