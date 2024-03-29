// Copyright (C) by Ashton Mason. See LICENSE.txt for licensing information.


#ifndef THERON_DEFAULTALLOCATOR_H
#define THERON_DEFAULTALLOCATOR_H


/**
\file DefaultAllocator.h
The allocator used within Theron by default.
*/


#include <Theron/Align.h>
#include <Theron/BasicTypes.h>
#include <Theron/Defines.h>
#include <Theron/IAllocator.h>

#include <Theron/Detail/Allocators/TrivialAllocator.h>
#include <Theron/Detail/Debug/Assert.h>
#include <Theron/Detail/Threading/Lock.h>
#include <Theron/Detail/Threading/Mutex.h>


namespace Theron
{


/**
\brief A simple general purpose memory allocator used by default.

This is the allocator implementation used by default within Theron.
It is a simple wrapper around a lower-level allocator (which is by default
itself a trivial wrapper around global new and delete). The purpose of DefaultAllocator
is to extend the lower-level allocator with support for aligned allocations,
allocation counting, and guardband checking.

The DefaultAllocator is used by Theron for its internal allocations, unless it
is replaced by a custom allocator via \ref AllocatorManager::SetAllocator.
The DefaultAllocator may also be used for allocations within user application code,
if desired, in which case it can be accessed via \ref AllocatorManager::GetAllocator.

The DefaultAllocator respects aligned allocation requests, and allocates
memory blocks whose start addresses are aligned to a boundary of a specified
multiple of bytes, when requested. For example, when requested, it can allocate
a block of memory starting at an address that is a multiple of 16 bytes.

Because this allocator supports alignment, it can be safely used by users needing
to align their actor types (using \ref THERON_ALIGN_ACTOR) or message types (using
\ref THERON_ALIGN_MESSAGE).

The \ref THERON_ENABLE_DEFAULTALLOCATOR_CHECKS define, defined in \ref Defines.h,
controls the enabling of various checking code, which is intended to be enabled
only for debugging. It is defined to 1 by default in debug builds and to 0 in
optimized (non-debug) builds.

The checks performed when \ref THERON_ENABLE_DEFAULTALLOCATOR_CHECKS is enabled include:
- Guardband checking of allocated memory blocks.
- Tracking of current and peak allocated memory (in bytes).
- Detection and reporting of memory leaks on application exit via asserts.

The checking of allocated memory, if enabled, is made thread-safe by means of an
internal Mutex object, which unavoidably adds to the overhead of the checking.
Generally the checking shouldn't be enabled in production code.

\note This default allocator can be replaced with a custom allocator implementation
using \ref AllocatorManager::SetAllocator.

\see AllocatorManager
\see <a href="http://www.theron-library.com/index.php?t=page&p=CustomAllocator">Using a custom allocator</a>
*/
class DefaultAllocator : public IAllocator
{
public:

    static const uint32_t GUARD_VALUE = 0xdddddddd;

    /**
    \brief Default constructor.

    Constructs a DefaultAllocator around an internally owned Detail::TrivialAllocator.
    The TrivialAllocator acts as a trivial wrapper around global new and delete. The
    DefaultAllocator adds support for alignment and tracking of allocations.
    */
    inline DefaultAllocator();

    /**
    \brief Explicit constructor.
    
    Constructs a DefaultAllocator around an explicitly provided lower-level allocator.
    Constructed like this, the DefaultAllocator wraps the provided allocator, adding
    support for alignment and tracking of allocations.

    \note The provided allocator is expected to always align to at least 4-byte boundaries.

    \param allocator Pointer to an allocator to be wrapped by the constructed DefaultAllocator.
    */
    inline explicit DefaultAllocator(IAllocator *const allocator);

    /**
    \brief Virtual destructor.

    When enabled via \ref THERON_ENABLE_DEFAULTALLOCATOR_CHECKS, the destructor
    checks that the amount of memory still allocated has been reduced to zero, in
    order to detect memory leaks.
    */
    inline virtual ~DefaultAllocator();

