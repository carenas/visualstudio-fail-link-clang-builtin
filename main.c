#include <windows.h>

static void clear_cache(void* from, void* to)
{
	size_t size = (size_t)((char*)to - (char*)from);
	FlushInstructionCache(GetCurrentProcess(), from, size);
}

#ifdef __has_builtin
#if __has_builtin(__builtin___clear_cache)
#define CLEAR_CACHE(from, to) __builtin___clear_cache((char *)(from), (char *)(to))
#endif
#endif

#ifndef CLEAR_CACHE
#define CLEAR_CACHE(from, to) clear_cache((void *)(from), (void *)(to))
#endif

int main(void)
{
	char* p = (char*)&clear_cache;
	CLEAR_CACHE(p, p + 1);
	return 0;
}
