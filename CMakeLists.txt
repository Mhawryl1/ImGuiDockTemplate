cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (WIN32)
  # Enable Hot Reload for MSVC compilers if supported.
  if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  endif()
endif()
if (WIN32)
  set(CMAKE_TOOLCHAIN_FILE "E:/DevSoft/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
  set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif()
project("imguiTemplate")

find_package(SDL3 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Add source to this project's executable.
add_executable (imguiTemplate  "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET imguiTemplate PROPERTY CXX_STANDARD 23)
endif()
target_include_directories(imguiTemplate  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/backends)
target_link_libraries(imguiTemplate PRIVATE glfw imgui::imgui OpenGL::GL)
# TODO: Add tests and install targets if needed.

#target_sources(imguiTemplate PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
