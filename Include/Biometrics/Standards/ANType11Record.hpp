#ifndef AN_TYPE_11_RECORD_HPP_INCLUDED
#define AN_TYPE_11_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType11Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAudioObjectDescriptor)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSourceOrganizationType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAssignedVoiceIndicator)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSpeakerPluralityCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANContainerCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANCodecCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDiarizationIndicator)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSpeechStyleDescription)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANEmotionalState)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANVocalStyle)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANRecordingAwareness)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAudioCaptureDevice)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANMicrophoneType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANProcessingIndicator)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_11_RECORD_FIELD_LEN
#undef AN_TYPE_11_RECORD_FIELD_IDC

#undef AN_TYPE_11_RECORD_FIELD_AOD

#undef AN_TYPE_11_RECORD_FIELD_SRC

#undef AN_TYPE_11_RECORD_FIELD_VRSO
#undef AN_TYPE_11_RECORD_FIELD_VRC
#undef AN_TYPE_11_RECORD_FIELD_AREC
#undef AN_TYPE_11_RECORD_FIELD_AQS
#undef AN_TYPE_11_RECORD_FIELD_RCD
#undef AN_TYPE_11_RECORD_FIELD_VRD
#undef AN_TYPE_11_RECORD_FIELD_TRD
#undef AN_TYPE_11_RECORD_FIELD_PMO
#undef AN_TYPE_11_RECORD_FIELD_CONT
#undef AN_TYPE_11_RECORD_FIELD_CDC
#undef AN_TYPE_11_RECORD_FIELD_RED
#undef AN_TYPE_11_RECORD_FIELD_RDD
#undef AN_TYPE_11_RECORD_FIELD_DIS
#undef AN_TYPE_11_RECORD_FIELD_DSD
#undef AN_TYPE_11_RECORD_FIELD_VOC
#undef AN_TYPE_11_RECORD_FIELD_VCD
#undef AN_TYPE_11_RECORD_FIELD_OCON
#undef AN_TYPE_11_RECORD_FIELD_OCD
#undef AN_TYPE_11_RECORD_FIELD_SGEO
#undef AN_TYPE_11_RECORD_FIELD_SQV
#undef AN_TYPE_11_RECORD_FIELD_VCI
#undef AN_TYPE_11_RECORD_FIELD_PPY
#undef AN_TYPE_11_RECORD_FIELD_VSCD
#undef AN_TYPE_11_RECORD_FIELD_SCC
#undef AN_TYPE_11_RECORD_FIELD_SCH
#undef AN_TYPE_11_RECORD_FIELD_COM

#undef AN_TYPE_11_RECORD_FIELD_ANN
#undef AN_TYPE_11_RECORD_FIELD_SAN
#undef AN_TYPE_11_RECORD_FIELD_EFR
#undef AN_TYPE_11_RECORD_FIELD_ASC
#undef AN_TYPE_11_RECORD_FIELD_HAS
#undef AN_TYPE_11_RECORD_FIELD_SOR

#undef AN_TYPE_11_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_11_RECORD_FIELD_UDF

#undef AN_TYPE_11_RECORD_FIELD_DATA

#undef AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_NAME_LENGTH
#undef AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_CONTACT_LENGTH
#undef AN_TYPE_11_RECORD_MIN_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH
#undef AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH

#undef AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MAKE_LENGTH
#undef AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MODEL_LENGTH
#undef AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_SERIAL_NUMBER_LENGTH

#undef AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_TIME
#undef AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_COMPRESSED_BYTES
#undef AN_TYPE_11_RECORD_MAX_RECORDING_DIGITAL_SAMPLES_BYTES

#undef AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_DESCRIPTION_LENGTH
#undef AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_RECORDING_SPEED_LENGTH

#undef AN_TYPE_11_RECORD_MAX_CONTAINER_EXTERNAL_REFERENCE_LENGTH

#undef AN_TYPE_11_RECORD_MAX_CODEC_SAMPLING_RATE_NUMBER
#undef AN_TYPE_11_RECORD_MAX_CODEC_BIT_DEPTH
#undef AN_TYPE_11_RECORD_MAX_CODEC_NUMERIC_FORMAT_LENGTH
#undef AN_TYPE_11_RECORD_MAX_CODEC_EXTERNAL_REFERENCE_LENGTH

#undef AN_TYPE_11_RECORD_MAX_AUTHORITY_ORGANIZATION_LENGTH

#undef AN_TYPE_11_RECORD_MAX_TRACK_AND_CHANNEL

#undef AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_IDENTIFIER

#undef AN_TYPE_11_RECORD_MAX_REDACTION_DIARY_COUNT
#undef AN_TYPE_11_RECORD_MAX_DISCONTINUITY_DIARY_COUNT
#undef AN_TYPE_11_RECORD_MAX_VOCAL_CONTENT_DIARY_COUNT
#undef AN_TYPE_11_RECORD_MAX_OTHER_CONTENT_DIARY_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_GEOGRAPHIC_LOCATION_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_QUALITY_BLOCK_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_DESCRIPTION_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_SPEAKER_CHARACTERISTICS_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_COUNT

#undef AN_TYPE_11_RECORD_MAX_CONTENT_DIARY_TIME_SOURCE_DESCRIPTION_LENGTH

#undef AN_TYPE_11_RECORD_MAX_SGEO_CELL_PHONE_TOWER_CODE_LENGTH

#undef AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_COUNT
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_VALUE

#undef AN_TYPE_11_RECORD_LANGUAGE_CODE_LENGTH
#undef AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_PHONETIC_TRANSCRIPT_CONVENTION_LENGTH
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_SPEAKER
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_TYPE_2_RECORD_REFERENCE
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_IMPAIRMENT_LEVEL
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_LANGUAGE_PROFICIENCY_SCALE
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_INTELLIGIBILITY_SCALE
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_FAMILIARITY_DEGREE
#undef AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_VOCAL_EFFORT_SCALE

#undef AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_TRANSDUCER_DISTANCE

const NInt AN_TYPE_11_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_11_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_11_RECORD_FIELD_AOD = 3;

const NInt AN_TYPE_11_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;

