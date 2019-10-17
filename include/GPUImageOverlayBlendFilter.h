#ifndef GPU_IMAGE_OverlayBlend_FILTER
#define GPU_IMAGE_OverlayBlend_FILTER

#include "GPUImageTwoInputFilter.h"


class GPUImageOverlayBlendFilter : public GPUImageTwoInputFilter
{
public:
    GPUImageOverlayBlendFilter();
    ~GPUImageOverlayBlendFilter();
protected:
private:
    static string OVERLAY_BLEND_FRAGMENT_SHADER;
};

#endif