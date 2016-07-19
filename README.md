# Urho3D-Base

This is a base Urho3D project I created for my personal needs. It is aimed to provide clean base for prototyping while
including only basic building blocks that are absolutely necessary.

Features
========

* Simple state manager which allows suspending and resuming states.
* Builds and uses Urho3D through cmake add_subdirectory()

How to use
==========

1. Clone this repository
2. `make -C /path/to/cloned/folder`
3. Modify Urho3D build options in `CMake/Urho3D.cmake`
4. `cmake /path/to/cloned/folder` and `make` as you normally would build any other cmake project.

Warning
=======

Urho3D does not support building through `add_subdirectory()` yet. `patch/add_subdirectory.patch` combined with
`project(Urho3D)` project name tricks Urho3D build system into building correctly via `add_subdirectory()`. As this is
officially unsupported method you will get no support if things break. It is advised to use this only if you know what
you are doing.
