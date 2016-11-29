////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_EXCEPTION_H__
#define __CORE_EXCEPTION_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Whenever an error is generated in Noesis (NS_ERROR) an instance of this class is created
/// There are two posible kind of exceptions:
///  - Normal exceptions: C++ exceptions created with NS_ERROR
///  - Critical exceptions: notified by the operating system, for example: access violation
///      Critical exceptions should not be catched. The state of the application is corrupt and 
///      the program should be terminated. If you want to catch a critical exception (for example, 
///      for saving data before closing the application, you should clear the critical flag or you 
///      will get a warning in the logger.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API Exception: public std::exception
{
public:
    /// Constructor to create an empty Exception
    Exception();

    /// Constructor for non critical exceptions (reported by NS_ERROR)
    /// \param buffer desc textual description of the error
    /// \param line line where the error was generated
    /// \param file file where the error was generated
    Exception(const NsChar* desc, NsInt line, const NsChar* file, void* context = 0);
 
    /// Constructor for critical exceptions (reported by Operating System)
    /// \param buffer desc textual description of the error
    Exception(const NsChar* desc, void* context = 0);

    // Copy Constructor
    Exception(const Exception& exception);

    /// Destructor
    ~Exception() throw();

    /// Copy operator
    Exception& operator=(const Exception& exception);

    /// \return the description of the error
    const NsChar* GetDescription() const;

    /// \return the stack trace
    void* const* GetStackTrace() const;

    /// \return If this exception is critical
    NsBool IsCritical() const;

    /// \return Set the critical flag to false. This function should be called when you are
    /// intentionally catching a critical exception
    void ClearCriticalFlag() const;

    /// Reset to the status of an empty Exception
    void Clear();

    /// Dump the content of this Exception to the Log
    void DumpExceptionToLog(NsByte severity, NsBool dumpStack, const NsChar* channel
        = "General") const;
    
    /// Increases the detail of this exception description. The description passed to this function
    /// is added as a new line to the previous description. This is usually useful when an exception
    /// is catched and rethrowed again.
    void RefineDescription(const NsChar* desc);

    /// Comparisson operator
    NsBool operator==(const Exception& exception) const;

    /// Generate a string representation of the exception
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Exception that are moved from one thread to another use the functions move() and destroy().
    /// TBB destroy() the moved exception when the memory manager is closed.
    static void *operator new(size_t size);
    static void operator delete(void* ptr);

    /// From std::exception
    const char* what() const throw();

private:
    /// Internal helper for construction
    void ConstructException(const NsChar* desc, NsInt line, const NsChar* file, void* context,
        NsBool isCritical); 

    /// Internal helper for copy operations
    void Copy(const Exception& exception);

private:
    mutable NsBool mIsCritical;
    NsInt mLine;
    
    static const NsInt FileSize = 256;
    NsChar mFile[FileSize];

    static const NsInt DescSize = 1024;
    NsChar mDesc[DescSize];

    static const NsInt StackTraceSize = 64;
    void* mStackTrace[StackTraceSize];
    
private:
    NS_DECLARE_REFLECTION(Exception, NoParent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
