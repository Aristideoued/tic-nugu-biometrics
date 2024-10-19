#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
#define AN_ASCII_BINARY_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANRecord.hpp>
namespace Neurotec {
	namespace Biometrics {
		namespace Standards
{
#include <Biometrics/Standards/ANAsciiBinaryRecord.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSubjectStatusCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSubjectBodyStatusCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSubjectBodyClassCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANGeographicCoordinateSystem)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAcquisitionSourceType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANEndianCode)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_ASCII_BINARY_RECORD_FIELD_SRC
#undef AN_ASCII_BINARY_RECORD_FIELD_DAT

#undef AN_ASCII_BINARY_RECORD_FIELD_SUB
#undef AN_ASCII_BINARY_RECORD_FIELD_CON

#undef AN_ASCII_BINARY_RECORD_FIELD_ANN
#undef AN_ASCII_BINARY_RECORD_FIELD_DUI
#undef AN_ASCII_BINARY_RECORD_FIELD_MMS

#undef AN_ASCII_BINARY_RECORD_FIELD_SAN
#undef AN_ASCII_BINARY_RECORD_FIELD_EFR
#undef AN_ASCII_BINARY_RECORD_FIELD_ASC
#undef AN_ASCII_BINARY_RECORD_FIELD_HAS
#undef AN_ASCII_BINARY_RECORD_FIELD_SOR
#undef AN_ASCII_BINARY_RECORD_FIELD_GEO

#undef AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#undef AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#undef AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#undef AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH
#undef AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH_V5
#undef AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH_V4

#undef AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_NOT_AVAILABLE
#undef AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_FAILED

#undef AN_ASCII_BINARY_RECORD_MAX_QUALITY_METRIC_SCORE

#undef AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_NAME_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_NAME_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_CAPTURE_ORGANIZATION_NAME_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_CAPTURE_ORGANIZATION_NAME_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_NUMBER
#undef AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_NUMBER
#undef AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION
#undef AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION

#undef AN_ASCII_BINARY_RECORD_MAX_MAKE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_MODEL_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_SERIAL_NUMBER_LENGTH

#undef AN_ASCII_BINARY_RECORD_HASH_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_LATITUTE_DEGREE
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_LONGITUDE_DEGREE
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_MINUTE
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_SECOND
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_ELEVATION
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION

#undef AN_ASCII_BINARY_RECORD_MIN_GEODETIC_DATUM_CODE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEODETIC_DATUM_CODE_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_GEO_UTM_ZONE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_ZONE_LENGTH

#undef AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_EASTING
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_NORTHING

#undef AN_ASCII_BINARY_RECORD_MAX_GEO_REFERENCE_TEXT_LENGTH

#undef AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_ID_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_VALUE_LENGTH
#undef AN_ASCII_BINARY_RECORD_GEO_DEFAULT_COORDINATE_SYSTEM

#undef AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_FILE_TYPE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_FILE_TYPE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_DECODING_INSTR_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_EXTERNAL_FILE_REFERENCE_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_EXTERNAL_FILE_REFERENCE_LENGTH

#undef AN_ASCII_BINARY_RECORD_MIN_TIME_INDEX_COUNT
#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_COUNT

#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_LENGTH
#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_HOUR
#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MINUTE
#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_SECOND
#undef AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MILLISECOND

#undef AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH
#undef AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH_V51
#undef AN_ASCII_BINARY_RECORD_MAX_ICDR_LENGTH


const NInt AN_ASCII_BINARY_RECORD_FIELD_SRC = 4;
const NInt AN_ASCII_BINARY_RECORD_FIELD_DAT = 5;

const NInt AN_ASCII_BINARY_RECORD_FIELD_SUB = 46;
const NInt AN_ASCII_BINARY_RECORD_FIELD_CON = 47;

const NInt AN_ASCII_BINARY_RECORD_FIELD_ANN = 902;
const NInt AN_ASCII_BINARY_RECORD_FIELD_DUI = 903;
const NInt AN_ASCII_BINARY_RECORD_FIELD_MMS = 904;

const NInt AN_ASCII_BINARY_RECORD_FIELD_SAN = 993;
const NInt AN_ASCII_BINARY_RECORD_FIELD_EFR = 994;
const NInt AN_ASCII_BINARY_RECORD_FIELD_ASC = 995;
const NInt AN_ASCII_BINARY_RECORD_FIELD_HAS = 996;
const NInt AN_ASCII_BINARY_RECORD_FIELD_SOR = 997;
const NInt AN_ASCII_BINARY_RECORD_FIELD_GEO = 998;

const NInt AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM = 200;
const NInt AN_ASCII_BINARY_RECORD_FIELD_UDF_TO = 998;
const NInt AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5 = 900;

const NInt AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH = 9;
const NInt AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH_V5 = 1;
const NInt AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH = 20;
const NInt AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH_V4 = 35;

const NByte AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_NOT_AVAILABLE = 254;
const NByte AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_FAILED = 255;

const NByte AN_ASCII_BINARY_RECORD_MAX_QUALITY_METRIC_SCORE = 100;

const NUShort AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_NAME_LENGTH = 1;
const NUShort AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_NAME_LENGTH = 125;

const NUShort AN_ASCII_BINARY_RECORD_MIN_CAPTURE_ORGANIZATION_NAME_LENGTH = 1;
const NUShort AN_ASCII_BINARY_RECORD_MAX_CAPTURE_ORGANIZATION_NAME_LENGTH = 1000;

const NByte AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_NUMBER           = 1;
const NByte AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_NUMBER           = 255;
const NByte AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION = 1;
const NByte AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION = 99;

const NInt AN_ASCII_BINARY_RECORD_MAX_MAKE_LENGTH = AN_RECORD_MAX_MAKE_LENGTH;
const NInt AN_ASCII_BINARY_RECORD_MAX_MODEL_LENGTH = AN_RECORD_MAX_MODEL_LENGTH;
const NInt AN_ASCII_BINARY_RECORD_MAX_SERIAL_NUMBER_LENGTH = AN_RECORD_MAX_SERIAL_NUMBER_LENGTH;

const NUShort AN_ASCII_BINARY_RECORD_HASH_LENGTH = 64;

const NInt AN_ASCII_BINARY_RECORD_MIN_GEO_LATITUTE_DEGREE = -90;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE = 90;

const NInt AN_ASCII_BINARY_RECORD_MIN_GEO_LONGITUDE_DEGREE = -180;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE = 180;

const NInt AN_ASCII_BINARY_RECORD_MIN_GEO_MINUTE = 0;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE = 59;

const NInt AN_ASCII_BINARY_RECORD_MIN_GEO_SECOND = 0;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND = 59;

const NInt AN_ASCII_BINARY_RECORD_MIN_GEO_ELEVATION = -422;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION = 8848;

const NByte AN_ASCII_BINARY_RECORD_MIN_GEODETIC_DATUM_CODE_LENGTH = 3;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEODETIC_DATUM_CODE_LENGTH = 6;
const NUShort AN_ASCII_BINARY_RECORD_GEO_DEFAULT_COORDINATE_SYSTEM = angcsWgs84;

const NByte AN_ASCII_BINARY_RECORD_MIN_GEO_UTM_ZONE_LENGTH = 2;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_ZONE_LENGTH = 3;

const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_EASTING  = 999999;
const NInt AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_NORTHING = 99999999;

const NUShort AN_ASCII_BINARY_RECORD_MAX_GEO_REFERENCE_TEXT_LENGTH  = 150;

const NUShort AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_ID_LENGTH    = 10;
const NUShort AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_VALUE_LENGTH = 126;

const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE_LENGTH  = 9;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE_LENGTH = 10;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE_LENGTH = 8;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND_LENGTH = 8;
const NByte AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION_LENGTH = 8;

const NUShort AN_ASCII_BINARY_RECORD_MIN_FILE_TYPE_LENGTH     = 3;
const NUShort AN_ASCII_BINARY_RECORD_MAX_FILE_TYPE_LENGTH     = 6;
const NUShort AN_ASCII_BINARY_RECORD_MAX_DECODING_INSTR_LENGTH = 1000;

const NUShort AN_ASCII_BINARY_RECORD_MIN_EXTERNAL_FILE_REFERENCE_LENGTH = 1;
const NUShort AN_ASCII_BINARY_RECORD_MAX_EXTERNAL_FILE_REFERENCE_LENGTH = 200;

const NByte AN_ASCII_BINARY_RECORD_MIN_TIME_INDEX_COUNT = 1;
const NByte AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_COUNT = 99;

const NByte AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_LENGTH      = 12;
const NByte AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_HOUR        = 99;
const NByte AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MINUTE      = 59;
const NByte AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_SECOND      = 59;
const NUShort AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MILLISECOND = 999;

const NByte AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH     = 3;
const NByte AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH_V51 = 2;
const NByte AN_ASCII_BINARY_RECORD_MAX_ICDR_LENGTH     = 9;

class ANQualityMetric : public ANQualityMetric_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANQualityMetric)

public:
	ANQualityMetric(NByte score, NUShort algorithmVendorId, NUShort algorithmProductId)
	{
		Score = score;
		AlgorithmVendorId = algorithmVendorId;
		AlgorithmProductId = algorithmProductId;
	}
};

class ANSubjectCondition : public ANSubjectCondition_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANSubjectCondition)
public:
	ANSubjectCondition(ANSubjectStatusCode subjectStatus, ANSubjectBodyStatusCode subjectBodyStatus, ANSubjectBodyClassCode subjectBodyClass)
	{
		SubjectStatus = subjectStatus;
		SubjectBodyStatus = subjectBodyStatus;
		SubjectBodyClass = subjectBodyClass;
	}
};

