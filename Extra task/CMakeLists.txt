CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(SymmetricDispatcher CXX)
set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(TestRunner Tests.cpp TestClasses.h MeetingExecutor.h)
