# =======================================================================
# zxing lib support
# =======================================================================

find_package(SCons)

message(STATUS "Building zxing")

IF(SCONS_EXEC)

    ADD_CUSTOM_TARGET(
        zxing ALL
        COMMAND ${SCONS_EXEC} lib
        WORKING_DIRECTORY ${DisCODe_SOURCE_DIR}/src/Processors/KS_BarcodeReader/zxing_src
        COMMENT "Kompilacja zxing" 
    )

    install(
      FILES ${DisCODe_SOURCE_DIR}/src/Processors/KS_BarcodeReader/zxing_src/build/libzxing.so
      DESTINATION lib
    )

ENDIF(SCONS_EXEC)