    /**
    \brief Allocates a block of contiguous memory.

    \ref Allocate is called by Theron for its internal allocations, unless the
    DefaultAllocator is replaced by a custom allocator via \ref AllocatorManager::SetAllocator.
    The DefaultAllocator may also be used for allocations within user application code,
    if desired, in which case it can be accessed via \ref AllocatorManager::GetAllocator.

    \note The returned memory is typically aligned to at least four-byte boundaries.
    For larger alignments, use \ref AllocateAligned.

    \param size The size of the memory block to allocate, in bytes, which must be a non-zero multiple of four bytes.
    \return A pointer to the allocated memory.
    */
    inline virtual void *Allocate(const SizeType size);

    /**
    \brief Allocates a block of contiguous memory aligned to a given byte-multiple boundary.

    This method supports alignment, and the returned memory is correctly aligned,
    starting at a memory address that is a multiple of the requested alignment value.

    The support for aligned allocations, as well as guardband checking and tracking of
    allocated memory when enabled, are implemented by allocating an extra preamble
    and postamble before and after each allocated memory block. This naturally adds
    'hidden' overheads to the size of each allocated memory block, making the actual
    amount of memory allocated greater than the total amount of memory allocated from
    the point of view of the caller. The internal layout of each allocated block is
    illustrated below:

    \verbatim
    |-----------|--------|--------|--------|---------------------------------|--------|---------|
    |  padding  | offset |  size  | guard  |          caller block           | guard  |  waste  |
    |-----------|--------|--------|--------|---------------------------------|--------|---------|
    \endverbatim

    When \ref THERON_ENABLE_DEFAULTALLOCATOR_CHECKS is zero, some checking fields are omitted,
    and allocated blocks have the following structure:

    \verbatim
    |-----------|--------|----------------------------------|---------|
    |  padding  | offset |           caller block           |  waste  |
    |-----------|--------|----------------------------------|---------|
    \endverbatim

    Where:
    - The \em caller \em  block starts at an aligned address.
    - \em padding is a padding field of variable size used to ensure that \em caller \em block is aligned.
    - \em offset is a uint32_t recording the offset in bytes of \em caller \em block within the block.
    - \em size is a uint32_t recording the size of \em caller \em block.
    - \em guard is a uint32_t marker word with known value of <code>0xdddddddd</code>.
    - \em waste is an unused field of variable size left over within the block after offsetting of the \em caller \em block.

    \param size The size of the memory block to allocate, in bytes, which must be a non-zero multiple of four bytes.
    \param alignment The alignment of the memory to allocate, in bytes, which must be a power of two.
    \return A pointer to the allocated memory.
    */
    inline virtual void *AllocateAligned(const SizeType size, const SizeType alignment);

    /**
    \brief Frees a previously allocated block of contiguous memory.

    \ref Free is called by Theron for its internal allocations, unless the
    DefaultAllocator is replaced by a custom allocator via \ref AllocatorManager::SetAllocator.
    The DefaultAllocator may also be used for allocations within user application code,
    if desired, in which case it can be accessed via \ref AllocatorManager::GetAllocator.

    \param memory Pointer to the memory to be deallocated.

    \note The pointer must not be null, and must address an allocated block of memory.
    */
    inline virtual void Free(void *const memory);

    /**
    \brief Gets the number of bytes currently allocated by the allocator.

    Returns the total number of bytes of memory currently allocated by calls to
    \ref Allocate or \ref AllocateAligned, but not freed in calls to \ref Free.

    \code
    Theron::IAllocator *const allocator = Theron::AllocatorManager::Instance().GetAllocator();
    Theron::DefaultAllocator *const defaultAllocator = dynamic_cast<Theron::DefaultAllocator *>(allocator);

    if (defaultAllocator)
    {
        printf("Default allocator has %d bytes currently allocated\n", defaultAllocator->GetBytesAllocated());
    }
    \endcode

    This method is only useful when allocation checking is enabled using \ref
    THERON_ENABLE_DEFAULTALLOCATOR_CHECKS (enabled, by default, in debug builds).
    If allocation checking is disabled then GetBytesAllocated returns zero.

    \note This method counts user allocations and doesn't include internal overheads
    introduced by alignment and memory tracking. The actual amount of memory
    allocated via the wrapped lower-level allocator is typically larger.

    \see GetPeakBytesAllocated
    */
    inline uint32_t GetBytesAllocated() const;

