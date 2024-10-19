#ifndef N_MEMORY_HPP_INCLUDED
#define N_MEMORY_HPP_INCLUDED

#include <stdarg.h>
#include <string.h>
namespace Neurotec
{
#define N_CPP_API_HEADER_INCLUDED
#include <Core/NMemory.h>
inline NInt NCheck(NResult result);
}

namespace Neurotec
{

#undef NClear
#undef NAlignedAlloc
#undef NAlignedCAlloc
#undef NAlignedReAlloc
#undef NAlignedAllocArray
#undef NAlignedCAllocArray
#undef NAlignedReAllocArray

inline NResult NClear(void * pBlock, NSizeType size)
{
	return NFill(pBlock, 0, size);
}

inline NResult NAlignedAlloc(NSizeType size, NSizeType alignment, void * * ppBlock)
{
	return NAlignedOffsetAlloc(size, alignment, 0, ppBlock);
}

inline NResult NAlignedCAlloc(NSizeType size, NSizeType alignment, void * * ppBlock)
{
	return NAlignedOffsetCAlloc(size, alignment, 0, ppBlock);
}

inline NResult NAlignedReAlloc(void * * ppBlock, NSizeType size, NSizeType alignment)
{
	return NAlignedOffsetReAlloc(ppBlock, size, alignment, 0);
}

inline NResult NAlignedAllocArray(NSizeType elementSize, NInt length, NSizeType alignment, void * * ppRow)
{
	return NAlignedOffsetAllocArray(elementSize, length, alignment, 0, ppRow);
}

inline NResult NAlignedCAllocArray(NSizeType elementSize, NInt length, NSizeType alignment, void * * ppRow)
{
	return NAlignedOffsetCAllocArray(elementSize, length, alignment, 0, ppRow);
}

inline NResult NAlignedReAllocArray(NSizeType elementSize, void * * ppRow, NInt length, NSizeType alignment)
{
	return NAlignedOffsetReAllocArray(elementSize, ppRow, length, alignment, 0);
}

inline void * NAlloc(NSizeType size)
{
	void * pBlock;
	NCheck(NAlloc(size, &pBlock));
	return pBlock;
}

inline void * NCAlloc(NSizeType size)
{
	void * pBlock;
	NCheck(NCAlloc(size, &pBlock));
	return pBlock;
}

inline void * NReAlloc(void * pBlock, NSizeType size)
{
	NCheck(NReAlloc(&pBlock, size));
	return pBlock;
}

inline void NCopyMemory(void * pDstBlock, const void * pSrcBlock, NSizeType size)
{
	NCheck(NCopy(pDstBlock, pSrcBlock, size));
}

inline void NMoveMemory(void * pDstBlock, const void * pSrcBlock, NSizeType size)
{
	NCheck(NMove(pDstBlock, pSrcBlock, size));
}

inline void NFillMemory(void * pBlock, NByte value, NSizeType size)
{
	NCheck(NFill(pBlock, value, size));
}

inline void NClearMemory(void * pBlock, NSizeType size)
{
	NCheck(NClear(pBlock, size));
}

inline NInt NCompare(const void * pBlock1, const void * pBlock2, NSizeType size)
{
	NInt result;
	NCheck(NCompare(pBlock1, pBlock2, size, &result));
	return result;
}

inline void * NAlignedAlloc(NSizeType size, NSizeType alignment, NSizeType offset = 0)
{
	void * pBlock;
	NCheck(NAlignedOffsetAlloc(size, alignment, offset, &pBlock));
	return pBlock;
}

inline void * NAlignedCAlloc(NSizeType size, NSizeType alignment, NSizeType offset = 0)
{
	void * pBlock;
	NCheck(NAlignedOffsetCAlloc(size, alignment, offset, &pBlock));
	return pBlock;
}

inline void * NAlignedReAlloc(void * pBlock, NSizeType size, NSizeType alignment, NSizeType offset = 0)
{
	NCheck(NAlignedOffsetReAlloc(&pBlock, size, alignment, offset));
	return pBlock;
}


template<typename T> T * NAllocArray(NInt length)
{
	T * pArray;
	NCheck(NAllocArray(sizeof(T), length, (void * *)&pArray));
	return pArray;
}

template<typename T> T * NCAllocArray(NInt length)
{
	T * pArray;
	NCheck(NCAllocArray(sizeof(T), length, (void * *)&pArray));
	return pArray;
}

template<typename T> T * NReAllocArray(T * pArray, NInt length)
{
	NCheck(NReAllocArray(sizeof(T), (void * *)&pArray, length));
	return pArray;
}

template<typename T> void NCopyArray(T * pDstArray, const T * pSrcArray, NInt length)
{
	NCheck(NCopyArray(sizeof(T), pDstArray, pSrcArray, length));
}

template<typename T> void NMoveArray(T * pDstArray, const T * pSrcArray, NInt length)
{
	NCheck(NMoveArray(sizeof(T), pDstArray, pSrcArray, length));
}

template<typename T> void NClearArray(T * pArray, NInt length)
{
	NCheck(NClearArray(sizeof(T), pArray, length));
}

template<typename T> void * NAlignedAllocArray(NInt length, NSizeType alignment, NInt offset = 0)
{
	T * pArray;
	NCheck(NAlignedOffsetAllocArray(sizeof(T), length, alignment, offset, (void**)&pArray));
	return pArray;
}

template<typename T> void * NAlignedCAllocArray(NInt length, NSizeType alignment, NInt offset = 0)
{
	T * pArray;
	NCheck(NAlignedOffsetCAllocArray(sizeof(T), length, alignment, offset, (void**)&pArray));
	return pArray;
}

template<typename T> void * NAlignedReAllocArray(T * pArray, NInt length, NSizeType alignment, NInt offset = 0)
{
	NCheck(NAlignedOffsetReAllocArray(sizeof(T), (void**)&pArray, length, alignment, offset));
	return pArray;
}

template<typename T> NInt NArrayFromArray(const T * pSrcArray, NInt srcLength, T * pDstArray, NInt dstLength)
{
	return NCheck(NGetElements(T, pSrcArray, srcLength, pDstArray, dstLength));
}

template<typename T> T * NArrayFromArray(const T * pSrcArray, NInt srcLength, NInt * pDstValueCount)
{
	T * pDstArray;
	NCheck(NGetArray(T, pSrcArray, srcLength, (void**)&pDstArray, pDstValueCount));
	return pDstArray;
}

struct Clear
{
};

extern const Clear clear;

class NAutoFree
{
private:
	void * m_ptr;

public:
	explicit NAutoFree(void * ptr = NULL)
		: m_ptr(ptr)
	{
	}

