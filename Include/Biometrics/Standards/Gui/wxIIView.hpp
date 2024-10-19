#ifndef WX_IIVIEW_HPP_INCLUDED
#define WX_IIVIEW_HPP_INCLUDED

#include <math.h>

#include <Core/NError.hpp>
#include <Biometrics/Standards/IIRecord.hpp>
#include <Gui/wxNView.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards { namespace Gui
{

class wxIIView : public Neurotec::Gui::wxNView
{
public:
	wxIIView(wxWindow *parent, wxWindowID winid = wxID_ANY) :
		wxNView(parent, winid),
		m_record(NULL),
		m_w(0),
		m_h(0),
		m_bitmap(),
		m_imageError((::Neurotec::NError::HandleType)NULL)
	{
	}

	virtual ~wxIIView()
	{
	}

virtual void OnDraw(wxGraphicsContext *gc)
{
	if (m_bitmap.IsOk())
	{
		gc->DrawBitmap(m_bitmap, 0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());
	}
	else if (!m_imageError.IsNull())
	{
		gc->SetBrush(*wxWHITE_BRUSH);
		gc->DrawRectangle(0, 0, m_w, m_h);

		gc->SetPen(*wxRED_PEN);
		gc->StrokeLine(0, 0, m_w - 1, m_h - 1);
		gc->StrokeLine(0, m_h - 1, m_w - 1, m_h - 1);

		gc->SetPen(*wxBLACK_PEN);
		gc->DrawText(m_imageError.GetMessage(), 0 , 0);
	}
}

::Neurotec::Biometrics::Standards::IirIrisImage GetRecord() const
{
	return m_record;
}

void SetRecord(const ::Neurotec::Biometrics::Standards::IirIrisImage & value)
{
	m_bitmap = wxNullImage;
	m_imageError = NULL;
	m_record = value;

	if (value.IsNull())
	{
		m_w = 0;
		m_h = 0;
	}
	else
	{
		m_w = value.GetOwner().GetRawImageWidth();
		m_h = value.GetOwner().GetRawImageHeight();
		try
		{
			::Neurotec::Images::NImage image = m_record.ToNImage();
			m_bitmap = image.ToBitmap();
		}
		catch (::Neurotec::NError & e)
		{
			m_imageError = e;
		}
	}
	SetViewSize(m_w, m_h);
}

private:
	::Neurotec::Biometrics::Standards::IirIrisImage m_record;
	::Neurotec::NInt m_w, m_h;
	wxImage m_bitmap;
	::Neurotec::NError m_imageError;
};

}}}}

#endif // !WX_IIVIEW_HPP_INCLUDED
