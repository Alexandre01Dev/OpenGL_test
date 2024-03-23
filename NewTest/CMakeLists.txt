set(PROJECT_NAME NewTest)
set (CMAKE_CXX_STANDARD 17)
################################################################################
# Source groups
################################################################################
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files
file(GLOB SOURCES src/*.cpp src/*.c)

# Add the executable
add_executable(NewTest ${SOURCES}
        src/light.cpp
        src/light.h
        src/mesh.cpp
        src/mesh.h
        src/gameObject.cpp
        src/gameObject.h
        src/block.cpp
        src/block.h)

# Include directories
target_include_directories(NewTest PRIVATE Linking/include)

# Link against libraries
target_link_libraries(NewTest PRIVATE
        "-framework CoreVideo"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework Carbon"
        "${CMAKE_SOURCE_DIR}/Linking/lib/GLFW/arm64/libglfw3.a"
)