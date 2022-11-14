cmake_minimum_required(VERSION 3.23)
project(BinaryTreeDict)

set(CMAKE_CXX_STANDARD 14)

add_executable(BinaryTreeDict Node.cpp Node.h BinaryTreeDict.cpp BinaryTreeDict.h main.cpp keyitemgenerator.cpp keyitemgenerator.h timing_tests.cpp)


find_package(Boost 1.80.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

if(Boost_FOUND)
    target_link_libraries(BinaryTreeDict ${Boost_LIBRARIES})
endif()

