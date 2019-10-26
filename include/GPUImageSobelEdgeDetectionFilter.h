#ifndef GPU_IMAGE_Sobel_Edge_Detection_FILTER
#define GPU_IMAGE_Sobel_Edge_Detection_FILTER

#include <vector>
#include <string>
#include <memory>
#include "GPUImageFilterGroup.h"


class GPUImageSobelEdgeDetectionFilter : public GPUImageFilterGroup
{
public:
    GPUImageSobelEdgeDetectionFilter();
    ~GPUImageSobelEdgeDetectionFilter() = default;

    void setLineSize(float size);
private:
    static std::string SOBEL_EDGE_DETECTION;
};

#endif