const NInt AN_TYPE_11_RECORD_FIELD_VRSO = 5;
const NInt AN_TYPE_11_RECORD_FIELD_VRC  = 6;
const NInt AN_TYPE_11_RECORD_FIELD_AREC = 7;
const NInt AN_TYPE_11_RECORD_FIELD_AQS  = 8;
const NInt AN_TYPE_11_RECORD_FIELD_RCD  = 9;
const NInt AN_TYPE_11_RECORD_FIELD_TRD = 11;
const NInt AN_TYPE_11_RECORD_FIELD_PMO = 12;
const NInt AN_TYPE_11_RECORD_FIELD_CONT = 13;
const NInt AN_TYPE_11_RECORD_FIELD_CDC = 14;
const NInt AN_TYPE_11_RECORD_FIELD_RED = 21;
const NInt AN_TYPE_11_RECORD_FIELD_RDD = 22;
const NInt AN_TYPE_11_RECORD_FIELD_DIS = 23;
const NInt AN_TYPE_11_RECORD_FIELD_DSD = 24;
const NInt AN_TYPE_11_RECORD_FIELD_VOC = 25;
const NInt AN_TYPE_11_RECORD_FIELD_VCD = 26;
const NInt AN_TYPE_11_RECORD_FIELD_OCON = 27;
const NInt AN_TYPE_11_RECORD_FIELD_OCD = 28;
const NInt AN_TYPE_11_RECORD_FIELD_SGEO = 32;
const NInt AN_TYPE_11_RECORD_FIELD_SQV = 33;
const NInt AN_TYPE_11_RECORD_FIELD_VCI = 34;
const NInt AN_TYPE_11_RECORD_FIELD_PPY = 35;
const NInt AN_TYPE_11_RECORD_FIELD_VSCD = 36;
const NInt AN_TYPE_11_RECORD_FIELD_SCC = 37;
const NInt AN_TYPE_11_RECORD_FIELD_SCH  = 38;
const NInt AN_TYPE_11_RECORD_FIELD_COM  = 51;

const NInt AN_TYPE_11_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;

const NInt AN_TYPE_11_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_11_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_11_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_11_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_11_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;

const NInt AN_TYPE_11_RECORD_FIELD_UDF_FROM = 100;
const NInt AN_TYPE_11_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_11_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_NAME_LENGTH = 400;
const NInt AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_CONTACT_LENGTH = 200;
const NInt AN_TYPE_11_RECORD_MIN_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH = 2;
const NInt AN_TYPE_11_RECORD_MAX_SOURCE_ORGANIZATION_COUNTRY_CODE_LENGTH = 3;

const NInt  AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MAKE_LENGTH = AN_RECORD_MAX_MAKE_LENGTH;
const NInt  AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_MODEL_LENGTH = AN_RECORD_MAX_MODEL_LENGTH;
const NInt  AN_TYPE_11_RECORD_MAX_RECORDING_DEVICE_SERIAL_NUMBER_LENGTH = AN_RECORD_MAX_SERIAL_NUMBER_LENGTH;

const NLong AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_TIME = 99999999999;
const NLong AN_TYPE_11_RECORD_MAX_RECORDING_DURATION_COMPRESSED_BYTES = 99999999999999;
const NLong AN_TYPE_11_RECORD_MAX_RECORDING_DIGITAL_SAMPLES_BYTES = 99999999999999;

const NInt AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_DESCRIPTION_LENGTH = 300;
const NInt AN_TYPE_11_RECORD_MAX_PHYSICAL_MEDIA_RECORDING_SPEED_LENGTH = 9;

const NInt AN_TYPE_11_RECORD_MAX_CONTAINER_EXTERNAL_REFERENCE_LENGTH = 80;

const NInt AN_TYPE_11_RECORD_MAX_CODEC_SAMPLING_RATE_NUMBER = 100000000;
const NInt AN_TYPE_11_RECORD_MAX_CODEC_BIT_DEPTH = 1024;
const NInt AN_TYPE_11_RECORD_MAX_CODEC_NUMERIC_FORMAT_LENGTH = 5;
const NInt AN_TYPE_11_RECORD_MAX_CODEC_EXTERNAL_REFERENCE_LENGTH = 80;

const NInt AN_TYPE_11_RECORD_MAX_AUTHORITY_ORGANIZATION_LENGTH = 300;

const NInt AN_TYPE_11_RECORD_MAX_TRACK_AND_CHANNEL = 9999;

const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT = 600000;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_IDENTIFIER = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;

const NInt AN_TYPE_11_RECORD_MAX_REDACTION_DIARY_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_DISCONTINUITY_DIARY_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_VOCAL_CONTENT_DIARY_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_OTHER_CONTENT_DIARY_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_GEOGRAPHIC_LOCATION_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;

const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_QUALITY_BLOCK_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_DESCRIPTION_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_SPEAKER_CHARACTERISTICS_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_COUNT = AN_TYPE_11_RECORD_MAX_SEGMENT_COUNT;

const NInt AN_TYPE_11_RECORD_MAX_CONTENT_DIARY_TIME_SOURCE_DESCRIPTION_LENGTH = 300;

const NInt AN_TYPE_11_RECORD_MAX_SGEO_CELL_PHONE_TOWER_CODE_LENGTH = 100;

const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_COUNT = 9;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_PROCESSING_PRIORITY_VALUE = 9;

const NInt AN_TYPE_11_RECORD_LANGUAGE_CODE_LENGTH = 3;
const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_CONTENT_PHONETIC_TRANSCRIPT_CONVENTION_LENGTH = 100;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_SPEAKER = 9999;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_TYPE_2_RECORD_REFERENCE = AN_RECORD_MAX_IDC_V5;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_IMPAIRMENT_LEVEL = 5;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_LANGUAGE_PROFICIENCY_SCALE = 9;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_INTELLIGIBILITY_SCALE = 9;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_FAMILIARITY_DEGREE = 5;
const NInt AN_TYPE_11_RECORD_MAX_SPEAKER_CHARACTERISTICS_VOCAL_EFFORT_SCALE = 5;

const NInt AN_TYPE_11_RECORD_MAX_SEGMENT_CHANNEL_TRANSDUCER_DISTANCE = 99999;

class ANSourceOrganization : public ANSourceOrganization_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSourceOrganization)

public:
	ANSourceOrganization(ANSourceOrganizationType organizationType, const NStringWrapper & organizationName, const NStringWrapper & pointOfContact, const NStringWrapper & organizationCountryCode)
	{
		NCheck(ANSourceOrganizationCreateN(organizationType, organizationName.GetHandle(), pointOfContact.GetHandle(), organizationCountryCode.GetHandle(), this));
	}

	NString GetOrganizationName() const
	{
		return NString(hOrganizationName, false);
	}

	void SetOrganizationName(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hOrganizationName));
	}

	NString GetPointOfContact() const
	{
		return NString(hPointOfContact, false);
	}

	void SetPointOfContact(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hPointOfContact));
	}

	NString GetSourceCountryCode() const
	{
		return NString(hSourceCountryCode, false);
	}

	void SetSourceCountryCode(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hSourceCountryCode));
	}
};

class ANVoiceRecordingContent : public ANVoiceRecordingContent_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANVoiceRecordingContent)

public:
	ANVoiceRecordingContent(ANAssignedVoiceIndicator assignedVoiceIndicator, ANSpeakerPluralityCode speakerPlurality, const NStringWrapper & comment)
	{
		NCheck(ANVoiceRecordingContentCreateN(assignedVoiceIndicator, speakerPlurality, comment.GetHandle(), this));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANAudioRecordingDevice : public ANAudioRecordingDevice_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANAudioRecordingDevice)

