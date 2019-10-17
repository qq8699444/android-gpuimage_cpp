#pragma once
#include <stdio.h>
#include <vector>
#include <atlimage.h>
//#include "esUtil.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class TextureUtil
{
public:
    enum 
    {
        Stretch_Mode_None,
        Stretch_Mode_Repeat,
        Stretch_Mode_Clamp_to_Edge,
        Stretch_Mode_Mirror_Repeat,
    };
    static GLuint load(const std::string imgfile, 
        int strtchmode = Stretch_Mode_None,
        GLfloat minFilter = GL_NEAREST,
        GLfloat magFilter = GL_LINEAR
        )
    {
        HRESULT hResult;
        CImage img;
        hResult = img.Load(imgfile.c_str());
        if (!FAILED(hResult))
        {
            GLuint textureId;
            glGenTextures
            (
                1,          //产生的纹理id的数量
                &textureId   //纹理id的数组

                );


            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if (strtchmode == Stretch_Mode_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, //T轴为重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            else if (strtchmode == Stretch_Mode_Clamp_to_Edge)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为截取拉伸方式
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D, //T轴为截取拉伸方式
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            else if (strtchmode == Stretch_Mode_Mirror_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, //T轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            }
            else
            {

            }
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_GREEN);

            GLubyte* data = new GLubyte[img.GetWidth() * img.GetHeight() * 3];
            for (int y = 0; y < img.GetHeight(); y++)
            {
                for (int x = 0; x < img.GetWidth(); x++)
                {
                    auto pixel = img.GetPixel(x, y);
                    auto r = GetRValue(pixel);
                    auto g = GetGValue(pixel);
                    auto b = GetBValue(pixel);
                    data[(y * img.GetHeight() + x) * 3] = (GLubyte)r;
                    data[(y * img.GetHeight() + x) * 3 + 1] = (GLubyte)g;
                    data[(y * img.GetHeight() + x) * 3 + 2] = (GLubyte)b;
                }
            }
            glTexImage2D
            (
                GL_TEXTURE_2D, //纹理类型
                0, 					  //纹理的层次，0表示基本图像层，可以理解为直接贴图
                GL_RGB,
                img.GetWidth(),
                img.GetHeight(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data 			  //纹理图像
            );

            img.Detach();
            delete[] data;
            return textureId;
        }
        return -1;
    }
#if 1
    static GLuint loadCompressTexture(const std::string etclfile,
        int strtchmode = Stretch_Mode_None,
        GLfloat minFilter = GL_NEAREST,
        GLfloat magFilter = GL_LINEAR
    )
    {
        HRESULT hResult;
        FILE* fp = fopen(etclfile.c_str(),"rb");
        if (fp != nullptr)
        {
            GLuint textureId;
            glGenTextures
            (
                1,          //产生的纹理id的数量
                &textureId   //纹理id的数组

            );


            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if (strtchmode == Stretch_Mode_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, //T轴为重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            else if (strtchmode == Stretch_Mode_Clamp_to_Edge)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为截取拉伸方式
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D, //T轴为截取拉伸方式
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            else if (strtchmode == Stretch_Mode_Mirror_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D, //S轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, //T轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            }
            else
            {

            }
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_GREEN);
            struct stat statbuf;
            stat(etclfile.c_str(), &statbuf);

            GLubyte* data = new GLubyte[statbuf.st_size];
            size_t readlen = fread(data, 1, statbuf.st_size, fp);
            
            int imgw = data[12] * 256 + data[13];
            int imgh = data[14] * 256 + data[15];
            glCompressedTexImage2D
            (
                GL_TEXTURE_2D, //纹理类型
                0, 					  //纹理的层次，0表示基本图像层，可以理解为直接贴图
                GL_ETC1_RGB8_OES,
                imgw,//img.GetWidth(),
                imgh,// img.GetHeight(),
                0,
                
                statbuf.st_size - 16,
                data + 16 			  //纹理图像
            );

            fclose(fp);
            delete[] data;
            return textureId;
        }
        return -1;
    }
#endif

    static GLuint loadArray(const std::vector<std::string> imgfileArr,
        int imgW,int imgH,
        int strtchmode = Stretch_Mode_None,
        GLfloat minFilter = GL_NEAREST,
        GLfloat magFilter = GL_LINEAR
    )
    {
        //HRESULT hResult;
        //CImage img;
        //hResult = img.Load(imgfile.c_str());
        //if (!FAILED(hResult))
        {
            GLuint textureId;
            glGenTextures
            (
                1,          //产生的纹理id的数量
                &textureId   //纹理id的数组

            );


            glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
            glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, magFilter);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            if (strtchmode == Stretch_Mode_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //S轴为重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //T轴为重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            else if (strtchmode == Stretch_Mode_Clamp_to_Edge)
            {
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //S轴为截取拉伸方式
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //T轴为截取拉伸方式
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            else if (strtchmode == Stretch_Mode_Mirror_Repeat)
            {
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //S轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                glTexParameterf(GL_TEXTURE_2D_ARRAY, //T轴为镜像重复拉伸方式
                    GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            }
            else
            {

            }
            //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_GREEN);
            int perPicByteCount = imgW * imgH * 3;
            GLubyte* data = new GLubyte[perPicByteCount * imgfileArr.size()];
            int fileoffset = 0;
            for (auto imgfile : imgfileArr)
            {
                HRESULT hResult;
                CImage img;
                hResult = img.Load(imgfile.c_str());
                if (!FAILED(hResult))
                { 
                    
                    for (int y = 0; y < imgH; y++)
                    {
                        for (int x = 0; x < imgW; x++)
                        {
                            auto pixel = img.GetPixel(x, y);
                            auto r = GetRValue(pixel);
                            auto g = GetGValue(pixel);
                            auto b = GetBValue(pixel);
                            data[fileoffset + (y * img.GetHeight() + x) * 3] = (GLubyte)r;
                            data[fileoffset + (y * img.GetHeight() + x) * 3 + 1] = (GLubyte)g;
                            data[fileoffset + (y * img.GetHeight() + x) * 3 + 2] = (GLubyte)b;
                        }
                    }
                }

                fileoffset += perPicByteCount;
                img.Detach();
            }
            glTexImage3D
            (
                GL_TEXTURE_2D_ARRAY, //纹理类型
                0, 					  //纹理的层次，0表示基本图像层，可以理解为直接贴图
                GL_RGB,
                imgW,
                imgH,
                imgfileArr.size(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data 			  //纹理图像
            );
            //checkGLError("glTexImage3D");
            
            delete[] data;
            return textureId;
        }
        
    }
protected:
private:
};