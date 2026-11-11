cmake_minimum_required(VERSION 3.15)
project(bouncy VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    # Set a custom path for SDL3
    set(SDL3_PATH "C:/vclib" CACHE PATH "Path to SDL3 on Windows")
    list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}/SDL3-3.4.18")
    list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}/SDL3_image-3.4.8")
    list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}/SDL3_mixer-3.2.4")
    list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}/SDL3_ttf-3.2.2")
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(bouncy ${SOURCES})

target_link_libraries(bouncy PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image 
    SDL3_mixer::SDL3_mixer
	SDL3_ttf::SDL3_ttf
)

if(WIN32)
    # Copy SDL3 dll
    add_custom_command(TARGET bouncy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_PATH}/SDL3-3.4.18/lib/x64/SDL3.dll"
            $<TARGET_FILE_DIR:bouncy>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_PATH}/SDL3_image-3.4.8/lib/x64/SDL3_image.dll"
            $<TARGET_FILE_DIR:bouncy>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_PATH}/SDL3_mixer-3.2.4/lib/x64/SDL3_mixer.dll"
            $<TARGET_FILE_DIR:bouncy>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_PATH}/SDL3_ttf-3.2.2/lib/x64/SDL3_ttf.dll"
            $<TARGET_FILE_DIR:bouncy>
        COMMENT "Copying SDL3 DLLs to output directory..."
    )
endif()

# Copy assets
add_custom_command(TARGET bouncy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:bouncy>/images"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/audio"
        "$<TARGET_FILE_DIR:bouncy>/audio"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/retrogaming.ttf"
        "$<TARGET_FILE_DIR:bouncy>/retrogaming.ttf"
    COMMENT "Copying assets into build directory..."
)
