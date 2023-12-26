cmake_minimum_required(VERSION 3.5)

project(Chapter1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(chapter1-exec src/main.cpp)
target_include_directories(
  chapter1-exec
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

target_link_libraries(chapter1-exec PUBLIC glad glfw)

include(GNUInstallDirs)
install(
  TARGETS chapter1-exec
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
