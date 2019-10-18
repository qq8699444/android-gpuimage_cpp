#ifndef GPU_IMAGE_WhiteBalance_FILTER
#define GPU_IMAGE_WhiteBalance_FILTER

#include "GPUImageFilter.h" 

class GPUImageWhiteBalanceFilter: public GPUImageFilter
{
public:
    GPUImageWhiteBalanceFilter();
    GPUImageWhiteBalanceFilter(float temperature,  float tint);
    ~GPUImageWhiteBalanceFilter();

    void setTemperature(float temperature);
    void setTint(float tint);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int temperatureLocation;
    float temperature;
    int tintLocation;
    float tint;

    static string WHITE_BALANCE_FRAGMENT_SHADER;
};
#endif