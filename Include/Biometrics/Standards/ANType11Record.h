#ifndef AN_TYPE_11_RECORD_H_INCLUDED
#define AN_TYPE_11_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.h>
#include <Sound/NSoundBuffer.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType11Record, ANAsciiBinaryRecord)

#define AN_TYPE_11_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_11_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC

#define AN_TYPE_11_RECORD_FIELD_AOD 3

#define AN_TYPE_11_RECORD_FIELD_SRC AN_ASCII_BINARY_RECORD_FIELD_SRC

#define AN_TYPE_11_RECORD_FIELD_VRSO 5
#define AN_TYPE_11_RECORD_FIELD_VRC  6
#define AN_TYPE_11_RECORD_FIELD_AREC 7 
#define AN_TYPE_11_RECORD_FIELD_AQS  8
#define AN_TYPE_11_RECORD_FIELD_RCD  9 
#define AN_TYPE_11_RECORD_FIELD_VRD  10 
#define AN_TYPE_11_RECORD_FIELD_TRD  11
#define AN_TYPE_11_RECORD_FIELD_PMO  12
#define AN_TYPE_11_RECORD_FIELD_CONT 13
#define AN_TYPE_11_RECORD_FIELD_CDC  14
#define AN_TYPE_11_RECORD_FIELD_RED  21
#define AN_TYPE_11_RECORD_FIELD_RDD  22
#define AN_TYPE_11_RECORD_FIELD_DIS  23
#define AN_TYPE_11_RECORD_FIELD_DSD  24
#define AN_TYPE_11_RECORD_FIELD_VOC  25
#define AN_TYPE_11_RECORD_FIELD_VCD  26
#define AN_TYPE_11_RECORD_FIELD_OCON 27
#define AN_TYPE_11_RECORD_FIELD_OCD	 28
#define AN_TYPE_11_RECORD_FIELD_SGEO 32
#define AN_TYPE_11_RECORD_FIELD_SQV  33
#define AN_TYPE_11_RECORD_FIELD_VCI  34
#define AN_TYPE_11_RECORD_FIELD_PPY  35
#define AN_TYPE_11_RECORD_FIELD_VSCD 36
#define AN_TYPE_11_RECORD_FIELD_SCC  37
#define AN_TYPE_11_RECORD_FIELD_SCH  38
#define AN_TYPE_11_RECORD_FIELD_COM  51

#define AN_TYPE_11_RECORD_FIELD_UDF_FROM 100
#define AN_TYPE_11_RECORD_FIELD_UDF AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_11_RECORD_FIELD_ANN  AN_ASCII_BINARY_RECORD_FIELD_ANN
#define AN_TYPE_11_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_11_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_11_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_11_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_11_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR

#define AN_TYPE_11_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA


#define AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_NAME_LENGTH		400
#define AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_CONTACT_LENGTH	200
#define AN_TYPE_11_RECORD_MIN_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH	2
#define AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH	3

#define AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MAKE_LENGTH			AN_RECORD_MAX_MAKE_LENGTH
#define AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MODEL_LENGTH			AN_RECORD_MAX_MODEL_LENGTH
#define AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_SERIAL_NUMBER_LENGTH	AN_RECORD_MAX_SERIAL_NUMBER_LENGTH

#define AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_TIME				99999999999
#define AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_COMPRESSED_BYTES	99999999999999
#define AN_TYPE_11_RECORD_MAX_RECORDING_DIGITAL_SAMPLES_BYTES		99999999999999

#define AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_DESCRIPTION_LENGTH		300
#define AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_RECORDING_SPEED_LENGTH	9

#define AN_TYPE_11_RECORD_MAX_CONTAINER_EXTERNAL_REFERENCE_LENGTH	80

#define AN_TYPE_11_RECORD_MAX_CODEC_SAMPLING_RATE_NUMBER	100000000
#define AN_TYPE_11_RECORD_MAX_CODEC_BIT_DEPTH				1024
#define AN_TYPE_11_RECORD_MAX_CODEC_NUMERIC_FORMAT_LENGTH	5
#define AN_TYPE_11_RECORD_MAX_CODEC_EXTERNAL_REFERENCE_LENGTH	80

#define AN_TYPE_11_RECORD_MAX_AUTHORITY_ORGANIZATION_LENGTH	300

#define AN_TYPE_11_RECORD_MAX_TRACK_AND_CHANNEL			9999

#define AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT	600000
#define AN_TYPE_11_RECORD_MAX_SEGMENT_IDENTIFIER	AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT

#define AN_TYPE_11_RECORD_MAX_REDACTION_DIARY_COUNT			AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_DISCONTINUITY_DIARY_COUNT		AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_VOCAL_CONTENT_DIARY_COUNT		AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_OTHER_CONTENT_DIARY_COUNT		AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_SEGMENT_GEOGRAPHIC_LOCATION_COUNT	AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT

#define AN_TYPE_11_RECORD_MAX_SEGMENT_QUALITY_BLOCK_COUNT		9

#define AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_COUNT	9
#define AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_VALUE	9

#define AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_DESCRIPTION_COUNT			AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_SEGMENT_SPEAKER_CHARACTERISTICS_COUNT		AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#define AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_COUNT						AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT

#define AN_TYPE_11_RECORD_MAX_CONTENT_DIARY_TIME_SOURCE_DESCRIPTION_LENGTH	300

#define AN_TYPE_11_RECORD_MAX_SGEO_CELL_PHONE_TOWER_CODE_LENGTH	100

#define AN_TYPE_11_RECORD_LANGUAGE_CODE_LENGTH	3

#define AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_PHONETIC_TRANSCRIPT_CONVENTION_LENGTH	100

#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_SPEAKER		9999

#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_TYPE_2_RECORD_REFERENCE		AN_RECORD_MAX_IDC_V5
#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_IMPAIRMENT_LEVEL				5 
#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_LANGUAGE_PROFICIENCY_SCALE	9
#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_INTELLIGIBILITY_SCALE			9
#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_FAMILIARITY_DEGREE			5
#define AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_VOCAL_EFFORT_SCALE			5

#define AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_TRANSDUCER_DISTANCE			99999

typedef enum ANAudioObjectDescriptor_
{
	anadUnspecified = -1,
	anadInternalDigitalVoiceDataFile = 0,
	anadExternalDigitalVoiceDataFile = 1,
	anadPhysicalMediaObjectDigitalData = 2,
	anadPhysicalMediaObjectAnalogSignals = 3,
	anadPhysicalMediaObjectUnknownData = 4,
	anadNoAudioObject = 5
} ANAudioObjectDescriptor;

N_DECLARE_TYPE(ANAudioObjectDescriptor)

typedef enum ANSourceOrganizationType_
{
	ansotUnknown = 0,
	ansotPrivateIndividual = 1,
	ansotIndustryCommercial = 2,
	ansotGovernment = 3,
	ansotOther = 255
} ANSourceOrganizationType;

N_DECLARE_TYPE(ANSourceOrganizationType)

