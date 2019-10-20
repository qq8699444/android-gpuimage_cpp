#ifndef GPU_IMAGE_Chroma_Key_FILTER
#define GPU_IMAGE_Chroma_Key_FILTER

#include "GPUImageTwoInputFilter.h"


class GPUImageChromaKeyBlendFilter : public GPUImageTwoInputFilter
{
public:
    GPUImageChromaKeyBlendFilter();
    ~GPUImageChromaKeyBlendFilter() = default;

    void setSmoothing(float smoothing);
    void setThresholdSensitivity(float thresholdSensitivity);
    void setColorToReplace(float _colorToReplace[3]);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int thresholdSensitivityLocation;
    int smoothingLocation;
    int colorToReplaceLocation;

	float thresholdSensitivity = 0.4f;
    float smoothing = 0.1f;
    float colorToReplace[3] = { 0.0f, 1.0f, 0.0f };

    static string CHROMA_KEY_BLEND_FRAGMENT_SHADER;
};
#endif