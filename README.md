# ArtemisBase

Result of ArtemisLib after splicing off utilities; math; and implementation modules.

This represents the "core" Artemis that should be resuable via static libary.

Dependencies are referenced by submodule; in addition to utilities and math, this includes:

* SDL

* glew

* SDL_image

* SDL_mixer

## WIP

- [ ] Header definition order probably needs to be reworked

- [ ] No source files yet... duh

- [x] Need "internal" dependencies from other Artemis submodules

- [x] Need "external" dependencies from core SDL and individual SDL submodules

- [ ] There's enough submodules to build now, but as we add source, more may be needed