class ANGeographicLocation : public ANGeographicLocation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANGeographicLocation)

public:
	ANGeographicLocation(const NDateTime * pUniversalTimeEntry, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond,
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode,
		const NStringWrapper & otherGeodeticDatumCode, const NStringWrapper & utmZone, NInt utmEasting, NInt utmNorthing, const NStringWrapper & referenceText,
		const NStringWrapper & otherSystemId, const NStringWrapper & otherSystemValue)
	{
		NCheck(ANGeographicLocationCreateN((const NDateTime_ *)pUniversalTimeEntry, pLatitudeDegree, latitudeMinute, latitudeSecond,
		pLongitudeDegree, longitudeMinute, longitudeSecond, pElevation, geodeticDatumCode, otherGeodeticDatumCode.GetHandle(),
		utmZone.GetHandle(), utmEasting, utmNorthing, referenceText.GetHandle(), otherSystemId.GetHandle(), otherSystemValue.GetHandle(), this));
	}

	bool GetUniversalTimeEntry(NDateTime * pValue) const
	{
		*pValue = NDateTime(universalTimeEntry);
		return hasUniversalTimeEntry != false;
	}
	void SetUniversalTimeEntry(const NDateTime * pValue)
	{
		hasUniversalTimeEntry = pValue != NULL ? true : false;
		if (pValue != NULL)
			universalTimeEntry = *((const NDateTime_ *)(pValue));
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

class ANFileFormat : public ANFileFormat_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANFileFormat)

