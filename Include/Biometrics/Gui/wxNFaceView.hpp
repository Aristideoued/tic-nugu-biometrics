#ifndef WX_NFACE_VIEW_HPP_INCLUDED
#define WX_NFACE_VIEW_HPP_INCLUDED

#include <Gui/wxNView.hpp>
#include <Biometrics/NFace.hpp>

#include <wx/timer.h>

#define MAX_FPS_ENTRIES 30

namespace Neurotec { namespace Biometrics { namespace Gui
{

wxDECLARE_EVENT(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_FACE_PROPERTY_CHANGED, wxCommandEvent);

class wxNFaceView : public Neurotec::Gui::wxNView
{
	#define ID_IMAGE_CHANGED          wxID_HIGHEST + 1
	#define ID_PROPERTY_CHANGED       wxID_HIGHEST + 2
	#define ID_COLLECTION_ITEM_ADD    wxID_HIGHEST + 3
	#define ID_COLLECTION_ITEM_REMOVE wxID_HIGHEST + 4
	#define ID_COLLECTION_ITEM_RESET  wxID_HIGHEST + 5

	struct ResolutionParams
	{
		float fontSize{ 0.f };
		float ovalMultiplier{ 1.f };
	};

public:
	wxNFaceView(wxWindow *parent, wxWindowID winid = wxID_ANY)
		: wxNView(parent, winid),
		m_faceRectangleColor(wxColour(0, 255, 0)),
		m_livenessItemsColor(wxColour(255, 255, 0)),
		m_livenessItemsFaceOvalColor(wxColour(0, 0, 0)),
		m_showFaceOval(false),
		m_showFaceRectangle(true),
		m_lastTime(0),
		m_firstTime(0),
		m_frameCount(0),
		m_currentFps(0),
		m_showFps(false),
		m_showEyes(true),
		m_showNose(true),
		m_showMouth(true),
		m_showNoseConfidence(false),
		m_showEyesConfidence(false),
		m_showFaceConfidence(true),
		m_showFaceQuality(true),
		m_showMouthConfidence(false),
		m_showGender(true),
		m_showGenderConfidence(false),
		m_showExpression(true),
		m_showExpressionConfidence(false),
		m_showProperties(true),
		m_showEmotion(true),
		m_showEmotionConfidence(false),
		m_showPropertiesConfidence(false),
		m_showBaseFeaturePoints(true),
		m_mirrorHorizontally(false),
		m_showAge(true),
		m_face(NULL),
		m_icaoColor(*wxRED),
		m_showIcaoArrows(true),
		m_showTokenImageRectangle(true),
		m_tokenImageColor(*wxWHITE),
		m_faceRectangleWidth(-1),
		m_featureWidth(-1),
		m_baseFeatureWidth(-1),
		m_faceRectangleWidthMultiplier(1),
		m_featureWidthMultiplier(1),
		m_baseFeatureWidthMultiplier(1),
		m_faceOvalSizePercentage(1.2f),
		m_faceOvalBackgroundColor(wxColour(255, 255, 255, 242)),
		m_greenFaceOvalColor(m_faceRectangleColor),
		m_grayFaceOvalColor(wxColour(128, 128, 128)),
		m_faceOvalWidth(12)
	{
		SetScrollRate(1, 1);
		SetBackgroundColour(wxColour(0, 0, 0));
		this->Bind(wxEVT_FACE_PROPERTY_CHANGED, &wxNFaceView::OnPropertyChanged, this);
		this->Bind(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, &wxNFaceView::OnCollectionChanged, this);
	}

	~wxNFaceView()
	{
		SetFace(NULL);
		this->Unbind(wxEVT_FACE_PROPERTY_CHANGED, &wxNFaceView::OnPropertyChanged, this);
		this->Unbind(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, &wxNFaceView::OnCollectionChanged, this);
	}

private:
		static void OnPropertyChangedCallback(::Neurotec::Biometrics::NFace::PropertyChangedEventArgs args)
		{
			if (args.GetPropertyName() == N_T("Image"))
			{
				::Neurotec::Biometrics::NFace face = args.GetObject< ::Neurotec::Biometrics::NFace>();
				::Neurotec::Images::NImage image = face.GetImage();

				wxNFaceView * faceView = static_cast<wxNFaceView *>(args.GetParam());
				wxCommandEvent ev(wxEVT_FACE_PROPERTY_CHANGED, ID_IMAGE_CHANGED);
				if (!image.IsNull())
					ev.SetEventObject(new wxImage(image.ToBitmap()));
				else
					ev.SetEventObject(new wxImage());
				::wxPostEvent(faceView, ev);
			}
		}

		static void OnCollectionChangedCallback(::Neurotec::Collections::CollectionChangedEventArgs< ::Neurotec::Biometrics::NLAttributes> args)
		{
			wxNFaceView * faceView = static_cast<wxNFaceView*>(args.GetParam());
			wxCommandEvent ev(wxEVT_FACE_OBJECT_COLLECTION_CHANGED);
			if (args.GetAction() == ::Neurotec::Collections::nccaAdd)
			{
				if (args.GetNewItems().GetCount() > 1) NThrowNotImplementedException();
				ev.SetClientData(args.GetNewItems()[0].RefHandle());
				ev.SetId(ID_COLLECTION_ITEM_ADD);
			}
			else if (args.GetAction() == ::Neurotec::Collections::nccaRemove)
			{
				NThrowNotImplementedException();
			}
			else if (args.GetAction() == ::Neurotec::Collections::nccaReset)
			{
				ev.SetId(ID_COLLECTION_ITEM_RESET);
			}
			::wxPostEvent(faceView, ev);
		}

		static void OnAttributesPropertyChangedCallback(::Neurotec::Biometrics::NLAttributes::PropertyChangedEventArgs args)
		{
			wxNFaceView * faceView = static_cast<wxNFaceView*>(args.GetParam());
			wxCommandEvent ev(wxEVT_FACE_PROPERTY_CHANGED, ID_PROPERTY_CHANGED);
			::wxPostEvent(faceView, ev);
		}

		void SubscribeToFaceEvents()
		{
			if (!m_face.IsNull())
			{
				m_face.AddPropertyChangedCallback(&wxNFaceView::OnPropertyChangedCallback, this);
				m_face.GetObjects().AddCollectionChangedCallback(&wxNFaceView::OnCollectionChangedCallback, this);
				OnAttributesAdded(m_face.GetObjects().GetAll());
			}
		}

		void UnsubscribeFromFaceEvents()
		{
			if (!m_face.IsNull())
			{
				m_face.RemovePropertyChangedCallback(&wxNFaceView::OnPropertyChangedCallback, this);
				m_face.GetObjects().RemoveCollectionChangedCallback(&wxNFaceView::OnCollectionChangedCallback, this);
				OnAttributesReset();
			}
		}

		void SetImage(const wxImage & image)
		{
			if (image.IsOk())
			{
				m_bitmap = wxBitmap(image);
				SetViewSize(image.GetWidth(), image.GetHeight());
			}
			else
			{
				m_bitmap = wxBitmap();
				SetViewSize(1, 1);
			}
			Refresh(false);
		}

		void OnPropertyChanged(wxEvent & event)
		{
			int id = event.GetId();
			if (id == ID_IMAGE_CHANGED)
			{
				wxImage * pImage = (wxImage*)event.GetEventObject();
				SetImage(*pImage);
				delete pImage;
			}
			else Refresh();
		}

		void OnCollectionChanged(wxCommandEvent & event)
		{
			int id = event.GetId();
			if (id == ID_COLLECTION_ITEM_ADD)
			{
				::Neurotec::Biometrics::NLAttributes attributes(static_cast< ::Neurotec::Biometrics::HNLAttributes>(event.GetClientData()), true);
				std::vector< ::Neurotec::Biometrics::NLAttributes> attrVector;
				attrVector.push_back(attributes);
				NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attrArray(attrVector.begin(), attrVector.end());
				OnAttributesAdded(attrArray);
			}
			else if (id == ID_COLLECTION_ITEM_RESET)
			{
				OnAttributesReset();
			}
		}

		void OnAttributesAdded(NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attributes)
		{
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				attributes[i].AddPropertyChangedCallback(&wxNFaceView::OnAttributesPropertyChangedCallback, this);
				m_attributes.push_back(attributes[i]);
			}
			Refresh();
		}

		void OnAttributesReset()
		{
			for (std::vector< ::Neurotec::NObject>::iterator it = m_attributes.begin(); it < m_attributes.end(); it++)
			{
				it->RemovePropertyChangedCallback(&wxNFaceView::OnAttributesPropertyChangedCallback, this);
			}
			m_attributes.clear();
			Refresh();
		}
public:
	void Clear()
	{
		m_bitmap = wxBitmap();
		SetFace(NULL);
		m_faceIds.Clear();
		Refresh(false);
	}

	void SetFace(::Neurotec::Biometrics::NFace face)
	{
		if (GetShowFps())
		{
			UpdateFps();
		}

		UnsubscribeFromFaceEvents();

		m_face = face;

		SubscribeToFaceEvents();
		if (!m_face.IsNull())
		{
			::Neurotec::Images::NImage image = m_face.GetImage();
			SetImage(!image.IsNull() ? image.ToBitmap() : wxImage());
		}
		else SetImage(wxImage());
	}