	NAutoFree(NAutoFree & value)
		: m_ptr(value.Release())
	{
	}

	~NAutoFree()
	{
		Reset();
	}

	NAutoFree & operator=(NAutoFree & value)
	{
		Reset(value.Release());
		return (*this);
	}

	void * Get() const
	{
		return m_ptr;
	}

	void * Release()
	{
		void * ptr = this->m_ptr;
		this->m_ptr = NULL;
		return ptr;
	}

	void Reset(void * ptr = NULL)
	{
		if (ptr != this->m_ptr)
		{
			NFree(this->m_ptr);
			this->m_ptr = ptr;
		}
	}
};

class NAutoAlignedFree
{
private:
	void * m_ptr;

public:
	explicit NAutoAlignedFree(void * ptr = NULL)
		: m_ptr(ptr)
	{
	}

	NAutoAlignedFree(NAutoAlignedFree & value)
		: m_ptr(value.Release())
	{
	}

	~NAutoAlignedFree()
	{
		Reset();
	}

	NAutoAlignedFree & operator=(NAutoAlignedFree & value)
	{
		Reset(value.Release());
		return (*this);
	}

	void * Get() const
	{
		return m_ptr;
	}

	void * Release()
	{
		void * ptr = this->m_ptr;
		this->m_ptr = NULL;
		return ptr;
	}

