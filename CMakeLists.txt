cmake_minimum_required(VERSION 3.15)
project(learngl 
  VERSION 0.1.0
  LANGUAGES C CXX
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Global include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Executable sources
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/shader.cpp
  src/stb_image.cpp
  src/test.cpp
)

# Shader files
set(SHADER_FILES
    ${CMAKE_SOURCE_DIR}/shaders/vertex.glsl
    ${CMAKE_SOURCE_DIR}/shaders/fragment.glsl
)
set(RESOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/resources/awesomeface.png 
    ${CMAKE_SOURCE_DIR}/resources/container.jpg 
    ${CMAKE_SOURCE_DIR}/resources/wood.png
)

# Copy shaders and resources to output directory (individual file copying)
foreach(SHADER ${SHADER_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()

foreach(RESOURCE ${RESOURCE_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RESOURCE}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()

# Find glm (via vcpkg or system)
find_package(glm CONFIG REQUIRED)
# Find glfw (via vcpkg or system)
find_package(glfw3 CONFIG REQUIRED)

# On Windows vs Linux
if(WIN32)
    # Windows does not need X11, dl, or pthreads
    target_link_libraries(${PROJECT_NAME} 
      PRIVATE
      glad
      glfw
      glm::glm
      opengl32
    )
else()
    # Linux/Unix
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} 
      PRIVATE
      glad
      glfw
      glm::glm
      GL
      Threads::Threads
      ${X11_LIBRARIES}
      dl
    )
endif()