# ArtemisBase

Result of ArtemisLib after splicing off utilities; math; and implementation modules.

This represents the "core" Artemis that should be resuable via static libary.

Dependencies are referenced by submodule; these are separated into "internals" and "externals".

## Internal Dependencies

Other Artemis projects broken off for purposes of organization include:

* ArtemisUtility

* KirkMath

## External Dependencies

External dependencies are mostly SDL (core and several extensions), and include:

* glew-cmake (e.g., a cmake-supported fork of glew)

* SDL

* SDL_image

* SDL_mixer

* SDL_ttf

## Building

The standard CMake two-step should work once submodules are initialized:

```sh
> git submodule update --init --recursive
> cmake -S . -B build
> cmake --build build
```

## WIP

- [ ] Header definition order probably needs to be reworked

- ~~[x] No source files yet... duh~~

- ~~[x] Need "internal" dependencies from other Artemis submodules~~

- ~~[x] Need "external" dependencies from core SDL and individual SDL submodules~~

- ~~[x] There's enough submodules to build now, but as we add source, more may be needed~~

- [ ] Start debugging builds!

Utilimately we'd like a library output that can be used to build old Artemis-based projects.
