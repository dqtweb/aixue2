// Copyright (C) by Ashton Mason. See LICENSE.txt for licensing information.


#ifndef THERON_ALIGN_H
#define THERON_ALIGN_H


#include <Theron/BasicTypes.h>
#include <Theron/Defines.h>

#include <Theron/Detail/Core/ActorAlignment.h>
#include <Theron/Detail/Debug/Assert.h>
#include <Theron/Detail/Messages/MessageAlignment.h>


/**
\file Align.h
Alignment markup for actor and message types.
*/


#ifndef THERON_ALIGN_ACTOR
/**
\brief Informs Theron of the alignment requirements of an actor type.
Use of this macro is optional. Using it, users can notify Theron of any
specialized memory alignment requirements of their custom actor classes.
If the memory alignment of an actor type is specified using this macro,
Theron will request correctly aligned memory when allocating instances
of that actor type in \ref Framework::CreateActor. If not, then a default
alignment of four bytes will be used.

\code
namespace MyNamespace
{

class MyActor : public Theron::Actor
{
};

}

THERON_ALIGN_ACTOR(MyNamespace::MyActor, 16);
\endcode

An important limitation of the actor alignment macro is that it
can only be used from within the global namespace. Furthermore the full
name of the actor type must be given, including all namespace scoping.
Unfortunately this means that it isn't generally possible to align actors
immediately after their declaration, as we'd often prefer.

\note Specifying the alignment requirements of an actor type is not enough,
by itself, to guarantee correct alignment of actor allocations. Users must also
ensure that any custom allocator provided via \ref Theron::AllocatorManager::SetAllocator
supports aligned allocations. The DefaultAllocator, used by default, supports alignment.

\see <a href="http://www.theron-library.com/index.php?t=page&p=AligningActors">Aligning actors</a>
*/
#define THERON_ALIGN_ACTOR(ActorType, alignment)                            \
namespace Theron                                                            \
{                                                                           \
namespace Detail                                                            \
{                                                                           \
template <>                                                                 \
struct ActorAlignment<ActorType>                                            \
{                                                                           \
    static const uint32_t ALIGNMENT = (alignment);                          \
};                                                                          \
}                                                                           \
}
#endif // THERON_ALIGN_ACTOR


#ifndef THERON_ALIGN_MESSAGE
/**
\brief Informs Theron of the alignment requirements of a message type.
Use of this macro is optional. Using it, users can notify Theron of any
specialized memory alignment requirements of their custom message classes.
If the memory alignment of a message type is specified using this macro,
Theron will request correctly aligned memory when allocating instances
of that message type internally (ie. when sending messages). If not, then
a default alignment of four bytes will be used.

\code
namespace MyNamespace
{

class MyMessage
{
};

}

THERON_ALIGN_MESSAGE(MyNamespace::MyMessage, 16);
\endcode

An important limitation of the message alignment macro is that it
can only be used from within the global namespace. Furthermore the full
name of the message type must be given, including all namespace scoping.
Unfortunately this means that it isn't generally possible to align messages
immediately after their declaration, as we'd often prefer.

\note Specifying the alignment requirements of an actor type is not enough,
by itself, to guarantee correct alignment of actor allocations. Users must also
ensure that any custom allocator provided via \ref Theron::AllocatorManager::SetAllocator
supports aligned allocations. The DefaultAllocator, used by default, supports alignment.

\see <a href="http://www.theron-library.com/index.php?t=page&p=AligningMessages">Aligning messages</a>
*/
#define THERON_ALIGN_MESSAGE(MessageType, alignment)                        \
namespace Theron                                                            \
{                                                                           \
namespace Detail                                                            \
{                                                                           \
template <>                                                                 \
struct MessageAlignment<MessageType>                                        \
{                                                                           \
    static const uint32_t ALIGNMENT = (alignment);                          \
};                                                                          \
}                                                                           \
}
#endif // THERON_ALIGN_MESSAGE