public:
	ANFileFormat(const NStringWrapper & fileType, const NStringWrapper & decodingInstructions)
	{
		NCheck(ANFileFormatCreateN(fileType.GetHandle(), decodingInstructions.GetHandle(), this));
	}

	NString GetFileType() const
	{
		return NString(hFileType, false);
	}
	void SetFileType(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hFileType));
	}

	NString GetDecodingInstructions() const
	{
		return NString(hDecodingInstructions, false);
	}
	void SetDecodingInstructions(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDecodingInstructions));
	}
};

class ANSegment : public ANSegment_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSegment)

public:
	ANSegment(NByte segmentPosition, const NStringWrapper & internalFilePointer)
	{
		NCheck(ANSegmentCreateN(segmentPosition, internalFilePointer.GetHandle(), this));
	}

	NString GetInternalFilePointer() const
	{
		return NString(hInternalFilePointer, false);
	}
	void SetInternalFilePointer(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hInternalFilePointer));
	}
};

class ANSourceContextRepresentation : public ANSourceContextRepresentation_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANSourceContextRepresentation)

public:
	ANSourceContextRepresentation(NUInt referenceNumber, NUInt segmentPosition)
	{
		ReferenceNumber = referenceNumber;
		SegmentPosition = segmentPosition;
	}
};

