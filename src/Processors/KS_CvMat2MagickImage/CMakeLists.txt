# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR} /usr/local/include/ImageMagick/)

# Create an executable file from sources:
ADD_LIBRARY(KS_CvMat2MagickImage SHARED ${files})
TARGET_LINK_LIBRARIES(KS_CvMat2MagickImage ${OpenCV_LIBS} ${DisCODe_LIBRARIES})

INSTALL_PROCESSOR(KS_CvMat2MagickImage)
