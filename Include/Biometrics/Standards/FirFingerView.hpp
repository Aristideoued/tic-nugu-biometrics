#ifndef FIR_FINGER_VIEW_HPP_INCLUDED
#define FIR_FINGER_VIEW_HPP_INCLUDED

#include <Biometrics/Standards/BdifTypes.hpp>
#include <Images/NImage.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Images::HNImage;
using ::Neurotec::Geometry::NPoint;
#include <Biometrics/Standards/FirFingerView.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{
class FirFingerViewSegmentation;

class FirFingerViewSegment : public NObject
{
	N_DECLARE_OBJECT_CLASS(FirFingerViewSegment, NObject)
public:
	class CoordinateCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, FirFingerViewSegment,
		FirFingerViewSegmentGetCoordinateCount, FirFingerViewSegmentGetCoordinate, FirFingerViewSegmentGetCoordinates>
	{
		CoordinateCollection(const FirFingerViewSegment & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerViewSegment;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewSegmentGetCoordinateCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSegmentSetCoordinateCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(FirFingerViewSegmentSetCoordinate(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(FirFingerViewSegmentAddCoordinate(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(FirFingerViewSegmentInsertCoordinate(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewSegmentRemoveCoordinateAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewSegmentClearCoordinates(this->GetOwnerHandle()));
		}
	};

private:
	static HFirFingerViewSegment Create()
	{
		HFirFingerViewSegment handle;
		NCheck(FirFingerViewSegmentCreate(&handle));
		return handle;
	}

public:
	FirFingerViewSegment()
		: NObject(Create(), true)
	{
	}

	BdifFPPosition GetFingerPosition() const
	{
		BdifFPPosition value;
		NCheck(FirFingerViewSegmentGetFingerPosition(GetHandle(), &value));
		return value;
	}

	void SetFingerPosition(BdifFPPosition value)
	{
		NCheck(FirFingerViewSegmentSetFingerPosition(GetHandle(), value));
	}

	NByte GetFingerQuality() const
	{
		NByte value;
		NCheck(FirFingerViewSegmentGetFingerQuality(GetHandle(), &value));
		return value;
	}

	void SetFingerQuality(NByte value)
	{
		NCheck(FirFingerViewSegmentSetFingerQuality(GetHandle(), value));
	}

	NUShort GetFingerQualityAlgorithmOwnerId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentGetFingerQualityAlgorithmOwnerId(GetHandle(), &value));
		return value;
	}

	void SetFingerQualityAlgorithmOwnerId(NUShort value)
	{
		NCheck(FirFingerViewSegmentSetFingerQualityAlgorithmOwnerId(GetHandle(), value));
	}

	NUShort GetFingerQualityAlgorithmId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentGetFingerQualityAlgorithmId(GetHandle(), &value));
		return value;
	}

	void SetFingerQualityAlgorithmId(NUShort value)
	{
		NCheck(FirFingerViewSegmentSetFingerQualityAlgorithmId(GetHandle(), value));
	}

	NByte GetFingerOrientation() const
	{
		NByte value;
		NCheck(FirFingerViewSegmentGetFingerOrientation(GetHandle(), &value));
		return value;
	}

	void SetFingerOrientation(NByte value)
	{
		NCheck(FirFingerViewSegmentSetFingerOrientation(GetHandle(), value));
	}

	CoordinateCollection GetCoordinates()
	{
		return CoordinateCollection(*this);
	}

	const CoordinateCollection GetCoordinates() const
	{
		return CoordinateCollection(*this);
	}

	FirFingerViewSegmentation GetOwner() const;
};

}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{
class FirFingerView;

class FirFingerViewSegmentation : public NObject
{
	N_DECLARE_OBJECT_CLASS(FirFingerViewSegmentation, NObject)
public:
	class FingerSegmentCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<FirFingerViewSegment, FirFingerViewSegmentation,
		FirFingerViewSegmentationGetFingerSegmentCount, FirFingerViewSegmentationGetFingerSegment, FirFingerViewSegmentationGetFingerSegments>
	{
		FingerSegmentCollection(const FirFingerViewSegmentation & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerViewSegmentation;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewSegmentationGetFingerSegmentCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSegmentationSetFingerSegmentCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const FirFingerViewSegment & value)
		{
			NCheck(FirFingerViewSegmentationSetFingerSegment(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		FirFingerViewSegment Add()
		{
			HFirFingerViewSegment hSegment;
			NCheck(FirFingerViewSegmentationAddFingerSegmentEx(this->GetOwnerHandle(), &hSegment));
			return FromHandle<FirFingerViewSegment>(hSegment);
		}

		FirFingerViewSegment Insert(NInt index)
		{
			HFirFingerViewSegment hSegment;
			NCheck(FirFingerViewSegmentationInsertFingerSegmentEx(this->GetOwnerHandle(), index, &hSegment));
			return FromHandle<FirFingerViewSegment>(hSegment);
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewSegmentationRemoveFingerSegmentAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewSegmentationClearFingerSegments(this->GetOwnerHandle()));
		}
	};

	BdifFPSegmentationStatus GetStatus() const
	{
		BdifFPSegmentationStatus value;
		NCheck(FirFingerViewSegmentationGetStatus(GetHandle(), &value));
		return value;
	}

	void SetStatus(BdifFPSegmentationStatus value)
	{
		NCheck(FirFingerViewSegmentationSetStatus(GetHandle(), value));
	}

	NUShort GetAlgorithmOwnerId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentationGetAlgorithmOwnerId(GetHandle(), &value));
		return value;
	}

	void SetAlgorithmOwnerId(NUShort value)
	{
		NCheck(FirFingerViewSegmentationSetAlgorithmOwnerId(GetHandle(), value));
	}

	NUShort GetAlgorithmId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentationGetAlgorithmId(GetHandle(), &value));
		return value;
	}

	void SetAlgorithmId(NUShort value)
	{
		NCheck(FirFingerViewSegmentationSetAlgorithmId(GetHandle(), value));
	}
	
	NByte GetAlgorithmQuality() const
	{
		NByte value;
		NCheck(FirFingerViewSegmentationGetAlgorithmQuality(GetHandle(), &value));
		return value;
	}

	void SetAlgorithmQuality(NByte value)
	{
		NCheck(FirFingerViewSegmentationSetAlgorithmQuality(GetHandle(), value));
	}

	NUShort GetFingerImageQualityAlgorithmOwnerId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentationGetFingerImageQualityAlgorithmOwnerId(GetHandle(), &value));
		return value;
	}

	void SetFingerImageQualityAlgorithmOwnerId(NUShort value)
	{
		NCheck(FirFingerViewSegmentationSetFingerImageQualityAlgorithmOwnerId(GetHandle(), value));
	}

	NUShort GetFingerImageQualityAlgorithmId() const
	{
		NUShort value;
		NCheck(FirFingerViewSegmentationGetFingerImageQualityAlgorithmId(GetHandle(), &value));
		return value;
	}

	void SetFingerImageQualityAlgorithmId(NUShort value)
	{
		NCheck(FirFingerViewSegmentationSetFingerImageQualityAlgorithmId(GetHandle(), value));
	}

	FingerSegmentCollection GetFingerSegments()
	{
		return FingerSegmentCollection(*this);
	}

	const FingerSegmentCollection GetFingerSegments() const
	{
		return FingerSegmentCollection(*this);
	}

	FirFingerView GetOwner() const;
};
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{
class FIRecord;

class FirFingerView : public NObject
{
	N_DECLARE_OBJECT_CLASS(FirFingerView, NObject)
public:
	class QualityBlockCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifQualityBlock, FirFingerView,
		FirFingerViewGetQualityBlockCount, FirFingerViewGetQualityBlock, FirFingerViewGetQualityBlocks>
	{
		QualityBlockCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetQualityBlockCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetQualityBlockCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifQualityBlock & value)
		{
			NCheck(FirFingerViewSetQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifQualityBlock & value)
		{
			NInt index;
			NCheck(FirFingerViewAddQualityBlock(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifQualityBlock & value)
		{
			NCheck(FirFingerViewInsertQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveQualityBlockAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearQualityBlocks(this->GetOwnerHandle()));
		}
	};

	class CertificationBlockCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifCertificationBlock, FirFingerView,
		FirFingerViewGetCertificationBlockCount, FirFingerViewGetCertificationBlock, FirFingerViewGetCertificationBlocks>
	{
		CertificationBlockCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetCertificationBlockCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetCertificationBlockCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifCertificationBlock & value)
		{
			NCheck(FirFingerViewSetCertificationBlock(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifCertificationBlock & value)
		{
			NInt index;
			NCheck(FirFingerViewAddCertificationBlock(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifCertificationBlock & value)
		{
			NCheck(FirFingerViewInsertCertificationBlock(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveCertificationBlockAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearCertificationBlocks(this->GetOwnerHandle()));
		}
	};

	class SegmentationCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<FirFingerViewSegmentation, FirFingerView,
		FirFingerViewGetSegmentationCount, FirFingerViewGetSegmentation, FirFingerViewGetSegmentations>
	{
		SegmentationCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetSegmentationCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetSegmentationCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const FirFingerViewSegmentation & value)
		{
			NCheck(FirFingerViewSetSegmentation(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		FirFingerViewSegmentation Add()
		{
			HFirFingerViewSegmentation hSegmentation;
			NCheck(FirFingerViewAddSegmentation(this->GetOwnerHandle(), &hSegmentation));
			return FromHandle<FirFingerViewSegmentation>(hSegmentation);
		}
		FirFingerViewSegmentation Insert(NInt index)
		{
			HFirFingerViewSegmentation hSegmentation;
			NCheck(FirFingerViewInsertSegmentation(this->GetOwnerHandle(), index, &hSegmentation));
			return FromHandle<FirFingerViewSegmentation>(hSegmentation);
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveSegmentationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearSegmentations(this->GetOwnerHandle()));
		}
	};

	class AnnotationCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFPAnnotation, FirFingerView,
		FirFingerViewGetAnnotationCount, FirFingerViewGetAnnotation, FirFingerViewGetAnnotations>
	{
		AnnotationCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetAnnotationCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetAnnotationCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifFPAnnotation & value)
		{
			NCheck(FirFingerViewSetAnnotation(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifFPAnnotation & value)
		{
			NInt index;
			NCheck(FirFingerViewAddAnnotation(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifFPAnnotation & value)
		{
			NCheck(FirFingerViewInsertAnnotation(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveAnnotationAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearAnnotations(this->GetOwnerHandle()));
		}
	};

	class CommentCollection : public ::Neurotec::Collections::NCollectionBase<NString, FirFingerView,
		FirFingerViewGetCommentCount, FirFingerViewGetCommentEx>
	{
		CommentCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetCommentCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetCommentCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(FirFingerViewSetCommentExN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(FirFingerViewAddComment(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(FirFingerViewInsertComment(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveCommentAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearComments(this->GetOwnerHandle()));
		}

		void RemoveRange(NInt index, NInt count)
		{
			NCheck(FirFingerViewRemoveCommentRange(this->GetOwnerHandle(), index, count));
		}
	};

	class VendorExtendedDataCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFPExtendedData, FirFingerView,
		FirFingerViewGetVendorExtendedDataCount, FirFingerViewGetVendorExtendedData, FirFingerViewGetVendorExtendedDatas>
	{
		VendorExtendedDataCollection(const FirFingerView & owner)
		{
			SetOwner(owner);
		}

		friend class FirFingerView;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FirFingerViewGetVendorExtendedDataCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FirFingerViewSetVendorExtendedDataCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifFPExtendedData & value)
		{
			NCheck(FirFingerViewSetVendorExtendedData(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifFPExtendedData & value)
		{
			NInt index;
			NCheck(FirFingerViewAddVendorExtendedData(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifFPExtendedData & value)
		{
			NCheck(FirFingerViewInsertVendorExtendedData(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FirFingerViewRemoveVendorExtendedDataAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FirFingerViewClearVendorExtendedData(this->GetOwnerHandle()));
		}
	};

public:


	::Neurotec::Images::NImage ToNImage(NUInt flags = 0) const
	{
		HNImage hImage;
		NCheck(FirFingerViewToNImage(GetHandle(), flags, &hImage));
		return FromHandle< ::Neurotec::Images::NImage>(hImage);
	}

	void SetImage(const ::Neurotec::Images::NImage & image, NUInt flags = 0)
	{
		NCheck(FirFingerViewSetImage(GetHandle(), flags, image.GetHandle()));
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(FirFingerViewGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(FirFingerViewGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	BdifCaptureDateTime GetCaptureDateAndTime() const
	{
		BdifCaptureDateTime_ value;
		NCheck(FirFingerViewGetCaptureDateAndTime(GetHandle(), &value));
		return BdifCaptureDateTime(value);
	}

	void SetCaptureDateAndTime(const BdifCaptureDateTime & value)
	{
		NCheck(FirFingerViewSetCaptureDateAndTime(GetHandle(), value));
	}

	BdifFPCaptureDeviceTechnology GetCaptureDeviceTechnology() const
	{
		BdifFPCaptureDeviceTechnology value;
		NCheck(FirFingerViewGetCaptureDeviceTechnology(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceTechnology(BdifFPCaptureDeviceTechnology value)
	{
		NCheck(FirFingerViewSetCaptureDeviceTechnology(GetHandle(), value));
	}

	NUShort GetCaptureDeviceVendorId() const
	{
		NUShort value;
		NCheck(FirFingerViewGetCaptureDeviceVendorId(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceVendorId(NUShort value)
	{
		NCheck(FirFingerViewSetCaptureDeviceVendorId(GetHandle(), value));
	}

	NUShort GetCaptureDeviceTypeId() const
	{
		NUShort value;
		NCheck(FirFingerViewGetCaptureDeviceTypeId(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceTypeId(NUShort value)
	{
		NCheck(FirFingerViewSetCaptureDeviceTypeId(GetHandle(), value));
	}
	
	BdifFPPosition GetPosition() const
	{
		BdifFPPosition value;
		NCheck(FirFingerViewGetPosition(GetHandle(), &value));
		return value;
	}

	void SetPosition(BdifFPPosition value)
	{
		NCheck(FirFingerViewSetPosition(GetHandle(), value));
	}

	NInt GetViewNumber() const
	{
		NInt value;
		NCheck(FirFingerViewGetViewNumber(GetHandle(), &value));
		return value;
	}

	NByte GetImageQuality() const
	{
		NByte value;
		NCheck(FirFingerViewGetImageQuality(GetHandle(), &value));
		return value;
	}

	void SetImageQuality(NByte value)
	{
		NCheck(FirFingerViewSetImageQuality(GetHandle(), value));
	}

	BdifFPImpressionType GetImpressionType() const
	{
		BdifFPImpressionType value;
		NCheck(FirFingerViewGetImpressionType(GetHandle(), &value));
		return value;
	}

	void SetImpressionType(BdifFPImpressionType value)
	{
		NCheck(FirFingerViewSetImpressionType(GetHandle(), value));
	}

	NUShort GetHorzLineLength() const
	{
		NUShort value;
		NCheck(FirFingerViewGetHorzLineLength(GetHandle(), &value));
		return value;
	}

	void SetHorzLineLength(NUShort value)
	{
		NCheck(FirFingerViewSetHorzLineLength(GetHandle(), value));
	}

	NUShort GetVertLineLength() const
	{
		NUShort value;
		NCheck(FirFingerViewGetVertLineLength(GetHandle(), &value));
		return value;
	}

	void SetVertLineLength(NUShort value)
	{
		NCheck(FirFingerViewSetVertLineLength(GetHandle(), value));
	}

	::Neurotec::IO::NBuffer GetImageData() const
	{
		return GetObject<HandleType, ::Neurotec::IO::NBuffer>(FirFingerViewGetImageDataN, true);
	}

	void SetImageData(const ::Neurotec::IO::NBuffer & value)
	{
		SetObject(FirFingerViewSetImageDataN, value);
	}

	void SetImageData(const void * pValue, NSizeType valueSize, bool copy = true)
	{
		NCheck(FirFingerViewSetImageDataEx(GetHandle(), pValue, valueSize, copy ? NTrue : NFalse));
	}

	BdifScaleUnits GetScaleUnits() const
	{
		BdifScaleUnits value;
		NCheck(FirFingerViewGetScaleUnits(GetHandle(), &value));
		return value;
	}

	void SetScaleUnits(BdifScaleUnits value)
	{
		NCheck(FirFingerViewSetScaleUnits(GetHandle(), value));
	}

	NUShort GetHorzScanResolution() const
	{
		NUShort value;
		NCheck(FirFingerViewGetHorzScanResolution(GetHandle(), &value));
		return value;
	}

	void SetHorzScanResolution(NUShort value)
	{
		NCheck(FirFingerViewSetHorzScanResolution(GetHandle(), value));
	}

	NUShort GetVertScanResolution() const
	{
		NUShort value;
		NCheck(FirFingerViewGetVertScanResolution(GetHandle(), &value));
		return value;
	}

	void SetVertScanResolution(NUShort value)
	{
		NCheck(FirFingerViewSetVertScanResolution(GetHandle(), value));
	}

	NUShort GetHorzImageResolution() const
	{
		NUShort value;
		NCheck(FirFingerViewGetHorzImageResolution(GetHandle(), &value));
		return value;
	}

	void SetHorzImageResolution(NUShort value)
	{
		NCheck(FirFingerViewSetHorzImageResolution(GetHandle(), value));
	}

	NUShort GetVertImageResolution() const
	{
		NUShort value;
		NCheck(FirFingerViewGetVertImageResolution(GetHandle(), &value));
		return value;
	}

	void SetVertImageResolution(NUShort value)
	{
		NCheck(FirFingerViewSetVertImageResolution(GetHandle(), value));
	}

	NByte GetPixelDepth() const
	{
		NByte value;
		NCheck(FirFingerViewGetPixelDepth(GetHandle(), &value));
		return value;
	}

	void SetPixelDepth(NByte value)
	{
		NCheck(FirFingerViewSetPixelDepth(GetHandle(), value));
	}

	FirImageCompressionAlgorithm GetImageCompressionAlgorithm() const
	{
		FirImageCompressionAlgorithm value;
		NCheck(FirFingerViewGetImageCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	void SetImageCompressionAlgorithm(FirImageCompressionAlgorithm value)
	{
		NCheck(FirFingerViewSetImageCompressionAlgorithm(GetHandle(), value));
	}

	NUShort GetImageCompressionAlgorithmId() const
	{
		NUShort value;
		NCheck(FirFingerViewGetImageCompressionAlgorithmId(GetHandle(), &value));
		return value;
	}

	void SetImageCompressionAlgorithmId(NUShort value)
	{
		NCheck(FirFingerViewSetImageCompressionAlgorithmId(GetHandle(), value));
	}

	NUShort GetImageCompressionAlgorithmVendorId() const
	{
		NUShort value;
		NCheck(FirFingerViewGetImageCompressionAlgorithmVendorId(GetHandle(), &value));
		return value;
	}

	void SetImageCompressionAlgorithmVendorId(NUShort value)
	{
		NCheck(FirFingerViewSetImageCompressionAlgorithmVendorId(GetHandle(), value));
	}

	QualityBlockCollection GetQualityBlocks()
	{
		return QualityBlockCollection(*this);
	}

	const QualityBlockCollection GetQualityBlocks() const
	{
		return QualityBlockCollection(*this);
	}

	CertificationBlockCollection GetCertificationBlocks()
	{
		return CertificationBlockCollection(*this);
	}

	const CertificationBlockCollection GetCertificationBlocks() const
	{
		return CertificationBlockCollection(*this);
	}

	SegmentationCollection GetSegmentations()
	{
		return SegmentationCollection(*this);
	}

	const SegmentationCollection GetSegmentations() const
	{
		return SegmentationCollection(*this);
	}

	AnnotationCollection GetAnnotations()
	{
		return AnnotationCollection(*this);
	}

	const AnnotationCollection GetAnnotations() const
	{
		return AnnotationCollection(*this);
	}
	
	CommentCollection GetComments()
	{
		return CommentCollection(*this);
	}

	const CommentCollection GetComments() const
	{
		return CommentCollection(*this);
	}

	VendorExtendedDataCollection GetVendorExtendedDatas()
	{
		return VendorExtendedDataCollection(*this);
	}

	const VendorExtendedDataCollection GetVendorExtendedDatas() const
	{
		return VendorExtendedDataCollection(*this);
	}

	FIRecord GetOwner() const;
};
}}}

#include <Biometrics/Standards/FIRecord.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{

inline FIRecord FirFingerView::GetOwner() const
{
	return NObject::GetOwner<FIRecord>();
}

inline FirFingerView FirFingerViewSegmentation::GetOwner() const
{
	return NObject::GetOwner<FirFingerView>();
}

inline FirFingerViewSegmentation FirFingerViewSegment::GetOwner() const
{
	return NObject::GetOwner<FirFingerViewSegmentation>();
}

}}}

#endif // !FIR_FINGER_VIEW_HPP_INCLUDED
