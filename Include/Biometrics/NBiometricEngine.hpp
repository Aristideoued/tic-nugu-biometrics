#include <Biometrics/NBiometricTask.hpp>
#include <Biometrics/NBiometricEngineTypes.hpp>
#include <Biometrics/NBiographicDataSchema.hpp>

#ifndef N_BIOMETRIC_ENGINE_HPP_INCLUDED
#define N_BIOMETRIC_ENGINE_HPP_INCLUDED

#include <Core/NObject.hpp>
#include <Core/NAsyncOperation.hpp>
#include <Biometrics/NSubject.hpp>
namespace Neurotec { namespace Biometrics
{
#include <Biometrics/NBiometricEngine.h>
}}

namespace Neurotec { namespace Biometrics
{

class NBiometricEngine : public NObject
{
	N_DECLARE_OBJECT_CLASS(NBiometricEngine, NObject)

private:
	static HNBiometricEngine Create()
	{
		HNBiometricEngine handle;
		NCheck(NBiometricEngineCreate(&handle));
		return handle;
	}

public:
	NBiometricEngine()
		: NObject(Create(), true)
	{
	}

	void Initialize()
	{
		NCheck(NBiometricEngineInitialize(GetHandle()));
	}

	NAsyncOperation InitializeAsync()
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineInitializeAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricTask CreateTask(NBiometricOperations operations, const NSubject & subject, const NSubject & otherSubject = NULL) const
	{
		HNBiometricTask hBiometricTask;
		NCheck(NBiometricEngineCreateTask(GetHandle(), operations, subject.GetHandle(), otherSubject.GetHandle(), &hBiometricTask));
		return FromHandle<NBiometricTask>(hBiometricTask);
	}

	void PerformTask(const NBiometricTask & biometricTask) const
	{
		NCheck(NBiometricEnginePerformTask(GetHandle(), biometricTask.GetHandle()));
	}

	NAsyncOperation PerformTaskAsync(const NBiometricTask & biometricTask) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEnginePerformTaskAsync(GetHandle(), biometricTask.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NArrayWrapper<NString> ListGalleries() const
	{
		HNString * arhValues;
		NInt valueCount;
		NCheck(NBiometricEngineListGalleries(GetHandle(), &arhValues, &valueCount));
		return NArrayWrapper<NString>(arhValues, valueCount);
	}

	NAsyncOperation ListGalleriesAsync() const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineListGalleriesAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Enroll(const NSubject & subject, bool checkForDuplicates = false)
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineEnroll(GetHandle(), subject.GetHandle(), checkForDuplicates ? NTrue : NFalse, &result));
		return result;
	}

