SET(CMAKE_INCLUDE_CURRENT_DIR ON)

MESSAGE(STATUS "Building processors:")

ADD_PROCESSOR(Example)
ADD_PROCESSOR(BlobExtractor)
ADD_PROCESSOR(CvThreshold)
ADD_PROCESSOR(CvColorConv)
ADD_PROCESSOR(CvGaussianBlur)
ADD_PROCESSOR(CvSplit)
ADD_PROCESSOR(CvMorphology)
ADD_PROCESSOR(CvFilter2D)
ADD_PROCESSOR(CvPixelOperator)
ADD_PROCESSOR(ExecTimer)
ADD_PROCESSOR(Stereo)

# Task specific processors
ADD_PROCESSOR(MS_Sign_LUT)
ADD_PROCESSOR(MS_Sign_Decide)

ADD_PROCESSOR(MS_Barcode_Macro)
ADD_PROCESSOR(MS_Barcode_Prepare)
ADD_PROCESSOR(MS_Barcode_Decide)

ADD_PROCESSOR(KS_CvMat2MagickImage)
ADD_PROCESSOR(KS_MagickImage2CvMat)
ADD_PROCESSOR(KS_BarcodeReader)
ADD_PROCESSOR(KS_ROICrop)

ADD_PROCESSOR(CvSolvePnP)
ADD_PROCESSOR(CvUndistort)

ADD_PROCESSOR(VisualServoPB)
ADD_PROCESSOR(VisualServoIB)
ADD_PROCESSOR(CameraCalib)
ADD_PROCESSOR(GrayImageSegmentation)
ADD_PROCESSOR(ConvertSegments)
ADD_PROCESSOR(EdgeDetectorForSegmentedImage)
ADD_PROCESSOR(LineSegments)

ADD_PROCESSOR(KW_Palm_LUT)
ADD_PROCESSOR(KW_Skin)
ADD_PROCESSOR(KW_Cov)