public:
	ANAudioRecordingDevice(const NStringWrapper & descriptiveText, const NStringWrapper & make, const NStringWrapper & model, const NStringWrapper & serialNumber)
	{
		NCheck(ANAudioRecordingDeviceCreateN(descriptiveText.GetHandle(), make.GetHandle(), model.GetHandle(), serialNumber.GetHandle(), this));
	}

	NString GetDescriptiveText() const
	{
		return NString(hDescriptiveText, false);
	}

	void SetDescriptiveText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDescriptiveText));
	}

	NString GetMake() const
	{
		return NString(hMake, false);
	}

	void SetMake(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hMake));
	}

	NString GetModel() const
	{
		return NString(hModel, false);
	}

	void SetModel(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hModel));
	}

	NString GetSerialNumber() const
	{
		return NString(hSerialNumber, false);
	}

	void SetSerialNumber(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hSerialNumber));
	}
};

class ANRecordingDuration : public ANRecordingDuration_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANRecordingDuration)

public:
	ANRecordingDuration(NULong recordingTime, NULong compressedBytes, NULong totalDigitalSamples)
	{
		this->recordingTime = recordingTime;
		this->compressedBytes = compressedBytes;
		this->totalDigitalSamples = totalDigitalSamples;
	}
};

class ANPhysicalMediaObject : public ANPhysicalMediaObject_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANPhysicalMediaObject)

public:
	ANPhysicalMediaObject(const NStringWrapper & mediaTypeDescription, NDouble recordingSpeed, const NStringWrapper & recordingSpeedUnits, const NStringWrapper & equalizationDescription, 
		NShort trackCount, const NArray & speakerTrackList, const NStringWrapper & comment)
	{
		NCheck(ANPhysicalMediaObjectCreateN(mediaTypeDescription.GetHandle(), recordingSpeed, recordingSpeedUnits.GetHandle(), equalizationDescription.GetHandle(), trackCount, 
			speakerTrackList.GetHandle(), comment.GetHandle(), this));
	}

	ANPhysicalMediaObject(const NStringWrapper & mediaTypeDescription, NDouble recordingSpeed, const NStringWrapper & recordingSpeedUnits, const NStringWrapper & equalizationDescription,
		NShort trackCount, const NUShort * arSpeakerTrackList, NInt speakerTrackListLength, const NStringWrapper & comment)
	{
		NCheck(ANPhysicalMediaObjectCreateExN(mediaTypeDescription.GetHandle(), recordingSpeed, recordingSpeedUnits.GetHandle(), equalizationDescription.GetHandle(), trackCount,
			arSpeakerTrackList, speakerTrackListLength, comment.GetHandle(), this));
	}

	NString GetMediaTypeDescription() const
	{
		return NString(hMediaTypeDescription, false);
	}

	void SetMediaTypeDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hMediaTypeDescription));
	}

	NString GetRecordingSpeedUnits() const
	{
		return NString(hRecordingSpeedUnits, false);
	}

	void SetRecordingSpeedUnits(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hRecordingSpeedUnits));
	}

	NString GetEqualizationDescription() const
	{
		return NString(hEqualizationDescription, false);
	}

	void SetEqualizationDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hEqualizationDescription));
	}

	NArray GetSpeakerTrackList() const
	{
		return NArray(hSpeakerTrackList, false);
	}

	void SetSpeakerTrackList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSpeakerTrackList));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANContainer : public ANContainer_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANContainer)

public:
	ANContainer(ANContainerCode containerCode, const NStringWrapper & externalContainerReference, const NStringWrapper & comment)
	{
		NCheck(ANContainerCreateN(containerCode, externalContainerReference.GetHandle(), comment.GetHandle(), this));
	}

	NString GetExternalContainerReference() const
	{
		return NString(hExternalContainerReference, false);
	}

	void SetExternalContainerReference(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hExternalContainerReference));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANCodec : public ANCodec_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANCodec)

public:
	ANCodec(ANCodecCode codecCode, NInt samplingRate, NShort bitDepth, ANEndianCode endianCode, const NStringWrapper & numericFormat, NShort channelCount, const NStringWrapper & externalCodecReference, const NStringWrapper & comment)
	{
		NCheck(ANCodecCreateN(codecCode, samplingRate, bitDepth, endianCode, numericFormat.GetHandle(), channelCount, externalCodecReference.GetHandle(), comment.GetHandle(), this));
	}

	NString GetNumericFormat() const
	{
		return NString(hNumericFormat, false);
	}

	void SetNumericFormat(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hNumericFormat));
	}

	NString GetExternalCodecReference() const
	{
		return NString(hExternalCodecReference, false);
	}

	void SetExternalCodecReference(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hExternalCodecReference));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANAudioInformation : public ANAudioInformation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANAudioInformation)

public:
	ANAudioInformation(ANProcessingIndicator indicator, const NStringWrapper & authorityOrganization, const NStringWrapper & comment)
	{
		NCheck(ANAudioInformationCreateN(indicator, authorityOrganization.GetHandle(), comment.GetHandle(), this));
	}

	NString GetAuthorityOrganization() const
	{
		return NString(hAuthorityOrganization, false);
	}

	void SetAuthorityOrganization(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hAuthorityOrganization));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANDiaryInformation : public ANDiaryInformation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANDiaryInformation)

public:
	ANDiaryInformation(NUInt segmentIdentifier, const NArray & trackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NStringWrapper & comment)
	{
		NCheck(ANDiaryInformationCreateN(segmentIdentifier, trackChannelList.GetHandle(), relativeStartTime, relativeEndTime, comment.GetHandle(), this));
	}

	ANDiaryInformation(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NStringWrapper & comment)
	{
		NCheck(ANDiaryInformationCreateExN(segmentIdentifier, arTrackChannelList, trackChannelListLength, relativeStartTime, relativeEndTime, comment.GetHandle(), this));
	}

	NArray GetTrackChannelList() const
	{
		return NArray(hTrackChannelList, false);
	}

	void SetTrackChannelList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hTrackChannelList));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANContentInformation : public ANContentInformation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANContentInformation)

public:
	ANContentInformation(ANDiarizationIndicator diarizationIndicator, const NStringWrapper & authorityOrganization, const NStringWrapper & comment)
	{
		NCheck(ANContentInformationCreateN(diarizationIndicator, authorityOrganization.GetHandle(), comment.GetHandle(), this));
	}

	NString GetAuthorityOrganization() const
	{
		return NString(hAuthorityOrganization, false);
	}

	void SetAuthorityOrganization(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hAuthorityOrganization));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANContentDiaryInformation : public ANContentDiaryInformation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANContentDiaryInformation)

