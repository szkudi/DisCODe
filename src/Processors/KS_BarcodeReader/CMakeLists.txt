# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ZXING_LIB_PATH ${DisCODe_SOURCE_DIR}/src/Processors/KS_BarcodeReader)
#set(IMAGE_MAGICK_PATH /home/kszkudla/workspace/ImageMagick)
set(IMAGE_MAGICK_PATH /usr/local)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR} ${IMAGE_MAGICK_PATH}/include/ImageMagick/)
#/home/kszkudla/workspace/ImageMagick/include/ImageMagick/)

# Create an executable file from sources:
ADD_LIBRARY(KS_BarcodeReader SHARED ${files})
TARGET_LINK_LIBRARIES(KS_BarcodeReader ${OpenCV_LIBS} ${DisCODe_LIBRARIES} ${IMAGE_MAGICK_PATH}/lib/libMagick++.so ${ZXING_LIB_PATH}/libzxing_64.so )
#${ZGING_LIB_PATH}/libzxing_32.so)

INSTALL_PROCESSOR(KS_BarcodeReader)
