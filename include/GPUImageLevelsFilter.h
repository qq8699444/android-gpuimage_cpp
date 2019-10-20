#ifndef GPU_IMAGE_Levels_FILTER
#define GPU_IMAGE_Levels_FILTER

#include "GPUImageFilter.h" 


class GPUImageLevelsFilter : public GPUImageFilter
{
public:
    GPUImageLevelsFilter(float min = 0.0f, float mid = 1.0f, float max = 1.0f, float minOUt=0.0f, float maxOut=1.0f);
    ~GPUImageLevelsFilter() = default;

    void updateUniforms();
    void setMin(float min, float mid, float max, float minOut = 0.0f, float maxOut = 1.0f);
    void setRedMin(float min, float mid, float max, float minOut = 0.0f, float maxOut = 1.0f);
    void setGreenMin(float min, float mid, float max, float minOut = 0.0f, float maxOut = 1.0f);
    void setBlueMin(float min, float mid, float max, float minOut = 0.0f, float maxOut= 1.0f);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int minLocation;
    float min[3];
    int midLocation;
    float mid[3];
    int maxLocation;
    float max[3];
    int minOutputLocation;
    float minOutput[3];
    int maxOutputLocation;
    float maxOutput[3];


    static string LEVELS_FRAGMET_SHADER;
};
#endif