# Locate SCons program

# This module defines
# SCONS_FOUND, is set to true

IF(NOT SCONS_FOUND)
  FIND_PROGRAM(SCONS_EXEC
    NAMES scons
    PATHS 
        "/usr/bin"
        "/usr/local/bin"
    DOC "SCons building tool"
  )
  
  if(SCONS_EXEC)
      set(SCONS_FOUND TRUE)
      message(STATUS "SCons found at ${SCONS_EXEC}")
  else(SCONS_EXEC)
      message(FATAL_ERROR "SCons not found")
  endif(SCONS_EXEC)
  
endif(NOT SCONS_FOUND)
