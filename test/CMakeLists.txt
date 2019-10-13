#指定生成目标
add_executable(android-gpuimage_cpp-test android-gpuimage_cpp-test.cpp esUtil_win32.cpp esUtil.cpp)
target_link_libraries(android-gpuimage_cpp-test android-gpuimage_cpp )
#set_target_properties(android-gpuimage_cpp-test PROPERTIES FOLDER "test") 
