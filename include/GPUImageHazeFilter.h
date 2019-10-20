#ifndef GPU_IMAGE_Haze_FILTER
#define GPU_IMAGE_Haze_FILTER

#include "GPUImageFilter.h" 


class GPUImageHazeFilter : public GPUImageFilter
{
public:
    GPUImageHazeFilter(float distance = 0.2f, float slope = 0.0f);
    ~GPUImageHazeFilter();

    void setDistance(float distance);
    void setSlope(float distance);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    float distance;
    int distanceLocation;
    float slope;
    int slopeLocation;


    static string HAZE_FRAGMENT_SHADER;
};
#endif