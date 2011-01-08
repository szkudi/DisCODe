# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(IMAGE_MAGICK_PATH /home/kszkudla/workspace/ImageMagick)


# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR} ${IMAGE_MAGICK_PATH}/include/ImageMagick/)

# Create an executable file from sources:
ADD_LIBRARY(KS_MagickImage2CvMat SHARED ${files})
TARGET_LINK_LIBRARIES(KS_MagickImage2CvMat ${OpenCV_LIBS} ${DisCODe_LIBRARIES} ${IMAGE_MAGICK_PATH}/lib/libMagick++.so)

INSTALL_PROCESSOR(KS_MagickImage2CvMat)
