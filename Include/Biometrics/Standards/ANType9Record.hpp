#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
#define AN_TYPE_9_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANAsciiRecord.hpp>
#include <Biometrics/Standards/BdifTypes.hpp>
#include <Biometrics/NFRecord.hpp>
#include <Biometrics/Standards/FMRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType9Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFPMinutiaeMethod)

namespace Neurotec { namespace Biometrics { namespace Standards
{
#undef AN_TYPE_9_RECORD_FIELD_LEN
#undef AN_TYPE_9_RECORD_FIELD_IDC

#undef AN_TYPE_9_RECORD_FIELD_IMP
#undef AN_TYPE_9_RECORD_FIELD_FMT

#undef AN_TYPE_9_RECORD_FIELD_OFR
#undef AN_TYPE_9_RECORD_FIELD_FGP
#undef AN_TYPE_9_RECORD_FIELD_FPC
#undef AN_TYPE_9_RECORD_FIELD_CRP
#undef AN_TYPE_9_RECORD_FIELD_DLT
#undef AN_TYPE_9_RECORD_FIELD_MIN
#undef AN_TYPE_9_RECORD_FIELD_RDG
#undef AN_TYPE_9_RECORD_FIELD_MRC

#undef AN_TYPE_9_RECORD_FIELD_M1_CBI
#undef AN_TYPE_9_RECORD_FIELD_M1_CEI
#undef AN_TYPE_9_RECORD_FIELD_M1_HLL
#undef AN_TYPE_9_RECORD_FIELD_M1_VLL
#undef AN_TYPE_9_RECORD_FIELD_M1_SLC
#undef AN_TYPE_9_RECORD_FIELD_M1_THPS
#undef AN_TYPE_9_RECORD_FIELD_M1_TVPS
#undef AN_TYPE_9_RECORD_FIELD_M1_FVW
#undef AN_TYPE_9_RECORD_FIELD_M1_FGP
#undef AN_TYPE_9_RECORD_FIELD_M1_FQD
#undef AN_TYPE_9_RECORD_FIELD_M1_NOM
#undef AN_TYPE_9_RECORD_FIELD_M1_FMD
#undef AN_TYPE_9_RECORD_FIELD_M1_RCI
#undef AN_TYPE_9_RECORD_FIELD_M1_CIN
#undef AN_TYPE_9_RECORD_FIELD_M1_DIN
#undef AN_TYPE_9_RECORD_FIELD_M1_ADA

#undef AN_TYPE_9_RECORD_FIELD_OOD
#undef AN_TYPE_9_RECORD_FIELD_PAG
#undef AN_TYPE_9_RECORD_FIELD_SOD
#undef AN_TYPE_9_RECORD_FIELD_DTX

#undef AN_TYPE_9_RECORD_FIELD_ULA
#undef AN_TYPE_9_RECORD_FIELD_ANN
#undef AN_TYPE_9_RECORD_FIELD_DUI
#undef AN_TYPE_9_RECORD_FIELD_MMS

#undef AN_TYPE_9_RECORD_FIELD_ALL_FROM
#undef AN_TYPE_9_RECORD_FIELD_ALL_TO

#undef AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_FROM
#undef AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_TO

#undef AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_FROM
#undef AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO
#undef AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO_V5

#undef AN_TYPE_9_RECORD_MAX_FINGERPRINT_X
#undef AN_TYPE_9_RECORD_MAX_FINGERPRINT_Y
#undef AN_TYPE_9_RECORD_MAX_PALMPRINT_X
#undef AN_TYPE_9_RECORD_MAX_PALMPRINT_Y

#undef AN_TYPE_9_RECORD_MINUTIA_QUALITY_MANUAL
#undef AN_TYPE_9_RECORD_MINUTIA_QUALITY_NOT_AVAILABLE
#undef AN_TYPE_9_RECORD_MINUTIA_QUALITY_BEST
#undef AN_TYPE_9_RECORD_MINUTIA_QUALITY_WORST

#undef AN_TYPE_9_RECORD_M1_CBEFF_FORMAT_OWNER

#undef AN_TYPE_9_RECORD_M1_MIN_LINE_LENGTH
#undef AN_TYPE_9_RECORD_M1_MAX_LINE_LENGTH

#undef AN_TYPE_9_RECORD_M1_MIN_MINUTIAE_COUNT

#undef AN_TYPE_9_RECORD_M1_MIN_RIDGE_COUNT_V50
#undef AN_TYPE_9_RECORD_M1_MAX_RIDGE_COUNT
#undef AN_TYPE_9_RECORD_M1_MAX_CORE_COUNT
#undef AN_TYPE_9_RECORD_M1_MAX_DELTA_COUNT

#undef AN_TYPE_9_RECORD_MAX_MAKE_LENGTH
#undef AN_TYPE_9_RECORD_MAX_MODEL_LENGTH
#undef AN_TYPE_9_RECORD_MAX_SERIAL_NUMBER_LENGTH

#undef AN_TYPE_9_RECORD_MIN_ULW_ANNOTATION_LENGTH
#undef AN_TYPE_9_RECORD_MAX_ULW_ANNOTATION_LENGTH

#undef AN_TYPE_9_RECORD_MAX_OFS_OWNER_LENGTH
#undef AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_NAME_LENGTH
#undef AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_VERSION_LENGTH
#undef AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_NAME_LENGTH
#undef AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_VERSION_LENGTH
#undef AN_TYPE_9_RECORD_MAX_OFS_CONTACT_INFORMATION_LENGTH

#undef AN_TYPE_9_RECORD_M1_SKIP_RIDGE_COUNTS
#undef AN_TYPE_9_RECORD_M1_SKIP_SINGULAR_POINTS
#undef AN_TYPE_9_RECORD_M1_SKIP_NEUROTEC_FIELDS

#undef AN_TYPE_9_RECORD_OFS_NEUROTEC_OWNER

const NInt AN_TYPE_9_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_9_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_9_RECORD_FIELD_IMP = 3;
const NInt AN_TYPE_9_RECORD_FIELD_FMT = 4;

const NInt AN_TYPE_9_RECORD_FIELD_OFR = 5;
const NInt AN_TYPE_9_RECORD_FIELD_FGP = 6;
const NInt AN_TYPE_9_RECORD_FIELD_FPC = 7;
const NInt AN_TYPE_9_RECORD_FIELD_CRP = 8;
const NInt AN_TYPE_9_RECORD_FIELD_DLT = 9;
const NInt AN_TYPE_9_RECORD_FIELD_MIN = 10;
const NInt AN_TYPE_9_RECORD_FIELD_RDG = 11;
const NInt AN_TYPE_9_RECORD_FIELD_MRC = 12;

const NInt AN_TYPE_9_RECORD_FIELD_M1_CBI = 126;
const NInt AN_TYPE_9_RECORD_FIELD_M1_CEI = 127;
const NInt AN_TYPE_9_RECORD_FIELD_M1_HLL = 128;
const NInt AN_TYPE_9_RECORD_FIELD_M1_VLL = 129;
const NInt AN_TYPE_9_RECORD_FIELD_M1_SLC = 130;
const NInt AN_TYPE_9_RECORD_FIELD_M1_THPS = 131;
const NInt AN_TYPE_9_RECORD_FIELD_M1_TVPS = 132;
const NInt AN_TYPE_9_RECORD_FIELD_M1_FVW = 133;
const NInt AN_TYPE_9_RECORD_FIELD_M1_FGP = 134;
const NInt AN_TYPE_9_RECORD_FIELD_M1_FQD = 135;
const NInt AN_TYPE_9_RECORD_FIELD_M1_NOM = 136;
const NInt AN_TYPE_9_RECORD_FIELD_M1_FMD = 137;
const NInt AN_TYPE_9_RECORD_FIELD_M1_RCI = 138;
const NInt AN_TYPE_9_RECORD_FIELD_M1_CIN = 139;
const NInt AN_TYPE_9_RECORD_FIELD_M1_DIN = 140;
const NInt AN_TYPE_9_RECORD_FIELD_M1_ADA = 141;

const NInt AN_TYPE_9_RECORD_FIELD_OOD = 176;
const NInt AN_TYPE_9_RECORD_FIELD_PAG = 177;
const NInt AN_TYPE_9_RECORD_FIELD_SOD = 178;
const NInt AN_TYPE_9_RECORD_FIELD_DTX = 179;

const NInt AN_TYPE_9_RECORD_FIELD_ULA = 901;
const NInt AN_TYPE_9_RECORD_FIELD_ANN = 902;
const NInt AN_TYPE_9_RECORD_FIELD_DUI = 903;
const NInt AN_TYPE_9_RECORD_FIELD_MMS = 904;

const NInt AN_TYPE_9_RECORD_FIELD_ALL_FROM = AN_TYPE_9_RECORD_FIELD_LEN;
const NInt AN_TYPE_9_RECORD_FIELD_ALL_TO = AN_TYPE_9_RECORD_FIELD_FMT;

const NInt AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_FROM = AN_TYPE_9_RECORD_FIELD_OFR;
const NInt AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_TO = AN_TYPE_9_RECORD_FIELD_MRC;

const NInt AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_FROM = (AN_TYPE_9_RECORD_FIELD_MRC + 1);
const NInt AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO = AN_ASCII_RECORD_MAX_FIELD_NUMBER;
const NInt AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO_V5 = 225;

const NUShort AN_TYPE_9_RECORD_MAX_FINGERPRINT_X = 4999;
const NUShort AN_TYPE_9_RECORD_MAX_FINGERPRINT_Y = 4999;
const NUInt AN_TYPE_9_RECORD_MAX_PALMPRINT_X = 13999;
const NUInt AN_TYPE_9_RECORD_MAX_PALMPRINT_Y = 20999;

const NByte AN_TYPE_9_RECORD_MINUTIA_QUALITY_MANUAL = 0;
const NByte AN_TYPE_9_RECORD_MINUTIA_QUALITY_NOT_AVAILABLE = 1;
const NByte AN_TYPE_9_RECORD_MINUTIA_QUALITY_BEST = 2;
const NByte AN_TYPE_9_RECORD_MINUTIA_QUALITY_WORST = 63;

const NUShort AN_TYPE_9_RECORD_M1_MIN_LINE_LENGTH = 10;
const NUShort AN_TYPE_9_RECORD_M1_MAX_LINE_LENGTH = 65535;

const NByte AN_TYPE_9_RECORD_M1_MIN_MINUTIAE_COUNT = 1;

const NByte AN_TYPE_9_RECORD_M1_MIN_RIDGE_COUNT_V50 = 1;
const NByte AN_TYPE_9_RECORD_M1_MAX_RIDGE_COUNT = 99;
const NByte AN_TYPE_9_RECORD_M1_MAX_CORE_COUNT = 9;
const NByte AN_TYPE_9_RECORD_M1_MAX_DELTA_COUNT = 9;

const NInt AN_TYPE_9_RECORD_MAX_MAKE_LENGTH          = AN_RECORD_MAX_MAKE_LENGTH;
const NInt AN_TYPE_9_RECORD_MAX_MODEL_LENGTH         = AN_RECORD_MAX_MODEL_LENGTH;
const NInt AN_TYPE_9_RECORD_MAX_SERIAL_NUMBER_LENGTH = AN_RECORD_MAX_SERIAL_NUMBER_LENGTH;

const NUShort AN_TYPE_9_RECORD_MIN_ULW_ANNOTATION_LENGTH = 22;
const NUShort AN_TYPE_9_RECORD_MAX_ULW_ANNOTATION_LENGTH = 300;

const NUShort AN_TYPE_9_RECORD_MAX_OFS_OWNER_LENGTH = 40;
const NUShort AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_NAME_LENGTH = 100;
const NUShort AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_VERSION_LENGTH = 100;
const NUShort AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_NAME_LENGTH = 100;
const NUShort AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_VERSION_LENGTH = 100;
const NUShort AN_TYPE_9_RECORD_MAX_OFS_CONTACT_INFORMATION_LENGTH = 1000;

const NChar AN_TYPE_9_RECORD_OFS_NEUROTEC_OWNER[] = N_T("Neurotechnology");

const NUInt AN_TYPE_9_RECORD_M1_SKIP_RIDGE_COUNTS = FMRFV_SKIP_RIDGE_COUNTS;
const NUInt AN_TYPE_9_RECORD_M1_SKIP_SINGULAR_POINTS = FMRFV_SKIP_SINGULAR_POINTS;
const NUInt AN_TYPE_9_RECORD_M1_SKIP_NEUROTEC_FIELDS = FMRFV_SKIP_NEUROTEC_FIELDS;

class ANOfrs : public ANOfrs_
{
	N_DECLARE_DISPOSABLE_STRUCT_CLASS(ANOfrs)

public:
	ANOfrs(const NStringWrapper & name, ANFPMinutiaeMethod method, const NStringWrapper & equipment)
	{
		NCheck(ANOfrsCreateN(name.GetHandle(), method, equipment.GetHandle(), this));
	}