class ANTimeIndex : public ANTimeIndex_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANTimeIndex)

public:
	ANTimeIndex(NLong timeIndexStart, NLong timeIndexEnd)
	{
		TimeIndexStart = timeIndexStart;
		TimeIndexEnd = timeIndexEnd;
	}

	void GetTimeIndexStart(NInt * pHour, NInt * pMinute, NInt * pSecond, NInt * pMillisecond) const
	{
		NCheck(ANTimeIndexDecodeTime(TimeIndexStart, pHour, pMinute, pSecond, pMillisecond));
	}
	void SetTimeIndexStart(NInt hour, NInt minute, NInt second, NInt millisecond)
	{
		NCheck(ANTimeIndexCreateTime(hour, minute, second, millisecond, &TimeIndexStart));
	}

	void GetTimeIndexend(NInt * pHour, NInt * pMinute, NInt * pSecond, NInt * pMillisecond) const
	{
		NCheck(ANTimeIndexDecodeTime(TimeIndexEnd, pHour, pMinute, pSecond, pMillisecond));
	}
	void SetTimeIndexEnd(NInt hour, NInt minute, NInt second, NInt millisecond)
	{
		NCheck(ANTimeIndexCreateTime(hour, minute, second, millisecond, &TimeIndexEnd));
	}
};

class ANAcquisitionSource : public ANAcquisitionSource_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANAcquisitionSource)

