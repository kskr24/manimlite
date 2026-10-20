# manimlite

A small 2D animation library in C++20, inspired by Manim.

## Build and test

```sh
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Sanitizers (ASan + UBSan) are on by default. Turn them off with
`-DML_ENABLE_SANITIZERS=OFF`.

## Layout

- `include/ml/` headers (header-only for now)
- `tests/` GoogleTest unit tests
- `examples/` scenes, added from week 4 on
