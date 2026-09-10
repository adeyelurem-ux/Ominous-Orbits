cmake_minimum_required(VERSION 3.24)
project(Ominous_Orbits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(Ominous_Orbits
        src/main.cpp
        include/Maths/LinearAlgebra/Vector3.h
        include/Physics/body.h
        include/Physics/World.h
        src/World.cpp
        include/Physics/Gravity.h
        src/Gravity.cpp
        include/Maths/Integrators/EulerIntegrator.h
        include/Maths/Integrators/RK2.h
        include/Maths/Units.h
        include/Renderer2D.h
        src/Renderer2D.cpp
        include/Logger.h
)

target_link_libraries(Ominous_Orbits PRIVATE SDL3::SDL3)

find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
            "src/*.cpp"
            "include/*.h"
    )
    add_custom_target(
            format
            COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCE_FILES}
            COMMENT "Formatting source code with clang-format..."
    )
endif()