#ifndef THERON_PREALIGN
#ifdef _MSC_VER
#define THERON_PREALIGN(alignment) __declspec(align(alignment))
#elif defined(__GNUC__)
#define THERON_PREALIGN(alignment)
#else
/**
\brief Informs the compiler of the stack alignment requirements of a type.
First of two macros that can be used together when defining a class
to inform the compiler of the alignment requirements of the class.
This causes the compiler to automatically align instances of the class
when they are allocated on the stack (for example, when used as local
variables within user functions).

\code
#ifdef _MSC_VER
#pragma warning( disable : 4324 )
#endif // _MSC_VER

// A message type that requires alignment.
struct THERON_PREALIGN(128) AlignedMessage
{
    int mValue;
    
} THERON_POSTALIGN(128);

int main()
{
    AlignedMessage message;  // Aligned to 128 bytes by the compiler
}
\endcode
The reason for using two macros is for portability: GCC and Visual C++
differ on whether the alignment decoration comes before or after the
type definition.

The THERON_PREALIGN and THERON_POSTALIGN macros don't actually affect
Theron at all, because Theron never allocates user message types on the
stack. They are provided only for user convenience. Users with
types that require alignment can use these macros to cause those types
to be aligned correctly when used on the stack in their own code. Many
users with aligned types will of course already have their own similar
mechanism, and if so they can ignore THERON_PREALIGN and THERON_POSTALIGN.

In any event users with aligned actor and message types should remember
to also use the \ref THERON_ALIGN_ACTOR and \ref THERON_ALIGN_MESSAGE
macros, which do affect Theron and are important for ensuring that
actor and message objects allocated within Theron are correctly aligned.

This macro can be overridden, for example with a custom implementation for
a different compiler, by defining it in a local header included in user
code before any Theron headers.

\note You may need to disable warning C4324 in Visual C++ builds when using this macro.
\note If you use this macro, you should also use \ref THERON_POSTALIGN for portability.

\see THERON_POSTALIGN
\see <a href="http://www.theron-library.com/index.php?t=page&p=AligningMessages">Aligning messages</a>
*/
#define THERON_PREALIGN(alignment)
#endif
#endif // THERON_PREALIGN


#ifndef THERON_POSTALIGN
#ifdef _MSC_VER
#define THERON_POSTALIGN(alignment)
#elif defined(__GNUC__)
#define THERON_POSTALIGN(alignment) __attribute__ ((__aligned__ (alignment)))
#else
/**
\brief Informs the compiler of the stack alignment requirements of a type.
Declares an aligned type. Second of two parts, used after the type definition.

\note If you use this macro, you should also use \ref THERON_PREALIGN.

\see THERON_PREALIGN
\see <a href="http://www.theron-library.com/index.php?t=page&p=AligningMessages">Aligning messages</a>
*/
#define THERON_POSTALIGN(alignment)
#endif
#endif // THERON_POSTALIGN


#ifndef THERON_ALIGNOF
#ifdef _MSC_VER
#define THERON_ALIGNOF(type) __alignof(type)
#elif defined(__GNUC__)
#define THERON_ALIGNOF(type) __alignof(type)
#else
/**
\brief Queries the compiler for the stack alignment requirements of a type.
Portable macro for querying the compiler for the alignment requirement of a type.
This is a wrapper around the compiler function __alignof(). It is provided
in case different compilers have different syntax. Currently both supported
compilers use the same syntax.

This macro can be overridden, for example with a custom implementation for
a different compiler, by defining it in a local header included in user
code before any Theron headers.
*/
#define THERON_ALIGNOF(type) __alignof(type)
#endif
#endif // THERON_ALIGNOF


#ifndef THERON_ALIGN
/**
\brief Aligns the given pointer to the given alignment, in bytes, increasing its value if necessary.
\note Alignment values are expected to be powers of two.
*/
#define THERON_ALIGN(p, alignment) Theron::Detail::AlignPointer(p, alignment)
#endif // THERON_ALIGN


#ifndef THERON_ALIGNED
/**
\brief Checks the alignment of a pointer.
\note Alignment values are expected to be powers of two.
*/
#define THERON_ALIGNED(pointer, alignment) Theron::Detail::IsAligned(pointer, alignment)
#endif // THERON_ALIGNED


namespace Theron
{
namespace Detail
{


template <class Type>
THERON_FORCEINLINE void AlignPointer(Type *& pointer, const uint32_t alignment)
{
    // The uintptr_t type is an integer wide enough to store the value of a pointer.
    // It isn't defined in traditional C++, but is introduced via BasicTypes.h included above.
    THERON_ASSERT_MSG((alignment & (alignment - 1)) == 0, "Alignment values must be powers of two");
    pointer = reinterpret_cast<Type *>((reinterpret_cast<uintptr_t>(pointer) + alignment - 1) & ~uintptr_t(alignment - 1));
}


THERON_FORCEINLINE bool IsAligned(void *const pointer, const uint32_t alignment)
{
    THERON_ASSERT_MSG((alignment & (alignment - 1)) == 0, "Alignment values must be powers of two");
    return ((reinterpret_cast<uintptr_t>(pointer) & uintptr_t(alignment - 1)) == 0);
}


} // namespace Detail
} // namespace Theron


#endif // THERON_ALIGN_H

