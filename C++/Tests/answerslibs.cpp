// author: Adrian Michałek
// email: devmichalek@gmail.com

0.0 // The proper order for the specified needs is:
    // Compile test.c:
    //    gcc -c test.c
    // Create static library:
    //    ar -cvq libtest.a test.o
    // Compile and create executable:
    //    gcc -o main main.c libtest.a # or
    //    gcc -o main main.o -L/path/to/current/directory -ltest

0.1 // The proper order for the specified needs is:
    // Compile test.c with -fPIC (Platform Independent Code flag)
    //    gcc -fPIC -c test.c
    // Create dynamic library
    //    gcc -shared test.o -o libtest.so
    // Compile and create executable:
    //    gcc main.c -L/path/to/current/directory -ltest -o main
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH

0.2 // You have to use --whole-archive and --no-whole-archive flag.
    // These flags are linker flags so the use is actually -Wl,<flag>
    // While creating shared library we specify --whole-archive that means take all the objects from static library even these not needed (add2() function is not used in dynamic library but it may be used by dynamic library users). Then turn off this flag by setting --no-whole-archive, this step is crucial to escape infinite loop error.

    // Compile part.c and create static library:
    //    gcc -c part.c
    //    ar -cvq libpart.a part.o
    // Compile test.c and create a shared library:
    //    gcc -fPIC -c test.c
    //    gcc -shared -Wl,--whole-archive libpart.a Wl,--no-whole-archive test.o -o libtest.so
    // Set $LD_LIBRARY_PATH variable:
    //    LD_LIBRARY_PATH=path/to/current/directory
    //    export LD_LIBRARY_PATH
    // Compile and create executable:
    //    gcc main.c libtest.so -o main

0.3 // The only substantial difference is that by default all Windows DLL linker symbols are hidden, whereas in Linux all the dynamic library linker symbols are by default exported.

0.4 // Method I (affecting the whole body of code):
    // -fvisibility compiler flag
    // by passing the -fvisibility=hidden it is possible to make every dynamic library symbos invisible to whoever tries to dynamically link against the dynamic library.
    // Method II (affecting individual symbols only)
    // __attribute__ ((visibility("<default | hidden>")))
    // By decorating the function signature with the attribute property, you instruct the linker to either allow (default) or not allow (hidden) exporting the symbol.
    // Method III (affecting individual symbols or a group of symbols)
    // #pragma GCC visibility [push | pop]
    /* // Some header file may contain:
      #pragma visibility push(hidden)
      void someprivatefunction_1(void);
      void someprivatefunction_2(void);
      ...
      void someprivatefunction_N(void);
      #pragma visibility pop
    */

0.5 // Purpose, Linux Version, Windows Version
    // Library Loading, dlopen(), LoadLibrary()
    // Finding Symbol, dlsym(), GetProcAddress()
    // Library Unloading, dlclose(), FreeLibrary()
    // Error Reporting, dlerror(), GetLastError()

0.6 // By looking at the file size, static library will take times more bytes than import library (it's not the case but mostly).

0.7 // When RUNPATH field is specified (i.e. DT_RUNPATH is non-empty)
    // 1. LD_LIBRARY_PATH
    // 2. runpath (DT_RUNPATH field)
    // 3. ld.so.cache
    // 4. default library paths(/lib and /usr/lib)

    // In the absence of RUNPATH (i.e. DT_RUNPATH is empty string)
    // 1. RPATH of the loaded binary, followed by the RPATH of the binary
    // 2. LD_LIBRARY_PATH
    // 3. ld.so.cache
    /// 4. default library paths(/lib and /usr/lib)

0.8 // Windows Runtime Dynamic Library Location Rules:
    // In the simplest, popular, most widespread knowledge about the topic, the following two locations are used the most as the favorite paths to deploy the DLL needed at runtime:
    // The very same path in which the application binary file resides.
    // One of the system DLL folders (such as C:\Windows\System or C:\Windows\System32)

0.9 // There is missing -L switch written as follows:
    // gcc main.o -ldl -L. -lsh -o main

1.0 // The shared library and executable file format is called ELF (Executable and Linkable Format). In summary, an ELF file contains:
    // - ELF header
    // - File data, which may contain:
    // -  . Program header table (a list of segment headers)
    // -  . Section header table (a list of section headers)
    // -  . Data pointed to by the above headers
    // The ELF header specifies the size and number of segments in the program header table and the size and number of sections in the section header table. Each such table consists of fixed size entries. Entries are headers and they contain a “pointer” (an offset in the file) to the location of the actual body of the segment or section. That body exists in the data part of the file. To make matters more complicated - each section is a part of a segment, and a segment can contain many sections. In effect, the same data is referenced as either part of a segment or a section depending on the current context.
    // We use readelf to read the ELF.

1.1 // The only difference between rpath and runpath is the order they are searched in. Specifically, their relation to LD_LIBRARY_PATH - rpath is searched in before LD_LIBRARY_PATH while runpath is searched in after (if runpath is not set!). The meaning of this is that rpath cannot be changed dynamically with environment variables while runpath can.

1.2 // The same functionality between __cdecl and __stdcall is that arguments of function are pushed in reverse order (last pushed argument is first). The main difference is that functions declared with __stdcall automatically cleans up the stack, functions declared with __cdecl declaration requests calee to clean up the stack.

1.3 // ABIs cover details such as:
    // data type, size, and alignment,
    // the calling convention, which controls how functions' arguments are passed and return values retrieved,
    // the system call numbers and how an application should make system calls to the operating system.
    // Other ABIs standardize details such as:
    // the C++ name mangling,
    // exception propagation, and
    // calling convention between compilers on the same platform, but do not require cross-platform compatibility.
    // Short definition:
    // You are already familiar with the concept of an API. If you want to use the features of, say, some library or your OS, you will use an API. The API consists of data types/structures, constants, functions, etc that you can use in your code to access the functionality of that external component.
    // An ABI is very similar. Think of it as the compiled version of an API (or as an API on the machine-language level). When you write source code, you access the library through an API. Once the code is compiled, your application accesses the binary data in the library through the ABI. The ABI defines the structures and methods that your compiled application will use to access the external library (just like the API did), only on a lower level.
    // ABIs are important when it comes to applications that use external libraries. If a program is built to use a particular library and that library is later updated, you don't want to have to re-compile that application (and from the end-user's standpoint, you may not have the source). If the updated library uses the same ABI, then your program will not need to change. The interface to the library (which is all your program really cares about) is the same even though the internal workings may have changed. Two versions of a library that have the same ABI are sometimes called "binary-compatible" since they have the same low-level interface (you should be able to replace the old version with the new one and not have any major problems).
    // Sometimes, ABI changes are unavoidable. When this happens, any programs that use that library will not work unless they are re-compiled to use the new version of the library. If the ABI changes but the API does not, then the old and new library versions are sometimes called "source compatible". This implies that while a program compiled for one library version will not work with the other, source code written for one will work for the other if re-compiled.

1.5
    // Number of program headers: 9 (segments)
    // Number of section headers: 30 (sections)
    
