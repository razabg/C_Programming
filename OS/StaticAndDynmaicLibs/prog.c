void a(void);
void b(void);
int main(void)
{
    a();
    b();
    return 0;
}


// # --- inspect -------------------------------------------------------------
// file x                    # what kind of file is this
// nm x.o                    # symbols: T/D/B defined, U undefined, lower=static
// nm -u x.o                 # undefined only
// nm -A *.o | grep -w sym   # who defines / who needs a symbol
// nm -S --size-sort x.o     # symbols by size (flash/binary bloat hunting)
// nm -C x.o                 # demangle C++
// readelf -h x              # ELF header
// readelf -SW x             # sections   (linker's view)
// readelf -lW x             # segments   (loader's view) + section→segment map
// readelf -d x              # .dynamic: NEEDED, SONAME, RUNPATH
// objdump -f x              # overall header
// objdump -h x              # section list  (note VMA vs LMA)
// objdump -d x              # disassemble
// objdump -T x              # dynamic (exported) symbols
// ldd x                     # transitive shared-lib deps (don't run on untrusted files)

// # --- static library ------------------------------------------------------
// gcc -c a.c b.c
// ar cr libab.a a.o b.o
// gcc -o app main.o -L. -lab            # library AFTER the objects!

// # --- shared library ------------------------------------------------------
// gcc -c -fPIC a.c b.c
// gcc -shared -o libab.so a.o b.o
// gcc -o app main.o -L. -lab
// LD_LIBRARY_PATH=. ./app                        # quick fix
// gcc -o app main.o -L. -lab -Wl,-rpath,'$ORIGIN' # shipped fix

// # --- versioned shared library -------------------------------------------
// gcc -shared -o libab.so.1.0.0 -Wl,-soname,libab.so.1 a.o b.o
// ln -sf libab.so.1.0.0 libab.so.1 && ln -sf libab.so.1 libab.so

// # --- explicit loading ----------------------------------------------------
// gcc -o loader loader.c -ldl
