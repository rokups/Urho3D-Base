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
set (DEBUG 0)
set (RELEASE 0)
set (DEVELOPER_BUILD 0)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set (DEBUG 1)
    if (NOT ANDROID)
        set (DEVELOPER_BUILD 1)
    endif ()
else ()
    set (RELEASE 1)
endif ()

if (ANDROID)
    set (MOBILE_BUILD 1)
    link_directories (
        ${CMAKE_BINARY_DIR}/libs/${ANDROID_ABI}/Urho3D
    )
else ()
    set (MOBILE_BUILD 0)
endif ()

include_directories (
    ${URHO3D_INCLUDE_DIRS}
)

add_definitions (
    -DDEVELOPER_BUILD=${DEVELOPER_BUILD}
    -DMOBILE_BUILD=${MOBILE_BUILD}
    -DDEBUG=${DEBUG}
    -DRELEASE=${RELEASE}
    -DDEVELOPER_BUILD=${DEVELOPER_BUILD}
)

add_subdirectory (Shared)
add_subdirectory (Game)
