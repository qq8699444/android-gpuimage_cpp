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

#include "GPUImageFilter.h"
#include "GPUImageGrayscaleFilter.h"

const int WIDTH = 640;
const int HEIGHT = 480 ;

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

class Scene
{
public:
    Scene();
    ~Scene();
    void init();
    void update();
    void draw();
private:
    std::shared_ptr<GPUImageFilter> filter;
    int textureId;
} ;

Scene::Scene()
{
    textureId = TextureUtil::load("wall.png");
    filter = std::make_shared<GPUImageGrayscaleFilter>();
}

Scene::~Scene()
{
    filter.reset();
}


void Scene::init()
{

    //onSurfaceCreated
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);


    filter->ifNeedInit();


    //打开深度检测
    glDisable(GL_DEPTH_TEST);

    //onSurfaceChanged
    //设置视口的大小及位置 
    glViewport(0, 0, WIDTH, HEIGHT);
    glUseProgram(filter->getProgram());
    filter->onOutputSizeChanged(WIDTH, HEIGHT);
}

void Scene::draw()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    filter->onDraw(textureId, cubes, textureCoords);
}

void Scene::update()
{

}
///
// Initialize the shader and program object
//
bool Init ( ESContext *esContext )
{
   Scene *scene = (Scene *)esContext->userData;
   scene->init();
   return true;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
   Scene *scene = (Scene *)esContext->userData;
   scene->draw();
}

void Update(ESContext *esContext, float)
{
    Scene *scene = (Scene *)esContext->userData;
    scene->update();
}

void Shutdown ( ESContext *esContext )
{
    Scene *scene = (Scene *)esContext->userData;

   //delete userData->star;
   delete scene;
   esContext->userData = nullptr;
}


extern "C" int esMain ( ESContext *esContext )
{
   esCreateWindow ( esContext, "android gpuimage cpp", WIDTH, HEIGHT, ES_WINDOW_RGB );

   esContext->userData = new Scene();
   if ( !Init ( esContext ) )
   {
      return GL_FALSE;
   }

   esRegisterShutdownFunc ( esContext, Shutdown );
   esRegisterDrawFunc ( esContext, Draw );
   esRegisterUpdateFunc(esContext, Update);
   return GL_TRUE;
}