struct ANSourceOrganization_
{
	ANSourceOrganizationType organizationType;
	HNString hOrganizationName;
	HNString hPointOfContact;
	HNString hSourceCountryCode;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSourceOrganization_ ANSourceOrganization;
#endif

N_DECLARE_TYPE(ANSourceOrganization)

NResult N_API ANSourceOrganizationCreateN(ANSourceOrganizationType organizationType, HNString hOrganizationName, HNString hPointOfContact, HNString hSourceCountryCode, struct ANSourceOrganization_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSourceOrganizationCreateA(ANSourceOrganizationType organizationType, const NAChar * szOrganizationName, const NAChar * szPointOfContact, const NAChar * szSourceCountryCode, struct ANSourceOrganization_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSourceOrganizationCreateW(ANSourceOrganizationType organizationType, const NWChar * szOrganizationName, const NWChar * szPointOfContact, const NWChar * szSourceCountryCode, struct ANSourceOrganization_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSourceOrganizationCreate(ANSourceOrganizationType organizationType, const NChar * szOrganizationName, const NChar * szPointOfContact, const NChar * szSourceCountryCode, struct ANSourceOrganization_ * pValue);
#endif
#define ANSourceOrganizationCreate N_FUNC_AW(ANSourceOrganizationCreate)

NResult N_API ANSourceOrganizationDispose(struct ANSourceOrganization_ * pValue);
NResult N_API ANSourceOrganizationCopy(const struct ANSourceOrganization_ * pSrcValue, struct ANSourceOrganization_ * pDstValue);
NResult N_API ANSourceOrganizationSet(const struct ANSourceOrganization_ * pSrcValue, struct ANSourceOrganization_ * pDstValue);


typedef enum ANAssignedVoiceIndicator_
{
	anaviAssignedIdentity = 1,
	anaviNotAssignedIdentity = 2,
	anaviQuestionedIdentity = 3
} ANAssignedVoiceIndicator;

N_DECLARE_TYPE(ANAssignedVoiceIndicator)

typedef enum ANSpeakerPluralityCode_
{
	anspcUnspecified = 0,
	anspcMultiple = 1,
	anspcSingle = 2
} ANSpeakerPluralityCode;

N_DECLARE_TYPE(ANSpeakerPluralityCode)

struct ANVoiceRecordingContent_
{
	ANAssignedVoiceIndicator assignedVoiceIndicator;
	ANSpeakerPluralityCode speakerPlurality;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANVoiceRecordingContent_ ANVoiceRecordingContent;
#endif

N_DECLARE_TYPE(ANVoiceRecordingContent)

NResult N_API ANVoiceRecordingContentCreateN(ANAssignedVoiceIndicator assignedVoiceIndicator, ANSpeakerPluralityCode speakerPlurality, HNString hComment, struct ANVoiceRecordingContent_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANVoiceRecordingContentA(ANAssignedVoiceIndicator assignedVoiceIndicator, ANSpeakerPluralityCode speakerPlurality, const NAChar * szComment, struct ANVoiceRecordingContent_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANVoiceRecordingContentW(ANAssignedVoiceIndicator assignedVoiceIndicator, ANSpeakerPluralityCode speakerPlurality, const NWChar * szComment, struct ANVoiceRecordingContent_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANVoiceRecordingContentCreate(ANAssignedVoiceIndicator assignedVoiceIndicator, ANSpeakerPluralityCode speakerPlurality, const NChar * szComment, struct ANVoiceRecordingContent_ * pValue);
#endif
#define ANVoiceRecordingContentCreate N_FUNC_AW(ANVoiceRecordingContentCreate)

NResult N_API ANVoiceRecordingContentDispose(struct ANVoiceRecordingContent_ * pValue);
NResult N_API ANVoiceRecordingContentCopy(const struct ANVoiceRecordingContent_ * pSrcValue, struct ANVoiceRecordingContent_ * pDstValue);
NResult N_API ANVoiceRecordingContentSet(const struct ANVoiceRecordingContent_ * pSrcValue, struct ANVoiceRecordingContent_ * pDstValue);


struct ANAudioRecordingDevice_
{
	HNString hDescriptiveText;
	HNString hMake;
	HNString hModel;
	HNString hSerialNumber;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANAudioRecordingDevice_ ANAudioRecordingDevice;
#endif

N_DECLARE_TYPE(ANAudioRecordingDevice)

NResult N_API ANAudioRecordingDeviceCreateN(HNString hDescriptiveText, HNString hMake, HNString hModel, HNString hSerialNumber, struct ANAudioRecordingDevice_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAudioRecordingDeviceCreateA(const NAChar * szDescriptiveText, const NAChar * szMake, const NAChar * szModel, const NAChar * szSerialNumber, struct ANAudioRecordingDevice_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAudioRecordingDeviceCreateW(const NWChar * szDescriptiveText, const NWChar * szMake, const NWChar * szModel, const NWChar * szSerialNumber, struct ANAudioRecordingDevice_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAudioRecordingDeviceCreate(const NChar * szDescriptiveText, const NChar * szMake, const NChar * szModel, const NChar * szSerialNumber, struct ANAudioRecordingDevice_ * pValue);
#endif
#define ANAudioRecordingDeviceCreate N_FUNC_AW(ANAudioRecordingDeviceCreate)

NResult N_API ANAudioRecordingDeviceDispose(struct ANAudioRecordingDevice_ * pValue);
NResult N_API ANAudioRecordingDeviceCopy(const struct ANAudioRecordingDevice_ * pSrcValue, struct ANAudioRecordingDevice_ * pDstValue);
NResult N_API ANAudioRecordingDeviceSet(const struct ANAudioRecordingDevice_ * pSrcValue, struct ANAudioRecordingDevice_ * pDstValue);


struct ANRecordingDuration_
{
	NLong recordingTime;
	NLong compressedBytes;
	NLong totalDigitalSamples;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANRecordingDuration_ ANRecordingDuration;
#endif

N_DECLARE_TYPE(ANRecordingDuration)

struct ANPhysicalMediaObject_
{
	HNString hMediaTypeDescription;
	NDouble recordingSpeed;
	HNString hRecordingSpeedUnits;
	HNString hEqualizationDescription;
	NShort trackCount;
	HNArray hSpeakerTrackList;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANPhysicalMediaObject_ ANPhysicalMediaObject;
#endif

N_DECLARE_TYPE(ANPhysicalMediaObject)

NResult N_API ANPhysicalMediaObjectCreateN(HNString hMediaTypeDescription, NDouble recordingSpeed, HNString hRecordingSpeedUnits, HNString hEqualizationDescription,
	NShort trackCount, HNArray hSpeakerTrackList, HNString hComment, struct ANPhysicalMediaObject_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANPhysicalMediaObjectCreateA(const NAChar * szMediaTypeDescription, NDouble recordingSpeed, const NAChar * szRecordingSpeedUnits, const NAChar * szEqualizationDescription,
	NShort trackCount, HNArray hSpeakerTrackList, const NAChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANPhysicalMediaObjectCreateW(const NWChar * szMediaTypeDescription, NDouble recordingSpeed, const NWChar * szRecordingSpeedUnits, const NWChar * szEqualizationDescription,
	NShort trackCount, HNArray hSpeakerTrackList, const NWChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANPhysicalMediaObjectCreate(const NChar * szMediaTypeDescription, NDouble recordingSpeed, const NChar * szRecordingSpeedUnits, const NChar * szEqualizationDescription,
	NShort trackCount, HNArray hSpeakerTrackList, const NChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#define ANAudioRecordingDeviceCreate N_FUNC_AW(ANAudioRecordingDeviceCreate)

NResult N_API ANPhysicalMediaObjectCreateExN(HNString hMediaTypeDescription, NDouble recordingSpeed, HNString hRecordingSpeedMeasurementUnits, HNString hEqualizationDescription,
	NShort trackCount, const NUShort * arSpeakerTrackList, NInt speakerTrackListLength, HNString hComment, struct ANPhysicalMediaObject_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANPhysicalMediaObjectCreateExA(const NAChar * szMediaTypeDescription, NDouble recordingSpeed, const NAChar * szRecordingSpeedMeasurementUnits, const NAChar * szEqualizationDescription,
	NShort trackCount, const NUShort * arSpeakerTrackList, NInt speakerTrackListLength, const NAChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANPhysicalMediaObjectCreateExW(const NWChar * szMediaTypeDescription, NDouble recordingSpeed, const NWChar * szRecordingSpeedMeasurementUnits, const NWChar * szEqualizationDescription,
	NShort trackCount, const NUShort * arSpeakerTrackList, NInt speakerTrackListLength, const NWChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANPhysicalMediaObjectCreateEx(const NChar * szMediaTypeDescription, NDouble recordingSpeed, const NChar * szRecordingSpeedMeasurementUnits, const NChar * szEqualizationDescription,
	NShort trackCount, const NUShort * arSpeakerTrackList, NInt speakerTrackListLength, const NChar * szComment, struct ANPhysicalMediaObject_ * pValue);
#endif
#define ANAudioRecordingDeviceCreateEx N_FUNC_AW(ANAudioRecordingDeviceCreateEx)


NResult N_API ANPhysicalMediaObjectDispose(struct ANPhysicalMediaObject_ * pValue);
NResult N_API ANPhysicalMediaObjectCopy(const struct ANPhysicalMediaObject_ * pSrcValue, struct ANPhysicalMediaObject_ * pDstValue);
NResult N_API ANPhysicalMediaObjectSet(const struct ANPhysicalMediaObject_ * pSrcValue, struct ANPhysicalMediaObject_ * pDstValue);

typedef enum ANContainerCode_
{
	anccRaw = 0,
	anccReference = 1,
	anccOther = 2,
	anccWav = 3,
	anccMobileVideo3GP3G2 = 4,
	anccAiff = 5,
	anccMp3 = 6,
	anccNistSphere = 7,
	anccQuickTime = 8,
	anccVideoForWindows = 9,
	anccVorbis = 10,
	anccWinMediaType1 = 11,
	anccWinMediaType2 = 12,
	anccMpeg4 = 13
} ANContainerCode;

N_DECLARE_TYPE(ANContainerCode)

struct ANContainer_
{
	ANContainerCode containerCode;
	HNString hExternalContainerReference;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANContainer_ ANContainer;
#endif

N_DECLARE_TYPE(ANContainer)

NResult N_API ANContainerCreateN(ANContainerCode containerCode, HNString hExternalContainerReference, HNString hComment, struct ANContainer_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANContainerCreateA(ANContainerCode containerCode, const NAChar * szExternalContainerReference, const NAChar * szComment, struct ANContainer_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANContainerCreateW(ANContainerCode containerCode, const NWChar * szExternalContainerReference, const NWChar * szComment, struct ANContainer_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANContainerCreate(ANContainerCode containerCode, const NChar * szExternalContainerReference, const NChar * szComment, struct ANContainer_ * pValue);
#endif
#define ANContainerCreate N_FUNC_AW(ANContainerCreate)

NResult N_API ANContainerDispose(struct ANContainer_ * pValue);
NResult N_API ANContainerCopy(const struct ANContainer_ * pSrcValue, struct ANContainer_ * pDstValue);
NResult N_API ANContainerSet(const struct ANContainer_ * pSrcValue, struct ANContainer_ * pDstValue);

typedef enum ANCodecCode_
{
	ancdcLinearPcm = 0,
	ancdcCodecTypeReference = 1,
	ancdcOther = 2,
	ancdcFloatingPointLinearPcm = 3,
	ancdcULawWithForwardOrderDigitalSamples = 4,
	ancdcULawWithReverseOrderDigitalSamples = 5,
	ancdcALawWithForwardOrderDigitalSamples = 6,
	ancdcALawWithReverseOrderDigitalSamples = 7
} ANCodecCode;

N_DECLARE_TYPE(ANCodecCode)

struct ANCodec_
{
	ANCodecCode codecCode;
	NInt samplingRate;
	NShort bitDepth;
	ANEndianCode endianCode;
	HNString hNumericFormat;
	NShort channelCount;
	HNString hExternalCodecReference;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANCodec_ ANCodec;
#endif

N_DECLARE_TYPE(ANCodec)

NResult N_API ANCodecCreateN(ANCodecCode codecCode, NInt samplingRate, NShort bitDepth, ANEndianCode endianCode, HNString hNumericFormat, NShort channelCount, HNString hExternalCodecReference, HNString hComment, struct ANCodec_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANCodecCreateA(ANCodecCode codecCode, NInt samplingRate, NShort bitDepth, ANEndianCode endianCode, const NAChar * szNumericFormat, NShort channelCount, const NAChar * szExternalCodecReference, const NAChar * szComment, struct ANCodec_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANCodecCreateW(ANCodecCode codecCode, NInt samplingRate, NShort bitDepth, ANEndianCode endianCode, const NWChar * szNumericFormat, NShort channelCount, const NWChar * szExternalCodecReference, const NWChar * szComment, struct ANCodec_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANCodecCreate(ANCodecCode codecCode, NInt samplingRate, NShort bitDepth, ANEndianCode endianCode, const NChar * szNumericFormat, NShort channelCount, const NChar * szExternalCodecReference, const NChar * szComment, struct ANCodec_ * pValue);
#endif
#define ANCodecCreate N_FUNC_AW(ANCodecCreate)

NResult N_API ANCodecDispose(struct ANCodec_ * pValue);
NResult N_API ANCodecCopy(const struct ANCodec_ * pSrcValue, struct ANCodec_ * pDstValue);
NResult N_API ANCodecSet(const struct ANCodec_ * pSrcValue, struct ANCodec_ * pDstValue);

typedef enum ANProcessingIndicator_
{
	anpiNoRedactionDiscontinuity = 0,
	anpiRedactionDiscontinuity = 1,
	anpiUndetermined = 2,
} ANProcessingIndicator;

N_DECLARE_TYPE(ANProcessingIndicator)

struct ANAudioInformation_
{
	ANProcessingIndicator indicator;
	HNString hAuthorityOrganization;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANAudioInformation_ ANAudioInformation;
#endif

N_DECLARE_TYPE(ANAudioInformation)

NResult N_API ANAudioInformationCreateN(ANProcessingIndicator indicator, HNString hAuthorityOrganization, HNString hComment, struct ANAudioInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAudioInformationCreateA(ANProcessingIndicator indicator, const NAChar * szAuthorityOrganization, const NAChar * szComment, struct ANAudioInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAudioInformationCreateW(ANProcessingIndicator indicatore, const NWChar * szAuthorityOrganization, const NWChar * szComment, struct ANAudioInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAudioInformationCreate(ANProcessingIndicator indicator, const NChar * szAuthorityOrganization, const NChar * szComment, struct ANAudioInformation_ * pValue);
#endif
#define ANAudioInformationCreate N_FUNC_AW(ANAudioInformationCreate)

NResult N_API ANAudioInformationDispose(struct ANAudioInformation_ * pValue);
NResult N_API ANAudioInformationCopy(const struct ANAudioInformation_ * pSrcValue, struct ANAudioInformation_ * pDstValue);
NResult N_API ANAudioInformationSet(const struct ANAudioInformation_ * pSrcValue, struct ANAudioInformation_ * pDstValue);

struct ANDiaryInformation_
{
	NUInt segmentIdentifier;
	HNArray hTrackChannelList;
	NULong relativeStartTime;
	NULong relativeEndTime;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANDiaryInformation_ ANDiaryInformation;
#endif

N_DECLARE_TYPE(ANDiaryInformation)

NResult N_API ANDiaryInformationCreateN(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, HNString hComment, struct ANDiaryInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANDiaryInformationCreateA(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NAChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANDiaryInformationCreateW(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NWChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANDiaryInformationCreate(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#define ANDiaryInformationCreate N_FUNC_AW(ANDiaryInformationCreate)

NResult N_API ANDiaryInformationCreateExN(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, HNString hComment, struct ANDiaryInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANDiaryInformationCreateExA(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NAChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANDiaryInformationCreateExW(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NWChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANDiaryInformationCreateEx(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NChar * szComment, struct ANDiaryInformation_ * pValue);
#endif
#define ANDiaryInformationCreateEx N_FUNC_AW(ANDiaryInformationCreateEx)

NResult N_API ANDiaryInformationDispose(struct ANDiaryInformation_ * pValue);
NResult N_API ANDiaryInformationCopy(const struct ANDiaryInformation_ * pSrcValue, struct ANDiaryInformation_ * pDstValue);
NResult N_API ANDiaryInformationSet(const struct ANDiaryInformation_ * pSrcValue, struct ANDiaryInformation_ * pDstValue);

typedef enum ANDiarizationIndicator_
{
	andriNoDiary = 0,
	andriDiary = 1
} ANDiarizationIndicator;

N_DECLARE_TYPE(ANDiarizationIndicator)

struct ANContentInformation_
{
	ANDiarizationIndicator diarizationIndicator;
	HNString hAuthorityOrganization;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANContentInformation_ ANContentInformation;
#endif

N_DECLARE_TYPE(ANContentInformation)

NResult N_API ANContentInformationCreateN(ANDiarizationIndicator diarizationIndicator, HNString hAuthorityOrganization, HNString hComment, struct ANContentInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANContentInformationCreateA(ANDiarizationIndicator diarizationIndicator, const NAChar * szAuthorityOrganization, const NAChar * szComment, struct ANContentInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANContentInformationCreateW(ANDiarizationIndicator diarizationIndicator, const NWChar * szAuthorityOrganization, const NWChar * szComment, struct ANContentInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANContentInformationCreate(ANDiarizationIndicator diarizationIndicator, const NChar * szAuthorityOrganization, const NChar * szComment, struct ANContentInformation_ * pValue);
#endif
#define ANContentInformationCreate N_FUNC_AW(ANAudioRecordingDeviceCreate)

NResult N_API ANContentInformationDispose(struct ANContentInformation_ * pValue);
NResult N_API ANContentInformationCopy(const struct ANContentInformation_ * pSrcValue, struct ANContentInformation_ * pDstValue);
NResult N_API ANContentInformationSet(const struct ANContentInformation_ * pSrcValue, struct ANContentInformation_ * pDstValue);

struct ANContentDiaryInformation_
{
	NUInt segmentIdentifier;
	HNArray hTrackChannelList;
	NULong relativeStartTime;
	NULong relativeEndTime;
	HNString hComment;
	NBool hasTaggedDate;
	NDateTime_ taggedDate;
	NBool hasTaggedStartTime;
	NDateTime_ taggedStartTime;
	NBool hasTaggedEndTime;
	NDateTime_ taggedEndTime;
	NBool hasOriginalRecordingDate;
	NDateTime_ originalRecordingDate;
	NBool hasSegmentRecordingStartTime;
	NDateTime_ segmentRecordingStartTime;
	NBool hasSegmentRecordingEndTime;
	NDateTime_ segmentRecordingEndTime;
	HNString hTimeSourceDescription;
	HNString hTimingComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANContentDiaryInformation_ ANContentDiaryInformation;
#endif

N_DECLARE_TYPE(ANContentDiaryInformation)

NResult N_API ANContentDiaryInformationCreateN(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, HNString hComment, 
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, HNString hTimeSourceDescription, HNString hTimingComment, struct ANContentDiaryInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANContentDiaryInformationCreateA(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NAChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NAChar * szTimeSourceDescription, const NAChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANContentDiaryInformationCreateW(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NWChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NWChar * szTimeSourceDescription, const NWChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANContentDiaryInformationCreate(NUInt segmentIdentifier, HNArray hTrackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NChar * szTimeSourceDescription, const NChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#define ANContentDiaryInformationCreate N_FUNC_AW(ANAudioRecordingDeviceCreate)

NResult N_API ANContentDiaryInformationCreateExN(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, HNString hComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, HNString hTimeSourceDescription, HNString hTimingComment, struct ANContentDiaryInformation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANContentDiaryInformationCreateExA(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NAChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NAChar * szTimeSourceDescription, const NAChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANContentDiaryInformationCreateExW(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NWChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NWChar * szTimeSourceDescription, const NWChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANContentDiaryInformationCreateEx(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NChar * szComment,
	const NDateTime_ * pTaggedDate, const NDateTime_ * pTaggedStartTime, const NDateTime_ * pTaggedEndTime, const NDateTime_ * pOriginalRecordingDate,
	const NDateTime_ * pSegmentRecordingStartTime, const NDateTime_ * pSegmentRecordingEndTime, const NChar * szTimeSourceDescription, const NChar * szTimingComment, struct ANContentDiaryInformation_ * pValue);
#endif
#define ANContentDiaryInformationCreateEx N_FUNC_AW(ANAudioRecordingDeviceCreateEx)

NResult N_API ANContentDiaryInformationDispose(struct ANContentDiaryInformation_ * pValue);
NResult N_API ANContentDiaryInformationCopy(const struct ANContentDiaryInformation_ * pSrcValue, struct ANContentDiaryInformation_ * pDstValue);
NResult N_API ANContentDiaryInformationSet(const struct ANContentDiaryInformation_ * pSrcValue, struct ANContentDiaryInformation_ * pDstValue);

struct ANSegmentGeographicLocation_
{
	HNArray hSegmentIdentifierList;
	HNString hCellPhoneTowerCode;
	NBool hasLatitude;
	NDouble latitudeDegree;
	NDouble latitudeMinute;
	NDouble latitudeSecond;
	NBool hasLongitude;
	NDouble longitudeDegree;
	NDouble longitudeMinute;
	NDouble longitudeSecond;
	NBool hasElevation;
	NDouble elevation;
	ANGeographicCoordinateSystem geodeticDatumCode;
	HNString hOtherGeodeticDatumCode;
	HNString hUtmZone;
	NInt utmEasting;
	NInt utmNorthing;
	HNString hReferenceText;
	HNString hOtherSystemId;
	HNString hOtherSystemValue;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentGeographicLocation_ ANSegmentGeographicLocation;
#endif

N_DECLARE_TYPE(ANSegmentGeographicLocation)

NResult N_API ANSegmentGeographicLocationCreateN(HNArray hSegmentIdentifierList, HNString hCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	HNString szOtherGeodeticDatumCode, HNString hUtmZone, NInt utmEasting, NInt utmNorthing, HNString hReferenceText, HNString hOtherSystemId, HNString hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentGeographicLocationCreateA(HNArray hSegmentIdentifierList, const NAChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NAChar * szOtherGeodeticDatumCode, const NAChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NAChar * szReferenceText, const NAChar * szOtherSystemId, const NAChar * hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentGeographicLocationCreateW(HNArray hSegmentIdentifierList, const NWChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NWChar * szOtherGeodeticDatumCode, const NWChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NWChar * szReferenceText, const NWChar * szOtherSystemId, const NWChar * hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentGeographicLocationCreate(HNArray hSegmentIdentifierList, const NChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NChar * hOtherGeodeticDatumCode, const NChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NChar * szReferenceText, const NChar * szOtherSystemId, const NChar * hOtherSystemValue, ANSegmentGeographicLocation * pValue);
#endif
#define ANSegmentGeographicLocationCreate N_FUNC_AW(ANSegmentGeographicLocationCreate)

NResult N_API ANSegmentGeographicLocationCreateExN(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, HNString hCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	HNString szOtherGeodeticDatumCode, HNString hUtmZone, NInt utmEasting, NInt utmNorthing, HNString hReferenceText, HNString hOtherSystemId, HNString hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentGeographicLocationCreateExA(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NAChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NAChar * szOtherGeodeticDatumCode, const NAChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NAChar * szReferenceText, const NAChar * szOtherSystemId, const NAChar * hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentGeographicLocationCreateExW(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NWChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NWChar * szOtherGeodeticDatumCode, const NWChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NWChar * szReferenceText, const NWChar * szOtherSystemId, const NWChar * hOtherSystemValue, struct ANSegmentGeographicLocation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentGeographicLocationCreateEx(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NChar * szCellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute,
	NDouble latitudeSecond, const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
	const NChar * hOtherGeodeticDatumCode, const NChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NChar * szReferenceText, const NChar * szOtherSystemId, const NChar * hOtherSystemValue, ANSegmentGeographicLocation * pValue);
#endif
#define ANSegmentGeographicLocationCreateEx N_FUNC_AW(ANSegmentGeographicLocationCreateEx)

NResult N_API ANSegmentGeographicLocationDispose(struct ANSegmentGeographicLocation_ * pValue);
NResult N_API ANSegmentGeographicLocationCopy(const struct ANSegmentGeographicLocation_ * pSrcValue, struct ANSegmentGeographicLocation_ * pDstValue);
NResult N_API ANSegmentGeographicLocationSet(const struct ANSegmentGeographicLocation_ * pSrcValue, struct ANSegmentGeographicLocation_ * pDstValue);

struct ANSegmentQualityBlock_
{
	HNArray hSegmentIdentifierList;
	NByte Score;
	NUShort AlgorithmVendorId;
	NUShort AlgorithmProductId;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentQualityBlock_ ANSegmentQualityBlock;
#endif

N_DECLARE_TYPE(ANSegmentQualityBlock)

NResult N_API ANSegmentQualityBlockCreateN(HNArray hSegmentIdentifierList, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, HNString hComment, struct ANSegmentQualityBlock_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentQualityBlockCreateA(HNArray hSegmentIdentifierList, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NAChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentQualityBlockCreateW(HNArray hSegmentIdentifierList, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NWChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentQualityBlockCreate(HNArray hSegmentIdentifierList, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#define ANSegmentQualityBlockCreate N_FUNC_AW(ANAudioRecordingDeviceCreate)

NResult N_API ANSegmentQualityBlockCreateExN(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, HNString hComment, struct ANSegmentQualityBlock_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentQualityBlockCreateExA(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NAChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentQualityBlockCreateExW(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NWChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentQualityBlockCreateEx(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NChar * szComment, struct ANSegmentQualityBlock_ * pValue);
#endif
#define ANSegmentQualityBlockCreateEx N_FUNC_AW(ANAudioRecordingDeviceCreateEx)

NResult N_API ANSegmentQualityBlockDispose(struct ANSegmentQualityBlock_ * pValue);
NResult N_API ANSegmentQualityBlockCopy(const struct ANSegmentQualityBlock_ * pSrcValue, struct ANSegmentQualityBlock_ * pDstValue);
NResult N_API ANSegmentQualityBlockSet(const struct ANSegmentQualityBlock_ * pSrcValue, struct ANSegmentQualityBlock_ * pDstValue);

struct ANSegmentProcessingPriority_
{
	HNArray hSegmentIdentifierList;
	NByte priority;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentProcessingPriority_ ANSegmentProcessingPriority;
#endif

N_DECLARE_TYPE(ANSegmentProcessingPriority)

NResult N_API ANSegmentProcessingPriorityCreate(HNArray hSegmentIdentifierList, NByte priority, struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANSegmentProcessingPriorityCreateEx(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte priority, struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANSegmentProcessingPriorityDispose(struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANSegmentProcessingPriorityCopy(const struct ANSegmentProcessingPriority_ * pSrcValue, struct ANSegmentProcessingPriority_ * pDstValue);
NResult N_API ANSegmentProcessingPrioritySet(const struct ANSegmentProcessingPriority_ * pSrcValue, struct ANSegmentProcessingPriority_ * pDstValue);

struct ANSegmentContentDescription_
{
	HNArray hSegmentIdentifierList;
	HNString hTranscriptText;
	HNString hTranscriptLanguage;
	HNString hPhoneticTranscriptText;
	HNString hPhoneticTranscriptConvention;
	HNString hTranslationText;
	HNString hTranslationLanguage;
	HNString hContentComment;
	HNString hTranscriptAuthorityComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentContentDescription_ ANSegmentContentDescription;
#endif

N_DECLARE_TYPE(ANSegmentContentDescription)

NResult N_API ANSegmentContentDescriptionCreateN(HNArray hSegmentIdentifierList, HNString hTranscriptText, HNString hTranscriptLanguage, HNString hPhoneticTranscriptText, HNString hPhoneticTranscriptConvention,
	HNString hTranslationText, HNString hTranslationLanguage, HNString hContentComment, HNString hTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentContentDescriptionCreateA(HNArray hSegmentIdentifierList, const NAChar * szTranscriptText, const NAChar * szTranscriptLanguage, const NAChar * szPhoneticTranscriptText, const NAChar * szPhoneticTranscriptConvention,
	const NAChar * szTranslationText, const NAChar * szTranslationLanguage, const NAChar * szContentComment, const NAChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentContentDescriptionCreateW(HNArray hSegmentIdentifierList, const NWChar * szTranscriptText, const NWChar * szTranscriptLanguage, const NWChar * szPhoneticTranscriptText, const NWChar * szPhoneticTranscriptConvention,
	const NWChar * szTranslationText, const NWChar * szTranslationLanguage, const NWChar * szContentComment, const NWChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentContentDescriptionCreate(HNArray hSegmentIdentifierList, const NChar * szTranscriptText, const NChar * szTranscriptLanguage, const NChar * szPhoneticTranscriptText, const NChar * szPhoneticTranscriptConvention,
	const NChar * szTranslationText, const NChar * szTranslationLanguage, const NChar * szContentComment, const NChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#define ANSegmentContentDescriptionCreate N_FUNC_AW(ANSegmentContentDescriptionCreate)

NResult N_API ANSegmentContentDescriptionCreateExN(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, HNString hTranscriptText, HNString hTranscriptLanguage, HNString hPhoneticTranscriptText, HNString hPhoneticTranscriptConvention,
	HNString hTranslationText, HNString hTranslationLanguage, HNString hContentComment, HNString hTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentContentDescriptionCreateExA(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NAChar * szTranscriptText, const NAChar * szTranscriptLanguage, const NAChar * szPhoneticTranscriptText, const NAChar * szPhoneticTranscriptConvention,
	const NAChar * szTranslationText, const NAChar * szTranslationLanguage, const NAChar * szContentComment, const NAChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentContentDescriptionCreateExW(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NWChar * szTranscriptText, const NWChar * szTranscriptLanguage, const NWChar * szPhoneticTranscriptText, const NWChar * szPhoneticTranscriptConvention,
	const NWChar * szTranslationText, const NWChar * szTranslationLanguage, const NWChar * szContentComment, const NWChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentContentDescriptionCreate(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NChar * szTranscriptText, const NChar * szTranscriptLanguage, const NChar * szPhoneticTranscriptText, const NChar * szPhoneticTranscriptConvention,
	const NChar * szTranslationText, const NChar * szTranslationLanguage, const NChar * szContentComment, const NChar * szTranscriptAuthorityComment, struct ANSegmentContentDescription_ * pValue);
#endif
#define ANSegmentContentDescriptionCreateEx N_FUNC_AW(ANSegmentContentDescriptionCreateEx)

NResult N_API ANSegmentContentDescriptionDispose(struct ANSegmentContentDescription_ * pValue);
NResult N_API ANSegmentContentDescriptionCopy(const struct ANSegmentContentDescription_ * pSrcValue, struct ANSegmentContentDescription_ * pDstValue);
NResult N_API ANSegmentContentDescriptionSet(const struct ANSegmentContentDescription_ * pSrcValue, struct ANSegmentContentDescription_ * pDstValue);

typedef enum ANSpeechStyleDescription_
{
	anssdUnspecified = -1,
	anssdUnknown = 0,
	anssdPublicOratorySpeech = 1,
	anssdConversationTelephone = 2,
	anssdConversationFaceToFace = 3,
	anssdRead = 4,
	anssdPromptedRepeated = 5,
	anssdStorytellingPictureDescription = 6,
	anssdTaskInducedSpeech = 7,
	anssdInterview = 8,
	anssdRecitedMemorized = 9,
	anssdSpontaneousFree = 10,
	anssdVariable = 11,
	anssdOther = 12
} ANSpeechStyleDescription;

N_DECLARE_TYPE(ANSpeechStyleDescription)

typedef enum ANEmotionalState_
{
	anesUnspecified = -1,
	anesUnknown = 0,
	anesCalm = 1,
	anesHurried = 2,
	anesHappy = 3,
	anesAngry = 4,
	anesFearful = 5,
	anesAgitatedCombative = 6,
	anesDefensive = 7,
	anesCrying = 8,
	anesVariable = 9,
	anesOther = 10
} ANEmotionalState;

N_DECLARE_TYPE(ANEmotionalState)

typedef enum ANVocalStyle_
{
	anvsUnspecified = -1,
	anvsUnknown = 0,
	anvsSpoken = 1,
	anvsWhispered = 2,
	anvsSung = 3,
	anvsChanted = 4,
	anvsRapped = 5,
	anvsMantra = 6,
	anvsFalsettoHeadVoice = 7,
	anvsSpokenWithLaughter = 8,
	anvsMegaphonePublicAddressSystem = 9,
	anvsShoutingYelling = 10,
	anvsOther = 11
} ANVocalStyle;

N_DECLARE_TYPE(ANVocalStyle)

typedef enum ANRecordingAwareness_
{
	anraUnspecified = -1,
	anraUnknown = 0,
	anraAware = 1,
	anraUnaware = 2
} ANRecordingAwareness;

N_DECLARE_TYPE(ANRecordingAwareness)

struct ANSegmentSpeakerCharacteristics_
{
	HNArray hSegmentIdentifierList;
	HNArray hSpeakerList;
	HNArray hType2RecordReferenceList;
	NSByte impairmentLevel;
	HNString hSpokenLanguage;
	NSByte languageProficiency;
	ANSpeechStyleDescription speechStyle;
	NSByte intelligibilityScale;
	NSByte familiarityDegree;
	HNString hHealthComment;
	ANEmotionalState emotionalState;
	NSByte vocalEffortScale;
	ANVocalStyle vocalStyle;
	ANRecordingAwareness recordingAwareness;
	HNString hScriptText;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentSpeakerCharacteristics_ ANSegmentSpeakerCharacteristics;
#endif

N_DECLARE_TYPE(ANSegmentSpeakerCharacteristics)

NResult N_API ANSegmentSpeakerCharacteristicsCreateN(HNArray hSegmentIdentifierList, HNArray hSpeakerList, HNArray hType2RecordReferenceList, NSByte impairmentLevel, HNString hSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale,
	NSByte familiarityDegree, HNString hHealthComment, ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, HNString hScriptText, HNString hComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentSpeakerCharacteristicsCreateA(HNArray hSegmentIdentifierList, HNArray hSpeakerList, HNArray hType2RecordReferenceList, NSByte impairmentLevel, const NAChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale,
	NSByte familiarityDegree, const NAChar * szhHealthComment, ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NAChar * szScriptText, const NAChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentSpeakerCharacteristicsCreateW(HNArray hSegmentIdentifierList, HNArray hSpeakerList, HNArray hType2RecordReferenceList, NSByte impairmentLevel, const NWChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale,
	NSByte familiarityDegree, const NWChar * szhHealthComment, ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NWChar * szScriptText, const NWChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentSpeakerCharacteristicsCreate(HNArray hSegmentIdentifierList, HNArray hSpeakerList, HNArray hType2RecordReferenceList, NSByte impairmentLevel, const NChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale,
	NSByte familiarityDegree, const NChar * szhHealthComment, ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NChar * szScriptText, const NChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#define ANSegmentSpeakerCharacteristicsCreate N_FUNC_AW(ANSegmentSpeakerCharacteristicsCreate)

NResult N_API ANSegmentSpeakerCharacteristicsCreateExN(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NUShort * arSpeakerList, NInt speakerListLength, const NInt * arType2RecordReferenceList, NInt type2RecordReferenceListLength,
	NSByte impairmentLevel, HNString hSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, HNString hHealthComment, ANEmotionalState emotionalState,
	NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, HNString hScriptText, HNString hComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentSpeakerCharacteristicsCreateExA(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NUShort * arSpeakerList, NInt speakerListLength, const NInt * arType2RecordReferenceList, NInt type2RecordReferenceListLength,
	NSByte impairmentLevel, const NAChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, const NAChar * szhHealthComment,
	ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NAChar * szScriptText, const NAChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentSpeakerCharacteristicsCreateExW(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NUShort * arSpeakerList, NInt speakerListLength, const NInt * arType2RecordReferenceList, NInt type2RecordReferenceListLength,
	NSByte impairmentLevel, const NWChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, const NWChar * szhHealthComment,
	ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NWChar * szScriptText, const NWChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentSpeakerCharacteristicsCreateEx(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NUShort * arSpeakerList, NInt speakerListLength, const NInt * arType2RecordReferenceList, NInt type2RecordReferenceListLength,
	NSByte impairmentLevel, const NChar * szSpokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, const NChar * szhHealthComment, 
	ANEmotionalState emotionalState, NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness subjectRecordingAwareness, const NChar * szScriptText, const NChar * szComment, struct ANSegmentSpeakerCharacteristics_ * pValue);
#endif
#define ANSegmentSpeakerCharacteristicsCreateEx N_FUNC_AW(ANSegmentSpeakerCharacteristicsCreateEx)

NResult N_API ANSegmentSpeakerCharacteristicsDispose(struct ANSegmentSpeakerCharacteristics_ * pValue);
NResult N_API ANSegmentSpeakerCharacteristicsCopy(const struct ANSegmentSpeakerCharacteristics_ * pSrcValue, struct ANSegmentSpeakerCharacteristics_ * pDstValue);
NResult N_API ANSegmentSpeakerCharacteristicsSet(const struct ANSegmentSpeakerCharacteristics_ * pSrcValue, struct ANSegmentSpeakerCharacteristics_ * pDstValue);

typedef enum ANAudioCaptureDevice_
{
	anacdUnspecified = -1,
	anacdUnknown = 0,
	anacdArray = 1,
	anacdMultipleStyleMicrophones = 2,
	anacdEarbud = 3,
	anacdBodyWire = 4,
	anacdMicrophone = 5,
	anacdHandset = 6,
	anacdHeadset = 7,
	anacdSpeakerPhone = 8,
	anacdLapelMicrophone = 9,
	anacdOther = 10
} ANAudioCaptureDevice;

N_DECLARE_TYPE(ANAudioCaptureDevice)

typedef enum ANMicrophoneType_
{
	anmtUnspecified = -1,
	anmtUnknown = 0,
	anmtCarbon = 1,
	anmtElectret = 2,
	anmtDynamic = 3,
	anmtOther = 4
} ANMicrophoneType;

N_DECLARE_TYPE(ANMicrophoneType)

struct ANSegmentChannel_
{
	HNArray hSegmentIdentifierList;
	ANAudioCaptureDevice audioCaptureDevice;
	ANMicrophoneType microphoneType;
	HNString hCaptureEnvironmentDescription;
	NInt transducerDistance;
	ANAcquisitionSourceType acquisitionSourceType;
	HNString hVoiceModificationDescription;
	HNString hComment;
};
#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
typedef struct ANSegmentChannel_ ANSegmentChannel;
#endif

N_DECLARE_TYPE(ANSegmentChannel)

NResult N_API ANSegmentChannelCreateN(HNArray hSegmentIdentifierList, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, HNString hCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType, 
	HNString hVoiceModificationDescription, HNString hComment, struct ANSegmentChannel_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentChannelCreateA(HNArray hSegmentIdentifierList, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NAChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NAChar * szVoiceModificationDescription, const NAChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentChannelCreateW(HNArray hSegmentIdentifierList, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NWChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NWChar * szVoiceModificationDescription, const NWChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentChannelCreate(HNArray hSegmentIdentifierList, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NChar * szVoiceModificationDescription, const NChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#define ANSegmentChannelCreate N_FUNC_AW(ANSegmentChannelCreate)

NResult N_API ANSegmentChannelCreateExN(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, HNString hCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	HNString hVoiceModificationDescription, HNString hComment, struct ANSegmentChannel_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSegmentChannelCreateExA(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NAChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NAChar * szVoiceModificationDescription, const NAChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentChannelCreateExW(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NWChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NWChar * szVoiceModificationDescription, const NWChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentChannelCreateEx(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NChar * szCaptureEnvironmentDescription, NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType,
	const NChar * szVoiceModificationDescription, const NChar * szComment, struct ANSegmentChannel_ * pValue);
#endif
#define ANSegmentChannelCreateEx N_FUNC_AW(ANSegmentChannelCreateEx)

NResult N_API ANSegmentChannelDispose(struct ANSegmentChannel_ * pValue);
NResult N_API ANSegmentChannelCopy(const struct ANSegmentChannel_ * pSrcValue, struct ANSegmentChannel_ * pDstValue);
NResult N_API ANSegmentChannelSet(const struct ANSegmentChannel_ * pSrcValue, struct ANSegmentChannel_ * pDstValue);

NResult N_API ANType11RecordToNSoundBuffer(HANType11Record hRecord, NUInt flags, HNSoundBuffer * phSoundBuffer);

NResult N_API ANType11RecordGetAudioObjectDescriptor(HANType11Record hRecord, ANAudioObjectDescriptor * pValue);
NResult N_API ANType11RecordSetAudioObjectDescriptor(HANType11Record hRecord, ANAudioObjectDescriptor value);
NResult N_API ANType11RecordGetSourceOrganization(HANType11Record hRecord, struct ANSourceOrganization_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetSourceOrganization(HANType11Record hRecord, const struct ANSourceOrganization_ * pValue);
NResult N_API ANType11RecordGetVoiceRecordingContent(HANType11Record hRecord, struct ANVoiceRecordingContent_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetVoiceRecordingContent(HANType11Record hRecord, const struct ANVoiceRecordingContent_ * pValue);
NResult N_API ANType11RecordGetAudioRecordingDevice(HANType11Record hRecord, struct ANAudioRecordingDevice_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetAudioRecordingDevice(HANType11Record hRecord, const struct ANAudioRecordingDevice_ * pValue);
NResult N_API ANType11RecordGetAcquisitionSource(HANType11Record hRecord, struct ANAcquisitionSource_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetAcquisitionSource(HANType11Record hRecord, const struct ANAcquisitionSource_ * pValue);
NResult N_API ANType11RecordGetRecordCreationDate(HANType11Record hRecord, NDateTime_ * pValue);
NResult N_API ANType11RecordSetRecordCreationDate(HANType11Record hRecord, NDateTime_ value);
NResult N_API ANType11RecordGetRecordingDuration(HANType11Record hRecord, struct ANRecordingDuration_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetRecordingDuration(HANType11Record hRecord, const struct ANRecordingDuration_ * pValue);
NResult N_API ANType11RecordGetPhysicalMediaObject(HANType11Record hRecord, struct ANPhysicalMediaObject_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetPhysicalMediaObject(HANType11Record hRecord, const struct ANPhysicalMediaObject_ * pValue);
NResult N_API ANType11RecordGetContainer(HANType11Record hRecord, struct ANContainer_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetContainer(HANType11Record hRecord, const struct ANContainer_ * pValue);
NResult N_API ANType11RecordGetCodec(HANType11Record hRecord, struct ANCodec_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetCodec(HANType11Record hRecord, const struct ANCodec_ * pValue);

NResult N_API ANType11RecordGetRedaction(HANType11Record hRecord, struct ANAudioInformation_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetRedaction(HANType11Record hRecord, const struct ANAudioInformation_ * pValue);

NResult N_API ANType11RecordGetRedactionDiaryCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetRedactionDiary(HANType11Record hRecord, NInt index, struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordGetRedactionDiaryCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetRedactionDiaryCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetRedactionDiaries(HANType11Record hRecord, struct ANDiaryInformation_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetRedactionDiary(HANType11Record hRecord, NInt index, const struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordAddRedactionDiary(HANType11Record hRecord, const struct ANDiaryInformation_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertRedactionDiary(HANType11Record hRecord, NInt index, const struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordRemoveRedactionDiaryAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearRedactionDiaries(HANType11Record hRecord);

NResult N_API ANType11RecordGetDiscontinuity(HANType11Record hRecord, struct ANAudioInformation_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetDiscontinuity(HANType11Record hRecord, const struct ANAudioInformation_ * pValue);

NResult N_API ANType11RecordGetDiscontinuityDiaryCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetDiscontinuityDiary(HANType11Record hRecord, NInt index, struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordGetDiscontinuityDiaryCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetDiscontinuityDiaryCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetDiscontinuityDiaries(HANType11Record hRecord, struct ANDiaryInformation_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetDiscontinuityDiary(HANType11Record hRecord, NInt index, const struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordAddDiscontinuityDiary(HANType11Record hRecord, const struct ANDiaryInformation_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertDiscontinuityDiary(HANType11Record hRecord, NInt index, const struct ANDiaryInformation_ * pValue);
NResult N_API ANType11RecordRemoveDiscontinuityDiaryAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearDiscontinuityDiaries(HANType11Record hRecord);

NResult N_API ANType11RecordGetVocalContent(HANType11Record hRecord, struct ANContentInformation_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetVocalContent(HANType11Record hRecord, const struct ANContentInformation_ * pValue);

NResult N_API ANType11RecordGetVocalContentDiaryCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetVocalContentDiary(HANType11Record hRecord, NInt index, struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordGetVocalContentDiaryCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetVocalContentDiaryCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetVocalContentDiaries(HANType11Record hRecord, struct ANContentDiaryInformation_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetVocalContentDiary(HANType11Record hRecord, NInt index, const struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordAddVocalContentDiary(HANType11Record hRecord, const struct ANContentDiaryInformation_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertVocalContentDiary(HANType11Record hRecord, NInt index, const struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordRemoveVocalContentDiaryAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearVocalContentDiaries(HANType11Record hRecord);

NResult N_API ANType11RecordGetOtherContent(HANType11Record hRecord, struct ANContentInformation_ * pValue, NBool * pHasValue);
NResult N_API ANType11RecordSetOtherContent(HANType11Record hRecord, const struct ANContentInformation_ * pValue);

NResult N_API ANType11RecordGetOtherContentDiaryCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetOtherContentDiary(HANType11Record hRecord, NInt index, struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordGetOtherContentDiaryCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetOtherContentDiaryCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetOtherContentDiaries(HANType11Record hRecord, struct ANContentDiaryInformation_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetOtherContentDiary(HANType11Record hRecord, NInt index, const struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordAddOtherContentDiary(HANType11Record hRecord, const struct ANContentDiaryInformation_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertOtherContentDiary(HANType11Record hRecord, NInt index, const struct ANContentDiaryInformation_ * pValue);
NResult N_API ANType11RecordRemoveOtherContentDiaryAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearOtherContentDiaries(HANType11Record hRecord);

NResult N_API ANType11RecordGetSegmentGeographicLocationCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentGeographicLocation(HANType11Record hRecord, NInt index, struct ANSegmentGeographicLocation_ * pValue);
NResult N_API ANType11RecordGetSegmentGeographicLocationCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentGeographicLocationCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentGeographicLocations(HANType11Record hRecord, struct ANSegmentGeographicLocation_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentGeographicLocation(HANType11Record hRecord, NInt index, const struct ANSegmentGeographicLocation_ * pValue);
NResult N_API ANType11RecordAddSegmentGeographicLocation(HANType11Record hRecord, const struct ANSegmentGeographicLocation_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentGeographicLocation(HANType11Record hRecord, NInt index, const struct ANSegmentGeographicLocation_ * pValue);
NResult N_API ANType11RecordRemoveSegmentGeographicLocationAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentGeographicLocations(HANType11Record hRecord);

NResult N_API ANType11RecordGetSegmentQualityBlockCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentQualityBlock(HANType11Record hRecord, NInt index, struct ANSegmentQualityBlock_ * pValue);
NResult N_API ANType11RecordGetSegmentQualityBlockCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentQualityBlockCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentQualityBlocks(HANType11Record hRecord, struct ANSegmentQualityBlock_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentQualityBlock(HANType11Record hRecord, NInt index, const struct ANSegmentQualityBlock_ * pValue);
NResult N_API ANType11RecordAddSegmentQualityBlock(HANType11Record hRecord, const struct ANSegmentQualityBlock_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentQualityBlock(HANType11Record hRecord, NInt index, const struct ANSegmentQualityBlock_ * pValue);
NResult N_API ANType11RecordRemoveSegmentQualityBlockAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentQualityBlocks(HANType11Record hRecord);

NResult N_API ANType11RecordGetVocalCollisionIdentifiers(HANType11Record hRecord, HNArray * phValue);
NResult N_API ANType11RecordSetVocalCollisionIdentifiers(HANType11Record hRecord, HNArray harValue);
NResult N_API ANType11RecordSetVocalCollisionIdentifiersEx(HANType11Record hRecord, const NUInt * arValues, NInt valuesLength);

NResult N_API ANType11RecordGetSegmentProcessingPriorityCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentProcessingPriority(HANType11Record hRecord, NInt index, struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANType11RecordGetSegmentProcessingPriorityCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentProcessingPriorityCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentProcessingPriorities(HANType11Record hRecord, struct ANSegmentProcessingPriority_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentProcessingPriority(HANType11Record hRecord, NInt index, const struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANType11RecordAddSegmentProcessingPriority(HANType11Record hRecord, const struct ANSegmentProcessingPriority_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentProcessingPriority(HANType11Record hRecord, NInt index, const struct ANSegmentProcessingPriority_ * pValue);
NResult N_API ANType11RecordRemoveSegmentProcessingPriorityAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentProcessingPriorities(HANType11Record hRecord);

NResult N_API ANType11RecordGetSegmentContentDescriptionCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentContentDescription(HANType11Record hRecord, NInt index, struct ANSegmentContentDescription_ * pValue);
NResult N_API ANType11RecordGetSegmentContentDescriptionCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentContentDescriptionCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentContentDescriptions(HANType11Record hRecord, struct ANSegmentContentDescription_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentContentDescription(HANType11Record hRecord, NInt index, const struct ANSegmentContentDescription_ * pValue);
NResult N_API ANType11RecordAddSegmentContentDescription(HANType11Record hRecord, const struct ANSegmentContentDescription_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentContentDescription(HANType11Record hRecord, NInt index, const struct ANSegmentContentDescription_ * pValue);
NResult N_API ANType11RecordRemoveSegmentContentDescriptionAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentContentDescriptions(HANType11Record hRecord);

NResult N_API ANType11RecordGetSegmentSpeakerCharacteristicsCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentSpeakerCharacteristics(HANType11Record hRecord, NInt index, struct ANSegmentSpeakerCharacteristics_ * pValue);
NResult N_API ANType11RecordGetSegmentSpeakerCharacteristicsCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentSpeakerCharacteristicsCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentSpeakersCharacteristics(HANType11Record hRecord, struct ANSegmentSpeakerCharacteristics_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentSpeakerCharacteristics(HANType11Record hRecord, NInt index, const struct ANSegmentSpeakerCharacteristics_ * pValue);
NResult N_API ANType11RecordAddSegmentSpeakerCharacteristics(HANType11Record hRecord, const struct ANSegmentSpeakerCharacteristics_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentSpeakerCharacteristics(HANType11Record hRecord, NInt index, const struct ANSegmentSpeakerCharacteristics_ * pValue);
NResult N_API ANType11RecordRemoveSegmentSpeakerCharacteristicsAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentSpeakersCharacteristics(HANType11Record hRecord);

NResult N_API ANType11RecordGetSegmentChannelCount(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordGetSegmentChannel(HANType11Record hRecord, NInt index, struct ANSegmentChannel_ * pValue);
NResult N_API ANType11RecordGetSegmentChannelCapacity(HANType11Record hRecord, NInt * pValue);
NResult N_API ANType11RecordSetSegmentChannelCapacity(HANType11Record hRecord, NInt value);
NResult N_API ANType11RecordGetSegmentChannels(HANType11Record hRecord, struct ANSegmentChannel_ * * parValues, NInt * pValueCount);
NResult N_API ANType11RecordSetSegmentChannel(HANType11Record hRecord, NInt index, const struct ANSegmentChannel_ * pValue);
NResult N_API ANType11RecordAddSegmentChannel(HANType11Record hRecord, const struct ANSegmentChannel_ * pValue, NInt * pIndex);
NResult N_API ANType11RecordInsertSegmentChannel(HANType11Record hRecord, NInt index, const struct ANSegmentChannel_ * pValue);
NResult N_API ANType11RecordRemoveSegmentChannelAt(HANType11Record hRecord, NInt index);
NResult N_API ANType11RecordClearSegmentChannels(HANType11Record hRecord);

NResult N_API ANType11RecordGetCommentN(HANType11Record hRecord, HNString * phValue);
NResult N_API ANType11RecordSetCommentN(HANType11Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType11RecordSetCommentA(HANType11Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType11RecordSetCommentW(HANType11Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType11RecordSetComment(HANType11Record hRecord, const NChar * szValue);
#endif
#define ANType11RecordSetComment N_FUNC_AW(ANType11RecordSetComment)

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_11_RECORD_H_INCLUDED
