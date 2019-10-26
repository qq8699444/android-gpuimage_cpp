#ifndef GPU_IMAGE_FILTER_GROUP
#define GPU_IMAGE_FILTER_GROUP

#include <vector>
#include <memory>
#include "GPUImageFilter.h" 


class GPUImageFilterGroup : public GPUImageFilter
{
public:
    GPUImageFilterGroup(std::vector<std::shared_ptr<GPUImageFilter>> filters= std::vector<std::shared_ptr<GPUImageFilter>>());
    ~GPUImageFilterGroup() = default;

    void updateMergedFilters();
    void addFilter(std::shared_ptr<GPUImageFilter> aFilter);

    std::vector<std::shared_ptr<GPUImageFilter>>  getFilters() {
        return filters;
    }

    std::vector<std::shared_ptr<GPUImageFilter>> getMergedFilters() {
        return mergedFilters;
    }

    virtual void onOutputSizeChanged(int width, int height) override;
    virtual void onDraw(int textureId, const GLfloat* cubeBuffer, const GLfloat* textureBuffer);

protected:
    virtual void onInit() override;
    virtual void onDestroy() override;
private:
    
    std::vector<std::shared_ptr<GPUImageFilter>> filters;
    std::vector<std::shared_ptr<GPUImageFilter>> mergedFilters;

    
    std::vector<GLuint> frameBuffers;
    std::vector<GLuint> frameBufferTextures;

    //private final FloatBuffer glCubeBuffer;
    //private final FloatBuffer glTextureBuffer;
    //private final FloatBuffer glTextureFlipBuffer;


    void destroyFramebuffers();
};
#endif