public:
	ANContentDiaryInformation(NUInt segmentIdentifier, const NArray & trackChannelList, NULong relativeStartTime, NULong relativeEndTime, const NStringWrapper & comment, const NDateTime * pTaggedDate, 
		const NDateTime * pTaggedStartTime, const NDateTime * pTaggedEndTime, const NDateTime * pOriginalRecordingDate, const NDateTime * pSegmentRecordingStartTime, const NDateTime * pSegmentRecordingEndTime,
		const NStringWrapper & timeSourceDescription, const NStringWrapper & timingComment)
	{
		NCheck(ANContentDiaryInformationCreateN(segmentIdentifier, trackChannelList.GetHandle(), relativeStartTime, relativeEndTime, comment.GetHandle(), (const NDateTime_ *)pTaggedDate,
			(const NDateTime_ *)pTaggedStartTime, (const NDateTime_ *)pTaggedEndTime, (const NDateTime_ *)pOriginalRecordingDate, (const NDateTime_ *)pSegmentRecordingStartTime, (const NDateTime_ *)pSegmentRecordingEndTime,
			timeSourceDescription.GetHandle(), timingComment.GetHandle(), this));
	}

	ANContentDiaryInformation(NUInt segmentIdentifier, const NUShort * arTrackChannelList, NInt trackChannelListLength, NULong relativeStartTime, NULong relativeEndTime, const NStringWrapper & comment, const NDateTime * pTaggedDate,
		const NDateTime * pTaggedStartTime, const NDateTime * pTaggedEndTime, const NDateTime * pOriginalRecordingDate, const NDateTime * pSegmentRecordingStartTime, const NDateTime * pSegmentRecordingEndTime,
		const NStringWrapper & timeSourceDescription, const NStringWrapper & timingComment)
	{
		NCheck(ANContentDiaryInformationCreateExN(segmentIdentifier, arTrackChannelList, trackChannelListLength, relativeStartTime, relativeEndTime, comment.GetHandle(), (const NDateTime_ *)pTaggedDate,
			(const NDateTime_ *)pTaggedStartTime, (const NDateTime_ *)pTaggedEndTime, (const NDateTime_ *)pOriginalRecordingDate, (const NDateTime_ *)pSegmentRecordingStartTime, (const NDateTime_ *)pSegmentRecordingEndTime,
			timeSourceDescription.GetHandle(), timingComment.GetHandle(), this));
	}

	NArray GetTrackChannelList() const
	{
		return NArray(hTrackChannelList, false);
	}

	void SetTrackChannelList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hTrackChannelList));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}

	bool GetTaggedDate(NDateTime * pValue) const
	{
		*pValue = NDateTime(taggedDate);
		return hasTaggedDate != false;
	}
	void SetTaggedDate(const NDateTime * pValue)
	{
		hasTaggedDate = pValue != NULL ? true : false;
		if (pValue != NULL)
			taggedDate = *((const NDateTime_ *)(pValue));
	}

	bool GetTaggedStartTime(NDateTime * pValue) const
	{
		*pValue = NDateTime(taggedStartTime);
		return hasTaggedStartTime != false;
	}
	void SetTaggedStartTime(const NDateTime * pValue)
	{
		hasTaggedStartTime = pValue != NULL ? true : false;
		if (pValue != NULL)
			taggedStartTime = *((const NDateTime_ *)(pValue));
	}

	bool GetTaggedEndTime(NDateTime * pValue) const
	{
		*pValue = NDateTime(taggedEndTime);
		return hasTaggedEndTime != false;
	}
	void SetTaggedEndTime(const NDateTime * pValue)
	{
		hasTaggedEndTime = pValue != NULL ? true : false;
		if (pValue != NULL)
			taggedEndTime = *((const NDateTime_ *)(pValue));
	}

	bool GetOriginalRecordingDate(NDateTime * pValue) const
	{
		*pValue = NDateTime(originalRecordingDate);
		return hasOriginalRecordingDate != false;
	}
	void SetOriginalRecordingDate(const NDateTime * pValue)
	{
		hasOriginalRecordingDate = pValue != NULL ? true : false;
		if (pValue != NULL)
			originalRecordingDate = *((const NDateTime_ *)(pValue));
	}

	bool GetSegmentRecordingStartTime(NDateTime * pValue) const
	{
		*pValue = NDateTime(segmentRecordingStartTime);
		return hasSegmentRecordingStartTime != false;
	}
	void SetSegmentRecordingStartTime(const NDateTime * pValue)
	{
		hasSegmentRecordingStartTime = pValue != NULL ? true : false;
		if (pValue != NULL)
			segmentRecordingStartTime = *((const NDateTime_ *)(pValue));
	}

	bool GetSegmentRecordingEndTime(NDateTime * pValue) const
	{
		*pValue = NDateTime(segmentRecordingEndTime);
		return hasSegmentRecordingEndTime != false;
	}
	void SetSegmentRecordingEndTime(const NDateTime * pValue)
	{
		hasSegmentRecordingEndTime = pValue != NULL ? true : false;
		if (pValue != NULL)
			segmentRecordingEndTime = *((const NDateTime_ *)(pValue));
	}

	NString GetTimeSourceDescription() const
	{
		return NString(hTimeSourceDescription, false);
	}

	void SetTimeSourceDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTimeSourceDescription));
	}

	NString GetTimingComment() const
	{
		return NString(hTimingComment, false);
	}

	void SetTimingComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTimingComment));
	}
};

class ANSegmentGeographicLocation : public ANSegmentGeographicLocation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentGeographicLocation)

