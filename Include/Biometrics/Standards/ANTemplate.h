#ifndef AN_TEMPLATE_H_INCLUDED
#define AN_TEMPLATE_H_INCLUDED

#include <Biometrics/Standards/ANType1Record.h>
#include <Biometrics/Standards/ANType2Record.h>
#include <Biometrics/Standards/ANType3Record.h>
#include <Biometrics/Standards/ANType4Record.h>
#include <Biometrics/Standards/ANType5Record.h>
#include <Biometrics/Standards/ANType6Record.h>
#include <Biometrics/Standards/ANType7Record.h>
#include <Biometrics/Standards/ANType8Record.h>
#include <Biometrics/Standards/ANType9Record.h>
#include <Biometrics/Standards/ANType10Record.h>
#include <Biometrics/Standards/ANType11Record.h>
#include <Biometrics/Standards/ANType13Record.h>
#include <Biometrics/Standards/ANType14Record.h>
#include <Biometrics/Standards/ANType15Record.h>
#include <Biometrics/Standards/ANType16Record.h>
#include <Biometrics/Standards/ANType17Record.h>
#include <Biometrics/Standards/ANType20Record.h>
#include <Biometrics/Standards/ANType21Record.h>
#include <Biometrics/Standards/ANType99Record.h>
#include <Images/NImage.h>
#include <Sound/NSoundBuffer.h>
#include <Biometrics/NTemplate.h>
#include <Biometrics/Standards/BdifTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANTemplate, NObject)

#define AN_TEMPLATE_VERSION_2_0 0x0200
#define AN_TEMPLATE_VERSION_2_1 0x0201
#define AN_TEMPLATE_VERSION_3_0 0x0300
#define AN_TEMPLATE_VERSION_4_0 0x0400
#define AN_TEMPLATE_VERSION_5_0 0x0500
#define AN_TEMPLATE_VERSION_5_1 0x0501
#define AN_TEMPLATE_VERSION_5_2 0x0502

#define AN_TEMPLATE_VERSION_CURRENT AN_TEMPLATE_VERSION_5_2

#define ANT_MAX_ANRECORD_COUNT_V5 1000

#define ANT_MAX_TYPE_8_RECORD_COUNT_V5 2


NResult N_API ANTemplateGetVersionsEx(NVersion_ * arValue, NInt valueLength);
NResult N_API ANTemplateIsVersionSupported(NVersion_ version, NBool * pValue);

NResult N_API ANTemplateGetVersionNameN(NVersion_ version, HNString * phValue);

#define ANT_LEAVE_INVALID_RECORDS_UNVALIDATED 0x00020000
#define ANT_USE_TWO_DIGIT_IDC                 0x00040000
#define ANT_USE_TWO_DIGIT_FIELD_NUMBER        0x00080000
#define ANT_USE_TWO_DIGIT_FIELD_NUMBER_TYPE_1 0x00100000
#define ANT_ALLOW_OUT_OF_BOUNDS_RESOLUTION    0x00200000
#define ANT_SKIP_NIST_MINUTIA_NEIGHBORS       0x00400000
#define ANT_CONVERT_NOT_SUPPORTED_IMAGES	  0x00800000

NResult N_API ANTemplateCreate(NUInt flags, HANTemplate * phTemplate);

NResult N_API ANTemplateCreateEx2(NVersion_ version, NUInt flags, HANTemplate * phTemplate);

