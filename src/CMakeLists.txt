set ( filter_src 
		ShaderUtil.cpp
		TextureRotationUtil.cpp
		GPUImageFilter.cpp
		GPUImageGrayscaleFilter.cpp
		Runnable.cpp
		GPUImageOpacityFilter.cpp
		GPUImage3x3TextureSamplingFilter.cpp
		GPUImage3x3ConvolutionFilter.cpp
		GPUImageTwoInputFilter.cpp
		GPUImageBrightnessFilter.cpp
		GPUImageRGBFilter.cpp
		GPUImagePosterizeFilter.cpp
		GPUImagePixelationFilter.cpp
		GPUImageBilateralBlurFilter.cpp
		GPUImageOverlayBlendFilter.cpp
		GPUImageSaturationFilter.cpp
		GPUImageContrastFilter.cpp
		GPUImageWhiteBalanceFilter.cpp
		GPUImageExposureFilter.cpp
		GPUImageVignetteFilter.cpp
		GPUImageMonochromeFilter.cpp
		GPUImageHighlightShadowFilter.cpp
		GPUImageHueFilter.cpp)


# Win32 Platform files
add_library( android-gpuimage_cpp STATIC ${filter_src}  )
target_link_libraries( android-gpuimage_cpp ${OPENGLES3_LIBRARY} ${EGL_LIBRARY} )

             