	::Neurotec::Biometrics::NFace GetFace()
	{
		return m_face;
	}
	void SetFaceIds(const wxArrayString &value) { m_faceIds = value; Refresh();}
	const wxArrayString & GetFaceIds() { return m_faceIds; }
	void SetFaceRectangleColor(const wxColour & value){ m_faceRectangleColor = value; }
	const wxColour & GetFaceRectangleColor(){ return m_faceRectangleColor; }

	void SetLivenessItemsColor(const wxColour & value) { m_livenessItemsColor = value; }
	const wxColour & GetLivenessItemsColor() { return m_livenessItemsColor; }

	bool GetShowFaceOval() { return m_showFaceOval; }
	void SetShowFaceOval(bool value) { m_showFaceOval = value; }

	bool GetShowFaceRectangle(){ return m_showFaceRectangle; }
	void SetShowFaceRectangle(bool value){ m_showFaceRectangle = value; }

	void SetShowFps(bool value){ m_showFps = value; }
	bool GetShowFps(){ return m_showFps; }

	bool GetShowEyes(){ return m_showEyes; }
	void SetShowEyes(bool value){ m_showEyes = value; }
	bool GetShowNose(){ return m_showNose; }
	void SetShowNose(bool value){ m_showNose = value; }
	bool GetShowMouth(){ return m_showMouth; }
	void SetShowMouth(bool value){ m_showMouth = value; }
	bool GetShowMouthConfidence(){ return m_showMouthConfidence; }
	void SetShowMouthConfidence(bool value){ m_showMouthConfidence = value; }
	bool GetShowNoseConfidence(){ return m_showNoseConfidence; }
	void SetShowNoseConfidence(bool value){ m_showNoseConfidence = value; }
	bool GetShowEyesConfidence(){ return m_showEyesConfidence; }
	void SetShowEyesConfidence(bool value){ m_showEyesConfidence = value; }
	bool GetShowFaceConfidence(){ return m_showFaceConfidence; }
	void SetShowFaceConfidence(bool value){ m_showFaceConfidence = value; }
	bool GetShowFaceQuality(){ return m_showFaceQuality; }
	void SetShowFaceQuality(bool value){ m_showFaceQuality = value; }
	void SetShowGender(bool value){ m_showGender = value; }
	bool GetShowGender(){ return m_showGender; }
	void SetShowGenderConfidence(bool value){ m_showGenderConfidence = value; }
	bool GetShowGenderConfidence(){ return m_showGenderConfidence; }
	bool GetShowExpression() { return m_showExpression; }
	void SetShowExpression(bool value) { m_showExpression = value; }
	bool GetShowExpressionConfidence() { return m_showExpressionConfidence; }
	void SetShowExpressionConfidence(bool value) { m_showExpressionConfidence = value; }
	bool GetShowProperties() { return m_showProperties; }
	void SetShowProperties(bool value) { m_showProperties = value; }
	bool GetShowPropertiesConfidence() { return m_showPropertiesConfidence; }
	void SetShowPropertiesConfidence(bool value) { m_showPropertiesConfidence = value; }
	void SetShowBaseFeaturePoints(bool value){ m_showBaseFeaturePoints = value; }
	bool GetShowBaseFeaturePoints(){ return m_showBaseFeaturePoints; }
	bool GetShowEmotion() { return m_showEmotion; }
	void SetShowEmotion(bool value) { m_showEmotion = value; }
	bool GetShowEmotionConfidence() { return m_showEmotionConfidence; }
	void SetShowEmotionConfidence(bool value) { m_showEmotionConfidence = value; }
	bool GetShowEthnicity() { return m_showEthnicity; }
	void SetShowEthnicity(bool value) { m_showEthnicity = value; }
	bool GetShowEthnicityConfidence() { return m_showEthnicityConfidence; }
	void SetShowEthnicityConfidence(bool value) { m_showEthnicityConfidence = value; }
	bool GetMirrorHorizontally() { return m_mirrorHorizontally; }
	void SetMirrorHorizontally(bool value) { m_mirrorHorizontally = value; }
	bool GetShowAge() { return m_showAge; }
	void SetShowAge(bool value) { m_showAge = value; }
	const wxColour & GetIcaoArrowsColor() const { return m_icaoColor; };
	void SetIcaoArrowsColor(const wxColour & value) { m_icaoColor = value; }
	bool GetShowIcaoArrows() const { return m_showIcaoArrows; }
	void SetShowIcaoArrows(bool value) { m_showIcaoArrows = value; }
	bool GetShowTokenImageRectangle() const { return m_showTokenImageRectangle; }
	void SetShowTokenImageRectangle(bool value) { m_showTokenImageRectangle = value; }
	const wxColour & GetTokenImageRecangleColor() const { return m_tokenImageColor; }
	void SetTokenImageRectangleColor(const wxColour & value) { m_tokenImageColor = value; }

	float GetFaceRectangleWidthMultiplier(){ return m_faceRectangleWidthMultiplier; }
	void SetFaceRectangleWidthMultiplier(float value){ m_faceRectangleWidthMultiplier = value; }
	float GetFeatureWidthMultiplier(){ return m_featureWidthMultiplier; }
	void SetFeatureWidthMultiplier(float value){ m_featureWidthMultiplier = value; }
	float GetBaseFeatureWidthMultiplier(){ return m_baseFeatureWidthMultiplier; }
	void SetBaseFeatureWidthMultiplier(float value){ m_baseFeatureWidthMultiplier = value; }
protected:
	virtual void OnDraw(wxGraphicsContext *gc)
	{
		if (!m_bitmap.IsOk()) return;
		if (m_bitmap.GetRefData())
		{
			if (m_mirrorHorizontally)
			{
				gc->Translate(m_bitmap.GetWidth(), 0);
				gc->Scale(-1, 1);
			}
			gc->DrawBitmap(m_bitmap, 0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());
		}

		gc->Clip(0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());

		if (m_face.GetStatus() == NBiometricStatus::nbsObjectNotFound)
		{
			PaintFaceOval(gc, NLivenessAction::nlaNone, CalculateResolutionParameters().ovalMultiplier);
		}

		if (!m_face.IsNull())
		{
			NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attributes = m_face.GetObjects().GetAll();
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				::Neurotec::Biometrics::NLAttributes item = attributes[i];
				wxString faceConfidence = wxEmptyString;
				NByte confidence = item.GetDetectionConfidence();
				if (confidence <= 100 && m_showFaceConfidence)
				{
					faceConfidence = wxString::Format(wxT("%d"), confidence);
				}

				wxString faceQuality = wxEmptyString;
				NByte quality = item.GetQuality();
				if (quality <= 100 && m_showFaceQuality)
				{
					faceQuality = wxString::Format(wxT("%d"), quality);
				}

				wxString faceId = wxEmptyString;
				if (i < (int)m_faceIds.GetCount())
				{
					faceId = m_faceIds[i];
				}
				DrawAttributes(gc, item, faceQuality, faceConfidence, faceId);
			}
		}
		gc->ResetClip();

		if (m_showFps
			&& m_currentFps > 0.5f
			&& m_currentFps < 1000.0f)
		{
			wxBrush brush(wxColour(127, 127, 127));
			wxGraphicsBrush graphicsBrush = gc->CreateBrush(brush);
			gc->DrawText(wxString::Format(wxT("%4.1f"), m_currentFps), 5, 5, graphicsBrush);
		}
	}

private:
	static wxPoint PreparePath(wxGraphicsContext *gc, wxGraphicsPath& gp, float angle, wxRect playArea, bool invert)
	{
		int border = 2;
		playArea.x += border;
		playArea.y += border;
		playArea.width -= border * 2;
		playArea.height -= border * 2;

		wxRect2DDouble rectd = gp.GetBox();

		float scalex = playArea.height / rectd.m_height;
		float translatey = playArea.y;
		float halfPath = rectd.m_width * scalex / 2;
		float maxYaw = 35;
		float offset = (-angle / maxYaw) * (playArea.width / 2) + halfPath;
		float center = playArea.x + playArea.width / 2;
		float translatex = center - offset;

		wxGraphicsMatrix m = gc->CreateMatrix();
		if (invert)
		{
			m.Translate(rectd.m_width, 0);
			m.Scale(-1, 1);
			gp.Transform(m);
		}

		m = gc->CreateMatrix();
		m.Translate(translatex, translatey);
		m.Scale(scalex, scalex);
		gp.Transform(m);

		rectd = gp.GetBox();
		return wxPoint(rectd.m_x + rectd.m_width / 2, rectd.m_y);
	}

	static wxGraphicsPath CreateArrowPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxPoint2DDouble points[] =
		{
			wxPoint2DDouble(32.380941f, 1022.1241f), wxPoint2DDouble(31.942188f, 1015.7183f), wxPoint2DDouble(29.758001f, 1008.0593f), wxPoint2DDouble(34.975683f, 1002.9847f),
			wxPoint2DDouble(63.530331f, 959.92008f), wxPoint2DDouble(92.084969f, 916.85544f), wxPoint2DDouble(120.6396f, 873.7908f),   wxPoint2DDouble(90.970216f, 829.04496f),
			wxPoint2DDouble(61.300833f, 784.29911f), wxPoint2DDouble(31.631451f, 739.55327f), wxPoint2DDouble(32.4174f, 735.10024f),   wxPoint2DDouble(30.920929f, 728.358f),
			wxPoint2DDouble(33.05677f, 725.25888f),  wxPoint2DDouble(40.037212f, 725.44802f), wxPoint2DDouble(47.596572f, 722.95826f), wxPoint2DDouble(53.587747f, 727.72521f),
			wxPoint2DDouble(145.07152f, 773.61583f), wxPoint2DDouble(236.87685f, 818.88016f), wxPoint2DDouble(327.96427f, 865.54932f), wxPoint2DDouble(337.43478f, 881.9015f),
			wxPoint2DDouble(317.96639f, 887.43366f), wxPoint2DDouble(306.82511f, 892.94892f), wxPoint2DDouble(220.62057f, 936.55761f), wxPoint2DDouble(134.10541f, 979.54806f),
			wxPoint2DDouble(47.717131f, 1022.7908f), wxPoint2DDouble(42.608566f, 1022.6599f), wxPoint2DDouble(37.414432f, 1023.1935f)
		};

