#ifndef N_FINGER_EXAMINER_HPP_INCLUDED
#define N_FINGER_EXAMINER_HPP_INCLUDED

#include <Biometrics/NBiometricEngine.hpp>
#include <Geometry/NGeometry.hpp>
namespace Neurotec { namespace Biometrics
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/NFingerExaminer.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFingerExaminer : public NObject
{
	N_DECLARE_OBJECT_CLASS(NFingerExaminer, NObject)

	static HNFingerExaminer Create()
	{
		HNFingerExaminer handle;
		NCheck(NFingerExaminerCreate(&handle));
		return handle;
	}

public:
	NFingerExaminer()
		: NObject(Create(), true)
	{
	}

	NAsyncOperation InitializeFromOriginalImageAsync(const NBiometricEngine & engine, const ::Neurotec::Images::NImage & image)
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NFingerExaminerInitializeFromOriginalImageAsync(GetHandle(), engine.GetHandle(), image.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	void InitializeFromOriginalImage(const NBiometricEngine & engine, const ::Neurotec::Images::NImage & image)
	{
		NCheck(NFingerExaminerInitializeFromOriginalImage(GetHandle(), engine.GetHandle(), image.GetHandle()));
	}

	void InitializeFromBinarizedImage(const ::Neurotec::Images::NImage & image)
	{
		NCheck(NFingerExaminerInitializeFromBinarizedImage(GetHandle(), image.GetHandle()));
	}

	::Neurotec::Images::NImage GetBinarizedImage()
	{
		HNImage hValue;
		NCheck(NFingerExaminerGetBinarizedImage(GetHandle(), &hValue));
		return FromHandle< ::Neurotec::Images::NImage>(hValue);
	}

	NInt CalculateRidgeCount(NInt x1, NInt y1, NInt x2, NInt y2)
	{
		NInt value;
		NCheck(NFingerExaminerCalculateRidgeCount(GetHandle(), x1, y1, x2, y2, &value));
		return value;
	}

	NArrayWrapper< ::Neurotec::Geometry::NPoint> FindRidgeIntersections(NInt x1, NInt y1, NInt x2, NInt y2)
	{
		struct NPoint_ * arPoints;
		NInt count;
		NCheck(NFingerExaminerFindRidgeIntersections(GetHandle(), x1, y1, x2, y2, &arPoints, &count));
		return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arPoints, count, true, true);
	}

	void FindSingularPoints(NFRecord & record)
	{
		NCheck(NFingerExaminerFindSingularPoints(GetHandle(), record.GetHandle()));
	}

	::Neurotec::Images::NImage GetSkeletonImage()
	{
		HNImage hValue;
		NCheck(NFingerExaminerGetSkeletonImage(GetHandle(), &hValue));
		return FromHandle< ::Neurotec::Images::NImage>(hValue);
	}
};

}}

#endif // !N_FINGER_EXAMINER_HPP_INCLUDED