NResult N_API ANTemplateCreateWithTransactionInformationN(NVersion_ version, HNString hTot, HNString hDai, HNString hOri, HNString hTcn, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateWithTransactionInformationA(NVersion_ version, const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateWithTransactionInformationW(NVersion_ version, const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateWithTransactionInformation(NVersion_ version, const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateWithTransactionInformation N_FUNC_AW(ANTemplateCreateWithTransactionInformation)


NResult N_API ANTemplateCreateWithTransactionInformationExN(HNString hTot, HNString hDai, HNString hOri, HNString hTcn, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateWithTransactionInformationExA(const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateWithTransactionInformationExW(const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateWithTransactionInformationEx(const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateWithTransactionInformationEx N_FUNC_AW(ANTemplateCreateWithTransactionInformationEx)

NResult N_API ANTemplateCreateFromFileEx2N(HNString hFileName, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateFromFileEx2A(const NAChar * szFileName, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateFromFileEx2W(const NWChar * szFileName, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateFromFileEx2(const NChar * szFileName, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromFileEx2 N_FUNC_AW(ANTemplateCreateFromFileEx2)

NResult N_API ANTemplateCreateFromMemoryEx2(const void * pBuffer, NSizeType bufferSize, NUInt flags, NSizeType * pSize, HANTemplate * phTemplate);
NResult N_API ANTemplateCreateFromMemoryEx2N(HNBuffer hBuffer, NUInt flags, NSizeType * pSize, HANTemplate * phTemplate);
NResult N_API ANTemplateCreateFromStreamEx2(HNStream hStream, NUInt flags, HANTemplate * phTemplate);

NResult N_API ANTemplateCreateFromANTemplate(HANTemplate hSrcTemplate, NVersion_ version, NUInt flags, HANTemplate * phTemplate);

NResult N_API ANTemplateCreateFromNTemplateExN(NVersion_ version, HNString hTot, HNString hDai, HNString hOri, HNString hTcn,
	NBool type9RecordFmtStd, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateFromNTemplateExA(NVersion_ version, const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn,
	NBool type9RecordFmtStd, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateFromNTemplateExW(NVersion_ version, const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn,
	NBool type9RecordFmtStd, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateFromNTemplateEx(NVersion_ version, const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn,
	NBool type9RecordFmtStd, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromNTemplateEx N_FUNC_AW(ANTemplateCreateFromNTemplateEx)


NResult N_API ANTemplateCreateFromFMRecordN(NVersion_ version, HNString hTot, HNString hDai, HNString hOri, HNString hTcn,
	HFMRecord hFMRecord, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateFromFMRecordA(NVersion_ version, const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn,
	HFMRecord hFMRecord, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateFromFMRecordW(NVersion_ version, const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn,
	HFMRecord hFMRecord, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateFromFMRecord(NVersion_ version, const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn,
	HFMRecord hFMRecord, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromFMRecord N_FUNC_AW(ANTemplateCreateFromFMRecord)


NResult N_API ANTemplateCheckValidity(HANTemplate hTemplate, NBool * pValue);
NResult N_API ANTemplateIsValidated(HANTemplate hTemplate, NBool * pValue);

NResult N_API ANTemplateGetRecordCount(HANTemplate hTemplate, NInt * pValue);
NResult N_API ANTemplateGetRecordEx(HANTemplate hTemplate, NInt index, HANRecord * phValue);
NResult N_API ANTemplateGetRecordCapacity(HANTemplate hTemplate, NInt * pValue);
NResult N_API ANTemplateSetRecordCapacity(HANTemplate hTemplate, NInt value);

NResult N_API ANTemplateAddType2Record(HANTemplate hTemplate, HANType2Record * phRecord);

NResult N_API ANTemplateAddType3Record(HANTemplate hTemplate, HANType3Record * phRecord);
NResult N_API ANTemplateAddType3RecordFromNImage(HANTemplate hTemplate, NBool isr, ANImageCompressionAlgorithm ca, HNImage hImage, HANType3Record * phRecord);
NResult N_API ANTemplateAddType3RecordFromImageDataN(HANTemplate hTemplate, NBool isr, HNBuffer hImageBuffer, HANType3Record * phRecord);

NResult N_API ANTemplateAddType4Record(HANTemplate hTemplate, HANType4Record * phRecord);
NResult N_API ANTemplateAddType4RecordFromNImage(HANTemplate hTemplate, NBool isr, ANImageCompressionAlgorithm ca, HNImage hImage, HANType4Record * phRecord);
NResult N_API ANTemplateAddType4RecordFromImageDataN(HANTemplate hTemplate, NBool isr, HNBuffer hImageBuffer, HANType4Record * phRecord);

NResult N_API ANTemplateAddType5Record(HANTemplate hTemplate, HANType5Record * phRecord);
NResult N_API ANTemplateAddType5RecordFromNImage(HANTemplate hTemplate, NBool isr, ANBinaryImageCompressionAlgorithm bca, HNImage hImage, HANType5Record * phRecord);

NResult N_API ANTemplateAddType6Record(HANTemplate hTemplate, HANType6Record * phRecord);
NResult N_API ANTemplateAddType6RecordFromNImage(HANTemplate hTemplate, NBool isr, ANBinaryImageCompressionAlgorithm bca, HNImage hImage, HANType6Record * phRecord);

NResult N_API ANTemplateAddType7Record(HANTemplate hTemplate, HANType7Record * phRecord);

NResult N_API ANTemplateAddType8Record(HANTemplate hTemplate, HANType8Record * phRecord);
NResult N_API ANTemplateAddType8RecordFromNImage(HANTemplate hTemplate, ANSignatureType st, ANSignatureRepresentationType srt, NBool isr, HNImage hImage, HANType8Record * phRecord);
NResult N_API ANTemplateAddType8RecordFromVectors(HANTemplate hTemplate, ANSignatureType st, const ANPenVector * arPenVectors, NInt penVectorCount, HANType8Record * phRecord);

NResult N_API ANTemplateAddType9Record(HANTemplate hTemplate, NUInt flags, HANType9Record * phRecord);
NResult N_API ANTemplateAddType9RecordFromNFRecordEx(HANTemplate hTemplate, NBool fmtStd, HNFRecord hNFRecord, NUInt flags, HANType9Record * phRecord);
NResult N_API ANTemplateAddType9RecordFromNFRecord(HANTemplate hTemplate, HNFRecord hNFRecord, NUInt flags, HANType9Record * phRecord);
NResult N_API ANTemplateAddType9RecordFromFMRecord(HANTemplate hTemplate, HFMRecord hFMRecord, NByte fingerViewIndex, NUInt flags, HANType9Record * phRecord);

NResult N_API ANTemplateAddType10Record(HANTemplate hTemplate, NUInt flags, HANType10Record * phRecord);

NResult N_API ANTemplateAddType10RecordFromNImageN(HANTemplate hTemplate, ANImageType imt, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType10Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType10RecordFromNImageA(HANTemplate hTemplate, ANImageType imt, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType10RecordFromNImageW(HANTemplate hTemplate, ANImageType imt, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType10RecordFromNImage(HANTemplate hTemplate, ANImageType imt, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#define ANTemplateAddType10RecordFromNImage N_FUNC_AW(ANType10RecordCreateFromNImage)

NResult N_API ANTemplateAddType10RecordFromImageDataN(HANTemplate hTemplate, ANImageType imt, HNString hSrc, HNBuffer hImageBuffer, NUInt flags, HANType10Record * phRecord);


NResult N_API ANTemplateAddType11Record(HANTemplate hTemplate, NUInt flags, HANType11Record * phRecord);

NResult N_API ANTemplateAddType11RecordFromNSoundBufferN(HANTemplate hTemplate, HNString hSrc, const struct ANAcquisitionSource_ * pAcquisitionSource, HNSoundBuffer hSoundBuffer, NUInt flags, HANType11Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType11RecordFromNSoundBufferA(HANTemplate hTemplate, const NAChar * szSrc, const struct ANAcquisitionSource_ * pAcquisitionSource, HNSoundBuffer hSoundBuffer, NUInt flags, HANType11Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType11RecordFromNSoundBufferW(HANTemplate hTemplate, const NWChar * szSrc, const struct ANAcquisitionSource_ * pAcquisitionSource, HNSoundBuffer hSoundBuffer, NUInt flags, HANType11Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType11RecordFromNSoundBuffer(HANTemplate hTemplate, const NChar * szSrc, const struct ANAcquisitionSource_ * pAcquisitionSource, HNSoundBuffer hSoundBuffer, NUInt flags, HANType11Record * phRecord);
#endif
#define ANTemplateAddType11RecordFromNSoundBuffer N_FUNC_AW(ANTemplateAddType11RecordFromNSoundBuffer)


NResult N_API ANTemplateAddType13Record(HANTemplate hTemplate, HANType13Record * phRecord);

NResult N_API ANTemplateAddType13RecordFromNImageN(HANTemplate hTemplate, BdifFPImpressionType imp, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType13Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType13RecordFromNImageA(HANTemplate hTemplate, BdifFPImpressionType imp, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType13Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType13RecordFromNImageW(HANTemplate hTemplate, BdifFPImpressionType imp, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType13Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType13RecordFromNImage(HANTemplate hTemplate, BdifFPImpressionType imp, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType13Record * phRecord);
#endif
#define ANTemplateAddType13RecordFromNImage N_FUNC_AW(ANType13RecordCreateFromNImage)

NResult N_API ANTemplateAddType13RecordFromImageDataN(HANTemplate hTemplate, BdifFPImpressionType imp, HNString hSrc, HNBuffer hImageBuffer, HANType13Record * phRecord);


NResult N_API ANTemplateAddType14Record(HANTemplate hTemplate, HANType14Record * phRecord);

NResult N_API ANTemplateAddType14RecordFromNImageN(HANTemplate hTemplate, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType14Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType14RecordFromNImageA(HANTemplate hTemplate, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType14Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType14RecordFromNImageW(HANTemplate hTemplate, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType14Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType14RecordFromNImage(HANTemplate hTemplate, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType14Record * phRecord);
#endif
#define ANTemplateAddType14RecordFromNImage N_FUNC_AW(ANType14RecordCreateFromNImage)

NResult N_API ANTemplateAddType14RecordFromImageDataN(HANTemplate hTemplate, HNString hSrc, HNBuffer hImageBuffer, HANType14Record * phRecord);


NResult N_API ANTemplateAddType15Record(HANTemplate hTemplate, HANType15Record * phRecord);

NResult N_API ANTemplateAddType15RecordFromNImageN(HANTemplate hTemplate, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType15Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType15RecordFromNImageA(HANTemplate hTemplate, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType15Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType15RecordFromNImageW(HANTemplate hTemplate, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType15Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType15RecordFromNImage(HANTemplate hTemplate, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType15Record * phRecord);
#endif
#define ANTemplateAddType15RecordFromNImage N_FUNC_AW(ANType15RecordCreateFromNImage)

NResult N_API ANTemplateAddType15RecordFromImageDataN(HANTemplate hTemplate, HNString hSrc, HNBuffer hImageBuffer, HANType15Record * phRecord);

NResult N_API ANTemplateAddType16Record(HANTemplate hTemplate, HANType16Record * phRecord);

NResult N_API ANTemplateAddType16RecordFromNImageN(HANTemplate hTemplate, HNString hUdi, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType16Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType16RecordFromNImageA(HANTemplate hTemplate, const NAChar * szUdi, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType16Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType16RecordFromNImageW(HANTemplate hTemplate, const NWChar * szUdi, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType16Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType16RecordFromNImage(HANTemplate hTemplate, const NChar * szUdi, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType16Record * phRecord);
#endif
#define ANTemplateAddType16RecordFromNImage N_FUNC_AW(ANType16RecordCreateFromNImage)

NResult N_API ANTemplateAddType16RecordFromImageDataN(HANTemplate hTemplate, HNString hUdi, HNString hSrc, HNBuffer hImageBuffer, HANType16Record * phRecord);


NResult N_API ANTemplateAddType17Record(HANTemplate hTemplate, HANType17Record * phRecord);

NResult N_API ANTemplateAddType17RecordFromNImageN(HANTemplate hTemplate, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType17Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType17RecordFromNImageA(HANTemplate hTemplate, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType17Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType17RecordFromNImageW(HANTemplate hTemplate, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType17Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType17RecordFromNImage(HANTemplate hTemplate, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType17Record * phRecord);
#endif
#define ANTemplateAddType17RecordFromNImage N_FUNC_AW(ANType17RecordCreateFromNImage)

NResult N_API ANTemplateAddType17RecordFromImageDataN(HANTemplate hTemplate, HNString hSrc, HNBuffer hImageBuffer, HANType17Record * phRecord);


NResult N_API ANTemplateAddType20Record(HANTemplate hTemplate, HANType20Record * phRecord);

NResult N_API ANTemplateAddType20RecordFromNImageN(HANTemplate hTemplate, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType20Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANTemplateAddType20RecordFromNImageA(HANTemplate hTemplate, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType20Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANTemplateAddType20RecordFromNImageW(HANTemplate hTemplate, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType20Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANTemplateAddType20RecordFromNImage(HANTemplate hTemplate, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, HANType20Record * phRecord);
#endif
#define ANTemplateAddType20RecordFromNImage N_FUNC_AW(ANType20RecordCreateFromNImage)

NResult N_API ANTemplateAddType20RecordFromImageDataN(HANTemplate hTemplate, HNString hSrc, HNBuffer hImageBuffer, HANType20Record * phRecord);

NResult N_API ANTemplateAddType21Record(HANTemplate hTemplate, HANType21Record * phRecord);
NResult N_API ANTemplateAddType99Record(HANTemplate hTemplate, HANType99Record * phRecord);

NResult N_API ANTemplateRemoveRecordAt(HANTemplate hTemplate, NInt index);
NResult N_API ANTemplateClearRecords(HANTemplate hTemplate);

NResult N_API ANTemplateSaveToFileN(HANTemplate hTemplate, HNString hFileName, NUInt flags);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateSaveToFileA(HANTemplate hTemplate, const NAChar * szFileName, NUInt flags);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateSaveToFileW(HANTemplate hTemplate, const NWChar * szFileName, NUInt flags);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateSaveToFile(HANTemplate hTemplate, const NChar * szFileName, NUInt flags);
#endif
#define ANTemplateSaveToFile N_FUNC_AW(ANTemplateSaveToFile)

NResult N_API ANTemplateSaveToFileExN(HANTemplate hTemplate, HNString hFileName, BdifEncodingType encodingType, NUInt flags);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateSaveToFileExA(HANTemplate hTemplate, const NAChar * szFileName, BdifEncodingType encodingType, NUInt flags);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateSaveToFileExW(HANTemplate hTemplate, const NWChar * szFileName, BdifEncodingType encodingType, NUInt flags);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateSaveToFileEx(HANTemplate hTemplate, const NChar * szFileName, BdifEncodingType encodingType, NUInt flags);
#endif
#define ANTemplateSaveToFileEx N_FUNC_AW(ANTemplateSaveToFileEx)

NResult N_API ANTemplateSaveToMemoryN(HANTemplate hTemplate, BdifEncodingType encodingType, NUInt flags, HNBuffer * phBuffer);


NResult N_API ANTemplateToNTemplate(HANTemplate hTemplate, NUInt flags, HNTemplate * phNTemplate);

NResult N_API ANTemplateGetVersion(HANTemplate hTemplate, NVersion_ * pValue);


#ifdef N_CPP
}
#endif

#endif // !AN_TEMPLATE_H_INCLUDED