		gp.MoveToPoint(points[0]);
		for (NUInt i = 1; i < sizeof(points)/sizeof(points[0]); i++)
		{
			gp.AddLineToPoint(points[i]);
		}
		gp.CloseSubpath();

		wxRect2DDouble bounds = gp.GetBox();
		wxGraphicsMatrix m = gc->CreateMatrix();
		m.Translate(-bounds.m_x, -bounds.m_y);
		gp.Transform(m);

		return gp;
	}

	static wxGraphicsPath CreateTargetPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxDouble radius[] =
		{
			40, 30, 20, 10
		};
		for (NUInt i = 0; i < sizeof(radius)/sizeof(radius[0]); i++)
		{
			gp.AddCircle(40, 40, radius[i]);
		}
		return gp;
	}

	static wxGraphicsPath CreateBlinkPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxPoint2DDouble points[] =
		{
			wxPoint2DDouble(435.85713f, 829.28988f), wxPoint2DDouble(435.85713f, 826.14134f), wxPoint2DDouble(435.85713f, 822.99279f), wxPoint2DDouble(435.85713f, 819.84425f),
			wxPoint2DDouble(431.52818f, 819.40493f), wxPoint2DDouble(427.2124f, 818.65847f),  wxPoint2DDouble(422.85713f, 818.61225f), wxPoint2DDouble(420.07381f, 823.2792f),
			wxPoint2DDouble(419.55592f, 829.21363f), wxPoint2DDouble(415.81523f, 833.2958f),  wxPoint2DDouble(411.88195f, 832.96632f), wxPoint2DDouble(402.56019f, 832.2983f),
			wxPoint2DDouble(403.59168f, 826.82747f), wxPoint2DDouble(404.49412f, 822.06959f), wxPoint2DDouble(407.38289f, 817.62303f), wxPoint2DDouble(407.23492f, 812.74024f),
			wxPoint2DDouble(403.97397f, 810.47656f), wxPoint2DDouble(400.43818f, 808.64918f), wxPoint2DDouble(397.01142f, 806.65399f), wxPoint2DDouble(393.40481f, 810.75036f),
			wxPoint2DDouble(390.50368f, 815.74657f), wxPoint2DDouble(385.74505f, 818.59108f), wxPoint2DDouble(381.53086f, 816.45821f), wxPoint2DDouble(371.30273f, 811.69373f),
			wxPoint2DDouble(377.16061f, 806.33105f), wxPoint2DDouble(379.68245f, 802.38916f), wxPoint2DDouble(387.71098f, 797.5141f),  wxPoint2DDouble(381.91398f, 792.84178f),
			wxPoint2DDouble(379.33556f, 788.89088f), wxPoint2DDouble(373.92253f, 785.09903f), wxPoint2DDouble(374.27125f, 780.28926f), wxPoint2DDouble(378.67829f, 776.95361f),
			wxPoint2DDouble(384.55646f, 773.59246f), wxPoint2DDouble(390.26417f, 775.09226f), wxPoint2DDouble(397.24491f, 778.82048f), wxPoint2DDouble(401.76433f, 785.81843f),
			wxPoint2DDouble(408.41041f, 790.09015f), wxPoint2DDouble(424.88655f, 801.96214f), wxPoint2DDouble(447.55374f, 803.93538f), wxPoint2DDouble(466.25184f, 796.46734f),
			wxPoint2DDouble(476.00331f, 792.64778f), wxPoint2DDouble(483.5214f, 785.18173f),  wxPoint2DDouble(491.17644f, 778.33114f), wxPoint2DDouble(495.00098f, 774.23975f),
			wxPoint2DDouble(501.2108f, 773.54521f),  wxPoint2DDouble(505.75694f, 776.89247f), wxPoint2DDouble(510.64456f, 778.33781f), wxPoint2DDouble(513.78144f, 782.54911f),
			wxPoint2DDouble(508.97685f, 786.32591f), wxPoint2DDouble(506.39681f, 789.80997f), wxPoint2DDouble(503.5728f, 793.10166f),  wxPoint2DDouble(500.83072f, 796.45699f),
			wxPoint2DDouble(504.57117f, 801.05482f), wxPoint2DDouble(508.90555f, 805.26143f), wxPoint2DDouble(511.85713f, 810.42573f), wxPoint2DDouble(508.73325f, 813.98587f),
			wxPoint2DDouble(502.37734f, 823.35014f), wxPoint2DDouble(498.04955f, 816.79531f), wxPoint2DDouble(494.57914f, 813.95975f), wxPoint2DDouble(492.73279f, 806.66381f),
			wxPoint2DDouble(487.41682f, 807.78358f), wxPoint2DDouble(482.55765f, 810.13083f), wxPoint2DDouble(475.96485f, 813.63492f), wxPoint2DDouble(480.85493f, 819.58648f),
			wxPoint2DDouble(482.7528f, 823.71135f),  wxPoint2DDouble(486.27353f, 830.95944f), wxPoint2DDouble(479.19952f, 832.07128f), wxPoint2DDouble(475.2306f, 833.59222f),
			wxPoint2DDouble(469.68497f, 836.70712f), wxPoint2DDouble(468.77703f, 830.32197f), wxPoint2DDouble(466.1358f, 826.89057f),  wxPoint2DDouble(466.61264f, 818.27641f),
			wxPoint2DDouble(461.63576f, 818.56925f), wxPoint2DDouble(458.07069f, 819.02156f), wxPoint2DDouble(454.49876f, 819.41691f), wxPoint2DDouble(450.92969f, 819.83583f),
			wxPoint2DDouble(450.73884f, 825.93985f), wxPoint2DDouble(450.54798f, 832.04386f), wxPoint2DDouble(450.35713f, 838.14788f), wxPoint2DDouble(445.5238f, 838.34375f),
			wxPoint2DDouble(440.69046f, 838.53963f), wxPoint2DDouble(435.85713f, 838.7355f),  wxPoint2DDouble(435.85713f, 835.58696f), wxPoint2DDouble(435.85713f, 832.43842f)
		};

		gp.MoveToPoint(points[0]);
		for (NUInt i = 1; i < sizeof(points)/sizeof(points[0]); i++)
		{
			gp.AddLineToPoint(points[i]);
		}
		gp.CloseSubpath();

		wxRect2DDouble bounds = gp.GetBox();
		wxGraphicsMatrix m = gc->CreateMatrix();
		m.Scale(0.8f, 1);
		m.Translate(-bounds.m_x, -bounds.m_y);
		gp.Transform(m);

		return gp;
	}

	static wxGraphicsPath CreateCubicPath(wxGraphicsContext * gc, wxPoint2DDouble * points, NUInt size)
	{
		wxGraphicsPath gp = gc->CreatePath();
		gp.MoveToPoint(points[0]);
		for (NUInt i = 1; i < size; i += 3)
		{
			gp.AddCurveToPoint(points[i + 0], points[i + 1], points[i + 2]);
		}
		return gp;
	}

	static wxGraphicsPath CreateRollPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxPoint2DDouble points[] =
		{
			wxPoint2DDouble(10.807925f, 297.74808f),
			wxPoint2DDouble(-1.9961604f, 301.04045f), wxPoint2DDouble(2.1508011f, 290.46635f), wxPoint2DDouble(5.1596062f, 282.04101f),
			wxPoint2DDouble(24.867047f, 210.22816f), wxPoint2DDouble(72.558732f, 147.46938f), wxPoint2DDouble(134.07262f, 106.02947f),
			wxPoint2DDouble(189.06534f, 68.051168f), wxPoint2DDouble(254.76815f, 46.937433f), wxPoint2DDouble(321.27411f, 42.639341f),
			wxPoint2DDouble(329.47975f, 41.379604f), wxPoint2DDouble(354.27532f, 43.399523f), wxPoint2DDouble(333.72507f, 36.617611f),
			wxPoint2DDouble(322.02949f, 27.764204f), wxPoint2DDouble(295.5855f, 30.343753f), wxPoint2DDouble(296.72086f, 11.70061f),
			wxPoint2DDouble(293.92859f, 1.002931f), wxPoint2DDouble(299.82907f, 3.0737994f), wxPoint2DDouble(306.87798f, 6.9928449f),
			wxPoint2DDouble(340.67083f, 21.458107f), wxPoint2DDouble(375.07219f, 34.581836f), wxPoint2DDouble(408.64422f, 49.497906f),
			wxPoint2DDouble(373.61609f, 68.486881f), wxPoint2DDouble(338.44047f, 87.363418f), wxPoint2DDouble(302.62394f, 104.79237f),
			wxPoint2DDouble(300.7859f, 99.961284f), wxPoint2DDouble(297.04733f, 86.649414f), wxPoint2DDouble(305.94702f, 84.826045f),
			wxPoint2DDouble(320.23171f, 76.786871f), wxPoint2DDouble(334.94037f, 69.54804f), wxPoint2DDouble(349.16191f, 61.393726f),
			wxPoint2DDouble(300.03751f, 61.211863f), wxPoint2DDouble(250.76437f, 69.760543f), wxPoint2DDouble(205.45816f, 89.09581f),
			wxPoint2DDouble(118.62501f, 124.7662f), wxPoint2DDouble(45.964726f, 199.44516f), wxPoint2DDouble(22.699416f, 291.57096f),
			wxPoint2DDouble(22.720315f, 299.77646f), wxPoint2DDouble(16.532752f, 297.71274f), wxPoint2DDouble(10.807925f, 297.74808f)
		};

		return CreateCubicPath(gc, points, (sizeof(points)/sizeof(points[0])));
	}

	static wxGraphicsPath CreateYawPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();

		wxPoint2DDouble points1[] =
		{
			wxPoint2DDouble(21.301227f, 102.58997f),
			wxPoint2DDouble(14.622369f, 95.61589f), wxPoint2DDouble(7.4074343f, 89.024558f), wxPoint2DDouble(1.560607f, 81.330591f),
			wxPoint2DDouble(9.9877053f, 70.78469f), wxPoint2DDouble(20.062028f, 61.604872f), wxPoint2DDouble(29.521354f, 51.977802f),
			wxPoint2DDouble(33.853491f, 48.686307f), wxPoint2DDouble(38.189633f, 41.749136f), wxPoint2DDouble(42.898643f, 40.930205f),
			wxPoint2DDouble(44.095111f, 47.981002f), wxPoint2DDouble(43.360463f, 55.215785f), wxPoint2DDouble(43.560607f, 62.349121f),
			wxPoint2DDouble(64.688084f, 62.483606f), wxPoint2DDouble(85.814034f, 59.302935f), wxPoint2DDouble(106.21234f, 53.901244f),
			wxPoint2DDouble(117.56727f, 50.728373f), wxPoint2DDouble(128.99898f, 45.835297f), wxPoint2DDouble(136.63498f, 36.482283f),
			wxPoint2DDouble(142.60095f, 30.792949f), wxPoint2DDouble(139.58476f, 44.753767f), wxPoint2DDouble(140.21844f, 48.287646f),
			wxPoint2DDouble(139.86458f, 57.069191f), wxPoint2DDouble(140.8417f, 67.11859f), wxPoint2DDouble(134.07908f, 73.940343f),
			wxPoint2DDouble(126.02983f, 83.922774f), wxPoint2DDouble(113.9664f, 89.281311f), wxPoint2DDouble(101.86608f, 92.546907f),
			wxPoint2DDouble(82.908956f, 98.142052f), wxPoint2DDouble(63.19891f, 100.23304f), wxPoint2DDouble(43.560607f, 101.72328f),
			wxPoint2DDouble(43.369245f, 108.41393f), wxPoint2DDouble(44.07906f, 115.20784f), wxPoint2DDouble(42.890809f, 121.80994f),
			wxPoint2DDouble(38.017995f, 120.72083f), wxPoint2DDouble(33.567038f, 113.68744f), wxPoint2DDouble(29.065518f, 110.26208f),
			wxPoint2DDouble(26.459895f, 107.72252f), wxPoint2DDouble(23.872945f, 105.16384f), wxPoint2DDouble(21.301227f, 102.58997f)
		};
		gp.AddPath(CreateCubicPath(gc, points1, sizeof(points1)/sizeof(points1[0])));

		wxPoint2DDouble points2[] =
		{
			wxPoint2DDouble(120.50489f, 34.770121f),
			wxPoint2DDouble(109.71223f, 26.910168f), wxPoint2DDouble(96.50135f, 23.566114f), wxPoint2DDouble(83.560607f, 21.207321f),
			wxPoint2DDouble(83.560607f, 14.178891f), wxPoint2DDouble(83.560607f, 7.1504612f), wxPoint2DDouble(83.560607f, 0.12203127f),
			wxPoint2DDouble(98.729554f, 2.0571253f), wxPoint2DDouble(114.00012f, 6.2121434f), wxPoint2DDouble(126.90044f, 14.635636f),
			wxPoint2DDouble(132.95727f, 18.253911f), wxPoint2DDouble(134.56738f, 27.246714f), wxPoint2DDouble(130.32935f, 32.776644f),
			wxPoint2DDouble(127.70526f, 36.669395f), wxPoint2DDouble(124.24263f, 38.902895f), wxPoint2DDouble(120.50489f, 34.770121f),
		};
		gp.AddPath(CreateCubicPath(gc, points2, sizeof(points2)/sizeof(points2[0])));

		return gp;
	}

	static wxGraphicsPath CreateMovePath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();

		wxPoint2DDouble points1[] =
		{
			wxPoint2DDouble(90.985556f, 105.74811f),
			wxPoint2DDouble(90.893313f, 100.83144f), wxPoint2DDouble(90.801069f, 95.914777f), wxPoint2DDouble(90.708826f, 90.998111f),
			wxPoint2DDouble(60.542159f, 90.824651f), wxPoint2DDouble(30.375492f, 90.651191f), wxPoint2DDouble(0.20882478f, 90.477731f),
			wxPoint2DDouble(0.20882478f, 70.491318f), wxPoint2DDouble(0.20882478f, 50.504904f), wxPoint2DDouble(0.20882478f, 30.518491f),
			wxPoint2DDouble(30.375492f, 30.345031f), wxPoint2DDouble(60.542159f, 30.171571f), wxPoint2DDouble(90.708826f, 29.998111f),
			wxPoint2DDouble(91.042159f, 20.116364f), wxPoint2DDouble(91.375493f, 10.234618f), wxPoint2DDouble(91.708826f, 0.35287129f),
			wxPoint2DDouble(121.86204f, 20.160298f), wxPoint2DDouble(152.35889f, 39.459494f), wxPoint2DDouble(182.06471f, 59.936169f),
			wxPoint2DDouble(180.1838f, 64.456897f), wxPoint2DDouble(170.51742f, 68.317666f), wxPoint2DDouble(165.37398f, 72.500777f),
			wxPoint2DDouble(140.85375f, 88.589161f), wxPoint2DDouble(116.44287f, 104.85865f), wxPoint2DDouble(91.634656f, 120.49811f),
			wxPoint2DDouble(91.073952f, 115.61178f), wxPoint2DDouble(91.151712f, 110.6599f), wxPoint2DDouble(90.985556f, 105.74811f)
		};
		gp.AddPath(CreateCubicPath(gc, points1, sizeof(points1)/sizeof(points1[0])));

		wxPoint2DDouble points2[] =
		{
			wxPoint2DDouble(136.97201f, 88.998111f),
			wxPoint2DDouble(150.74577f, 79.766029f), wxPoint2DDouble(165.06838f, 71.254461f), wxPoint2DDouble(178.13792f, 61.028952f),
			wxPoint2DDouble(176.51483f, 55.95456f), wxPoint2DDouble(166.77604f, 52.673274f), wxPoint2DDouble(161.80061f, 48.407502f),
			wxPoint2DDouble(138.80148f, 33.357215f), wxPoint2DDouble(115.89927f, 18.146483f), wxPoint2DDouble(92.642766f, 3.4981113f),
			wxPoint2DDouble(91.898243f, 12.802028f), wxPoint2DDouble(92.319249f, 22.166338f), wxPoint2DDouble(92.208826f, 31.498111f),
			wxPoint2DDouble(62.208826f, 31.498111f), wxPoint2DDouble(32.208825f, 31.498111f), wxPoint2DDouble(2.2088248f, 31.498111f),
			wxPoint2DDouble(2.2088248f, 50.831444f), wxPoint2DDouble(2.2088248f, 70.164778f), wxPoint2DDouble(2.2088248f, 89.498111f),
			wxPoint2DDouble(32.208825f, 89.498111f), wxPoint2DDouble(62.208826f, 89.498111f), wxPoint2DDouble(92.208826f, 89.498111f),
			wxPoint2DDouble(92.434259f, 98.768627f), wxPoint2DDouble(91.588162f, 108.17654f), wxPoint2DDouble(93.060316f, 117.33144f),
			wxPoint2DDouble(107.78682f, 108.02825f), wxPoint2DDouble(122.34975f, 98.464379f), wxPoint2DDouble(136.97201f, 88.998111f),
		};
		gp.AddPath(CreateCubicPath(gc, points2, sizeof(points2)/sizeof(points2[0])));
	
		return gp;
	}

	static wxGraphicsPath CreatePitchPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();

		wxPoint2DDouble points1[] =
		{
			wxPoint2DDouble(92.637494f, 45.644319f),
			wxPoint2DDouble(89.836361f, 45.747572f), wxPoint2DDouble(87.035227f, 45.850826f), wxPoint2DDouble(84.234094f, 45.954079f),
			wxPoint2DDouble(83.056664f, 72.994566f), wxPoint2DDouble(80.288415f, 100.28025f), wxPoint2DDouble(72.154982f, 126.19936f),
			wxPoint2DDouble(69.05075f, 134.22219f), wxPoint2DDouble(64.076871f, 141.46749f), wxPoint2DDouble(57.957293f, 147.49047f),
			wxPoint2DDouble(50.720403f, 151.3093f), wxPoint2DDouble(42.237345f, 149.18558f), wxPoint2DDouble(34.413094f, 149.68043f),
			wxPoint2DDouble(29.901904f, 150.65881f), wxPoint2DDouble(27.710166f, 146.69833f), wxPoint2DDouble(32.262636f, 144.3016f),
			wxPoint2DDouble(41.581339f, 132.57566f), wxPoint2DDouble(43.743937f, 117.19692f), wxPoint2DDouble(46.654507f, 102.94613f),
			wxPoint2DDouble(49.90055f, 84.132879f) ,wxPoint2DDouble(51.284381f, 65.03322f), wxPoint2DDouble(51.439993f, 45.954079f),
			wxPoint2DDouble(46.134972f, 45.08757f), wxPoint2DDouble(37.815334f, 47.048889f), wxPoint2DDouble(34.472932f, 43.696501f),
			wxPoint2DDouble(36.944979f, 37.056662f), wxPoint2DDouble(42.555046f, 32.192593f), wxPoint2DDouble(46.29016f, 26.262502f),
			wxPoint2DDouble(53.091377f, 17.236637f), wxPoint2DDouble(59.679324f, 8.0014404f), wxPoint2DDouble(67.442293f, -0.24157061f),
			wxPoint2DDouble(78.954749f, 12.299236f), wxPoint2DDouble(88.481525f, 26.479469f), wxPoint2DDouble(98.733548f, 40.012635f),
			wxPoint2DDouble(103.57105f, 46.093394f), wxPoint2DDouble(97.110288f, 45.350616f), wxPoint2DDouble(92.637494f, 45.644319f),
		};
		gp.AddPath(CreateCubicPath(gc, points1, sizeof(points1)/sizeof(points1[0])));

		wxPoint2DDouble points2[] =
		{
			wxPoint2DDouble(51.237593f, 22.859689f),
			wxPoint2DDouble(45.841123f, 30.014342f), wxPoint2DDouble(40.444653f, 37.168996f), wxPoint2DDouble(35.048183f, 44.323649f),
			wxPoint2DDouble(40.922053f, 44.323649f), wxPoint2DDouble(46.795923f, 44.323649f), wxPoint2DDouble(52.669793f, 44.323649f),
			wxPoint2DDouble(52.835981f, 72.341927f), wxPoint2DDouble(49.880496f, 100.50852f), wxPoint2DDouble(42.748509f, 127.63154f),
			wxPoint2DDouble(40.336311f, 135.53069f), wxPoint2DDouble(36.864843f, 143.66489f), wxPoint2DDouble(30.123883f, 148.83097f),
			wxPoint2DDouble(38.42277f, 148.13147f), wxPoint2DDouble(47.108788f, 149.2791f), wxPoint2DDouble(55.112762f, 146.76827f),
			wxPoint2DDouble(65.590255f, 140.51646f), wxPoint2DDouble(69.424411f, 128.00701f), wxPoint2DDouble(73.061263f, 117.10324f),
			wxPoint2DDouble(80.091431f, 93.498569f), wxPoint2DDouble(81.739041f, 68.77288f), wxPoint2DDouble(83.283394f, 44.323649f),
			wxPoint2DDouble(88.790928f, 44.323649f), wxPoint2DDouble(94.298461f, 44.323649f), wxPoint2DDouble(99.805995f, 44.323649f),
			wxPoint2DDouble(89.013082f, 30.014333f), wxPoint2DDouble(78.220106f, 15.705065f), wxPoint2DDouble(67.427193f, 1.3957494f),
			wxPoint2DDouble(62.030683f, 8.5504132f), wxPoint2DDouble(56.634103f, 15.705025f), wxPoint2DDouble(51.237593f, 22.859689f),
		};
		gp.AddPath(CreateCubicPath(gc, points2, sizeof(points2)/sizeof(points2[0])));

		wxPoint2DDouble points3[] =
		{
			wxPoint2DDouble(28.487453f, 138.88467f),
			wxPoint2DDouble(23.575699f, 146.76073f), wxPoint2DDouble(12.707761f, 140.9363f), wxPoint2DDouble(11.232665f, 133.36272f),
			wxPoint2DDouble(4.9850787f, 120.51548f), wxPoint2DDouble(2.5468592f, 106.16259f), wxPoint2DDouble(1.0057137f, 92.099676f),
			wxPoint2DDouble(3.5952825f, 86.096212f), wxPoint2DDouble(13.006677f, 89.178533f), wxPoint2DDouble(17.898812f, 90.085543f),
			wxPoint2DDouble(20.901598f, 95.651678f), wxPoint2DDouble(19.573598f, 102.64764f), wxPoint2DDouble(22.067121f, 108.59295f),
			wxPoint2DDouble(24.037721f, 116.9629f), wxPoint2DDouble(27.288111f, 124.97652f), wxPoint2DDouble(31.131276f, 132.62783f),
			wxPoint2DDouble(31.56646f, 135.04601f), wxPoint2DDouble(29.852111f, 137.10207f), wxPoint2DDouble(28.487453f, 138.88467f),
		};
		gp.AddPath(CreateCubicPath(gc, points3, sizeof(points3)/sizeof(points3[0])));

		wxPoint2DDouble points4[] =
		{
			wxPoint2DDouble(27.198983f, 128.45597f),
			wxPoint2DDouble(21.051783f, 117.37429f), wxPoint2DDouble(20.030363f, 104.49296f), wxPoint2DDouble(17.04449f, 92.444202f),
			wxPoint2DDouble(13.378432f, 89.056335f), wxPoint2DDouble(6.4484578f, 90.325661f), wxPoint2DDouble(2.1922269f, 91.275972f),
			wxPoint2DDouble(4.2946756f, 106.93357f), wxPoint2DDouble(7.0325838f, 123.16709f), wxPoint2DDouble(15.09949f, 137.03169f),
			wxPoint2DDouble(18.840249f, 144.12429f), wxPoint2DDouble(31.058067f, 139.62808f), wxPoint2DDouble(29.035871f, 132.20932f),
			wxPoint2DDouble(28.545292f, 130.9009f), wxPoint2DDouble(27.831945f, 129.69624f), wxPoint2DDouble(27.198983f, 128.45597f),
		};
		gp.AddPath(CreateCubicPath(gc, points4, sizeof(points4)/sizeof(points4[0])));

		return gp;
	}

	ResolutionParams CalculateResolutionParameters()
	{
		ResolutionParams resParams;

		// 1920 x 1080 = m_bitmap.GetWidth() x m_bitmap.GetHeight()
		int ratio = std::round(1080.f / m_bitmap.GetHeight());
		switch (ratio)
		{
		case 0: // 1080+
		case 1: // 1080 and less
			resParams.fontSize = 45;
			break;
		case 2: // 720 and less
			resParams.fontSize = 20;
			break;
		case 3: // 432 and less
		case 4: // 308 and less
		case 5: // 240 and less
			resParams.ovalMultiplier = 0.7f;
			resParams.fontSize = 9;
			break;
		case 6: // 196 and less
		case 7: // 166 and less
		case 8: // 144 and less
			resParams.ovalMultiplier = 0.4f;
			resParams.fontSize = 4;
			break;
		case 9: // 127 and less
		default:
			resParams.ovalMultiplier = 0.2f;
			resParams.fontSize = 4;
			break;
		}

		return resParams;

	}

	void PaintFaceOval(wxGraphicsContext *gc, NLivenessAction action, float multiplier)
	{
		if (m_showFaceOval)
		{
			wxGraphicsPath path = gc->CreatePath();

			int minSize = std::min(m_bitmap.GetWidth(), m_bitmap.GetHeight());
			float faceWidth = minSize / 1.8 * m_faceOvalSizePercentage;
			float faceHeight = minSize / 1.4 * m_faceOvalSizePercentage;
			wxRect boundingRect(m_bitmap.GetWidth() / 2 - faceWidth / 2, m_bitmap.GetHeight() / 2 - faceHeight / 2, faceWidth, faceHeight);

			wxPen pen(m_faceOvalBackgroundColor, 1, wxPENSTYLE_SOLID);
			wxBrush brush(m_faceOvalBackgroundColor, wxBRUSHSTYLE_SOLID);
			gc->SetBrush(brush);
			gc->SetPen(pen);
			path.AddRectangle(0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());
			path.AddEllipse(boundingRect.x, boundingRect.y, boundingRect.width, boundingRect.height);
			gc->DrawPath(path);
			gc->SetPen(wxNullPen);
			gc->SetBrush(wxNullBrush);

			wxPen greenOvalPen(m_greenFaceOvalColor, multiplier * m_faceOvalWidth);
			wxPen grayOvalPen(m_grayFaceOvalColor, multiplier * m_faceOvalWidth);
			bool drawGreen = (action == NLivenessAction::nlaKeepStill || action == NLivenessAction::nlaBlink);
			gc->SetPen(drawGreen ? greenOvalPen : grayOvalPen);
			gc->DrawEllipse(boundingRect.x, boundingRect.y, boundingRect.width, boundingRect.height);
		}
	}