	NString GetName() const
	{
		return NString(hName, false);
	}

	void SetName(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hName));
	}

	NString GetEquipment() const
	{
		return NString(hEquipment, false);
	}

	void SetEquipment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hEquipment));
	}
};

class ANFPatternClass : public ANFPatternClass_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANFPatternClass)

public:
	ANFPatternClass(BdifFPatternClass value, const NStringWrapper & vendorValue)
	{
		NCheck(ANFPatternClassCreateN(value, vendorValue.GetHandle(), this));
	}

	NString GetVendorValue() const
	{
		return NString(hVendorValue, false);
	}

	void SetVendorValue(const NStringWrapper & nStringWrapper)
	{
		NCheck(NStringSet(nStringWrapper.GetHandle(), &hVendorValue));
	}
};

class ANFCore : public ANFCore_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANFCore)

public:
	ANFCore(NUShort x, NUShort y)
	{
		X = x;
		Y = y;
	}
};

class ANFDelta : public ANFDelta_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANFDelta)

public:
	ANFDelta(NUShort x, NUShort y)
	{
		X = x;
		Y = y;
	}
};

class ANFPMinutia : public ANFPMinutia_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANFPMinutia)

public:
	ANFPMinutia(NUInt x, NUInt y, NUShort theta, NByte quality, BdifFPMinutiaType type)
	{
		X = x;
		Y = y;
		Theta = theta;
		Quality = quality;
		Type = type;
	}
};

