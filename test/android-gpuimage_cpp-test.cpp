// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//
// Hello_Triangle.c
//
//    This is a simple example that draws a single triangle with
//    a minimal vertex/fragment shader.  The purpose of this
//    example is to demonstrate the basic concepts of
//    OpenGL ES 3.0 rendering.
#include <string>
#include <memory>
#include <iostream>

using namespace std;
#include "esUtil.h"

#include "textureUtil.h"
#include "ShaderUtil.h"

#include "GPUImageFilter.h"
#include "GPUImageGrayscaleFilter.h"
#include "GPUImageOpacityFilter.h"
#include "GPUImage3x3ConvolutionFilter.h"
#include "GPUImageBrightnessFilter.h"
#include "GPUImageRGBFilter.h"
#include "GPUImagePosterizeFilter.h"
#include "GPUImagePixelationFilter.h"
#include "GPUImageBilateralBlurFilter.h"


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

static float mykernel[] = {
            -0.25f,-0.5f,-0.25f,
            0.0f,0.0f,0.0f,
            0.25f,0.5f,0.25f
};

class Scene : public IScene
{
public:
    Scene();
    ~Scene();
    virtual void init(ESContext*);
    virtual void update(ESContext*, float);
    virtual void draw(ESContext*);
    virtual void key(ESContext*);
private:
    std::shared_ptr<GPUImageBilateralBlurFilter> filter;
    GLuint textureId;
} ;

Scene::Scene()
{
    textureId = TextureUtil::load("wall.png");
    {
        //filter = std::make_shared<GPUImageOpacityFilter>(0.5f);    
    }

    {
        //filter = std::make_shared<GPUImage3x3ConvolutionFilter>(mykernel);
    }

    {
        //filter = std::make_shared<GPUImageBrightnessFilter>(0.5f);
        //filter = std::make_shared<GPUImageBrightnessFilter>(-0.5f);
    }

    {
        //filter = std::make_shared<GPUImageRGBFilter>(0.0f,1.0f,0.0f);
    }

    {
        //filter = std::make_shared<GPUImagePosterizeFilter>(3);
    }
    {
        //filter = std::make_shared<GPUImagePosterizeFilter>(3); 
    }

    {
        //filter = std::make_shared<GPUImagePixelationFilter>(); 
    }
    {
        filter = std::make_shared<GPUImageBilateralBlurFilter>();
    }
}

Scene::~Scene()
{
    filter.reset();
    glDeleteTextures(1, &textureId);
}

void Scene::init(ESContext* context)
{

    //onSurfaceCreated
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    filter->ifNeedInit();
    //filter->setTexelWidth(1.0f / 512);
    //filter->setTexelHeight(1.0f / 512);

    ShaderUtil::checkGlError("init --1");
    //打开深度检测
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_ALPHA);
    ShaderUtil::checkGlError("init --2");

    //onSurfaceChanged
    //设置视口的大小及位置 
    glViewport(0, 0, context->width, context->height);
    glUseProgram(filter->getProgram());
    filter->onOutputSizeChanged(context->width, context->height);
    ShaderUtil::checkGlError("init --3");
}

void Scene::draw(ESContext*)
{
    ShaderUtil::checkGlError("draw ++");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    filter->onDraw(textureId, cubes, textureCoords);
}

void Scene::update(ESContext*,float)
{

}

void Scene::key(ESContext*)
{

}



IScene* createScene()
{
    return new Scene();
}
