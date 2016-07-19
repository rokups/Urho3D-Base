#
# Copyright (c) 2016 Rokas Kupstys.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
if (ANDROID)
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/libs)
        file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
    endif ()
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/Android)
        file (COPY ${CMAKE_SOURCE_DIR}/Android DESTINATION ${CMAKE_BINARY_DIR})
        execute_process (COMMAND android update project -p ${CMAKE_BINARY_DIR}/Android -t 1)
    endif ()
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/Android/libs)
        execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/libs ${CMAKE_BINARY_DIR}/Android/libs)
    endif ()
endif ()

if (NOT EXISTS ${CMAKE_BINARY_DIR}/bin)
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/dep/Urho3D/CMake/Modules)
set (URHO3D_SAMPLES     0 CACHE BOOL "" FORCE)
set (URHO3D_C++11       1 CACHE BOOL "" FORCE)
set (URHO3D_USE_LIB_DEB 1 CACHE BOOL "" FORCE)
set (URHO3D_PCH         0 CACHE BOOL "" FORCE)
set (URHO3D_LUA	        0 CACHE BOOL "" FORCE)
if (ANDROID)
    set (URHO3D_LIB_TYPE STATIC CACHE STRING "" FORCE)
    set (URHO3D_TOOLS 0 CACHE BOOL "" FORCE)
else ()
    set (URHO3D_LIB_TYPE SHARED CACHE STRING "" FORCE)
    set (URHO3D_TOOLS 1 CACHE BOOL "" FORCE)
endif ()

add_subdirectory (dep/Urho3D)
find_package (Urho3D)

add_definitions (-DURHO3D_CXX11=1)
