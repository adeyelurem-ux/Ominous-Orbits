cmake_minimum_required(VERSION 4.3)
project(Ominous_Orbits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(Ominous_Orbits
        src/main.cpp
        include/Maths/LinearAlgebra/Vector3.h
        include/Physics/body.h
        include/Physics/World.h
        src/World.cpp
        include/Physics/Gravity.h
        src/Gravity.cpp)

find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
            "src/*.cpp"
            "include/*.hpp"
    )
    add_custom_target(
            format
            COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCE_FILES}
            COMMENT "Formatting source code with clang-format..."
    )
endif()