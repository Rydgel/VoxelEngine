project(stb_image)

set(HEADER_FILES stb_image.hpp)
set(SOURCE_FILES stb_image.cpp)

add_library(stb_image STATIC ${SOURCE_FILES} ${HEADER_FILES})