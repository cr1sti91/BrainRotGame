cmake_minimum_required(VERSION 3.16)
project(BrainRotGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(game main.cpp ${SRC_FILES})
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(game PRIVATE sfml-graphics)
target_compile_features(game PRIVATE cxx_std_20)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Fonts $<TARGET_FILE_DIR:game>/Fonts
    COMMENT "Copying resources to output directory")

if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif() 
