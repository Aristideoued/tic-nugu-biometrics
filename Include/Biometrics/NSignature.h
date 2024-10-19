#ifndef N_SIGNATURE_H_INCLUDED
#define N_SIGNATURE_H_INCLUDED

#include <Biometrics/NBiometric.h>
#include <Biometrics/NAAttributes.h>
#include <Images/NImage.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NSignature, NBiometric)

struct NPenVector_
{
	NUShort X;
	NUShort Y;
	NByte Pressure;
};
#ifndef N_SIGNATURE_HPP_INCLUDED
typedef struct NPenVector_ NPenVector;
#endif

N_DECLARE_TYPE(NPenVector)

NResult N_API NSignatureCreate(HNSignature * phSignature);

NResult N_API NSignatureGetImage(HNSignature hSignature, HNImage * phValue);
NResult N_API NSignatureSetImage(HNSignature hSignature, HNImage hValue);

NResult N_API NSignatureGetObjectCount(HNSignature hSignature, NInt * pValue);
NResult N_API NSignatureGetObject(HNSignature hSignature, NInt index, HNAAttributes * phValue);
NResult N_API NSignatureGetObjects(HNSignature hSignature, HNAAttributes * * parhValues, NInt * pValueCount);

NResult N_API NSignatureAddObjectsCollectionChanged(HNSignature hSignature, HNCallback hCallback);
NResult N_API NSignatureAddObjectsCollectionChangedCallback(HNSignature hSignature, N_COLLECTION_CHANGED_CALLBACK_ARG(HNAAttributes, pCallback), void * pParam);
NResult N_API NSignatureRemoveObjectsCollectionChanged(HNSignature hSignature, HNCallback hCallback);
NResult N_API NSignatureRemoveObjectsCollectionChangedCallback(HNSignature hSignature, N_COLLECTION_CHANGED_CALLBACK_ARG(HNAAttributes, pCallback), void * pParam);

NResult N_API NSignatureGetVectorCount(HNSignature hSignature, NInt * pValue);
NResult N_API NSignatureGetVector(HNSignature hSignature, NInt index, struct NPenVector_ * pValue);
NResult N_API NSignatureGetVectors(HNSignature hSignature, struct NPenVector_ * * parValues, NInt * pValueCount);
NResult N_API NSignatureGetVectorCapacity(HNSignature hSignature, NInt * pValue);
NResult N_API NSignatureSetVectorCapacity(HNSignature hSignature, NInt value);
NResult N_API NSignatureSetVector(HNSignature hSignature, NInt index, const struct NPenVector_ * pValue);
NResult N_API NSignatureAddVector(HNSignature hSignature, const struct NPenVector_ * pValue, NInt * pIndex);
NResult N_API NSignatureInsertVector(HNSignature hSignature, NInt index, const struct NPenVector_ * pValue);
NResult N_API NSignatureRemoveVectorAt(HNSignature hSignature, NInt index);
NResult N_API NSignatureClearVectors(HNSignature hSignature);

#ifdef N_CPP
}
#endif

#endif // !N_SIGNATURE_H_INCLUDED
