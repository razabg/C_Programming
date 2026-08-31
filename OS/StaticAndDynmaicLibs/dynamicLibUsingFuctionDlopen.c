#include <stdio.h>
#include <dlfcn.h>

// Runtime ("explicit") linking: instead of linking against libab.so at
// build time (-L. -lab), this program loads it manually while running,
// via the dlopen/dlsym/dlclose API (link with -ldl).
//   dlopen(path, flag) -> loads/maps the shared object, returns an opaque
//                         handle (NULL on failure). RTLD_LAZY resolves each
//                         symbol on first use rather than all at load time.
//   dlsym(handle, name) -> looks up a symbol (function/variable) by name in
//                          the library, returns its address as void*.
//   dlerror()            -> returns a string describing the last dlopen/
//                            dlsym/dlclose error, or NULL if none since it
//                            was last called; must be called right after
//                            the failing call, since it clears the error.
//   dlclose(handle)      -> unmaps the library, decrementing its refcount.

int main(void)
{
    void *h = dlopen("./libab.so", RTLD_LAZY);
    if (!h)
    {
        fprintf(stderr, "dlopen: %s\n", dlerror());
        return 1;
    }

    dlerror(); /* clear any stale error */
    void (*pa)(void) = (void (*)(void))dlsym(h, "a"); // look up a() by name
    char *err = dlerror();
    if (err)
    {
        fprintf(stderr, "dlsym: %s\n", err);
        dlclose(h);
        return 1;
    }

    pa(); /* call through the pointer */

    dlsym(h, "nope"); // no such symbol -> demonstrates dlerror() reporting a lookup failure
    if ((err = dlerror()))
        fprintf(stderr, "expected failure -> %s\n", err);

    dlclose(h);
    return 0;
}
