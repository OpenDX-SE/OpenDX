/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/


/* TeX starts here. Do not remove this comment. */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#ifndef _DXI_MEMORY_H_
#define _DXI_MEMORY_H_

/*
\section{Storage allocation}
The Data Explorer provides its own storage allocation routines, which provide
hooks for debugging.
*/

Pointer DXAllocate(unsigned int n);
Pointer DXAllocateZero(unsigned int n);
/**
\index{Pointer}\index{DXAllocate}\index{DXAllocateZero}
{\tt DXAllocate()} allocates {\tt n} bytes of storage in global memory.
{\tt DXAllocateZero()} allocates {\tt n} bytes and zeroes the allocated
memory.  Returns a pointer to the storage, or returns null and sets
the error code to indicate an error (such as out of memory or a
corrupted arena).
**/

Pointer DXReAllocate(Pointer x, unsigned int n);
/**
\index{DXReAllocate}
Increases the size of the previously allocated block of storage
pointed to by {\tt x} to {\tt n} bytes.  The block is copied if
necessary; this invalidates any pointers to the old storage.  Returns
a pointer to the new block, or returns null and sets the error code to
indicate an error (such as out of memory or a corrupted arena).
**/

Error DXFree(Pointer x);
/**
\index{DXFree}
Frees the previously allocated block of storage pointed to by {\tt x}.
Returns {\tt OK}, or returns {\tt ERROR} and sets the error code to
indicate an error such as a corrupted arena.
**/

typedef Error (*Scavenger)(ulong);
Scavenger DXRegisterScavenger(Scavenger scavenger);
/**
\index{Scavenger}\index{DXRegisterScavenger}
Declares to the memory allocation system a routine that it can call
to free up memory when necessary.  The scavenger routine will be
called with a target number of bytes, and is expected to return {\tt
OK} if it believes it has freed memory or null if it cannot free
any memory.
**/

#define MEMORY_SMALL  0x10
#define MEMORY_LARGE  0x20
#define MEMORY_LOCAL  0x40

void DXPrintAlloc(int t);
/**
\index{DXPrintAlloc}
If {\tt t} is 0, this routine prints out a summary of total memory
usage.  If {\tt t} is 1, this routine prints out more detailed summary
information.  If {\tt t} is 2, this routine prints out the address and
size of every allocated and free block.  In each case, the entire
arena is traversed, so this routine can be used to check for
corruption of the arena.  This routine can be exercised from the Data
Explorer in script or user-interface mode by using the Usage module.
**/

void DXFindAlloc(Pointer find);
void DXFoundAlloc(void);
/**
\index{DXFindAlloc}\index{DXFoundAlloc}
{\tt DXFindAlloc} allows you to set an address to look for allocations and frees
by calling this routine with the address to watch for.  When the given
address is then allocated or freed, the memory management system calls
{\tt DXFoundAlloc()}; this routine does nothing, and just exists for setting
breakpoints on.
**/


#define MEMORY_ALLOCATED 0x1
#define MEMORY_FREE      0x2
#define MEMORY_PRIVATE   0x4

typedef Error (*MemDebug)(int blocktype, Pointer start, ulong size, Pointer p);


Error DXDebugAlloc(int arena, int blocktype, MemDebug m, Pointer p);
/**
\index{DebugAlloc}
{\t DebugAlloc} allows you to specify a routine
to be called on any or all types of memory blocks.  The routine is called
with the type of block, the starting address of the block, the size in bytes, 
and a pointer to whatever private information the debug routine was called
with.  
**/


Error DXSetMemorySize(ulong size, int ratio);
Error DXGetMemorySize(ulong *sm, ulong *lg);
Error DXGetMemoryBase(Pointer *sm, Pointer *lg);
/**
\index{SetMemorySize}\index{GetMemorySize}\index{GetMemoryBase}
{\t SetMemorySize} must be called before any other library routine.
The maximum shared memory size in bytes is set with {\t size}, and the
ratio between shared memory allocated for large blocks compared to 
small blocks is set with {\t ratio}.  {\t GetMemorySize} returns the
size in bytes of the small and large arenas.  If any of the
arena types are is not supported on this architecture 0 is returned.  
{\t GetMemoryBase} returns the starting memory address of each arena.  
If any of the arena types are not supported on this architecture
0 is returned.
**/


/* new routine */
Error DXTraceAlloc(int n);
/**
Returns OK if all memory arenas are consistent, and ERROR if any appear 
to have been corrupted.  If n > 0, each Nth subsequent call to the memory
manager code will verify the memory arenas before doing any work.
This enables memory corruption problems to be detected sooner, however it
can severely impact performance if N is a low number.  This feature is only
available in the debuggable version of the library.  
If n == 0, the arenas are checked for consistency, but subsequent tracing
is not enabled, or if it was previously enabled it is now disabled.
**/

#endif /* _DXI_MEMORY_H_ */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
