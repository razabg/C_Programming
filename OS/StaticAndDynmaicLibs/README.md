# Building a static (.a) and shared (.so) library — command by command

Files: `a.c`, `b.c` (library source), `prog.c` (uses `a()` and `b()`)

## 1. Compile source files to object files

```sh
gcc -c a.c -o a.o
gcc -c b.c -o b.o
```
- `-c` : compile/assemble only, **don't link** — produces a relocatable `.o` object file instead of an executable.
- `-o a.o` : name the output file.

## 2. Static library (`.a`)

```sh
ar rcs libab.a a.o b.o
```
- `ar` : the GNU archiver — bundles multiple `.o` files into one archive file.
- `r` : insert/replace the given object files into the archive.
- `c` : create the archive if it doesn't already exist (suppresses the "creating" warning).
- `s` : write/update the archive's symbol index (like running `ranlib`) so the linker can quickly find which member defines which symbol.
- `libab.a` : conventional naming — `lib<name>.a`, referenced later as `-lab`.

Static libraries are just an archive of `.o` files — no special compilation flags are needed to build them.

### Link a program against the static library

```sh
gcc prog.c -o prog_static -L. -lab -static
```
- `-L.` : add the current directory to the linker's library search path.
- `-lab` : link against `libab.a` (or `libab.so` if present — see note below).
- `-static` : force fully static linking (embed the library code directly into the executable, plus the C runtime). Without `-static`, if both `libab.a` and `libab.so` exist in the search path, the linker prefers the `.so`.

Result: `prog_static` is self-contained — it does **not** need `libab.a` (or `libab.so`) to run, because the machine code from `a.o`/`b.o` was copied into the executable at link time.

## 3. Shared library (`.so`)

```sh
gcc -c -fPIC a.c -o a.o
gcc -c -fPIC b.c -o b.o
gcc -shared -o libab.so a.o b.o
```
- `-fPIC` : compile **Position-Independent Code**. A shared library can be mapped at a different address in every process that loads it, so its code can't hardcode absolute addresses — `-fPIC` makes it use relative addressing instead. (Not needed for static libs, since their code is copied into a fixed executable layout at link time.)
- `-shared` : tell the linker to produce a shared object instead of an executable — resolves what it can and leaves the rest to be resolved at runtime by the dynamic linker.
- `-o libab.so` : conventional naming — `lib<name>.so`, referenced later as `-lab`.

### Link a program against the shared library

```sh
gcc prog.c -o prog_dyn -L. -lab
```
Same meaning as before, but this time it picks up `libab.so`. The executable only stores a *reference* to `libab.so` — the actual code is loaded and linked at program start (or lazily, at first call) by the dynamic linker (`ld.so`).

### Running the dynamically-linked program

The dynamic linker needs to find `libab.so` at runtime. It won't look in the current directory by default, so one of these is needed:

```sh
LD_LIBRARY_PATH=. ./prog_dyn
```
- `LD_LIBRARY_PATH` : environment variable listing extra directories the dynamic linker searches for shared libraries, checked before the system default paths.

or bake the search path into the executable at link time:

```sh
gcc prog.c -o prog_rpath -L. -lab -Wl,-rpath,'$ORIGIN'
```
- `-Wl,-rpath,'$ORIGIN'` : `-Wl,` passes the following option through to the linker (`ld`); `-rpath,'$ORIGIN'` embeds a runtime search path into the executable itself, so it doesn't need `LD_LIBRARY_PATH`. `$ORIGIN` is a special token meaning "the directory the executable lives in" — quoted so the shell doesn't expand it.

## 4. Inspecting the results

```sh
ldd prog_dyn        # list the shared libraries prog_dyn depends on, and where they resolve from
ldd prog_rpath       # same, but shows libab.so resolved via the embedded rpath
file libab.so libab.a prog_static prog_dyn   # identify file types (ELF shared object, ar archive, executable, ...)
nm libab.a           # list symbols defined/undefined in each .o member of the archive
readelf -d prog_dyn  # show the dynamic section — e.g. NEEDED libab.so, RPATH/RUNPATH
```

## Static vs. shared — summary

| | Static (`.a`) | Shared (`.so`) |
|---|---|---|
| When code is linked in | Build/link time — copied into the executable | Load/run time — resolved by the dynamic linker |
| Executable size | Larger (contains library code) | Smaller (just a reference) |
| Compile flag needed | none | `-fPIC` |
| Runtime dependency | none | needs `.so` findable via `LD_LIBRARY_PATH`, rpath, or system path (`/lib`, `/usr/lib`, `ldconfig`) |
| Updating the library | requires recompiling/relinking every program that uses it | replace the `.so` file — every program picks up the new version automatically (as long as the ABI is unchanged) |
| Memory across processes | each process has its own copy of the code | one copy of the code page can be shared in memory across processes |