    /**
    \brief Gets the peak number of bytes ever allocated by the allocator at one time.

    Returns the peak number of bytes of memory ever allocated by calls to
    \ref Allocate or \ref AllocateAligned, but not freed in calls to \ref Free.

    \code
    Theron::IAllocator *const allocator = Theron::AllocatorManager::Instance().GetAllocator();
    Theron::DefaultAllocator *const defaultAllocator = dynamic_cast<Theron::DefaultAllocator *>(allocator);

    if (defaultAllocator)
    {
        printf("Default allocator peak allocation was %d bytes\n", defaultAllocator->GetPeakBytesAllocated());
    }
    \endcode

    This method is only useful when allocation checking is enabled using \ref
    THERON_ENABLE_DEFAULTALLOCATOR_CHECKS (enabled, by default, in debug builds).
    If allocation checking is disabled then GetPeakBytesAllocated returns zero.

    \note This method counts user allocations and doesn't include internal overheads
    introduced by alignment and memory tracking. The actual amount of memory
    allocated via the wrapped lower-level allocator is typically larger.

    \see GetBytesAllocated
    */
    inline uint32_t GetPeakBytesAllocated() const;

private:

    DefaultAllocator(const DefaultAllocator &other);
    DefaultAllocator &operator=(const DefaultAllocator &other);

    /// Internal method which is force-inlined to avoid a function call.
    inline void *AllocateInline(const SizeType size, const SizeType alignment);