public:
	ANAcquisitionSource(ANAcquisitionSourceType acquisitionSourceType, const NStringWrapper & analogToDigital,
		const NStringWrapper & radioTransmissionFormat, const NStringWrapper & specialCharacteristics)
	{
		NCheck(ANAcquisitionSourceCreateN(acquisitionSourceType, analogToDigital.GetHandle(), radioTransmissionFormat.GetHandle(), specialCharacteristics.GetHandle(), this));
	}

	NString GetAnalogToDigital() const
	{
		return NString(hAnalogToDigital, false);
	}
	void SetAnalogToDigital(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hAnalogToDigital));
	}

	NString GetRadioTransmissionFormat() const
	{
		return NString(hRadioTransmissionFormat, false);
	}
	void SetRadioTransmissionFormat(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hRadioTransmissionFormat));
	}

	NString GetSpecialCharacteristics() const
	{
		return NString(hSpecialCharacteristics, false);
	}
	void SetSpecialCharacteristics(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hSpecialCharacteristics));
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANQualityMetric)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSubjectCondition)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANGeographicLocation)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFileFormat)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSegment)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSourceContextRepresentation)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANTimeIndex)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANAcquisitionSource)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANAsciiBinaryRecord : public ANRecord
{
	N_DECLARE_OBJECT_CLASS(ANAsciiBinaryRecord, ANRecord)

public:

	class SourceRepresentationCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANSourceContextRepresentation, ANAsciiBinaryRecord,
		ANAsciiBinaryRecordGetSourceRepresentationCount, ANAsciiBinaryRecordGetSourceRepresentation, ANAsciiBinaryRecordGetSourceRepresentations>
	{
		SourceRepresentationCollection(const ANAsciiBinaryRecord & owner)
		{
			SetOwner(owner);
		}
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANSourceContextRepresentation, ANAsciiBinaryRecord,
			ANAsciiBinaryRecordGetSourceRepresentationCount, ANAsciiBinaryRecordGetSourceRepresentation, ANAsciiBinaryRecordGetSourceRepresentations>::GetAll;

		void Set(NInt index, const ANSourceContextRepresentation & value)
		{
			NCheck(ANAsciiBinaryRecordSetSourceRepresentation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSourceContextRepresentation & value)
		{
			NInt index;
			NCheck(ANAsciiBinaryRecordAddSourceRepresentation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSourceContextRepresentation & value)
		{
			NCheck(ANAsciiBinaryRecordInsertSourceRepresentation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANAsciiBinaryRecordRemoveSourceRepresentationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANAsciiBinaryRecordClearSourceRepresentations(this->GetOwnerHandle()));
		}

		friend class ANAsciiBinaryRecord;
	};

	class AnnotationCollection : public ::Neurotec::Collections::NCollectionBase<ANAnnotation, ANAsciiBinaryRecord,
		ANAsciiBinaryRecordGetAnnotationCount, ANAsciiBinaryRecordGetAnnotation>
	{
		AnnotationCollection(const ANAsciiBinaryRecord & owner)
		{
			SetOwner(owner);
		}
	public:
		void Set(NInt index, const ANAnnotation & value)
		{
			NCheck(ANAsciiBinaryRecordSetAnnotation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANAnnotation & value)
		{
			NInt index;
			NCheck(ANAsciiBinaryRecordAddAnnotation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANAnnotation & value)
		{
			NCheck(ANAsciiBinaryRecordInsertAnnotation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANAsciiBinaryRecordRemoveAnnotationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANAsciiBinaryRecordClearAnnotations(this->GetOwnerHandle()));
		}

		friend class ANAsciiBinaryRecord;
	};

	class AssociatedContextCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANSourceContextRepresentation, ANAsciiBinaryRecord,
		ANAsciiBinaryRecordGetAssociatedContextCount, ANAsciiBinaryRecordGetAssociatedContext, ANAsciiBinaryRecordGetAssociatedContexts>
	{
		AssociatedContextCollection(const ANAsciiBinaryRecord & owner)
		{
			SetOwner(owner);
		}

		friend class ANAsciiBinaryRecord;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANSourceContextRepresentation, ANAsciiBinaryRecord,
			ANAsciiBinaryRecordGetAssociatedContextCount, ANAsciiBinaryRecordGetAssociatedContext, ANAsciiBinaryRecordGetAssociatedContexts>::GetAll;

		void Set(NInt index, const ANSourceContextRepresentation & value)
		{
			NCheck(ANAsciiBinaryRecordSetAssociatedContext(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSourceContextRepresentation & value)
		{
			NInt index;
			NCheck(ANAsciiBinaryRecordAddAssociatedContext(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSourceContextRepresentation & value)
		{
			NCheck(ANAsciiBinaryRecordInsertAssociatedContext(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANAsciiBinaryRecordRemoveAssociatedContextAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANAsciiBinaryRecordClearAssociatedContexts(this->GetOwnerHandle()));
		}
	};

	static NType ANGeographicCoordinateSystemNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANGeographicCoordinateSystem), true);
	}

	static NType ANAcquisitionSourceTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANAcquisitionSourceType), true);
	}

	static NType ANEndianCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANEndianCode), true);
	}

	NString GetSourceAgency() const
	{
		return GetString(ANAsciiBinaryRecordGetSourceAgencyN);
	}

	void SetSourceAgency(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetSourceAgencyN, value);
	}

	bool GetSubjectCondition(ANSubjectCondition * pValue) const
	{
		NBool hasValue;
		NCheck(ANAsciiBinaryRecordGetSubjectCondition(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetSubjectCondition(const ANSubjectCondition * pValue)
	{
		NCheck(ANAsciiBinaryRecordSetSubjectCondition(GetHandle(), pValue));
	}

	NString GetCaptureOrganizationName() const
	{
		return GetString(ANAsciiBinaryRecordGetCaptureOrganizationNameN);
	}
	void SetCaptureOrganizationName(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetCaptureOrganizationNameN, value);
	}

	NString GetDeviceUniqueIdentifier() const
	{
		return GetString(ANAsciiBinaryRecordGetDeviceUniqueIdentifierN);
	}

	void SetDeviceUniqueIdentifier(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetDeviceUniqueIdentifierN, value);
	}

	bool GetMakeModelSerialNumber(ANMakeModelSerialNumber * pValue) const
	{
		NBool hasValue;
		NCheck(ANAsciiBinaryRecordGetMakeModelSerialNumber(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NString GetMake() const
	{
		return GetString(ANAsciiBinaryRecordGetMakeN);
	}

	NString GetModel() const
	{
		return GetString(ANAsciiBinaryRecordGetModelN);
	}

	NString GetSerialNumber() const
	{
		return GetString(ANAsciiBinaryRecordGetSerialNumberN);
	}

	void SetMakeModelSerialNumber(const ANMakeModelSerialNumber * pValue)
	{
		NCheck(ANAsciiBinaryRecordSetMakeModelSerialNumberEx(GetHandle(), pValue));
	}

	void SetMakeModelSerialNumber(const NStringWrapper & make, const NStringWrapper & model, const NStringWrapper & serialNumber)
	{
		NCheck(ANAsciiBinaryRecordSetMakeModelSerialNumberN(GetHandle(), make.GetHandle(), model.GetHandle(), serialNumber.GetHandle()));
	}

	NDateTime GetDate() const
	{
		NDateTime_ value;
		NCheck(ANAsciiBinaryRecordGetDate(GetHandle(), &value));
		return NDateTime(value);
	}

	void SetDate(const NDateTime & value)
	{
		NCheck(ANAsciiBinaryRecordSetDate(GetHandle(), value.GetValue()));
	}

	NString GetSourceAgencyName() const
	{
		return GetString(ANAsciiBinaryRecordGetSourceAgencyNameN);
	}

	void SetSourceAgencyName(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetSourceAgencyNameN, value);
	}

	NString GetExternalFileReference() const
	{
		return GetString(ANAsciiBinaryRecordGetExternalFileReferenceN);
	}

	void SetExternalFileReference(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetExternalFileReferenceN, value);
	}

	NString GetDataHash() const
	{
		return GetString(ANAsciiBinaryRecordGetDataHashN);
	}

	void SetDataHash(const NStringWrapper & value)
	{
		SetString(ANAsciiBinaryRecordSetDataHashN, value);
	}

	bool GetGeographicLocation(ANGeographicLocation * pValue) const
	{
		NBool hasValue;
		NCheck(ANAsciiBinaryRecordGetGeographicLocation(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetGeographicLocation(const ANGeographicLocation * pValue)
	{
		NCheck(ANAsciiBinaryRecordSetGeographicLocation(GetHandle(), pValue));
	}

	AnnotationCollection GetAnnotations()
	{
		return AnnotationCollection(*this);
	}

	const AnnotationCollection GetAnnotations() const
	{
		return AnnotationCollection(*this);
	}

	SourceRepresentationCollection GetSourceRepresentations()
	{
		return SourceRepresentationCollection(*this);
	}

	const SourceRepresentationCollection GetSourceRepresentations() const
	{
		return SourceRepresentationCollection(*this);
	}

	AssociatedContextCollection GetAssociatedContexts()
	{
		return AssociatedContextCollection(*this);
	}

	const AssociatedContextCollection GetAssociatedContexts() const
	{
		return AssociatedContextCollection(*this);
	}

};

}}}

#endif // !AN_ASCII_BINARY_RECORD_HPP_INCLUDED
