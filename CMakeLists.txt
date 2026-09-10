cmake_minimum_required(VERSION 3.20)
project(Ominous_Orbits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

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
        include/CSVLogger.h
        include/JsonInit.h
        src/JsonInit.cpp
)

set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
        RapidJSON
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(RapidJSON)

target_link_libraries(Ominous_Orbits PRIVATE SDL3::SDL3)
target_include_directories(Ominous_Orbits PRIVATE ${rapidjson_SOURCE_DIR}/include)

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

option(BUILD_PLOTTING_TOOLS "Enable targets for Python plotting and telemetry analysis" OFF)

if(BUILD_PLOTTING_TOOLS)
    # 2. Locate the Python interpreter (prefers active venv if available)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)

    message(STATUS "Plotting tools enabled. Using Python interpreter: ${Python3_EXECUTABLE}")

    # 3. Create the custom plot target
    add_custom_target(plot
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/plot_orbits.py
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running orbital telemetry analysis script..."
    )
endif()
