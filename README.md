# README

This repository contains a simple "repro" to showcase failure to build issues shown with Visual Studio when using the included alternative clang toolchain for arm64.

The issue is presented through the use of the __clear_cache() function that is provided by compiler-rt but which is not linked, but as such the issue presented will also likely affect all other builtins as well as other architectures.

Note that the code makes an attempt to detect if the builtin is not available and provides a fallback which is used with other compilers, but the clang compiler doesn't expect its runtime library to not be used when linking and therefore reports incorrectly that it is supported, triggering a build issue.

The use of the builtin is not representative of its current use in the production code this is affecting, but if a full codebase would be of interest or discussion on its use would it is available in :

  https://github.com/zherczeg/sljit/pull/126

To Reproduce the problem run in a Visual Studio Developer CMD :

```
  cmake -B build -A arm64 -T CLangCL
  cmake --build build
```

Or Generate a Configuration for arm64-Clang-Debug or arm64-Clang-Release under Project / CMake Settings and build that, which should result in the following error:

```
  lld-link : error : undefined symbol: __clear_cache
```

AFAIK that symbol should be available as part of the ARM64 compiler-rt runtime library which seems to be missing.