	NAsyncOperation EnrollAsync(const NSubject & subject, bool checkForDuplicates = false)
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineEnrollAsync(GetHandle(), subject.GetHandle(), checkForDuplicates ? NTrue : NFalse, &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus CreateTemplate(const NSubject & subject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineCreateTemplate(GetHandle(), subject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation CreateTemplateAsync(const NSubject & subject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineCreateTemplateAsync(GetHandle(), subject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Identify(const NSubject & subject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineIdentify(GetHandle(), subject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation IdentifyAsync(const NSubject & subject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineIdentifyAsync(GetHandle(), subject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Verify(const NSubject & subject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineVerify(GetHandle(), subject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation VerifyAsync(const NSubject & subject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineVerifyAsync(GetHandle(), subject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Verify(const NSubject & subject, const NSubject & otherSubject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineVerifyOffline(GetHandle(), subject.GetHandle(), otherSubject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation VerifyAsync(const NSubject & subject, const NSubject & otherSubject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineVerifyOfflineAsync(GetHandle(), subject.GetHandle(), otherSubject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Delete(const NStringWrapper & id)
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineDelete(GetHandle(), id.GetHandle(), &result));
		return result;
	}

	NAsyncOperation DeleteAsync(const NStringWrapper & id)
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineDeleteAsync(GetHandle(), id.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Clear()
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineClear(GetHandle(), &result));
		return result;
	}

	NAsyncOperation ClearAsync()
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineClearAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Get(const NSubject & subject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineGet(GetHandle(), subject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation GetAsync(const NSubject & subject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineGetAsync(GetHandle(), subject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NBiometricStatus Update(const NSubject & subject) const
	{
		NBiometricStatus result;
		NCheck(NBiometricEngineUpdate(GetHandle(), subject.GetHandle(), &result));
		return result;
	}

	NAsyncOperation UpdateAsync(const NSubject & subject) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineUpdateAsync(GetHandle(), subject.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NInt GetCount() const
	{
		NInt result;
		NCheck(NBiometricEngineGetCount(GetHandle(), &result));
		return result;
	}

	NAsyncOperation GetCountAsync() const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineGetCountAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NArrayWrapper<NString> ListIds() const
	{
		HNString * arhValues;
		NInt valueCount;
		NCheck(NBiometricEngineListIds(GetHandle(), &arhValues, &valueCount));
		return NArrayWrapper<NString>(arhValues, valueCount);
	}

	NAsyncOperation ListIdsAsync() const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineListIdsAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NArrayWrapper<NSubject> List() const
	{
		HNSubject * arhValues;
		NInt valueCount;
		NCheck(NBiometricEngineList(GetHandle(), &arhValues, &valueCount));
		return NArrayWrapper<NSubject>(arhValues, valueCount);
	}

	NAsyncOperation ListAsync() const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineListAsync(GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	NFace DetectFaces(const ::Neurotec::Images::NImage & image) const
	{
		HNFace hResult;
		NCheck(NBiometricEngineDetectFaces(GetHandle(), image.GetHandle(), &hResult));
		return FromHandle<NFace>(hResult);
	}

	NAsyncOperation DetectFacesAsync(const ::Neurotec::Images::NImage & image) const
	{
		HNAsyncOperation hAsyncOperation;
		NCheck(NBiometricEngineDetectFacesAsync(GetHandle(), image.GetHandle(), &hAsyncOperation));
		return FromHandle<NAsyncOperation>(hAsyncOperation);
	}

	void WaitForAllTasks()
	{
		NCheck(NBiometricEngineWaitForAllTasks(GetHandle()));
	}

	NTimeSpan GetTimeout() const
	{
		return GetProperty<NTimeSpan>(N_T("Timeout"));
	}

	void SetTimeout(const NTimeSpan & value)
	{
		SetProperty(N_T("Timeout"), value);
	}

	NInt GetMaximalThreadCount() const
	{
		return GetProperty<NInt>(N_T("MaximalThreadCount"));
	}

	void SetMaximalThreadCount(NInt value)
	{
		SetProperty(N_T("MaximalThreadCount"), value);
	}

	NBiographicDataSchema GetBiographicDataSchema() const
	{
		return GetProperty<NBiographicDataSchema>(N_T("BiographicDataSchema"));
	}

	void SetBiographicDataSchema(const NBiographicDataSchema & value)
	{
		SetProperty(N_T("BiographicDataSchema"), value);
	}

	NString GetSelectedGalleryId() const
	{
		return GetProperty<NString>(N_T("SelectedGalleryId"));
	}

	void SetSelectedGalleryId(const NStringWrapper & value)
	{
		SetProperty(N_T("SelectedGalleryId"), value);
	}

	BiometricTemplateFormat GetBiometricTemplateFormat() const
	{
		return GetProperty<BiometricTemplateFormat>(N_T("BiometricTemplateFormat"));
	}

	void SetBiometricTemplateFormat(BiometricTemplateFormat value)
	{
		SetProperty(N_T("BiometricTemplateFormat"), value);
	}

	bool GetFingersDeterminePatternClass() const
	{
		return GetProperty<bool>(N_T("Fingers.DeterminePatternClass"));
	}

	void SetFingersDeterminePatternClass(bool value)
	{
		SetProperty(N_T("Fingers.DeterminePatternClass"), value);
	}

	bool GetFingersCalculateNfiq() const
	{
		return GetProperty<bool>(N_T("Fingers.CalculateNfiq"));
	}

	void SetFingersCalculateNfiq(bool value)
	{
		SetProperty(N_T("Fingers.CalculateNfiq"), value);
	}

	bool GetFingersCalculateNfiq2() const
	{
		return GetProperty<bool>(N_T("Fingers.CalculateNfiq2"));
	}

	void SetFingersCalculateNfiq2(bool value)
	{
		SetProperty(N_T("Fingers.CalculateNfiq2"), value);
	}

	bool GetFingersCalculateNfiq21() const
	{
		return GetProperty<bool>(N_T("Fingers.CalculateNfiq21"));
	}

	void SetFingersCalculateNfiq21(bool value)
	{
		SetProperty(N_T("Fingers.CalculateNfiq21"), value);
	}

	bool GetFingersDetectLiveness() const
	{
		return GetProperty<bool>(N_T("Fingers.DetectLiveness"));
	}

	void SetFingersDetectLiveness(bool value)
	{
		SetProperty(N_T("Fingers.DetectLiveness"), value);
	}

	NByte GetFingersLivenessConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Fingers.LivenessConfidenceThreshold"));
	}

	void SetFingersLivenessConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Fingers.LivenessConfidenceThreshold"), value);
	}

	bool GetFingersFastExtraction() const
	{
		return GetProperty<bool>(N_T("Fingers.FastExtraction"));
	}

	void SetFingersFastExtraction(bool value)
	{
		SetProperty(N_T("Fingers.FastExtraction"), value);
	}

	NTemplateSize GetFingersTemplateSize() const
	{
		return GetProperty<NTemplateSize>(N_T("Fingers.TemplateSize"));
	}

	void SetFingersTemplateSize(NTemplateSize value)
	{
		SetProperty(N_T("Fingers.TemplateSize"), value);
	}

	NByte GetFingersQualityThreshold() const
	{
		return GetProperty<NByte>(N_T("Fingers.QualityThreshold"));
	}

	void SetFingersQualityThreshold(NByte value)
	{
		SetProperty(N_T("Fingers.QualityThreshold"), value);
	}

	bool GetFingersReturnBinarizedImage() const
	{
		return GetProperty<bool>(N_T("Fingers.ReturnBinarizedImage"));
	}

	void SetFingersReturnBinarizedImage(bool value)
	{
		SetProperty(N_T("Fingers.ReturnBinarizedImage"), value);
	}

	NInt GetFingersMinimalMinutiaCount() const
	{
		return GetProperty<NInt>(N_T("Fingers.MinimalMinutiaCount"));
	}

	void SetFingersMinimalMinutiaCount(NInt value)
	{
		SetProperty(N_T("Fingers.MinimalMinutiaCount"), value);
	}

	NFloat GetFingersMaximalRotation() const
	{
		return GetProperty<NFloat>(N_T("Fingers.MaximalRotation"));
	}

	void SetFingersMaximalRotation(NFloat value)
	{
		SetProperty(N_T("Fingers.MaximalRotation"), value);
	}

	NMatchingSpeed GetFingersMatchingSpeed() const
	{
		return GetProperty<NMatchingSpeed>(N_T("Fingers.MatchingSpeed"));
	}

	void SetFingersMatchingSpeed(NMatchingSpeed value)
	{
		SetProperty(N_T("Fingers.MatchingSpeed"), value);
	}

	NExtractionScenario GetFingersExtractionScenario() const
	{
		return GetProperty<NExtractionScenario>(N_T("Fingers.ExtractionScenario"));
	}

	void SetFingersExtractionScenario(NExtractionScenario value)
	{
		SetProperty(N_T("Fingers.ExtractionScenario"), value);
	}

	NMatchingScenario GetMatchingScenario() const
	{
		return GetProperty<NMatchingScenario>(N_T("Matching.Scenario"));
	}

	void SetMatchingScenario(NMatchingScenario value)
	{
		SetProperty(N_T("Matching.Scenario"), value);
	}

	bool GetFacesCreateThumbnailImage() const
	{
		return GetProperty<bool>(N_T("Faces.CreateThumbnailImage"));
	}

	void SetFacesCreateThumbnailImage(bool value)
	{
		SetProperty(N_T("Faces.CreateThumbnailImage"), value);
	}

	int GetFacesThumbnailImageWidth() const
	{
		return GetProperty<int>(N_T("Faces.ThumbnailImageWidth"));
	}

	void SetFacesThumbnailWidth(int value)
	{
		SetProperty(N_T("Faces.ThumbnailImageWidth"), value);
	}

	NInt GetFacesMinimalInterOcularDistance() const
	{
		return GetProperty<NInt>(N_T("Faces.MinimalInterOcularDistance"));
	}

	void SetFacesMinimalInterOcularDistance(NInt value)
	{
		SetProperty(N_T("Faces.MinimalInterOcularDistance"), value);
	}

	NByte GetFacesConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.ConfidenceThreshold"));
	}

	void SetFacesConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Faces.ConfidenceThreshold"), value);
	}

	NFloat GetFacesMaximalRoll() const
	{
		return GetProperty<NFloat>(N_T("Faces.MaximalRoll"));
	}

	void SetFacesMaximalRoll(NFloat value)
	{
		SetProperty(N_T("Faces.MaximalRoll"), value);
	}

	NFloat GetFacesMaximalYaw() const
	{
		return GetProperty<NFloat>(N_T("Faces.MaximalYaw"));
	}

	void SetFacesMaximalYaw(NFloat value)
	{
		SetProperty(N_T("Faces.MaximalYaw"), value);
	}

	bool GetFacesDetectAllFeaturePoints() const
	{
		return GetProperty<bool>(N_T("Faces.DetectAllFeaturePoints"));
	}

	void SetFacesDetectAllFeaturePoints(bool value)
	{
		SetProperty(N_T("Faces.DetectAllFeaturePoints"), value);
	}

	bool GetFacesDetermineGender() const
	{
		return GetProperty<bool>(N_T("Faces.DetermineGender"));
	}

	void SetFacesDetermineGender(bool value)
	{
		SetProperty(N_T("Faces.DetermineGender"), value);
	}

	bool GetFacesDetermineAge() const
	{
		return GetProperty<bool>(N_T("Faces.DetermineAge"));
	}

	void SetFacesDetermineAge(bool value)
	{
		SetProperty(N_T("Faces.DetermineAge"), value);
	}

	bool GetFacesDetectProperties() const
	{
		return GetProperty<bool>(N_T("Faces.DetectProperties"));
	}

	void SetFacesDetectProperties(bool value)
	{
		SetProperty(N_T("Faces.DetectProperties"), value);
	}

	bool GetFacesRecognizeEmotion() const
	{
		return GetProperty<bool>(N_T("Faces.RecognizeEmotion"));
	}

	void SetFacesRecognizeEmotion(bool value)
	{
		SetProperty(N_T("Faces.RecognizeEmotion"), value);
	}

	bool GetFacesDetermineEthnicity() const
	{
		return GetProperty<bool>(N_T("Faces.DetermineEthnicity"));
	}

	void SetFacesDetermineEthnicity(bool value)
	{
		SetProperty(N_T("Faces.DetermineEthnicity"), value);
	}

	bool GetFacesDetectLiveness() const
	{
		return GetProperty<bool>(N_T("Faces.DetectLiveness"));
	}

	void SetFacesDetectLiveness(bool value)
	{
		SetProperty(N_T("Faces.DetectLiveness"), value);
	}

	NByte GetFacesLivenessConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.LivenessConfidenceThreshold"));
	}

	void SetFacesLivenessConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Faces.LivenessConfidenceThreshold"), value);
	}

	NByte GetFacesPassiveLivenessSensitivityThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.PassiveLivenessSensitivityThreshold"));
	}

	void SetFacesPassiveLivenessSensitivityThreshold(NByte value)
	{
		SetProperty(N_T("Faces.PassiveLivenessSensitivityThreshold"), value);
	}
	NTemplateSize GetFacesTemplateSize() const
	{
		return GetProperty<NTemplateSize>(N_T("Faces.TemplateSize"));
	}

	void SetFacesTemplateSize(NTemplateSize value)
	{
		SetProperty(N_T("Faces.TemplateSize"), value);
	}

	NByte GetFacesQualityThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.QualityThreshold"));
	}

	void SetFacesQualityThreshold(NByte value)
	{
		SetProperty(N_T("Faces.QualityThreshold"), value);
	}

	NByte GetFacesLivenessThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.LivenessThreshold"));
	}

	void SetFacesLivenessThreshold(NByte value)
	{
		SetProperty(N_T("Faces.LivenessThreshold"), value);
	}	

	NInt GetFacesLivenessBlinkTimeout() const
	{
		return GetProperty<NInt>(N_T("Faces.LivenessBlinkTimeout"));
	}

	void SetFacesLivenessBlinkTimeout(NInt value)
	{
		SetProperty(N_T("Faces.LivenessBlinkTimeout"), value);
	}

	NLivenessMode GetFacesLivenessMode() const
	{
		return GetProperty<NLivenessMode>(N_T("Faces.LivenessMode"));
	}

	void SetFacesLivenessMode(NLivenessMode value)
	{
		SetProperty(N_T("Faces.LivenessMode"), value);
	}

	NMatchingSpeed GetFacesMatchingSpeed() const
	{
		return GetProperty<NMatchingSpeed>(N_T("Faces.MatchingSpeed"));
	}

	void SetFacesMatchingSpeed(NMatchingSpeed value)
	{
		SetProperty(N_T("Faces.MatchingSpeed"), value);
	}

	NInt GetFacesTokenImageWidth() const
	{
		return GetProperty<NInt>(N_T("Faces.TokenImageWidth"));
	}

	void SetFacesTokenImageWidth(NInt value)
	{
		SetProperty(N_T("Faces.TokenImageWidth"), value);
	}

	NByte GetFacesTokenQualityThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.TokenQualityThreshold"));
	}

	void SetFacesTokenQualityThreshold(NByte value)
	{
		SetProperty(N_T("Faces.TokenQualityThreshold"), value);
	}

	bool GetFacesCheckIcaoCompliance() const
	{
		return GetProperty<bool>(N_T("Faces.CheckIcaoCompliance"));
	}

	void SetFacesCheckIcaoCompliance(bool value)
	{
		SetProperty(N_T("Faces.CheckIcaoCompliance"), value);
	}

	bool GetFacesIcaoRemoveRedEye() const
	{
		return GetProperty<bool>(N_T("Faces.IcaoRemoveRedEye"));
	}

	void SetFacesIcaoRemoveRedEye(bool value)
	{
		SetProperty(N_T("Faces.IcaoRemoveRedEye"), value);
	}

	bool GetFacesIcaoRemoveBackground() const
	{
		return GetProperty<bool>(N_T("Faces.IcaoRemoveBackground"));
	}

	void SetFacesIcaoRemoveBackground(bool value)
	{
		SetProperty(N_T("Faces.IcaoRemoveBackground"), value);
	}

	NExtractionScenario GetFacesExtractionScenario() const
	{
		return GetProperty<NExtractionScenario>(N_T("Faces.ExtractionScenario"));
	}

	void SetFacesExtractionScenario(NExtractionScenario value)
	{
		SetProperty(N_T("Faces.ExtractionScenario"), value);
	}

	NByte GetFacesAdditionalFacesConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Faces.AdditionalFacesConfidenceThreshold"));
	}

	void SetFacesAdditionalFacesConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Faces.AdditionalFacesConfidenceThreshold"), value);
	}

	NByte GetIrisesConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Irises.ConfidenceThreshold"));
	}

	void SetIrisesConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Irises.ConfidenceThreshold"), value);
	}

	bool GetIrisesFastExtraction() const
	{
		return GetProperty<bool>(N_T("Irises.FastExtraction"));
	}

	void SetIrisesFastExtraction(bool value)
	{
		SetProperty(N_T("Irises.FastExtraction"), value);
	}

	bool GetIrisesDetectCosmeticLenses() const
	{
		return GetProperty<bool>(N_T("Irises.DetectCosmeticLenses"));
	}

	void SetIrisesDetectCosmeticLenses(bool value)
	{
		SetProperty(N_T("Irises.DetectCosmeticLenses"), value);
	}

	NTemplateSize GetIrisesTemplateSize() const
	{
		return GetProperty<NTemplateSize>(N_T("Irises.TemplateSize"));
	}

	void SetIrisesTemplateSize(NTemplateSize value)
	{
		SetProperty(N_T("Irises.TemplateSize"), value);
	}

	NByte GetIrisesQualityThreshold() const
	{
		return GetProperty<NByte>(N_T("Irises.QualityThreshold"));
	}

	void SetIrisesQualityThreshold(NByte value)
	{
		SetProperty(N_T("Irises.QualityThreshold"), value);
	}

	NMatchingSpeed GetIrisesMatchingSpeed() const
	{
		return GetProperty<NMatchingSpeed>(N_T("Irises.MatchingSpeed"));
	}

	void SetIrisesMatchingSpeed(NMatchingSpeed value)
	{
		SetProperty(N_T("Irises.MatchingSpeed"), value);
	}

	NFloat GetIrisesMaximalRotation() const
	{
		return GetProperty<NFloat>(N_T("Irises.MaximalRotation"));
	}

	void SetIrisesMaximalRotation(NFloat value)
	{
		SetProperty(N_T("Irises.MaximalRotation"), value);
	}

	NExtractionScenario GetIrisesExtractionScenario() const
	{
		return GetProperty<NExtractionScenario>(N_T("Irises.ExtractionScenario"));
	}

	void SetIrisesExtractionScenario(NExtractionScenario value)
	{
		SetProperty(N_T("Irises.ExtractionScenario"), value);
	}

	bool GetIrisesDetectLiveness() const
	{
		return GetProperty<bool>(N_T("Irises.DetectLiveness"));
	}

	void SetIrisesDetectLiveness(bool value)
	{
		SetProperty(N_T("Irises.DetectLiveness"), value);
	}

	bool GetIrisesDetectPosition() const
	{
		return GetProperty<bool>(N_T("Irises.DetectPosition"));
	}

	void SetIrisesDetectPosition(bool value)
	{
		SetProperty(N_T("Irises.DetectPosition"), value);
	}

	NByte GetIrisesLivenessConfidenceThreshold() const
	{
		return GetProperty<NByte>(N_T("Irises.LivenessConfidenceThreshold"));
	}

	void SetIrisesLivenessConfidenceThreshold(NByte value)
	{
		SetProperty(N_T("Irises.LivenessConfidenceThreshold"), value);
	}

	NTemplateSize GetPalmsTemplateSize() const
	{
		return GetProperty<NTemplateSize>(N_T("Palms.TemplateSize"));
	}

	void SetPalmsTemplateSize(NTemplateSize value)
	{
		SetProperty(N_T("Palms.TemplateSize"), value);
	}

	NByte GetPalmsQualityThreshold() const
	{
		return GetProperty<NByte>(N_T("Palms.QualityThreshold"));
	}

	void SetPalmsQualityThreshold(NByte value)
	{
		SetProperty(N_T("Palms.QualityThreshold"), value);
	}

	bool GetPalmsReturnBinarizedImage() const
	{
		return GetProperty<bool>(N_T("Palms.ReturnBinarizedImage"));
	}

	void SetPalmsReturnBinarizedImage(bool value)
	{
		SetProperty(N_T("Palms.ReturnBinarizedImage"), value);
	}

	NFloat GetPalmsMaximalRotation() const
	{
		return GetProperty<NFloat>(N_T("Palms.MaximalRotation"));
	}

	void SetPalmsMaximalRotation(NFloat value)
	{
		SetProperty(N_T("Palms.MaximalRotation"), value);
	}

	NMatchingSpeed GetPalmsMatchingSpeed() const
	{
		return GetProperty<NMatchingSpeed>(N_T("Palms.MatchingSpeed"));
	}

	void SetPalmsMatchingSpeed(NMatchingSpeed value)
	{
		SetProperty(N_T("Palms.MatchingSpeed"), value);
	}

	NExtractionScenario GetPalmsExtractionScenario() const
	{
		return GetProperty<NExtractionScenario>(N_T("Palms.ExtractionScenario"));
	}

	void SetPalmsExtractionScenario(NExtractionScenario value)
	{
		SetProperty(N_T("Palms.ExtractionScenario"), value);
	}

	NLong GetVoicesMaximalLoadedFileSize() const
	{
		return GetProperty<NLong>(N_T("Voices.MaximalLoadedFileSize"));
	}

	void SetVoicesMaximalLoadedFileSize(NLong value)
	{
		SetProperty(N_T("Voices.MaximalLoadedFileSize"), value);
	}

	bool GetVoicesExtractTextDependentFeatures() const
	{
		return GetProperty<bool>(N_T("Voices.ExtractTextDependentFeatures"));
	}

	void SetVoicesExtractTextDependentFeatures(bool value)
	{
		SetProperty(N_T("Voices.ExtractTextDependentFeatures"), value);
	}

	NInt GetVoicesMaximalPauseDurationMs() const
	{
		return GetProperty<NInt>(N_T("Voices.MaximalPauseDurationRaw"));
	}

	void SetVoicesMaximalPauseDurationMs(NInt value)
	{
		SetProperty(N_T("Voices.MaximalPauseDurationRaw"), value);
	}

	NTemplateSize GetVoicesTemplateSize() const
	{
		return GetProperty<NTemplateSize>(N_T("Voices.TemplateSize"));
	}

	void SetVoicesTemplateSize(NTemplateSize value)
	{
		SetProperty(N_T("Voices.TemplateSize"), value);
	}

	bool GetVoicesMatchTextDependentFeatures() const
	{
		return GetProperty<bool>(N_T("Voices.MatchTextDependentFeatures"));
	}

	void SetVoicesMatchTextDependentFeatures(bool value)
	{
		SetProperty(N_T("Voices.MatchTextDependentFeatures"), value);
	}

	bool GetVoicesMatchTextIndependentFeatures() const
	{
		return GetProperty<bool>(N_T("Voices.MatchTextIndependentFeatures"));
	}

	void SetVoicesMatchTextIndependentFeatures(bool value)
	{
		SetProperty(N_T("Voices.MatchTextIndependentFeatures"), value);
	}

	bool GetMatchingWithDetails() const
	{
		return GetProperty<bool>(N_T("Matching.WithDetails"));
	}

	void SetMatchingWithDetails(bool value)
	{
		SetProperty(N_T("Matching.WithDetails"), value);
	}

	NInt GetMatchingMaximalResultCount() const
	{
		return GetProperty<NInt>(N_T("Matching.MaximalResultCount"));
	}

	void SetMatchingMaximalResultCount(NInt value)
	{
		SetProperty(N_T("Matching.MaximalResultCount"), value);
	}

	bool GetFirstResultOnly() const
	{
		return GetProperty<bool>(N_T("Matching.FirstResultOnly"));
	}

	void SetFirstResultOnly(bool value)
	{
		SetProperty(N_T("Matching.FirstResultOnly"), value);
	}

	NInt GetMatchingThreshold() const
	{
		return GetProperty<NInt>(N_T("Matching.Threshold"));
	}

	void SetMatchingThreshold(NInt value)
	{
		SetProperty(N_T("Matching.Threshold"), value);
	}
};

}}

#endif // !N_BIOMETRIC_ENGINE_HPP_INCLUDED