public:
	ANSegmentGeographicLocation(const NArray & segmentIdentifierList, const NStringWrapper & cellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond,
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
		const NStringWrapper & otherGeodeticDatumCode, const NStringWrapper & utmZone, NInt utmEasting, NInt utmNorthing, const NStringWrapper & referenceText,
		const NStringWrapper & otherSystemId, const NStringWrapper & otherSystemValue)
	{
		NCheck(ANSegmentGeographicLocationCreateN(segmentIdentifierList.GetHandle() , cellPhoneTowerCode.GetHandle(), pLatitudeDegree, latitudeMinute, latitudeSecond,
			pLongitudeDegree, longitudeMinute, longitudeSecond, pElevation, geodeticDatumCode, otherGeodeticDatumCode.GetHandle(),
			utmZone.GetHandle(), utmEasting, utmNorthing, referenceText.GetHandle(), otherSystemId.GetHandle(), otherSystemValue.GetHandle(), this));
	}

	ANSegmentGeographicLocation(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NStringWrapper & cellPhoneTowerCode, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond,
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
		const NStringWrapper & otherGeodeticDatumCode, const NStringWrapper & utmZone, NInt utmEasting, NInt utmNorthing, const NStringWrapper & referenceText,
		const NStringWrapper & otherSystemId, const NStringWrapper & otherSystemValue)
	{
		NCheck(ANSegmentGeographicLocationCreateExN(arSegmentIdentifierList, segmentIdentifierListLength, cellPhoneTowerCode.GetHandle(), pLatitudeDegree, latitudeMinute, latitudeSecond,
			pLongitudeDegree, longitudeMinute, longitudeSecond, pElevation, geodeticDatumCode, otherGeodeticDatumCode.GetHandle(),
			utmZone.GetHandle(), utmEasting, utmNorthing, referenceText.GetHandle(), otherSystemId.GetHandle(), otherSystemValue.GetHandle(), this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}

	NString GetCellPhoneTowerCode() const
	{
		return NString(hCellPhoneTowerCode, false);
	}

	void SetCellPhoneTowerCode(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hCellPhoneTowerCode));
	}

	bool GetLatitudeDegree(NDouble * pValue) const
	{
		*pValue = latitudeDegree;
		return hasLatitude != false;
	}
	void SetLatitudeDegree(const NDouble * pValue)
	{
		hasLatitude = pValue != NULL ? true : false;
		if (pValue != NULL)
			latitudeDegree = *pValue;
	}

	bool GetLongitudeDegree(NDouble * pValue) const
	{
		*pValue = longitudeDegree;
		return hasLongitude != false;
	}
	void SetLongitudeDegree(const NDouble * pValue)
	{
		hasLongitude = pValue != NULL ? true : false;
		if (pValue != NULL)
			longitudeDegree = *pValue;
	}

	bool GetElevation(NDouble * pValue) const
	{
		*pValue = elevation;
		return hasElevation != false;
	}
	void SetElevation(const NDouble * pValue)
	{
		hasElevation = pValue != NULL ? true : false;
		if (pValue != NULL)
			elevation = *pValue;
	}

	NString GetOtherGeodeticDatumCode() const
	{
		return NString(hOtherGeodeticDatumCode, false);
	}
	void SetGeodeticDatumCode(ANGeographicCoordinateSystem value, const NStringWrapper & otherValue)
	{
		geodeticDatumCode = value;
		NCheck(NStringSet(otherValue.GetHandle(), &hOtherGeodeticDatumCode));
	}

	NString GetUtmZone() const
	{
		return NString(hUtmZone, false);
	}
	void SetUtmZone(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hUtmZone));
	}

	NString GetReferenceText() const
	{
		return NString(hReferenceText, false);
	}
	void SetReferenceText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hReferenceText));
	}

	NString GetOtherSystemId() const
	{
		return NString(hOtherSystemId, false);
	}
	void SetOtherSystemId(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hOtherSystemId));
	}

	NString GetOtherSystemValue() const
	{
		return NString(hOtherSystemValue, false);
	}
	void SetOtherSystemValue(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hOtherSystemValue));
	}
};

class ANSegmentQualityBlock : public ANSegmentQualityBlock_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentQualityBlock)

public:
	ANSegmentQualityBlock(const NArray & segmentIdentifierList, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NStringWrapper & comment)
	{
		NCheck(ANSegmentQualityBlockCreateN(segmentIdentifierList.GetHandle(), score, algorithmVendorId, algorithmProductId, comment.GetHandle(), this));
	}

	ANSegmentQualityBlock(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte score, NUShort algorithmVendorId, NUShort algorithmProductId, const NStringWrapper & comment)
	{
		NCheck(ANSegmentQualityBlockCreateExN(arSegmentIdentifierList, segmentIdentifierListLength, score, algorithmVendorId, algorithmProductId, comment.GetHandle(), this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANSegmentProcessingPriority : public ANSegmentProcessingPriority_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentProcessingPriority)

public:
	ANSegmentProcessingPriority(const NArray & segmentIdentifierList, NByte priority)
	{
		NCheck(ANSegmentProcessingPriorityCreate(segmentIdentifierList.GetHandle(), priority, this));
	}

	ANSegmentProcessingPriority(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, NByte priority)
	{
		NCheck(ANSegmentProcessingPriorityCreateEx(arSegmentIdentifierList, segmentIdentifierListLength, priority, this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}
};

class ANSegmentContentDescription : public ANSegmentContentDescription_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentContentDescription)

public:
	ANSegmentContentDescription(const NArray & segmentIdentifierList, const NStringWrapper & transcriptText, const NStringWrapper & transcriptLanguage,
		const NStringWrapper & phoneticTranscriptText, const NStringWrapper & phoneticTranscriptConvention, const NStringWrapper & translationText, 
		const NStringWrapper & translationLanguage, const NStringWrapper & contentComment, const NStringWrapper & transcriptAuthorityComment)
	{
		NCheck(ANSegmentContentDescriptionCreateN(segmentIdentifierList.GetHandle(), transcriptText.GetHandle(), transcriptLanguage.GetHandle(),
			phoneticTranscriptText.GetHandle(), phoneticTranscriptConvention.GetHandle(), translationText.GetHandle(),
			translationLanguage.GetHandle(), contentComment.GetHandle(), transcriptAuthorityComment.GetHandle(), this));
	}

	ANSegmentContentDescription(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NStringWrapper & transcriptText, const NStringWrapper & transcriptLanguage,
		const NStringWrapper & phoneticTranscriptText, const NStringWrapper & phoneticTranscriptConvention, const NStringWrapper & translationText,
		const NStringWrapper & translationLanguage, const NStringWrapper & contentComment, const NStringWrapper & transcriptAuthorityComment)
	{
		NCheck(ANSegmentContentDescriptionCreateExN(arSegmentIdentifierList, segmentIdentifierListLength, transcriptText.GetHandle(), transcriptLanguage.GetHandle(),
			phoneticTranscriptText.GetHandle(), phoneticTranscriptConvention.GetHandle(), translationText.GetHandle(),
			translationLanguage.GetHandle(), contentComment.GetHandle(), transcriptAuthorityComment.GetHandle(), this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}

	void SetTranscriptText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTranscriptText));
	}

	NString GetTranscriptText() const
	{
		return NString(hTranscriptText, false);
	}

	void SetTranscriptLanguage(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTranscriptLanguage));
	}

	NString GetTranscriptLanguage() const
	{
		return NString(hTranscriptLanguage, false);
	}

	void SetPhoneticTranscriptText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hPhoneticTranscriptText));
	}

	NString GetPhoneticTranscriptText() const
	{
		return NString(hPhoneticTranscriptText, false);
	}

	void SetPhoneticTranscriptConvention(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hPhoneticTranscriptConvention));
	}

	NString GetPhoneticTranscriptConvention() const
	{
		return NString(hPhoneticTranscriptConvention, false);
	}

	void SetTranslationText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTranslationText));
	}

	NString GetTranslationText() const
	{
		return NString(hTranslationText, false);
	}

	void SetTranslationLanguage(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTranslationLanguage));
	}

	NString GetTranslationLanguage() const
	{
		return NString(hTranslationLanguage, false);
	}

	void SetContentComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hContentComment));
	}

	NString GetContentComment() const
	{
		return NString(hContentComment, false);
	}

	void SetTranscriptAuthorityComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hTranscriptAuthorityComment));
	}

	NString GetTranscriptAuthorityComment() const
	{
		return NString(hTranscriptAuthorityComment, false);
	}
};

class ANSegmentSpeakerCharacteristics : public ANSegmentSpeakerCharacteristics_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentSpeakerCharacteristics)