protected:

	void DrawAttributes(wxGraphicsContext *gc, const ::Neurotec::Biometrics::NLAttributes & attributes, const wxString& faceQuality, const wxString& faceConfidence, const wxString& faceId)
	{
		::Neurotec::Biometrics::NLFeaturePoint item;
		NLivenessAction action = attributes.GetLivenessAction();
		ResolutionParams resolutionParams = CalculateResolutionParameters();
		::Neurotec::Geometry::NRect rect = attributes.GetBoundingRect();
		wxGraphicsMatrix oldTransform = gc->GetTransform();

		wxDouble fontWidth, fontHeight;
		gc->SetFont(wxFont(wxFontInfo(10)), m_faceRectangleColor);
		gc->GetTextExtent(std::string(30, '*'), &fontWidth, NULL, NULL, NULL);
		int fontSize = (int)((float)rect.Width / fontWidth * 10.0f + 0.5f);
		gc->SetFont(wxFont(wxFontInfo(fontSize)), m_faceRectangleColor);
		gc->GetTextExtent(std::string(30, '*'), NULL, &fontHeight, NULL, NULL);

		int brushSize;
		float pointSize, basePointSize, half;
		if (m_faceRectangleWidth < 0) brushSize = (int)((float)m_faceRectangleWidthMultiplier * rect.Width / 100.0f + 0.5f);
		else brushSize = m_faceRectangleWidth;
		if (m_featureWidth < 0) pointSize = m_featureWidthMultiplier * rect.Width / 25.0f;
		else pointSize = m_featureWidth;
		if (m_baseFeatureWidth < 0) basePointSize = m_baseFeatureWidthMultiplier * rect.Width / 25.0f;
		else basePointSize = m_baseFeatureWidth;
		half = pointSize / 2;

		wxBrush solidBrush(m_faceRectangleColor);
		wxPen pen(m_faceRectangleColor, brushSize);
		gc->SetPen(pen);
		if (rect.Width > 0 && rect.Height > 0)
		{
			PaintFaceOval(gc, attributes.GetLivenessAction(), resolutionParams.ovalMultiplier);

			wxPen penGreen(m_faceRectangleColor, brushSize);
			penGreen.SetCap(wxCAP_PROJECTING);
			penGreen.SetJoin(wxJOIN_MITER);
			gc->SetPen(penGreen);

			wxGraphicsMatrix pathMatrix = gc->CreateMatrix();
			wxGraphicsMatrix matrix = gc->CreateMatrix();
			matrix.Translate(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
			matrix.Rotate(attributes.GetRoll() * M_PI / 180.0);
			if (m_mirrorHorizontally)
			{
				matrix.Scale(-1, 1);
				pathMatrix.Translate(rect.Width, 0);
				pathMatrix.Scale(-1, 1);
			}
			matrix.Translate(-rect.Width / 2, -rect.Height / 2);
			gc->ConcatTransform(matrix);

			if (!m_showFaceOval && m_showFaceRectangle)
			{
				wxGraphicsPath path = gc->CreatePath();
				short yaw = attributes.GetYaw();
				path.MoveToPoint(0, 0);
				path.AddLineToPoint(rect.Width, 0);
				if (yaw < 0)
				{
					path.AddLineToPoint(rect.Width - (rect.Width / 5 * yaw / 45), rect.Height / 2);
				}
				path.AddLineToPoint(rect.Width, rect.Height);
				path.AddLineToPoint(0, rect.Height);
				if (yaw > 0)
				{
					path.AddLineToPoint(-(rect.Width / 5 * yaw / 45), rect.Height / 2);
				}
				path.CloseSubpath();
				path.Transform(pathMatrix);
				gc->StrokePath(path);
			}

			if (!m_showFaceOval && m_showTokenImageRectangle)
			{
				::Neurotec::Geometry::NRect token = attributes.GetTokenImageRect();
				if (token.Width > 0 && token.Height > 0)
				{
					double cx = token.X + token.Width / 2.0;
					double cy = token.Y + token.Height / 2.0;

					wxGraphicsMatrix m = gc->CreateMatrix();
					m.Translate(cx, cy);
					m.Rotate(attributes.GetRoll() * M_PI / 180.0);
					if (m_mirrorHorizontally) m.Scale(-1, 1);
					m.Translate(-cx, -cy);

					gc->SetTransform(oldTransform);
					gc->ConcatTransform(m);

				#if wxCHECK_VERSION(3, 1, 0)
					wxPen tokenPen(m_tokenImageColor, 1, wxPENSTYLE_USER_DASH);
				#else
					wxPen tokenPen(m_tokenImageColor, 1, wxUSER_DASH);
				#endif
					wxDash dashPattern[] = {(wxDash)(brushSize  * 6), (wxDash)(brushSize * 10)};
					tokenPen.SetDashes(2, dashPattern);

					gc->SetBrush(wxNullBrush);
					gc->SetPen(tokenPen);
					gc->DrawRectangle(token.X, token.Y, token.Width, token.Height);

					gc->SetTransform(oldTransform);
					gc->ConcatTransform(matrix);
				}
			}

			gc->SetPen(penGreen);

			if (m_showFaceConfidence && !faceConfidence.IsEmpty() && action == nlaNone)
			{
				gc->DrawText(faceConfidence, 0, rect.Height + fontHeight/3);
			}

			if (m_showFaceQuality && !faceQuality.IsEmpty() && action == nlaNone)
			{
				double textWidth, textHeight;
				gc->GetTextExtent(faceQuality, &textWidth, &textHeight, NULL, NULL);
				gc->DrawText(faceQuality, rect.Width - textWidth, rect.Height + fontHeight/3);
			}

			if (m_showGender || m_showProperties || m_showExpression || m_showEmotion || m_showAge || m_showEthnicity)
			{
				wxString value = GetDetailsString(attributes);
				if (value != wxEmptyString)
				{
					double textWidth;
					double faceWidth = rect.Width;
					gc->GetTextExtent(value, &textWidth, NULL, NULL, NULL);
					double offset = textWidth > faceWidth ? (textWidth - faceWidth) / 2 : 0;
					gc->DrawText(value, 0 - offset, 0 - fontHeight);
				}
			}

			if (!faceId.IsEmpty())
			{
				gc->DrawText(faceId, 4, rect.Height - fontHeight);
			}

			gc->SetTransform(oldTransform);

			half = pointSize / 2;
			if (m_showEyes)
			{
				::Neurotec::Biometrics::NLFeaturePoint left = attributes.GetLeftEyeCenter();
				::Neurotec::Biometrics::NLFeaturePoint right = attributes.GetRightEyeCenter();
				if ((IsConfidenceOk(left.Confidence) || IsConfidenceOk(right.Confidence)))
				{
					if (IsConfidenceOk(left.Confidence) && IsConfidenceOk(right.Confidence))
					{
						gc->StrokeLine((NShort)left.X, (NShort)left.Y, (NShort)right.X, (NShort)right.Y);
					}
					gc->SetBrush(solidBrush);
					if (IsConfidenceOk(left.Confidence))
					{
						gc->DrawEllipse(left.X - half, left.Y - half, pointSize, pointSize);
					}
					if (IsConfidenceOk(right.Confidence))
					{
						gc->DrawEllipse(right.X - half, right.Y - half, pointSize, pointSize);
					}
					gc->SetBrush(wxNullBrush);
					if (m_showEyesConfidence)
					{
						if (IsConfidenceOk(right.Confidence))
						{
							gc->DrawText(wxString::Format(wxT("%d"), right.Confidence), right.X - pointSize, right.Y + pointSize);
						}
						if (IsConfidenceOk(left.Confidence))
						{
							gc->DrawText(wxString::Format(wxT("%d"), left.Confidence), left.X - pointSize, left.Y + pointSize);
						}
					}
				}
			}
			if (m_showNose)
			{
				::Neurotec::Biometrics::NLFeaturePoint nose = attributes.GetNoseTip();
				if (IsConfidenceOk(nose.Confidence))
				{
					gc->SetBrush(solidBrush);
					gc->DrawEllipse(nose.X - half, nose.Y - half, pointSize, pointSize);
				
					if (m_showNoseConfidence)
					{
						gc->DrawText(wxString::Format(wxT("%d"), nose.Confidence), nose.X - pointSize, nose.Y + pointSize);
					}
					gc->SetBrush(wxNullBrush);
				}
			}
			if (m_showMouth)
			{
				::Neurotec::Biometrics::NLFeaturePoint mouth = attributes.GetMouthCenter();
				if (IsConfidenceOk(mouth.Confidence))
				{
					gc->SetBrush(solidBrush);
					gc->DrawEllipse(mouth.X - half, mouth.Y - half, pointSize, pointSize);
					gc->SetBrush(wxNullBrush);
				
					if (m_showMouthConfidence)
					{
						gc->DrawText(wxString::Format(wxT("%d"), mouth.Confidence), mouth.X - pointSize, mouth.Y + pointSize);
					}
				}
			}
			gc->SetPen(wxNullPen);

			if (m_showBaseFeaturePoints)
			{
				gc->SetBrush(solidBrush);
				NArrayWrapper< ::Neurotec::Biometrics::NLFeaturePoint> points = attributes.GetFeaturePoints().GetAll();
				for(int i = 0; i < points.GetCount(); i++)
				{
					item = points[i];
					if (item.Confidence > 0)
					{
						gc->DrawEllipse(item.X - half, item.Y - half, basePointSize, basePointSize);
					}
				}
			}
		}

		if (action != nlaNone)
		{
			bool rotateYaw = (action & nlaRotateYaw) == nlaRotateYaw;
			bool blink = (action & nlaBlink) == nlaBlink;
			bool keepStill = (action & nlaKeepStill) == nlaKeepStill;
			bool keepRotatingYaw = (action & nlaKeepRotatingYaw) == nlaKeepRotatingYaw;
			bool toCenter = (action & nlaTurnToCenter) == nlaTurnToCenter;
			bool left = (action & nlaTurnLeft) == nlaTurnLeft;
			bool right = (action & nlaTurnRight) == nlaTurnRight;
			bool up = (action & nlaTurnUp) == nlaTurnUp;
			bool down = (action & nlaTurnDown) == nlaTurnDown;
			bool closer = (action & nlaMoveCloser) == nlaMoveCloser;
			bool back = (action & nlaMoveBack) == nlaMoveBack;
			bool showScore = !rotateYaw && !blink && !keepStill && !keepRotatingYaw && !toCenter && !left && !right && !up && !down && !closer && !back;

			NByte score = attributes.GetLivenessScore();
			wxString text;
			if (blink) text = wxT("Please blink");
			else if (rotateYaw) text = wxT("Turn face on target");
			else if (keepStill) text = wxT("Please keep still");
			else if (keepRotatingYaw) text = wxT("Turn face from side to side");
			else if (toCenter) text = wxT("Turn face to the center");
			else if (left) text = wxT("Turn face left");
			else if (right) text = wxT("Turn face right");
			else if (up) text = wxT("Turn face up");
			else if (down) text = wxT("Turn face down");
			else if (closer) text = wxT("Move closer");
			else if (back) text = wxT("Move back");

			if (showScore && score <= 100)
			{
				text += wxString::Format(wxT(", Score: %d"), score);
			}

			wxBrush livenessBrush(m_livenessItemsColor);
			wxPen livenessPen(m_livenessItemsColor);
			gc->SetPen(livenessPen);
			gc->SetFont(wxFont(wxFontInfo(resolutionParams.fontSize)), m_showFaceOval ? m_livenessItemsFaceOvalColor : m_livenessItemsColor);

			if (!text.IsEmpty())
			{
				double textWidth, textHeight, descent, externalLeading;
				gc->GetTextExtent(text, &textWidth, &textHeight, &descent, &externalLeading);
				float fx = m_bitmap.GetWidth() / 2 - textWidth / 2;
				if (m_mirrorHorizontally)
				{
					gc->SetTransform(oldTransform);
					gc->Translate(m_bitmap.GetWidth(), 0);
					gc->Scale(-1, 1);
				}
				gc->DrawText(text, fx, 0);
			}

			gc->SetTransform(oldTransform);
			gc->Translate(m_bitmap.GetWidth(), 0);
			gc->Scale(-1, 1);

			float yaw = attributes.GetYaw();
			float targetYaw = attributes.GetLivenessTargetYaw();
			int imageWidth = m_bitmap.GetWidth();
			float width = (float)imageWidth / 4.0f;
			float height = (float)width / 8.0f;
			float y = m_bitmap.GetHeight() - height * 3.0f;
			wxRect imageRect(0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());

			if (rotateYaw)
			{
				wxPoint center;
				wxRect playArea(1.5f * width, y, width, height);
				gc->SetBrush(wxNullBrush);
				gc->DrawRectangle(playArea.x, playArea.y, playArea.width, playArea.height);
				gc->SetBrush(livenessBrush);
				if (!blink)
				{
					wxGraphicsPath arrow = CreateArrowPath(gc);
					PreparePath(gc, arrow, yaw, playArea, targetYaw < yaw);
					gc->DrawPath(arrow);

					wxGraphicsPath target = CreateTargetPath(gc);
					center = PreparePath(gc, target, targetYaw, playArea, false);
					gc->DrawPath(target);
				}
				else
				{
					wxGraphicsPath blinkPath = CreateBlinkPath(gc);
					center = PreparePath(gc, blinkPath, yaw, playArea, targetYaw < yaw);
					gc->DrawPath(blinkPath);
				}
				gc->SetBrush(wxNullBrush);
				
				gc->SetFont(wxFont(wxFontInfo(resolutionParams.fontSize)), m_livenessItemsColor);
				text = blink ? wxT("Blink") : wxT("Turn here");
				double textWidth, textHeight, descent, externalLeading;
				gc->GetTextExtent(text, &textWidth, &textHeight, &descent, &externalLeading);

				float fx, fy;
				if (m_mirrorHorizontally)
				{
					fx = center.x - textWidth / 2.0f;
					fy = playArea.y - textHeight;
				}
				else
				{
					// flip liveness text
					gc->Translate(m_bitmap.GetWidth(), 0);
					gc->Scale(-1, 1);
					// fix liveness text position
					wxPoint mirroredCenter = MirrorPoint(center, imageRect);
					fx = mirroredCenter.x - textWidth / 2.0f;
					fy = mirroredCenter.y - textHeight;
				}
				gc->DrawText(text, fx, fy);
			}
			gc->SetTransform(oldTransform);
		}

		DrawIcaoArrows(gc, attributes.GetIcaoWarnings(), attributes.GetBoundingRect(), attributes.GetRoll(), attributes.GetYaw());
		gc->SetFont(wxNullFont, wxNullColour);
	}

	wxPoint MirrorPoint(const wxPoint & point, const wxRect & rect)
	{
		float cx = rect.x + rect.width / 2.0f;

		float mirroredX = 2 * cx - point.x;
		float mirroredY = point.y;

		return wxPoint{ (int)mirroredX, (int)mirroredY };
	}

	void RotateAt(wxGraphicsContext * gc, double angle, double x, double y)
	{
		gc->Translate(x, y);
		gc->Rotate(angle);
		gc->Translate(-x, -y);
	}

	void ScaleAt(wxGraphicsContext * gc, double scaleX, double scaleY, double x, double y)
	{
		gc->Translate(x, y);
		gc->Scale(scaleX, scaleY);
		gc->Translate(-x, -y);
	}

	void ScalePath(wxGraphicsContext * gc, wxGraphicsPath & gp, double scale)
	{
		wxGraphicsMatrix m = gc->CreateMatrix();
		m.Scale(scale, scale);
		gp.Transform(m);
	}

	void DrawIcaoArrows(wxGraphicsContext * gc, ::Neurotec::Biometrics::NIcaoWarnings warnings, const ::Neurotec::Geometry::NRect & rect, float roll, float yaw)
	{
		if (warnings != niwNone && m_showIcaoArrows)
		{
			wxBrush icaoBrush(m_icaoColor);
			wxPen icaoPen(m_icaoColor);

			gc->SetBrush(icaoBrush);
			gc->SetPen(icaoPen);

			double rollInRadians = roll * M_PI / 180.0;
			if ((warnings & (niwRollLeft | niwRollRight)) != 0)
			{
				bool rollLeft = (warnings & niwRollLeft) == niwRollLeft;

				wxGraphicsPath gp = CreateRollPath(gc);

				wxRect2DDouble bounds = gp.GetBox();
				double scale = rect.Width / 5.0 / bounds.m_width;

				wxGraphicsMatrix restore = gc->GetTransform();
				gc->Translate(rect.X, rect.Y);
				RotateAt(gc, rollInRadians, rect.Width / 2.0, rect.Height / 2.0);
				if (rollLeft) ScaleAt(gc, -1, 1, rect.Width / 2.0, rect.Height / 2.0);
				gc->Translate(-bounds.m_width / 2.0 * scale, -bounds.m_height / 2.0 * scale);

				ScalePath(gc, gp, scale);
				gc->DrawPath(gp);
				gc->SetTransform(restore);
			}

			gc->SetBrush(wxNullBrush);
			if ((warnings & (niwYawLeft | niwYawRight)) != 0)
			{
				if (((warnings & niwYawLeft) != 0 && (warnings & niwTooEast) == 0) ||
					((warnings & niwYawRight) != 0 && (warnings & niwTooWest) == 0) || (warnings & niwTooNear) != 0)
				{
					bool yawRight = (warnings & niwYawRight) != 0;

					wxGraphicsPath gp = CreateYawPath(gc);
					wxRect2DDouble bounds = gp.GetBox();
					double scale = rect.Width / 5.0 / bounds.m_width;
					double centerX = (bounds.m_x + bounds.m_width) / 2.0 * scale;
					double centerY = (bounds.m_y + bounds.m_height) / 2.0 * scale;

					double offset = (rect.Width / 5.0 * yaw / 45.0);

					wxGraphicsMatrix restore = gc->GetTransform();
					gc->Translate(rect.X, rect.Y);
					RotateAt(gc, rollInRadians, rect.Width / 2.0, rect.Height / 2.0);
					if (yawRight)
					{
						ScaleAt(gc, -1, 1, rect.Width / 2.0, rect.Height / 2.0);
						offset *= -1;
					}

					gc->Translate(rect.Width - centerX - offset, rect.Height / 2.0 - centerY);
					ScalePath(gc, gp, scale);
					gc->DrawPath(gp);
					gc->SetTransform(restore);
				}
			}

			if ((warnings & niwTooNear) == 0)
			{
				if ((warnings & (niwTooSouth | niwTooNorth | niwTooEast | niwTooWest)) != 0)
				{
					wxGraphicsPath gp = CreateMovePath(gc);
					wxRect2DDouble bounds = gp.GetBox();
					double scale = rect.Width / 5.0 / bounds.m_width;
					double centerY = (bounds.m_y + bounds.m_height) / 2.0 * scale;

					ScalePath(gc, gp, scale);

					wxGraphicsMatrix restore = gc->GetTransform();
					double cx = rect.Width / 2.0;
					double cy = rect.Height / 2.0;

					gc->Translate(rect.X, rect.Y);
					RotateAt(gc, rollInRadians, cx, cy);
					if ((warnings & niwTooEast) != 0)
					{
						double offset = (warnings & niwYawLeft) != 0 ? (rect.Width / 5.0f * yaw / 45.0f) : 0;
						double dx = rect.Width + 5 - offset;
						double dy = cy - centerY;
						gc->Translate(dx, dy);
						gc->DrawPath(gp);
						gc->Translate(-dx, -dy);
					}
					if ((warnings & niwTooWest) == niwTooWest)
					{
						double offset = (warnings & niwYawRight) != 0 ? (rect.Width / 5.0 * yaw / 45.0) : 0;
						wxGraphicsMatrix r = gc->GetTransform();
						ScaleAt(gc, -1, 1, cx, cy);
						gc->Translate(rect.Width + 5 + offset, rect.Height / 2.0 - centerY);
						gc->DrawPath(gp);
						gc->SetTransform(r);
					}
					if ((warnings & niwTooSouth) != 0)
					{
						wxGraphicsMatrix r = gc->GetTransform();
						RotateAt(gc, -90 * M_PI / 180.0, cx, cy);
						gc->Translate(rect.Height + 5, rect.Width / 2.0 - centerY);
						gc->DrawPath(gp);
						gc->SetTransform(r);
					}
					if ((warnings & niwTooNorth) != 0)
					{
						wxGraphicsMatrix r = gc->GetTransform();
						ScaleAt(gc, 1, -1, cx, cy);
						RotateAt(gc, -90 * M_PI / 180.0, cx, cy);
						gc->Translate(rect.Height + 5, rect.Width / 2.0 - centerY);
						gc->DrawPath(gp);
						gc->SetTransform(r);
					}

					gc->SetTransform(restore);
				}
			}
			if ((warnings & (niwPitchDown | niwPitchUp)) != 0)
			{
				if (((warnings & niwPitchDown) != 0 && (warnings & niwTooSouth) == 0) ||
					((warnings & niwPitchUp) != 0 && (warnings & niwTooNorth) == 0) || (warnings & niwTooNear) != 0)
				{
					bool up = (warnings & niwPitchUp) != 0;

					double cx = rect.Width / 2.0;
					double cy = rect.Height / 2.0;

					wxGraphicsMatrix restore = gc->GetTransform();
					gc->Translate(rect.X, rect.Y);
					RotateAt(gc, rollInRadians, cx, cy);

					wxGraphicsPath gp = CreatePitchPath(gc);
					wxRect2DDouble bounds = gp.GetBox();
					double scale = rect.Width / 5.0 / bounds.m_width;
					double centerX = (bounds.m_x + bounds.m_width) / 2.0 * scale;
					double centerY = (bounds.m_y + bounds.m_height) / 2.0 * scale;

					if (up) ScaleAt(gc, 1, -1, cx, cy);
					gc->Translate(cx - centerX, -centerY);

					ScalePath(gc, gp, scale);
					gc->DrawPath(gp);
					gc->SetTransform(restore);
				}
			}
		}
	}

	wxString GetDetailsString( ::Neurotec::Biometrics::NLAttributes attributes)
	{
		wxString value = wxEmptyString;
		if (m_showGender && IsConfidenceOk(attributes.GetGenderConfidence()))
		{
			value = NEnum::ToString(NBiometricTypes::NGenderNativeTypeOf(), attributes.GetGender());
			if (m_showGenderConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetGenderConfidence()));
		}
		if (m_showAge && attributes[nbaiAge].GetValue() < 254)
		{
			if (value != wxEmptyString) value.Append(wxT(", "));
			value.Append(wxString::Format(wxT("Age: %d"), attributes[nbaiAge].GetValue()));
		}
		if (m_showExpression && attributes[nbaiSmile].GetValue())
		{
			if (value != wxEmptyString) value.Append(wxT(", "));
			value.append(wxT("Smile"));
			if (m_showExpressionConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiSmile].GetValue()));
		}
		if (m_showProperties)
		{
			if (IsConfidenceOk(attributes[nbaiGlasses].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.append(wxT("Glasses"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiGlasses].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiMouthOpen].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.append(wxT("Mouth Open"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiMouthOpen].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiEyesOpen].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Eyes open"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiEyesOpen].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiDarkGlasses].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Dark Glasses"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiDarkGlasses].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiBeard].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Beard"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiBeard].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiMustache].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Mustache"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiMustache].GetValue()));
			}
			if (IsConfidenceOk(attributes[nbaiHeadCovering].GetValue()))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Head covered"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes[nbaiHeadCovering].GetValue()));
			}
		}
		if (m_showEmotion)
		{
			NByte maxConfidence = 0;
			NByte confidence = 0;
			wxString valueString = wxEmptyString;

			confidence = attributes[nbaiEmotionNeutral].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Neutral");
			}
			confidence = attributes[nbaiEmotionAnger].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Anger");
			}
			confidence = attributes[nbaiEmotionContempt].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Contempt");
			}
			confidence = attributes[nbaiEmotionDisgust].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Disgust");
			}
			confidence = attributes[nbaiEmotionFear].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Fear");
			}
			confidence = attributes[nbaiEmotionHappiness].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Happiness");
			}
			confidence = attributes[nbaiEmotionSadness].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Sadness");
			}
			confidence = attributes[nbaiEmotionSurprise].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Surprise");
			}

			if (valueString != wxEmptyString)
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(valueString);
				if (m_showEmotionConfidence) value.Append(wxString::Format(wxT("(%d)"), maxConfidence));
			}
		}
		if (m_showEthnicity)
		{
			NByte maxConfidence = 0;
			NByte confidence = 0;
			wxString valueString = wxEmptyString;

			confidence = attributes[nbaiEthnicityWhite].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("White");
			}
			confidence = attributes[nbaiEthnicityBlack].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Black");
			}
			confidence = attributes[nbaiEthnicityAsian].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Asian");
			}
			confidence = attributes[nbaiEthnicityIndian].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Indian");
			}
			confidence = attributes[nbaiEthnicityHispanic].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Hispanic");
			}
			confidence = attributes[nbaiEthnicityArabian].GetValue();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				valueString = wxT("Arabian");
			}

			if (valueString != wxEmptyString)
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(valueString);
				if (m_showEthnicityConfidence) value.Append(wxString::Format(wxT("(%d)"), maxConfidence));
			}
		}
		return value;
	}
	static bool IsConfidenceOk(NByte confidence) { return confidence > 0 && confidence <= 100; }
	void UpdateFps()
	{
		wxLongLong currentTime = ::wxGetLocalTimeMillis();
		float previousFps = m_currentFps;
		m_currentFps = 0.0f;
		if (currentTime - m_lastTime > 5000)
		{
			m_frameCount = 0;
			m_firstTime = currentTime;
		}
		else
		{
			m_frameCount++;
			if (m_frameCount == MAX_FPS_ENTRIES)
			{
				m_currentFps = (float)((m_frameCount.ToDouble() * 1000.0) / (double)(currentTime - m_firstTime).ToDouble());
			}
			else if (m_frameCount > MAX_FPS_ENTRIES)
			{
				float frameFps = (float)(1000.0 / (currentTime - m_lastTime).ToDouble());
				const float newFpsWeight = (float)1.0f / (float)MAX_FPS_ENTRIES;
				m_currentFps = previousFps * (1.0f - newFpsWeight) + frameFps * newFpsWeight;
			}
		}
		m_lastTime = currentTime;
	}