    Detail::TrivialAllocator mTrivialAllocator;     ///< Trivial allocator used by default.
    IAllocator *const mAllocator;                   ///< Pointer to a lower-level allocator wrapped by this allocator.

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    Detail::Mutex mMutex;                           ///< Critical section object used to protect access to the allocation counts.
    uint32_t mBytesAllocated;                       ///< Tracks the number of bytes currently allocated not yet freed.
    uint32_t mPeakAllocated;                        ///< Tracks the peak number of bytes allocated but not yet freed.
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

};


inline DefaultAllocator::DefaultAllocator() :
  mTrivialAllocator(),
  mAllocator(&mTrivialAllocator)
{

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    Detail::Lock lock(mMutex);

    mBytesAllocated = 0;
    mPeakAllocated = 0;
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

}


inline DefaultAllocator::DefaultAllocator(IAllocator *const allocator) :
  mTrivialAllocator(),
  mAllocator(allocator)
{

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    Detail::Lock lock(mMutex);

    mBytesAllocated = 0;
    mPeakAllocated = 0;
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

}


inline DefaultAllocator::~DefaultAllocator()
{

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    // Memory leak detection.
    // Failures likely indicate Theron bugs, unless the allocator is used by user code.
    if (mBytesAllocated > 0)
    {
        THERON_FAIL_MSG("DefaultAllocator detected memory leaks");
    }
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

}


inline void *DefaultAllocator::Allocate(const SizeType size)
{
    // Default to 4-byte alignment in 32-bit builds.
    // This call is force-inlined.
    return AllocateInline(size, sizeof(int));
}


inline void *DefaultAllocator::AllocateAligned(const SizeType size, const SizeType alignment)
{
    // This call is force-inlined.
    return AllocateInline(size, alignment);
}


inline void DefaultAllocator::Free(void *const memory)
{
    // We don't expect to have allocated any blocks that aren't at least aligned to the machine word size.
    THERON_ASSERT_MSG(memory, "Free of null pointer");
    THERON_ASSERT_MSG(THERON_ALIGNED(memory, sizeof(int)), "Free of unaligned pointer");

    uint32_t *const callerBlock(reinterpret_cast<uint32_t *>(memory));

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    // Check the pre-and post-guard fields, bookending the caller block.
    const uint32_t *const offsetField(reinterpret_cast<uint32_t *>(callerBlock) - 3);
    const uint32_t *const sizeField(callerBlock - 2);
    const uint32_t *const preGuardField(callerBlock - 1);

    const uint32_t callerBlockSize(*sizeField);
    const uint32_t *const postGuardField(reinterpret_cast<uint32_t *>(reinterpret_cast<uint8_t *>(callerBlock) + callerBlockSize));

    if (*preGuardField != GUARD_VALUE || *postGuardField != GUARD_VALUE)
    {
        THERON_FAIL_MSG("Corrupted guardband indicates memory corruption");
    }

    {
        Detail::Lock lock(mMutex);

        THERON_ASSERT_MSG(mBytesAllocated >= callerBlockSize, "Unallocated free, suggests duplicate free");
        mBytesAllocated -= callerBlockSize;
    }

#else
    uint32_t *const offsetField(reinterpret_cast<uint32_t *>(callerBlock) - 1);
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

    // Address of the internally allocated block.
    const uint32_t callerBlockOffset(*offsetField);
    uint8_t *const block(reinterpret_cast<uint8_t *>(callerBlock) - callerBlockOffset);

    delete [] block;
}


THERON_FORCEINLINE uint32_t DefaultAllocator::GetBytesAllocated() const
{

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    return mBytesAllocated;
#else
    return 0;
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

}


THERON_FORCEINLINE uint32_t DefaultAllocator::GetPeakBytesAllocated() const
{

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    return mPeakAllocated;
#else
    return 0;
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

}


THERON_FORCEINLINE void *DefaultAllocator::AllocateInline(const SizeType size, const SizeType alignment)
{
    // Alignment values are expected to be powers of two greater than or equal to four bytes.
    // This ensures that the size, offset, and guard fields are 4-byte aligned.
    THERON_ASSERT_MSG(alignment >= 4, "Actor and message alignments must be at least 4 bytes");
    THERON_ASSERT_MSG((alignment & (alignment - 1)) == 0, "Actor and message alignments must be powers of two");

    // Allocation sizes are expected to be non-zero multiples of four bytes.
    // This ensures that the trailing guard field is 4-byte aligned.
    THERON_ASSERT_MSG(size >= 4, "Allocation of memory block less than four bytes in size");
    THERON_ASSERT_MSG((size & 0x3) == 0, "Allocation of memory block not a multiple of four bytes in size");

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
    const uint32_t numPreFields(3);
    const uint32_t numPostFields(1);
#else
    const uint32_t numPreFields(1);
    const uint32_t numPostFields(0);
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

    // Calculate the size of the internally allocated block.
    // We assume underlying allocations are always 4-byte aligned, so padding is at most (alignment-4) bytes.
    const uint32_t maxPaddingSize(alignment - 4);
    const uint32_t preambleSize(maxPaddingSize + numPreFields * sizeof(uint32_t));
    const uint32_t postambleSize(numPostFields * sizeof(uint32_t));
    const uint32_t internalSize(preambleSize + size + postambleSize);

    uint32_t *const block = reinterpret_cast<uint32_t *>(mAllocator->Allocate(internalSize));
    THERON_ASSERT_MSG(THERON_ALIGNED(block, 4), "Wrapped allocator is assumed to always align to 4-byte boundaries");

    if (block)
    {
        // Calculate the pre-padding required to offset the caller block to an aligned address.
        // We do this by accounting for the hidden pre-fields and then aligning the pointer.
        uint8_t *callerBlock(reinterpret_cast<uint8_t *>(block + numPreFields));
        THERON_ALIGN(callerBlock, alignment);

#if THERON_ENABLE_DEFAULTALLOCATOR_CHECKS
        uint32_t *const offsetField(reinterpret_cast<uint32_t *>(callerBlock) - 3);
        uint32_t *const sizeField(reinterpret_cast<uint32_t *>(callerBlock) - 2);
        uint32_t *const preGuardField(reinterpret_cast<uint32_t *>(callerBlock) - 1);
        uint32_t *const postGuardField(reinterpret_cast<uint32_t *>(callerBlock + size));

        *sizeField = size;
        *preGuardField = GUARD_VALUE;
        *postGuardField = GUARD_VALUE;

        {
            Detail::Lock lock(mMutex);

            mBytesAllocated += size;
            if (mBytesAllocated > mPeakAllocated)
            {
                mPeakAllocated = mBytesAllocated;
            }
        }
#else
        uint32_t *const offsetField(reinterpret_cast<uint32_t *>(callerBlock) - 1);
#endif // THERON_ENABLE_DEFAULTALLOCATOR_CHECKS

        // Offset of the caller block within the internally allocated block, in bytes.
        const uint32_t callerBlockOffset(static_cast<uint32_t>(callerBlock - reinterpret_cast<uint8_t *>(block)));
        *offsetField = callerBlockOffset;

        // Caller gets the address of the caller block, which is expected to be aligned.
        THERON_ASSERT(THERON_ALIGNED(callerBlock, alignment));
        return callerBlock;
    }

    THERON_FAIL_MSG("Out of memory in DefaultAllocator!");
    return 0;
}


} // namespace Theron


#endif // THERON_DEFAULTALLOCATOR_H

