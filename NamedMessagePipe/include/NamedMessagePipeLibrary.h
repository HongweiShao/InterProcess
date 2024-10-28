#ifndef NamedMessagePipeLibrary_h
#define NamedMessagePipeLibrary_h

#ifdef _WIN32
    #ifdef NAMEDMSGPIPELIB_EXPORTS
        #define NAMEDMSGPIPELIB_API __declspec(dllexport)
    #else
        #define NAMEDMSGPIPELIB_API __declspec(dllimport)
    #endif
#else
    #define NAMEDMSGPIPELIB_API
#endif


#endif /* NamedMessagePipeLibrary_h */