protected:
	wxBitmap m_bitmap;
	wxArrayString m_faceIds;
	wxColour m_faceRectangleColor;
	wxColour m_livenessItemsColor;
	wxColour m_livenessItemsFaceOvalColor;
	bool m_showFaceOval;
	bool m_showFaceRectangle;
	wxLongLong m_lastTime;
	wxLongLong m_firstTime;
	wxLongLong m_frameCount;
	float m_currentFps;
	bool m_showFps;
	bool m_showEyes;
	bool m_showNose;
	bool m_showMouth;
	bool m_showNoseConfidence;
	bool m_showEyesConfidence;
	bool m_showFaceConfidence;
	bool m_showFaceQuality;
	bool m_showMouthConfidence;
	bool m_showGender;
	bool m_showGenderConfidence;
	bool m_showExpression;
	bool m_showExpressionConfidence;
	bool m_showProperties;
	bool m_showEmotion;
	bool m_showEmotionConfidence;
	bool m_showPropertiesConfidence;
	bool m_showBaseFeaturePoints;
	bool m_mirrorHorizontally;
	bool m_showAge;
	bool m_showEthnicity;
	bool m_showEthnicityConfidence;
	::Neurotec::Biometrics::NFace m_face;
	std::vector< ::Neurotec::NObject> m_attributes;
	wxColour m_icaoColor;
	bool m_showIcaoArrows;
	bool m_showTokenImageRectangle;
	wxColour m_tokenImageColor;
	int m_faceRectangleWidth;
	int m_featureWidth;
	int m_baseFeatureWidth;
	float m_faceRectangleWidthMultiplier;
	float m_featureWidthMultiplier;
	float m_baseFeatureWidthMultiplier;
	float m_faceOvalSizePercentage;
	wxColour m_faceOvalBackgroundColor;
	wxColour m_greenFaceOvalColor;
	wxColour m_grayFaceOvalColor;
	int m_faceOvalWidth;
};

}}}

#endif // !WX_NFACE_VIEW_HPP_INCLUDED
