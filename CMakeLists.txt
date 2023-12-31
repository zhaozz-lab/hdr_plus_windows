cmake_minimum_required(VERSION 3.10)
project(HDR_PLUS)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

set(PNG_LIBRARY thirdParty/libjpeg/lib)
include("macro.cmake")
set(CMAKE_CXX_STANDARD 11)

# Define dependencies
SET(HALIDE_DISTRIB_DIR "thirdParty/Halide-10.0.0-x86-64-windows")
set(TIFF_INCLUDE_DIRS thirdParty/libtiff/include)
if(DEFINED HALIDE_DISTRIB_DIR)
  list(APPEND CMAKE_PREFIX_PATH ${HALIDE_DISTRIB_DIR})
endif(DEFINED HALIDE_DISTRIB_DIR)

# list(APPEND CMAKE_PREFIX_PATH zlib-1.2.7.f-win64-v1/zlib-win64)
if(DEFINED HALIDE_DISTRIB_DIR)
  link_directories(BEFORE "${HALIDE_DISTRIB_DIR}/lib")
endif(DEFINED HALIDE_DISTRIB_DIR)
find_package(Halide REQUIRED)

# find_package(ZLIB 1.2.7 REQUIRED)


# find_package(PNG REQUIRED)
set(src_files
    src/InputSource.cpp
    src/Burst.cpp
    src/LibRaw2DngConverter.cpp
    )

set(header_files
    "thirdParty/libraw"
    src/InputSource.h
    src/Burst.h
    src/dngwriter.h
    src/LibRaw2DngConverter.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RAW2DNG_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RAW2DNG_INCLUDE_DIRS} ${TIFF_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/genfiles)

add_executable(hdrplus_pipeline_generator src/hdrplus_pipeline_generator.cpp src/align.cpp src/merge.cpp src/finish.cpp src/util.cpp)
target_link_libraries(hdrplus_pipeline_generator PRIVATE Halide::Generator)
add_halide_library(hdrplus_pipeline
    # GENERATOR_DEPS  # We don't have any yet
    FROM hdrplus_pipeline_generator
    # GENERATOR_ARGS  # We don't have any yet
    FUNCTION_NAME hdrplus_pipeline
    # HALIDE_TARGET ${HALIDE_TARGET}  # TODO: add option with custom HALIDE_TARGET
    # HALIDE_TARGET_FEATURES ${HALIDE_TARGET_FEATURES}  # TODO: add option with custom HALIDE_TARGET
    # EXTRA_OUTPUTS "stmt;html;schedule") # uncomment for extra output
)

add_executable(align_and_merge_generator src/align_and_merge_generator.cpp src/align.cpp src/merge.cpp src/util.cpp)
target_link_libraries(align_and_merge_generator PRIVATE Halide::Generator)
add_halide_library(align_and_merge
    FROM align_and_merge_generator
    FUNCTION_NAME align_and_merge
    # HALIDE_TARGET ${HALIDE_TARGET}  # TODO: add option with custom HALIDE_TARGET
    # HALIDE_TARGET_FEATURES ${HALIDE_TARGET_FEATURES}  # TODO: add option with custom HALIDE_TARGET
    # EXTRA_OUTPUTS "stmt;html;schedule") # uncomment for extra output
)

# set(HALIDE_INCLUDE_PATH ${HALIDE_DISTRIB_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RAW2DNG_INCLUDE_DIRS} ${TIFF_INCLUDE_DIRS} ${HALIDE_INCLUDE_PATH} ${header_files}
    ${HALIDE_DISTRIB_DIR}/include)
link_directories("thirdParty/libraw/lib"
  "thirdParty/Halide-10.0.0-x86-64-windows/lib/Release"
  "thirdParty/libtiff/lib"
  "thirdParty/png/lib"
  )

add_executable(hdrplus bin/HDRPlus.cpp ${src_files})
add_dependencies(hdrplus hdrplus_pipeline)
target_link_libraries(hdrplus hdrplus_pipeline Halide libpng ${LIBRAW_LIBRARY} ${TIFF_LIBRARIES} ${TIFFXX_LIBRARY})

target_link_libraries(hdrplus 
                      Halide
                      libraw
                      tiff
                      tiffxx
                      )

add_executable(stack_frames bin/stack_frames.cpp ${src_files})
add_dependencies(stack_frames align_and_merge)
target_link_libraries(stack_frames Halide align_and_merge ${LIBRAW_LIBRARY} libpng.lib ${TIFF_LIBRARIES} ${TIFFXX_LIBRARY})