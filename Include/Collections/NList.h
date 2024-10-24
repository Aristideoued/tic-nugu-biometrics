#ifndef N_LIST_H_INCLUDED
#define N_LIST_H_INCLUDED

#include <Core/NType.h>

#ifdef N_CPP
extern "C"
{
#endif

#ifdef N_64
	#define N_LIST_SIZE 48
#else
	#define N_LIST_SIZE 32
#endif

N_DECLATE_PRIMITIVE(NList, N_LIST_SIZE)
N_DECLARE_TYPE(NList)

NResult N_API NListInitP(NList * pList, NSizeType elementSize, NTypeOfProc pElementTypeOf);
NResult N_API NListInit(NList * pList, NSizeType elementSize, HNType hElementType);
NResult N_API NListInitWithCapacityP(NList * pList, NSizeType elementSize, NTypeOfProc pElementTypeOf, NInt capacity);
NResult N_API NListInitWithCapacity(NList * pList, NSizeType elementSize, HNType hElementType, NInt capacity);
NResult N_API NListInitExP(NList * pList, NSizeType elementSize, NTypeOfProc pElementTypeOf, NInt capacity, NInt maxCapacity, NInt growthDelta, NSizeType alignment);
NResult N_API NListInitEx(NList * pList, NSizeType elementSize, HNType hElementType, NInt capacity, NInt maxCapacity, NInt growthDelta, NSizeType alignment);
NResult N_API NListDispose(NList * pList);
NResult N_API NListGetCapacity(const NList * pList, NInt * pValue);
NResult N_API NListSetCapacity(NList * pList, NInt value);
NResult N_API NListGetCount(const NList * pList, NInt * pValue);
NResult N_API NListSetCount(NList * pList, NInt value);
NResult N_API NListIndexOfInRange(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt startIndex, NInt count, NInt * pResult);
NResult N_API NListIndexOfInRangeP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt startIndex, NInt count, NInt * pResult);
NResult N_API NListIndexOfFrom(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt startIndex, NInt * pResult);
NResult N_API NListIndexOfFromP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt startIndex, NInt * pResult);
NResult N_API NListIndexOf(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt * pResult);
NResult N_API NListIndexOfP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt * pResult);
NResult N_API NListLastIndexOfInRange(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt startIndex, NInt count, NInt * pResult);
NResult N_API NListLastIndexOfInRangeP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt startIndex, NInt count, NInt * pResult);
NResult N_API NListLastIndexOfFrom(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt startIndex, NInt * pResult);
NResult N_API NListLastIndexOfFromP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt startIndex, NInt * pResult);
NResult N_API NListLastIndexOf(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt * pResult);
NResult N_API NListLastIndexOfP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt * pResult);
NResult N_API NListContains(const NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NBool * pResult);
NResult N_API NListContainsP(const NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NBool * pResult);
NResult N_API NListGetStart(const NList * pList, NSizeType elementSize, HNType hValueType, void * * ppValue);
NResult N_API NListGetStartP(const NList * pList, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValue);
NResult N_API NListGetEnd(const NList * pList, NSizeType elementSize, HNType hValueType, void * * ppValue);
NResult N_API NListGetEndP(const NList * pList, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValue);
NResult N_API NListGetPtr(const NList * pList, NInt index, NSizeType elementSize, HNType hValueType, void * * ppValue);
NResult N_API NListGetPtrP(const NList * pList, NInt index, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValue);
NResult N_API NListGet(const NList * pList, NInt index, HNType hValueType, void * pValue, NSizeType valueSize);
NResult N_API NListGetP(const NList * pList, NInt index, NTypeOfProc pValueTypeOf, void * pValue, NSizeType valueSize);
NResult N_API NListSet(NList * pList, NInt index, HNType hValueType, const void * pValue, NSizeType valueSize);
NResult N_API NListSetP(NList * pList, NInt index, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize);
NResult N_API NListAdd(NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize);
NResult N_API NListAddP(NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize);
NResult N_API NListAddRange(NList * pList, HNType hValueType, const void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListAddRangeP(NList * pList, NTypeOfProc pValueTypeOf, const void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListAddList(NList * pList, NList * pSrcList);
NResult N_API NListInsert(NList * pList, NInt index, HNType hValueType, const void * pValue, NSizeType valueSize);
NResult N_API NListInsertP(NList * pList, NInt index, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize);
NResult N_API NListInsertRange(NList * pList, NInt index, HNType hValueType, const void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListInsertRangeP(NList * pList, NInt index, NTypeOfProc pValueTypeOf, const void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListInsertList(NList * pList, NInt index, NList * pSrcList);
NResult N_API NListRemoveAt(NList * pList, NInt index);
NResult N_API NListRemoveRange(NList * pList, NInt index, NInt count);
NResult N_API NListRemove(NList * pList, HNType hValueType, const void * pValue, NSizeType valueSize, NInt * pIndex);
NResult N_API NListRemoveP(NList * pList, NTypeOfProc pValueTypeOf, const void * pValue, NSizeType valueSize, NInt * pIndex);
NResult N_API NListClear(NList * pList);
NResult N_API NListCopyToRange(NList * pList, NInt index, NInt count, HNType hValueType, void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListCopyToRangeP(NList * pList, NInt index, NInt count, NTypeOfProc pValueTypeOf, void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListCopyTo(NList * pList, HNType hValueType, void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListCopyToP(NList * pList, NTypeOfProc pValueTypeOf, void * pValues, NSizeType valuesSize, NInt valuesLength);
NResult N_API NListToArrayRange(NList * pList, NInt index, NInt count, NSizeType elementSize, HNType hValueType, void * * ppValues, NInt * pValuesLength);
NResult N_API NListToArrayRangeP(NList * pList, NInt index, NInt count, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValues, NInt * pValuesLength);
NResult N_API NListToArray(NList * pList, NSizeType elementSize, HNType hValueType, void * * ppValues, NInt * pValuesLength);
NResult N_API NListToArrayP(NList * pList, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValues, NInt * pValuesLength);
NResult N_API NListDetachArray(NList * pList, NSizeType elementSize, HNType hValueType, void * * ppValues, NInt * pValuesLength);
NResult N_API NListDetachArrayP(NList * pList, NSizeType elementSize, NTypeOfProc pValueTypeOf, void * * ppValues, NInt * pValuesLength);

#ifdef N_CPP
}
#endif

#endif // !N_LIST_H_INCLUDED
