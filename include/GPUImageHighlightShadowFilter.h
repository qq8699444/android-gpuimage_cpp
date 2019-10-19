#ifndef GPU_IMAGE_HighlightShadow_FILTER
#define GPU_IMAGE_HighlightShadow_FILTER

#include "GPUImageFilter.h" 


class GPUImageHighlightShadowFilter : public GPUImageFilter
{
public:
    GPUImageHighlightShadowFilter(float shadows = 0.0f, float highlights = 1.0f);
    ~GPUImageHighlightShadowFilter() = default;

    void setHighlights(float h);
    void setShadows(float s);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int shadowsLocation;
    float shadows;
    int highlightsLocation;
    float highlights;


    static string HIGHLIGHT_SHADOW_FRAGMENT_SHADER;
};
#endif