public:
	ANSegmentSpeakerCharacteristics(const NArray & segmentIdentifierList, const NArray & speakerList, const NArray & Type2RecordReferenceList, NSByte impairmentLevel, const NStringWrapper & spokenLanguage, NSByte languageProficiency,
		ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, const NStringWrapper & healthComment, ANEmotionalState emotionalState, NSByte vocalEffortScale,
		ANVocalStyle vocalStyle, ANRecordingAwareness recordingAwareness, const NStringWrapper & scriptText, const NStringWrapper & comment)
	{
		NCheck(ANSegmentSpeakerCharacteristicsCreateN(segmentIdentifierList.GetHandle(), speakerList.GetHandle(), Type2RecordReferenceList.GetHandle(), impairmentLevel, spokenLanguage.GetHandle(), languageProficiency,
			speechStyle, intelligibilityScale, familiarityDegree, healthComment.GetHandle(), emotionalState, vocalEffortScale,
			vocalStyle, recordingAwareness, scriptText.GetHandle(), comment.GetHandle(), this));
	}

	ANSegmentSpeakerCharacteristics(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, const NUShort * arSpeakerList, NInt speakerListLength, const NInt * arType2RecordReferenceList, NInt type2RecordReferenceListLength, NSByte impairmentLevel,
		const NStringWrapper & spokenLanguage, NSByte languageProficiency, ANSpeechStyleDescription speechStyle, NSByte intelligibilityScale, NSByte familiarityDegree, const NStringWrapper & healthComment, ANEmotionalState emotionalState,
		NSByte vocalEffortScale, ANVocalStyle vocalStyle, ANRecordingAwareness recordingAwareness, const NStringWrapper & scriptText, const NStringWrapper & comment)
	{
		NCheck(ANSegmentSpeakerCharacteristicsCreateExN(arSegmentIdentifierList, segmentIdentifierListLength, arSpeakerList, speakerListLength, arType2RecordReferenceList, 
			type2RecordReferenceListLength, impairmentLevel, spokenLanguage.GetHandle(), languageProficiency, speechStyle, intelligibilityScale, familiarityDegree, healthComment.GetHandle(), emotionalState,
			vocalEffortScale, vocalStyle, recordingAwareness, scriptText.GetHandle(), comment.GetHandle(), this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}

	NArray GetSpeakerList() const
	{
		return NArray(hSpeakerList, false);
	}

	void SetSpeakerList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSpeakerList));
	}

	NArray GetType2RecordReferenceList() const
	{
		return NArray(hType2RecordReferenceList, false);
	}

	void SetType2RecordReferenceList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hType2RecordReferenceList));
	}

	NString GetSpokenLanguage() const
	{
		return NString(hSpokenLanguage, false);
	}

	void SetSpokenLanguage(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hSpokenLanguage));
	}

	NString GetHealthComment() const
	{
		return NString(hHealthComment, false);
	}

	void SetHealthComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hHealthComment));
	}

	NString GetScriptText() const
	{
		return NString(hScriptText, false);
	}

	void SetScriptText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hScriptText));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

class ANSegmentChannel : public ANSegmentChannel_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegmentChannel)

public:
	ANSegmentChannel(const NArray & segmentIdentifierList, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NStringWrapper & captureEnvironmentDescription, 
		NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType, const NStringWrapper & voiceModificationDescription, const NStringWrapper & comment)
	{
		NCheck(ANSegmentChannelCreateN(segmentIdentifierList.GetHandle(), audioCaptureDevice, microphoneType, captureEnvironmentDescription.GetHandle(),
			transducerDistance, acquisitionSourceType, voiceModificationDescription.GetHandle(), comment.GetHandle(), this));
	}

	ANSegmentChannel(const NUInt * arSegmentIdentifierList, NInt segmentIdentifierListLength, ANAudioCaptureDevice audioCaptureDevice, ANMicrophoneType microphoneType, const NStringWrapper & captureEnvironmentDescription,
		NInt transducerDistance, ANAcquisitionSourceType acquisitionSourceType, const NStringWrapper & voiceModificationDescription, const NStringWrapper & comment)
	{
		NCheck(ANSegmentChannelCreateExN(arSegmentIdentifierList, segmentIdentifierListLength, audioCaptureDevice, microphoneType, captureEnvironmentDescription.GetHandle(),
			transducerDistance, acquisitionSourceType, voiceModificationDescription.GetHandle(), comment.GetHandle(), this));
	}

	NArray GetSegmentIdentifierList() const
	{
		return NArray(hSegmentIdentifierList, false);
	}

	void SetSegmentIdentifierList(const NArray & value)
	{
		NCheck(NObjectSet(value.GetHandle(), (HNObject *)&hSegmentIdentifierList));
	}

	NString GetCaptureEnvironmentDescription() const
	{
		return NString(hCaptureEnvironmentDescription, false);
	}

	void SetCaptureEnvironmentDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hCaptureEnvironmentDescription));
	}

	NString GetVoiceModificationDescription() const
	{
		return NString(hVoiceModificationDescription, false);
	}

	void SetVoiceModificationDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hVoiceModificationDescription));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}

	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANRecordingDuration)

N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSourceOrganization)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANVoiceRecordingContent)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAudioRecordingDevice)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANPhysicalMediaObject)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANContainer)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANCodec)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAudioInformation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDiaryInformation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANContentInformation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANContentDiaryInformation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentGeographicLocation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentQualityBlock)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentProcessingPriority)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentContentDescription)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentSpeakerCharacteristics)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegmentChannel)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType11Record : public ANAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType11Record, ANAsciiBinaryRecord)

