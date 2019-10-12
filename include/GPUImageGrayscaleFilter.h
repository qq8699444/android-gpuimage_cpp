#ifndef GPU_IMAGE_GRAYSCALE_FILTER
#define GPU_IMAGE_GRAYSCALE_FILTER


#include "GPUImageFilter.h"

class GPUImageGrayscaleFilter:public GPUImageFilter
{
public:
    GPUImageGrayscaleFilter();
    virtual ~GPUImageGrayscaleFilter();
protected:
    static string GRAYSCALE_FRAGMENT_SHADER;
private:

};
#endif