	void Reset(void * ptr = NULL)
	{
		if (ptr != this->m_ptr)
		{
			NAlignedFree(this->m_ptr);
			this->m_ptr = ptr;
		}
	}
};

template<typename T> class NAutoArray
{
private:
	T * m_ptr;
	NInt m_count;

public:
	NAutoArray()
		: m_ptr(NULL), m_count(0)
	{
	}

	NAutoArray(T * ptr, NInt count)
		: m_ptr(ptr), m_count(count)
	{
	}

	NAutoArray(NInt count)
		: m_ptr(count == 0 ? NULL : (T *)NCAllocArray<T>(count)), m_count(count)
	{
	}

	NAutoArray(NAutoArray & value)
		: m_ptr(value.m_ptr), m_count(value.m_count)
	{
		value.Release();
	}

	~NAutoArray()
	{
		Reset();
	}

	NAutoArray & operator=(NAutoArray & value)
	{
		NInt count = value.m_count;
		Reset(value.Release(), count);
		return (*this);
	}

	T * operator->() const
	{
		return Get();
	}

	T & operator*() const
	{
		return *Get();
	}

	T & operator[](int index) const
	{
		return Get()[index];
	}

	T * Get() const
	{
		return m_ptr;
	}

	T & Get(int index) const
	{
		return m_ptr[index];
	}

	int GetCount() const
	{
		return m_count;
	}

	T * Release()
	{
		T * ptr = this->m_ptr;
		this->m_ptr = NULL;
		m_count = 0;
		return ptr;
	}

	void Reset()
	{
		Reset(NULL, 0);
	}

	void Reset(T * ptr, NInt count)
	{
		if (ptr != this->m_ptr)
		{
			if (this->m_ptr)
			{
				NFree(this->m_ptr);
			}
			this->m_ptr = ptr;
		}
		this->m_count = count;
	}
};

template<typename T> class NAutoPtrArray
{
private:
	T ** m_ptrs;
	int m_count;

public:
	NAutoPtrArray()
		: m_ptrs(NULL), m_count(0)
	{
	}

	NAutoPtrArray(T * * ptrs, int count)
		: m_ptrs(ptrs), m_count(count)
	{
	}

	NAutoPtrArray(int count)
		: m_ptrs(count == 0 ? NULL : (T **)NCAllocArray<T*>(count)), m_count(count)
	{
	}

	NAutoPtrArray(NAutoPtrArray & value)
		: m_ptrs(value.get()), m_count(value.size())
	{
		value.release();
	}

	~NAutoPtrArray()
	{
		reset();
	}

	NAutoPtrArray & operator=(NAutoPtrArray & value)
	{
		reset(value.get(), value.size());
		value.release();
		return (*this);
	}

	T * * operator->() const
	{
		return get();
	}

	T * & operator*() const
	{
		return *get();
	}

	T * & operator[](int index) const
	{
		return get()[index];
	}

	T * * get() const
	{
		return m_ptrs;
	}

	T * & get(int index) const
	{
		return m_ptrs[index];
	}

	int size() const
	{
		return m_count;
	}

	T * * release()
	{
		T * * ptrs = this->m_ptrs;
		this->m_ptrs = NULL;
		this->m_count = 0;
		return ptrs;
	}

	void reset()
	{
		reset(NULL, 0);
	}

	void reset(T * * ptrs, int count)
	{
		if (ptrs != this->m_ptrs)
		{
			if (this->m_ptrs)
			{
				for (int i = 0; i < this->m_count; i++)
				{
					NFree(this->m_ptrs[i]);
				}
				NFree(this->m_ptrs);
			}
			this->m_ptrs = ptrs;
		}
		this->m_count = count;
	}
};

template<typename T> class NAutoAlignedArray
{
private:
	T * m_ptr;
	NInt m_count;

public:
	NAutoAlignedArray()
		: m_ptr(NULL), m_count(0)
	{
	}

	NAutoAlignedArray(T * ptr, NInt count)
		: m_ptr(ptr), m_count(count)
	{
	}

	NAutoAlignedArray(NInt count, NSizeType alignment, NInt offset = 0)
		: m_ptr(count == 0 ? NULL : (T *)NAlignedCAllocArray<T>(count, alignment, offset)), m_count(count)
	{
	}

	NAutoAlignedArray(NAutoAlignedArray & value)
		: m_ptr(value.m_ptr), m_count(value.m_count)
	{
		value.Release();
	}

	~NAutoAlignedArray()
	{
		Reset();
	}

	NAutoAlignedArray & operator=(NAutoAlignedArray & value)
	{
		NInt count = value.m_count;
		Reset(value.Release(), count);
		return (*this);
	}

	T * operator->() const
	{
		return Get();
	}

	T & operator*() const
	{
		return *Get();
	}

	T & operator[](int index) const
	{
		return Get()[index];
	}

	T * Get() const
	{
		return m_ptr;
	}

	T & Get(int index) const
	{
		return m_ptr[index];
	}

	int GetCount() const
	{
		return m_count;
	}

	T * Release()
	{
		T * ptr = this->m_ptr;
		this->m_ptr = NULL;
		m_count = 0;
		return ptr;
	}

	void Reset()
	{
		Reset(NULL, 0);
	}

	void Reset(T * ptr, NInt count)
	{
		if (ptr != this->m_ptr)
		{
			if (this->m_ptr)
			{
				NAlignedFree(this->m_ptr);
			}
			this->m_ptr = ptr;
		}
		this->m_count = count;
	}
};

}

#endif // !N_MEMORY_HPP_INCLUDED