public:
	class RedactionDiaryCollection : public ::Neurotec::Collections::NCollectionBase<ANDiaryInformation, ANType11Record,
		ANType11RecordGetRedactionDiaryCount, ANType11RecordGetRedactionDiary>
	{
		RedactionDiaryCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANDiaryInformation & value)
		{
			NCheck(ANType11RecordSetRedactionDiary(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANDiaryInformation & value)
		{
			NInt index;
			NCheck(ANType11RecordAddRedactionDiary(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANDiaryInformation & value)
		{
			NCheck(ANType11RecordInsertRedactionDiary(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveRedactionDiaryAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearRedactionDiaries(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class DiscontinuityDiaryCollection : public ::Neurotec::Collections::NCollectionBase<ANDiaryInformation, ANType11Record,
		ANType11RecordGetDiscontinuityDiaryCount, ANType11RecordGetDiscontinuityDiary>
	{
		DiscontinuityDiaryCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANDiaryInformation & value)
		{
			NCheck(ANType11RecordSetDiscontinuityDiary(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANDiaryInformation & value)
		{
			NInt index;
			NCheck(ANType11RecordAddDiscontinuityDiary(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANDiaryInformation & value)
		{
			NCheck(ANType11RecordInsertDiscontinuityDiary(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveDiscontinuityDiaryAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearDiscontinuityDiaries(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class VocalContentDiaryCollection : public ::Neurotec::Collections::NCollectionBase<ANContentDiaryInformation, ANType11Record,
		ANType11RecordGetVocalContentDiaryCount, ANType11RecordGetVocalContentDiary>
	{
		VocalContentDiaryCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANContentDiaryInformation & value)
		{
			NCheck(ANType11RecordSetVocalContentDiary(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANContentDiaryInformation & value)
		{
			NInt index;
			NCheck(ANType11RecordAddVocalContentDiary(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANContentDiaryInformation & value)
		{
			NCheck(ANType11RecordInsertVocalContentDiary(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveVocalContentDiaryAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearVocalContentDiaries(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};
	
	class OtherContentDiaryCollection : public ::Neurotec::Collections::NCollectionBase<ANContentDiaryInformation, ANType11Record,
		ANType11RecordGetOtherContentDiaryCount, ANType11RecordGetOtherContentDiary>
	{
		OtherContentDiaryCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANContentDiaryInformation & value)
		{
			NCheck(ANType11RecordSetOtherContentDiary(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANContentDiaryInformation & value)
		{
			NInt index;
			NCheck(ANType11RecordAddOtherContentDiary(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANContentDiaryInformation & value)
		{
			NCheck(ANType11RecordInsertOtherContentDiary(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveOtherContentDiaryAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearOtherContentDiaries(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentGeographicLocationCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentGeographicLocation, ANType11Record,
		ANType11RecordGetSegmentGeographicLocationCount, ANType11RecordGetSegmentGeographicLocation>
	{
		SegmentGeographicLocationCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentGeographicLocation & value)
		{
			NCheck(ANType11RecordSetSegmentGeographicLocation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentGeographicLocation & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentGeographicLocation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentGeographicLocation & value)
		{
			NCheck(ANType11RecordInsertSegmentGeographicLocation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentGeographicLocationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentGeographicLocations(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentQualityBlockCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentQualityBlock, ANType11Record,
		ANType11RecordGetSegmentQualityBlockCount, ANType11RecordGetSegmentQualityBlock>
	{
		SegmentQualityBlockCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentQualityBlock & value)
		{
			NCheck(ANType11RecordSetSegmentQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentQualityBlock & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentQualityBlock(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentQualityBlock & value)
		{
			NCheck(ANType11RecordInsertSegmentQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentQualityBlockAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentQualityBlocks(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentProcessingPriorityCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentProcessingPriority, ANType11Record,
		ANType11RecordGetSegmentProcessingPriorityCount, ANType11RecordGetSegmentProcessingPriority>
	{
		SegmentProcessingPriorityCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentProcessingPriority & value)
		{
			NCheck(ANType11RecordSetSegmentProcessingPriority(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentProcessingPriority & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentProcessingPriority(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentProcessingPriority & value)
		{
			NCheck(ANType11RecordInsertSegmentProcessingPriority(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentProcessingPriorityAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentProcessingPriorities(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentContentDescriptionCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentContentDescription, ANType11Record,
		ANType11RecordGetSegmentContentDescriptionCount, ANType11RecordGetSegmentContentDescription>
	{
		SegmentContentDescriptionCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentContentDescription & value)
		{
			NCheck(ANType11RecordSetSegmentContentDescription(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentContentDescription & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentContentDescription(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentContentDescription & value)
		{
			NCheck(ANType11RecordInsertSegmentContentDescription(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentContentDescriptionAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentContentDescriptions(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentSpeakerCharacteristicsCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentSpeakerCharacteristics, ANType11Record,
		ANType11RecordGetSegmentSpeakerCharacteristicsCount, ANType11RecordGetSegmentSpeakerCharacteristics>
	{
		SegmentSpeakerCharacteristicsCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentSpeakerCharacteristics & value)
		{
			NCheck(ANType11RecordSetSegmentSpeakerCharacteristics(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentSpeakerCharacteristics & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentSpeakerCharacteristics(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentSpeakerCharacteristics & value)
		{
			NCheck(ANType11RecordInsertSegmentSpeakerCharacteristics(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentSpeakerCharacteristicsAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentSpeakersCharacteristics(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};

	class SegmentChannelCollection : public ::Neurotec::Collections::NCollectionBase<ANSegmentChannel, ANType11Record,
		ANType11RecordGetSegmentChannelCount, ANType11RecordGetSegmentChannel>
	{
		SegmentChannelCollection(const ANType11Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegmentChannel & value)
		{
			NCheck(ANType11RecordSetSegmentChannel(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegmentChannel & value)
		{
			NInt index;
			NCheck(ANType11RecordAddSegmentChannel(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegmentChannel & value)
		{
			NCheck(ANType11RecordInsertSegmentChannel(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType11RecordRemoveSegmentChannelAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType11RecordClearSegmentChannels(this->GetOwnerHandle()));
		}

		friend class ANType11Record;
	};
private:

public:
	static NType ANAudioObjectDescriptorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANAudioObjectDescriptor), true);
	}
	static NType ANSourceOrganizationTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSourceOrganizationType), true);
	}
	static NType ANAssignedVoiceIndicatorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANAssignedVoiceIndicator), true);
	}
	static NType ANSpeakerPluralityCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSpeakerPluralityCode), true);
	}
	static NType ANContainerCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANContainerCode), true);
	}
	static NType ANCodecCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANCodecCode), true);
	}
	static NType ANDiarizationIndicatorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDiarizationIndicator), true);
	}
	static NType ANSpeechStyleDescriptionNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSpeechStyleDescription), true);
	}
	static NType ANEmotionalStateNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANEmotionalState), true);
	}
	static NType ANVocalStyleNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANVocalStyle), true);
	}
	static NType ANRecordingAwarenessNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANRecordingAwareness), true);
	}
	static NType ANAudioCaptureDeviceNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANAudioCaptureDevice), true);
	}
	static NType ANMicrophoneTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANMicrophoneType), true);
	}
	static NType ANProcessingIndicatorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANProcessingIndicator), true);
	}

	ANAudioObjectDescriptor GetAudioObjectDescriptor() const
	{
		ANAudioObjectDescriptor value;
		NCheck(ANType11RecordGetAudioObjectDescriptor(GetHandle(), &value));
		return value;
	}

	void SetAudioObjectDescriptor(ANAudioObjectDescriptor value)
	{
		NCheck(ANType11RecordSetAudioObjectDescriptor(GetHandle(), value));
	}

	bool GetSourceOrganization(ANSourceOrganization * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetSourceOrganization(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetSourceOrganization(const ANSourceOrganization * pValue)
	{
		NCheck(ANType11RecordSetSourceOrganization(GetHandle(), pValue));
	}

	bool GetVoiceRecordingContent(ANVoiceRecordingContent * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetVoiceRecordingContent(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetVoiceRecordingContent(const ANVoiceRecordingContent * pValue)
	{
		NCheck(ANType11RecordSetVoiceRecordingContent(GetHandle(), pValue));
	}

	bool GetAudioRecordingDevice(ANAudioRecordingDevice * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetAudioRecordingDevice(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetAudioRecordingDevice(const ANAudioRecordingDevice * pValue)
	{
		NCheck(ANType11RecordSetAudioRecordingDevice(GetHandle(), pValue));
	}

	bool GetAcquisitionSource(ANAcquisitionSource * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetAcquisitionSource(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetAcquisitionSource(const ANAcquisitionSource * pValue)
	{
		NCheck(ANType11RecordSetAcquisitionSource(GetHandle(), pValue));
	}

	NDateTime GetRecordCreationDate() const
	{
		NDateTime_ value;
		NCheck(ANType11RecordGetRecordCreationDate(GetHandle(), &value));
		return NDateTime(value);
	}

	void SetRecordCreationDate(const NDateTime & value)
	{
		NCheck(ANType11RecordSetRecordCreationDate(GetHandle(), value.GetValue()));
	}

	bool GetRecordingDuration(ANRecordingDuration * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetRecordingDuration(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetRecordingDuration(const ANRecordingDuration * pValue)
	{
		NCheck(ANType11RecordSetRecordingDuration(GetHandle(), pValue));
	}

	bool GetPhysicalMediaObject(ANPhysicalMediaObject * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetPhysicalMediaObject(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetPhysicalMediaObject(const ANPhysicalMediaObject * pValue)
	{
		NCheck(ANType11RecordSetPhysicalMediaObject(GetHandle(), pValue));
	}

	void SetContainer(const ANContainer * pValue)
	{
		NCheck(ANType11RecordSetContainer(GetHandle(), pValue));
	}

	bool GetContainer(ANContainer * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetContainer(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetCodec(const ANCodec * pValue)
	{
		NCheck(ANType11RecordSetCodec(GetHandle(), pValue));
	}

	bool GetCodec(ANCodec * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetCodec(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetRedaction(const ANAudioInformation * pValue)
	{
		NCheck(ANType11RecordSetRedaction(GetHandle(), pValue));
	}

	bool GetRedaction(ANAudioInformation * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetRedaction(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetDiscontinuity(const ANAudioInformation * pValue)
	{
		NCheck(ANType11RecordSetDiscontinuity(GetHandle(), pValue));
	}

	bool GetDiscontinuity(ANAudioInformation * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetDiscontinuity(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetVocalContent(const ANContentInformation * pValue)
	{
		NCheck(ANType11RecordSetVocalContent(GetHandle(), pValue));
	}

	bool GetVocalContent(ANContentInformation * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetVocalContent(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetOtherContent(const ANContentInformation * pValue)
	{
		NCheck(ANType11RecordSetOtherContent(GetHandle(), pValue));
	}

	bool GetOtherContent(ANContentInformation * pValue) const
	{
		NBool hasValue;
		NCheck(ANType11RecordGetOtherContent(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NArray GetVocalCollisionIdentifiers() const
	{
		HNArray hValue;
		NCheck(ANType11RecordGetVocalCollisionIdentifiers(GetHandle(), &hValue));
		return FromHandle<NArray>(hValue, true);
	}

	void SetVocalCollisionIdentifiers(const NArray & value)
	{
		NCheck(ANType11RecordSetVocalCollisionIdentifiers(GetHandle(), value.GetHandle()));
	}

	void SetVocalCollisionIdentifiers(const NUInt * arValues, NInt valuesLength)
	{
		NCheck(ANType11RecordSetVocalCollisionIdentifiersEx(GetHandle(), arValues, valuesLength));
	}


	RedactionDiaryCollection GetRedactionDiaries()
	{
		return RedactionDiaryCollection(*this);
	}

	const RedactionDiaryCollection GetRedactionDiaries() const
	{
		return RedactionDiaryCollection(*this);
	}

	DiscontinuityDiaryCollection GetDiscontinuityDiaries()
	{
		return DiscontinuityDiaryCollection(*this);
	}

	const DiscontinuityDiaryCollection GetDiscontinuityDiaries() const
	{
		return DiscontinuityDiaryCollection(*this);
	}

	VocalContentDiaryCollection GetVocalContentDiaries()
	{
		return VocalContentDiaryCollection(*this);
	}

	const VocalContentDiaryCollection GetVocalContentDiaries() const
	{
		return VocalContentDiaryCollection(*this);
	}

	OtherContentDiaryCollection GetOtherContentDiaries()
	{
		return OtherContentDiaryCollection(*this);
	}

	const OtherContentDiaryCollection GetOtherContentDiaries() const
	{
		return OtherContentDiaryCollection(*this);
	}

	SegmentGeographicLocationCollection GetSegmentGeographicLocations()
	{
		return SegmentGeographicLocationCollection(*this);
	}

	const SegmentGeographicLocationCollection GetSegmentGeographicLocations() const
	{
		return SegmentGeographicLocationCollection(*this);
	}

	SegmentQualityBlockCollection GetSegmentQualityBlocks()
	{
		return SegmentQualityBlockCollection(*this);
	}

	const SegmentQualityBlockCollection GetSegmentQualityBlocks() const
	{
		return SegmentQualityBlockCollection(*this);
	}

	SegmentProcessingPriorityCollection GetSegmentProcessingPriorities()
	{
		return SegmentProcessingPriorityCollection(*this);
	}

	const SegmentProcessingPriorityCollection GetSegmentProcessingPriorities() const
	{
		return SegmentProcessingPriorityCollection(*this);
	}

	SegmentContentDescriptionCollection GetSegmentContentDescriptions()
	{
		return SegmentContentDescriptionCollection(*this);
	}

	const SegmentContentDescriptionCollection GetSegmentContentDescriptions() const
	{
		return SegmentContentDescriptionCollection(*this);
	}

	SegmentSpeakerCharacteristicsCollection GetSegmentSpeakersCharacteristics()
	{
		return SegmentSpeakerCharacteristicsCollection(*this);
	}

	const SegmentSpeakerCharacteristicsCollection GetSegmentSpeakersCharacteristics() const
	{
		return SegmentSpeakerCharacteristicsCollection(*this);
	}

	SegmentChannelCollection GetSegmentChannels()
	{
		return SegmentChannelCollection(*this);
	}

	const SegmentChannelCollection GetSegmentChannels() const
	{
		return SegmentChannelCollection(*this);
	}

	NString GetComment() const
	{
		return GetString(ANType11RecordGetCommentN);
	}
	void SetComment(const NStringWrapper & value)
	{
		SetString(ANType11RecordSetCommentN, value);
	}

	::Neurotec::Sound::NSoundBuffer ToNSoundBuffer(NUInt flags = 0) const
	{
		HNSoundBuffer hSBuffer;
		NCheck(ANType11RecordToNSoundBuffer(GetHandle(), flags, &hSBuffer));
		return FromHandle< ::Neurotec::Sound::NSoundBuffer>(hSBuffer);
	}

};

}}}

#endif // !AN_TYPE_11_RECORD_HPP_INCLUDED
