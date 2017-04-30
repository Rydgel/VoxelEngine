# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

cmake_minimum_required(VERSION 3.0)

SET ( LIBNOISE_VERSION "1.0.0-cmake" )

OPTION(BUILD_SHARED_LIBS "Build shared libraries for libnoise" ON)
OPTION(BUILD_LIBNOISE_DOCUMENTATION "Create doxygen documentation for developers" OFF)
OPTION(BUILD_LIBNOISE_UTILS "Build utility functions for use with libnoise" ON)
OPTION(BUILD_LIBNOISE_EXAMPLES "Build libnoise examples" ON)

set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)
endif ()

ADD_SUBDIRECTORY(src)
IF (BUILD_LIBNOISE_UTILS)
    ADD_SUBDIRECTORY(noiseutils)
ENDIF()
IF (BUILD_LIBNOISE_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()
ADD_SUBDIRECTORY(doc)

#ADD_SUBDIRECTORY(samples)
