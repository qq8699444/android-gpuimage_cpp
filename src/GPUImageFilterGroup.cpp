#include <iostream>

using namespace  std;

#include "GPUImageFilterGroup.h"
#include "TextureRotationUtil.h"

static const float cubes[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            -1.0f, 1.0f,
            1.0f, 1.0f,
};

static const float textureCoords[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
};


GPUImageFilterGroup::GPUImageFilterGroup(std::vector<std::shared_ptr<GPUImageFilter>> _filters/* = std::list<std::shared_ptr<GPUImageFilter>>() */)
{
    filters = _filters;
    updateMergedFilters();



}


void GPUImageFilterGroup::addFilter(std::shared_ptr<GPUImageFilter> aFilter)
{
    if (aFilter == nullptr) {
        return;
    }

    filters.push_back(aFilter);
    updateMergedFilters();
}

void GPUImageFilterGroup::onInit()
{
    GPUImageFilter::onInit();
    for (auto& f : filters)
    {
        f->ifNeedInit();
    }
}

void GPUImageFilterGroup::onDestroy()
{
    destroyFramebuffers();

    for (auto& f : filters)
    {
        f->destroy();
    }

    GPUImageFilter::onDestroy();
}

void GPUImageFilterGroup::destroyFramebuffers()
{
    if (!frameBufferTextures.empty()) {
        glDeleteTextures(frameBufferTextures.size(), frameBufferTextures.data());
        frameBufferTextures.clear();
    }

    if (!frameBuffers.empty()) {
        glDeleteFramebuffers(frameBuffers.size(), frameBuffers.data());
        frameBuffers.clear();
    }
}


void GPUImageFilterGroup::onOutputSizeChanged(int width, int height)
{
    GPUImageFilter::onOutputSizeChanged(width, height);
    if (!frameBuffers.empty())
    {
        destroyFramebuffers();
    }

    for (auto& f:filters)
    {
        f->onOutputSizeChanged(width, height);
    }

    if (mergedFilters.size() > 0)
    {
        auto size = mergedFilters.size();
        //frameBuffers = new int[size - 1];
        frameBuffers.resize(size - 1);
        //frameBufferTextures = new int[size - 1];
        frameBufferTextures.resize(size - 1);

        for (int i= 0; i < size -1;i++)
        {
            glGenFramebuffers(1, &frameBuffers[i]);
            glGenTextures(1, &frameBufferTextures[i]);
            glBindTexture(GL_TEXTURE_2D, frameBufferTextures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D, frameBufferTextures[i], 0);

            glBindTexture(GL_TEXTURE_2D, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}


void GPUImageFilterGroup::onDraw(int textureId, const GLfloat* cubeBuffer, const GLfloat* textureBuffer)
{
    runPendingOnDrawTasks();

    if (!isInitialized() || frameBuffers.empty() || frameBufferTextures.empty()) {
        return;
    }

    if (!mergedFilters.empty())
    {
        int size = mergedFilters.size();
        int previousTexture = textureId;

        for (int i = 0; i < size; i++) {
            shared_ptr<GPUImageFilter>& filter = mergedFilters[i];
            bool isNotLast = i < size - 1;

            if (isNotLast) {
                glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[i]);
                glClearColor(0, 0, 0, 0);
            }


            if (i == 0) {
                filter->onDraw(previousTexture, cubeBuffer, textureBuffer);
            }
            else if (i == size - 1) {
                filter->onDraw(previousTexture, 
                    cubes, 
                    (size % 2 == 0) ? TextureRotationUtil::getRotation(NORMAL,false,true) : textureCoords
                );
                //filter->onDraw(previousTexture, cubes, textureCoords);
            }
            else {
                filter->onDraw(previousTexture, cubes, textureCoords);
            }

            if (isNotLast) {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                previousTexture = frameBufferTextures[i];
            }
        }
    }
}


void GPUImageFilterGroup::updateMergedFilters()
{
    if (filters .empty()) {
        return;
    }

    mergedFilters.clear();

    for (auto& filter : filters) {

        // TODO ,Ç¶Ì×GPUImageFilterGroup
        /*if (filter instanceof GPUImageFilterGroup) {
            ((GPUImageFilterGroup)filter).updateMergedFilters();
            filters = ((GPUImageFilterGroup)filter).getMergedFilters();
            if (filters == null || filters.isEmpty())
                continue;
            mergedFilters.addAll(filters);
            continue;
        }*/
        mergedFilters.push_back(filter);
    }
}