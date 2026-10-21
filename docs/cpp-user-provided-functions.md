# C++ User-Provided Functions

Summary of [cppreference: Function — User-provided functions](https://en.cppreference.com/w/cpp/language/function#User-provided_functions).

## Definition

A function is **user-provided** if it is:
- user-declared, **and**
- **not** explicitly defaulted or deleted on its *first* declaration.

## Key Rule

If a special member function is declared (but not `= default`/`= delete`) on its
first declaration, and later marked `= default` in a separate definition, it is
still considered user-provided. It is defined at the point where it's
explicitly defaulted. If the compiler would implicitly define it as deleted
at that point, the program is ill-formed.

## Why It Matters

Declaring a function as defaulted *after* its first declaration (rather than
inline) allows you to:
- Keep an efficient, implicitly-generated implementation.
- Maintain a stable binary/ABI interface as the codebase evolves (e.g., hiding
  the defaulted definition from a public header).

## Example

```cpp
// All special member functions of "trivial" are defaulted on their
// first declarations — they are NOT user-provided.
struct trivial {
    trivial() = default;
    trivial(const trivial&) = default;
    trivial(trivial&&) = default;
    trivial& operator=(const trivial&) = default;
    trivial& operator=(trivial&&) = default;
    ~trivial() = default;
};

struct nontrivial {
    nontrivial();  // first declaration — not defaulted here
};

// Defaulted after first declaration: this makes it user-provided,
// and it is defined at this point.
nontrivial::nontrivial() = default;
```

## Takeaway

| Declaration pattern                                   | User-provided? |
|---------------------------------------------------------|:--------------:|
| `Foo() = default;` (defaulted on first declaration)      | No              |
| `Foo() = delete;` (deleted on first declaration)         | No              |
| `Foo();` then later `Foo::Foo() = default;`               | Yes             |
| `Foo() { /* body */ }`                                    | Yes             |
