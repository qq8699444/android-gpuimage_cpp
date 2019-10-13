#ifndef GPU_IMAGE_RGB_FILTER
#define GPU_IMAGE_RGB_FILTER

#include "GPUImageFilter.h" 

class GPUImageRGBFilter:public GPUImageFilter
{
public:
    GPUImageRGBFilter();
    GPUImageRGBFilter(float red, float green = 1.0f, float blue = 1.0f);
    ~GPUImageRGBFilter();

    void setRed(float red) {
        this->red = red;
        setFloat(redLocation, red);
    }

    void setGreen(float green) {
        this->green = green;
        setFloat(greenLocation, green);
    }

    void setBlue( float blue) {
        this->blue = blue;
        setFloat(blueLocation, blue);
    }
protected:

    virtual void onInit() override;
    virtual void onInitialized() override;

private:
    int redLocation;
    float red;
    int greenLocation;
    float green;
    int blueLocation;
    float blue;

    static string RGB_FRAGMENT_SHADER;
};

#endif