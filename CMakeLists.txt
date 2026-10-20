cmake_minimum_required(VERSION 3.28)

project(abstract C)

include(FetchContent)
FetchContent_Declare(
    simple_wgsl
    GIT_REPOSITORY https://github.com/manuel5975p/simple_wgsl.git
    GIT_TAG f3abd93588c69dd2937e77b9090f2dbd0e8d3641
)
FetchContent_MakeAvailable(simple_wgsl)

add_library(abstract SHARED)
# add_executable(abstract)

target_link_libraries(abstract PUBLIC wgsl_compiler)
target_link_libraries(wgsl_compiler PUBLIC m)

target_include_directories(abstract PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(abstract PRIVATE DEBUG)

add_subdirectory(src)