class ANUlwAnnotation : public ANUlwAnnotation_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANUlwAnnotation)

public:
	ANUlwAnnotation(const NDateTime & dateTime, const NStringWrapper & text)
	{
		NCheck(ANUlwAnnotationCreateN(dateTime.GetValue(), text.GetHandle(), this));
	}

	NDateTime GetDateTime() const
	{
		return NDateTime(dateTime);
	}

	void SetDateTime(const NDateTime & value)
	{
		dateTime = value.GetValue();
	}

	NString GetText() const
	{
		return NString(hText, false);
	}

	void SetText(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hText));
	}
};

}}}

N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANOfrs)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFPatternClass)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANUlwAnnotation)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFCore)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFDelta)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFPMinutia)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType9Record : public ANAsciiRecord
{
	N_DECLARE_OBJECT_CLASS(ANType9Record, ANAsciiRecord)

public:
	class PositionCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFPPosition, ANType9Record,
		ANType9RecordGetPositionCount, ANType9RecordGetPosition, ANType9RecordGetPositions>
	{
		PositionCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFPPosition, ANType9Record,
			ANType9RecordGetPositionCount, ANType9RecordGetPosition, ANType9RecordGetPositions>::GetAll;

		void Set(NInt index, BdifFPPosition value)
		{
			NCheck(ANType9RecordSetPosition(this->GetOwnerHandle(), index, value));
		}

		NInt Add(BdifFPPosition value)
		{
			NInt index;
			NCheck(ANType9RecordAddPositionEx(this->GetOwnerHandle(), value, &index));
			return index;
		}

		void Insert(NInt index, BdifFPPosition value)
		{
			NCheck(ANType9RecordInsertPosition(this->GetOwnerHandle(), index, value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemovePositionAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearPositions(this->GetOwnerHandle()));
		}
	};

	class PatternClassCollection : public ::Neurotec::Collections::NCollectionBase<ANFPatternClass, ANType9Record,
		ANType9RecordGetPatternClassCount, ANType9RecordGetPatternClass>
	{
		PatternClassCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		void Set(NInt index, const ANFPatternClass & value)
		{
			NCheck(ANType9RecordSetPatternClass(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFPatternClass & value)
		{
			NInt index;
			NCheck(ANType9RecordAddPatternClassEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFPatternClass & value)
		{
			NCheck(ANType9RecordInsertPatternClass(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemovePatternClassAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearPatternClasses(this->GetOwnerHandle()));
		}
	};

	class CoreCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFCore, ANType9Record,
		ANType9RecordGetCoreCount, ANType9RecordGetCore, ANType9RecordGetCores>
	{
		CoreCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFCore, ANType9Record,
			ANType9RecordGetCoreCount, ANType9RecordGetCore, ANType9RecordGetCores>::GetAll;

		void Set(NInt index, const ANFCore & value)
		{
			NCheck(ANType9RecordSetCore(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFCore & value)
		{
			NInt index;
			NCheck(ANType9RecordAddCoreEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFCore & value)
		{
			NCheck(ANType9RecordInsertCore(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemoveCoreAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearCores(this->GetOwnerHandle()));
		}
	};

	class DeltaCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFDelta, ANType9Record,
		ANType9RecordGetDeltaCount, ANType9RecordGetDelta, ANType9RecordGetDeltas>
	{
		DeltaCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFDelta, ANType9Record,
			ANType9RecordGetDeltaCount, ANType9RecordGetDelta, ANType9RecordGetDeltas>::GetAll;

		void Set(NInt index, const ANFDelta & value)
		{
			NCheck(ANType9RecordSetDelta(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFDelta & value)
		{
			NInt index;
			NCheck(ANType9RecordAddDeltaEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFDelta & value)
		{
			NCheck(ANType9RecordInsertDelta(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemoveDeltaAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearDeltas(this->GetOwnerHandle()));
		}
	};

	class MinutiaCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPMinutia, ANType9Record,
		ANType9RecordGetMinutiaCount, ANType9RecordGetMinutia, ANType9RecordGetMinutiae>
	{
		MinutiaCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPMinutia, ANType9Record,
			ANType9RecordGetMinutiaCount, ANType9RecordGetMinutia, ANType9RecordGetMinutiae>::GetAll;

		void Set(NInt index, const ANFPMinutia & value)
		{
			NCheck(ANType9RecordSetMinutia(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFPMinutia & value)
		{
			NInt index;
			NCheck(ANType9RecordAddMinutiaEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFPMinutia & value)
		{
			NCheck(ANType9RecordInsertMinutia(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemoveMinutiaAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearMinutiae(this->GetOwnerHandle()));
		}
	};

	class MinutiaNeighborsCollection : public ::Neurotec::NObjectPartBase<ANType9Record>
	{
		MinutiaNeighborsCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType9RecordGetMinutiaNeighborCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, BdifFPMinutiaNeighbor * pValue) const
		{
			NCheck(ANType9RecordGetMinutiaNeighbor(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		BdifFPMinutiaNeighbor Get(NInt baseIndex, NInt index) const
		{
			BdifFPMinutiaNeighbor value;
			NCheck(ANType9RecordGetMinutiaNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper<BdifFPMinutiaNeighbor> GetAll(NInt baseIndex) const
		{
			BdifFPMinutiaNeighbor::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType9RecordGetMinutiaNeighbors(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper<BdifFPMinutiaNeighbor>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const BdifFPMinutiaNeighbor & value)
		{
			NCheck(ANType9RecordSetMinutiaNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const BdifFPMinutiaNeighbor & value)
		{
			NInt index;
			NCheck(ANType9RecordAddMinutiaNeighborEx(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const BdifFPMinutiaNeighbor & value)
		{
			NCheck(ANType9RecordInsertMinutiaNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType9RecordRemoveMinutiaNeighborAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType9RecordClearMinutiaNeighbors(this->GetOwnerHandle(), baseIndex));
		}
	};

	class UlwAnnotationCollection : public ::Neurotec::Collections::NCollectionBase<ANUlwAnnotation, ANType9Record,
		ANType9RecordGetUlwAnnotationCount, ANType9RecordGetUlwAnnotation>
	{
		UlwAnnotationCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		void Set(NInt index, const ANUlwAnnotation & value)
		{
			NCheck(ANType9RecordSetUlwAnnotation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANUlwAnnotation & value)
		{
			NInt index;
			NCheck(ANType9RecordAddUlwAnnotation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANUlwAnnotation & value)
		{
			NCheck(ANType9RecordInsertUlwAnnotation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemoveUlwAnnotationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearUlwAnnotations(this->GetOwnerHandle()));
		}
	};

	class AnnotationCollection : public ::Neurotec::Collections::NCollectionBase<ANAnnotation, ANType9Record,
		ANType9RecordGetAnnotationCount, ANType9RecordGetAnnotation>
	{
		AnnotationCollection(const ANType9Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType9Record;
	public:
		void Set(NInt index, const ANAnnotation & value)
		{
			NCheck(ANType9RecordSetAnnotation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANAnnotation & value)
		{
			NInt index;
			NCheck(ANType9RecordAddAnnotation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANAnnotation & value)
		{
			NCheck(ANType9RecordInsertAnnotation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType9RecordRemoveAnnotationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType9RecordClearAnnotations(this->GetOwnerHandle()));
		}
	};
private:


public:
	static NType ANFPMinutiaeMethodNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANFPMinutiaeMethod), true);
	}

	NFRecord ToNFRecord(NUInt flags = 0) const
	{
		HNFRecord hNFRecord;
		NCheck(ANType9RecordToNFRecord(GetHandle(), flags, &hNFRecord));
		return FromHandle<NFRecord>(hNFRecord);
	}

	BdifFPImpressionType GetImpressionType() const
	{
		BdifFPImpressionType value;
		NCheck(ANType9RecordGetImpressionType(GetHandle(), &value));
		return value;
	}

	void SetImpressionType(BdifFPImpressionType value)
	{
		NCheck(ANType9RecordSetImpressionType(GetHandle(), value));
	}

	bool GetMinutiaeFormat() const
	{
		NBool value;
		NCheck(ANType9RecordGetMinutiaeFormat(GetHandle(), &value));
		return value != 0;
	}

	void SetMinutiaeFormat(NBool value)
	{
		NCheck(ANType9RecordSetMinutiaeFormat(GetHandle(), value));
	}

	bool GetHasMinutiae() const
	{
		NBool value;
		NCheck(ANType9RecordHasMinutiae(GetHandle(), &value));
		return value != 0;
	}

	void SetHasMinutiae(bool value)
	{
		NCheck(ANType9RecordSetHasMinutiae(GetHandle(), value ? NTrue : NFalse));
	}

	bool GetHasMinutiaeRidgeCounts() const
	{
		NBool value;
		NCheck(ANType9RecordHasMinutiaeRidgeCounts(GetHandle(), &value));
		return value != 0;
	}

	bool GetHasMinutiaeRidgeCountsIndicator() const
	{
		NBool value;
		NCheck(ANType9RecordHasMinutiaeRidgeCountsIndicator(GetHandle(), &value));
		return value != 0;
	}

	void SetHasMinutiaeRidgeCounts(bool hasMinutiaeRidgeCountsIndicator, bool rdg)
	{
		NCheck(ANType9RecordSetHasMinutiaeRidgeCounts(GetHandle(), hasMinutiaeRidgeCountsIndicator ? NTrue : NFalse, rdg ? NTrue : NFalse));
	}

	bool GetOfrs(ANOfrs * pValue) const
	{
		NBool hasValue;
		NCheck(ANType9RecordGetOfrs(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NString GetOfrsName() const
	{
		return GetString(ANType9RecordGetOfrsNameN);
	}

	ANFPMinutiaeMethod GetOfrsMethod() const
	{
		ANFPMinutiaeMethod value;
		NCheck(ANType9RecordGetOfrsMethod(GetHandle(), &value));
		return value;
	}

	NString GetOfrsEquipment() const
	{
		return GetString(ANType9RecordGetOfrsEquipmentN);
	}

	void SetOfrs(const ANOfrs * pValue)
	{
		NCheck(ANType9RecordSetOfrsEx(GetHandle(), pValue));
	}

	void SetOfrs(const NStringWrapper & name, ANFPMinutiaeMethod method, const NStringWrapper & equipment)
	{
		NCheck(ANType9RecordSetOfrsN(GetHandle(), name.GetHandle(), method, equipment.GetHandle()));
	}

	bool GetMakeModelSerialNumber(ANMakeModelSerialNumber * pValue) const
	{
		NBool hasValue;
		NCheck(ANType9RecordGetMakeModelSerialNumber(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NString GetMake() const
	{
		return GetString(ANType9RecordGetMakeN);
	}

	NString GetModel() const
	{
		return GetString(ANType9RecordGetModelN);
	}

	NString GetSerialNumber() const
	{
		return GetString(ANType9RecordGetSerialNumberN);
	}

	void SetMakeModelSerialNumber(const ANMakeModelSerialNumber * pValue)
	{
		NCheck(ANType9RecordSetMakeModelSerialNumberEx(GetHandle(), pValue));
	}

	void SetMakeModelSerialNumber(const NStringWrapper & make, const NStringWrapper & model, const NStringWrapper & serialNumber)
	{
		NCheck(ANType9RecordSetMakeModelSerialNumberN(GetHandle(), make.GetHandle(), model.GetHandle(), serialNumber.GetHandle()));
	}

	NString GetDeviceUniqueIdentifier() const
	{
		return GetString(ANType9RecordGetDeviceUniqueIdentifierN);
	}

	void SetDeviceUniqueIdentifier(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetDeviceUniqueIdentifierN, value);
	}

	void SetFMRecord(FMRecord & value, NByte fmrFingerViewIndex, NUInt flags = 0)
	{
		NCheck(ANType9RecordSetFmRecord(GetHandle(), value.GetHandle(), fmrFingerViewIndex, flags));
	}

	::Neurotec::IO::NBuffer GetFMRecordBuffer()
	{
		return GetObject<HandleType, ::Neurotec::IO::NBuffer>(ANType9RecordGetFmRecordBufferN, true);
	}

	bool GetHasOtherFeatureSets() const
	{
		NBool value;
		NCheck(ANType9RecordHasOtherFeatureSets(GetHandle(), &value));
		return value != 0;
	}
	void SetHasOtherFeatureSets(bool value)
	{
		NCheck(ANType9RecordSetHasOtherFeatureSets(GetHandle(), value ? NTrue : NFalse));
	}

	NString GetOfsOwner() const
	{
		return GetString(ANType9RecordGetOfsOwnerN);
	}
	void SetOfsOwner(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsOwnerN, value);
	}

	NString GetOfsProcessingAlgorithmName() const
	{
		return GetString(ANType9RecordGetOfsProcessingAlgorithmNameN);
	}
	void SetOfsProcessingAlgorithmName(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsProcessingAlgorithmNameN, value);
	}

	NString GetOfsProcessingAlgorithmVersion() const
	{
		return GetString(ANType9RecordGetOfsProcessingAlgorithmVersionN);
	}
	void SetOfsProcessingAlgorithmVersion(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsProcessingAlgorithmVersionN, value);
	}

	NString GetOfsSystemName() const
	{
		return GetString(ANType9RecordGetOfsSystemNameN);
	}
	void SetOfsSystemName(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsSystemNameN, value);
	}

	NString GetOfsSystemVersion() const
	{
		return GetString(ANType9RecordGetOfsSystemVersionN);
	}
	void SetOfsSystemVersion(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsSystemVersionN, value);
	}

	NString GetOfsContactInformation() const
	{
		return GetString(ANType9RecordGetOfsContactInformationN);
	}
	void SetOfsContactInformation(const NStringWrapper & value)
	{
		SetString(ANType9RecordSetOfsContactInformationN, value);
	}

	PositionCollection GetPositions()
	{
		return PositionCollection(*this);
	}

	const PositionCollection GetPositions() const
	{
		return PositionCollection(*this);
	}

	PatternClassCollection GetPatternClasses()
	{
		return PatternClassCollection(*this);
	}

	const PatternClassCollection GetPatternClasses() const
	{
		return PatternClassCollection(*this);
	}

	CoreCollection GetCores()
	{
		return CoreCollection(*this);
	}

	const CoreCollection GetCores() const
	{
		return CoreCollection(*this);
	}

	DeltaCollection GetDeltas()
	{
		return DeltaCollection(*this);
	}

	const DeltaCollection GetDeltas() const
	{
		return DeltaCollection(*this);
	}

	MinutiaCollection GetMinutiae()
	{
		return MinutiaCollection(*this);
	}

	const MinutiaCollection GetMinutiae() const
	{
		return MinutiaCollection(*this);
	}

	MinutiaNeighborsCollection GetMinutiaeNeighbors()
	{
		return MinutiaNeighborsCollection(*this);
	}

	const MinutiaNeighborsCollection GetMinutiaeNeighbors() const
	{
		return MinutiaNeighborsCollection(*this);
	}

	UlwAnnotationCollection GetUlwAnnotations()
	{
		return UlwAnnotationCollection(*this);
	}

	const UlwAnnotationCollection GetUlwAnnotations() const
	{
		return UlwAnnotationCollection(*this);
	}

	AnnotationCollection GetAnnotations()
	{
		return AnnotationCollection(*this);
	}

	const AnnotationCollection GetAnnotations() const
	{
		return AnnotationCollection(*this);
	}
};

}}}

#endif // !AN_TYPE_9_RECORD_HPP_INCLUDED
