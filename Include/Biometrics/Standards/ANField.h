#ifndef AN_FIELD_H_INCLUDED
#define AN_FIELD_H_INCLUDED

#include <Biometrics/Standards/ANSubField.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANField, NObject)

NResult N_API ANFieldGetItemNameN(HANField hField, NInt index, HNString * phName, HNString * phTypeName);

NResult N_API ANFieldSetItemNameN(HANField hField, NInt index, HNString hName, HNString hTypeName);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldSetItemNameA(HANField hField, NInt index, const NAChar * szName, const NAChar * szTypeName);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldSetItemNameW(HANField hField, NInt index, const NWChar * szName, const NWChar * szTypeName);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldSetItemName(HANField hField, NInt index, const NChar * szName, const NChar * szTypeName);
#endif
#define ANFieldSetItem N_FUNC_AW(ANFieldSetItem)

NResult N_API ANFieldGetItemCount(HANField hField, NInt * pValue);
NResult N_API ANFieldGetItemN(HANField hField, NInt index, HNString * phValue);
NResult N_API ANFieldGetItemDataN(HANField hField, NInt index, HNBuffer * phValue);
NResult N_API ANFieldGetItemCapacity(HANField hField, NInt * pValue);
NResult N_API ANFieldSetItemCapacity(HANField hField, NInt value);

NResult N_API ANFieldSetItemN(HANField hField, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldSetItemExA(HANField hField, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldSetItemExW(HANField hField, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldSetItemEx(HANField hField, NInt index, const NChar * szValue);
#endif
#define ANFieldSetItemEx N_FUNC_AW(ANFieldSetItemEx)

NResult N_API ANFieldAddItemN(HANField hField, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldAddItemExA(HANField hField, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldAddItemExW(HANField hField, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldAddItemEx(HANField hField, const NChar * szValue, NInt * pIndex);
#endif
#define ANFieldAddItemEx N_FUNC_AW(ANFieldAddItemEx)

NResult N_API ANFieldAddItemExN(HANField hField, HNString hItemName, HNString hItemTypeName, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldAddItemEx2A(HANField hField, const NAChar * szItemName, const NAChar * szItemTypeName, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldAddItemEx2W(HANField hField, const NWChar * szItemName, const NWChar * szItemTypeName, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldAddItemEx2(HANField hField, const NChar * szItemName, const NChar * szItemTypeName, const NChar * szValue, NInt * pIndex);
#endif
#define ANFieldAddItemEx2 N_FUNC_AW(ANFieldAddItemEx2)


NResult N_API ANFieldInsertItemN(HANField hField, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldInsertItemExA(HANField hField, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldInsertItemExW(HANField hField, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldInsertItemEx(HANField hField, NInt index, const NChar * szValue);
#endif
#define ANFieldInsertItemEx N_FUNC_AW(ANFieldInsertItemEx)

NResult N_API ANFieldInsertItemExN(HANField hField, NInt index, HNString hItemName, HNString hItemTypeName, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldInsertItemEx2A(HANField hField, NInt index, const NAChar * szItemName, const NAChar * szItemTypeName, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldInsertItemEx2W(HANField hField, NInt index, const NWChar * szItemName, const NWChar * szItemTypeName, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldInsertItemEx2(HANField hField, NInt index, const NChar * szItemName, const NChar * szItemTypeName, const NChar * szValue);
#endif
#define ANFieldInsertItemEx2 N_FUNC_AW(ANFieldInsertItemEx2)


NResult N_API ANFieldRemoveItemAt(HANField hField, NInt index);
NResult N_API ANFieldRemoveItemRange(HANField hField, NInt index, NInt count);

NResult N_API ANFieldGetSubFieldCount(HANField hField, NInt * pValue);
NResult N_API ANFieldGetSubFieldEx(HANField hField, NInt index, HANSubField * phValue);
NResult N_API ANFieldGetSubFieldCapacity(HANField hField, NInt * pValue);
NResult N_API ANFieldSetSubFieldCapacity(HANField hField, NInt value);

NResult N_API ANFieldAddSubFieldN(HANField hField, HNString hValue, NInt * pIndex, HANSubField * phValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldAddSubFieldExA(HANField hField, const NAChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldAddSubFieldExW(HANField hField, const NWChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldAddSubFieldEx(HANField hField, const NChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#define ANFieldAddSubFieldEx N_FUNC_AW(ANFieldAddSubFieldEx)

NResult N_API ANFieldAddSubFieldExN(HANField hField, HNString hSubFieldName, HNString hValue, NInt * pIndex, HANSubField * phValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldAddSubFieldEx2A(HANField hField, const NAChar * szSubFieldName, const NAChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldAddSubFieldEx2W(HANField hField, const NWChar * szSubFieldName, const NWChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldAddSubFieldEx2(HANField hField, const NChar * szSubFieldName, const NChar * szValue, NInt * pIndex, HANSubField * phValue);
#endif
#define ANFieldAddSubFieldEx2 N_FUNC_AW(ANFieldAddSubFieldEx)


NResult N_API ANFieldInsertSubFieldN(HANField hField, NInt index, HNString hValue, HANSubField * phValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldInsertSubFieldExA(HANField hField, NInt index, const NAChar * szValue, HANSubField * phValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldInsertSubFieldExW(HANField hField, NInt index, const NWChar * szValue, HANSubField * phValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldInsertSubFieldEx(HANField hField, NInt index, const NChar * szValue, HANSubField * phValue);
#endif
#define ANFieldInsertSubFieldEx N_FUNC_AW(ANFieldInsertSubFieldEx)

NResult N_API ANFieldInsertSubFieldExN(HANField hField, NInt index, HNString hSubFieldName, HNString hValue, HANSubField * phValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldInsertSubFieldEx2A(HANField hField, NInt index, const NAChar * szSubFieldName, const NAChar * szValue, HANSubField * phValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldInsertSubFieldEx2W(HANField hField, NInt index, const NWChar * szSubFieldName, const NWChar * szValue, HANSubField * phValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldInsertSubFieldEx2(HANField hField, NInt index, const NChar * szSubFieldName, const NChar * szValue, HANSubField * phValue);
#endif
#define ANFieldInsertSubFieldEx2 N_FUNC_AW(ANFieldInsertSubFieldEx2)


NResult N_API ANFieldRemoveSubFieldAt(HANField hField, NInt index);
NResult N_API ANFieldRemoveSubFieldRange(HANField hField, NInt index, NInt count);

NResult N_API ANFieldGetValueN(HANField hField, HNString * phValue);
NResult N_API ANFieldGetDataN(HANField hField, HNBuffer * phValue);

NResult N_API ANFieldSetValueN(HANField hField, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldSetValueExA(HANField hField, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldSetValueExW(HANField hField, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldSetValueEx(HANField hField, const NChar * szValue);
#endif
#define ANFieldSetValueEx N_FUNC_AW(ANFieldSetValueEx)

NResult N_API ANFieldGetNumber(HANField hField, NInt * pValue);
NResult N_API ANFieldGetHeader(HANField hField, HNString * phValue);

NResult N_API ANFieldGetNameN(HANField hField, HNString * phValue);

NResult N_API ANFieldSetNameN(HANField hField, HNString hName);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFieldSetNameA(HANField hField, const NAChar * szName);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFieldSetNameW(HANField hField, const NWChar * szName);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFieldSetName(HANField hField, const NChar * szName);
#endif
#define ANSubFieldSetName N_FUNC_AW(ANSubFieldSetName)

#ifdef N_CPP
}
#endif

#endif // !AN_FIELD_H_INCLUDED
