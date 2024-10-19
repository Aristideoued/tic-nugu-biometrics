#ifndef S_CARD_HPP_INCLUDED
#define S_CARD_HPP_INCLUDED

#include <SmartCards/Interop/SCardApi.hpp>
#include <map>

namespace Neurotec { namespace SmartCards { namespace Interop {

	class HSCard
	{
	public:
		typedef SCardApi::HSCard HandleType;

	private:
		typedef std::map<HandleType, NSizeType> RefMap;

		HandleType handle_;
		SCardAction disposition_;
		NBool isDisposed_;

	protected:
		HSCard(HandleType handle)
			: handle_(handle),
			disposition_(scaReset),
			isDisposed_(NTrue)
		{
			Ref();
		}

		virtual ~HSCard() 
		{
			UnRef();
		}

	private:
		RefMap * GetRefMap() const
		{
			static RefMap refs;
			return &refs;
		}

		void Ref()
		{
			if(!isDisposed_) UnRef();
			if (GetRefMap()->find(handle_) == GetRefMap()->end())
			{
				GetRefMap()->insert(RefMap::value_type(handle_, 1));
			}
			else 
			{
				(*GetRefMap())[handle_] += 1;
			}
			isDisposed_ = NFalse;
		}

		void UnRef()
		{
			if(isDisposed_) return;
			if (GetRefMap()->find(handle_) != GetRefMap()->end())
			{
				if((*GetRefMap())[handle_] == 1)
				{
					GetRefMap()->erase(handle_);
					SCardApi::Disconnect(handle_, disposition_);
				}
				else
				{
					(*GetRefMap())[handle_] -= 1;
				}
			}
			isDisposed_ = NTrue;
		}

	protected:
		void SetHandle(HandleType handle)
		{
			if(handle_ != handle)
			{
				UnRef();
				handle_ = handle;
				Ref();
			}
		}

		void Dispose(SCardAction disposition)
		{
			disposition_ = disposition;
			UnRef();
		}

	public:
		HandleType GetHandle() const
		{
			return handle_;
		}
	};

}}}

namespace Neurotec { namespace SmartCards {
	class SCard : public Interop::HSCard
	{
	public:
		SCard(Interop::SCardApi::HSCardManager hContext, const NString& reader, SCardShare shareMode,
			SCardProtocols preferredProtocols, SCardProtocols * activeProtocol)
			: HSCard(Interop::SCardApi::Connect(hContext, reader, shareMode, preferredProtocols, activeProtocol))
		{
		}

		SCard(HandleType handle)
			: HSCard(handle)
		{
		}

		SCard(const SCard& scard)
			: HSCard(scard.GetHandle())
		{
		}

#ifdef N_CPP11
		SCard(const SCard&& scard)
			: HSCard(scard.GetHandle())
		{
		}
#endif

		bool operator==(const SCard& scard) const
		{
			return GetHandle() == scard.GetHandle();
		}

		bool operator!=(const SCard& scard) const
		{
			return GetHandle() != scard.GetHandle();
		}

		SCard operator=(const SCard& scard)
		{
			SetHandle(scard.GetHandle());
			return *this;
		}

		SCardProtocols Reconnect(SCardShare shareMode, SCardProtocols preferredProtocols, SCardAction initialization) const
		{
			return Interop::SCardApi::Reconnect(GetHandle(), shareMode, preferredProtocols, initialization);
		}

		void Disconnect(SCardAction disposition)
		{
			Dispose(disposition);
		}

		void BeginTransaction() const
		{
			Interop::SCardApi::BeginTransaction(GetHandle());
		}

		void EndTransaction(SCardAction disposition) const
		{
			Interop::SCardApi::EndTransaction(GetHandle(), disposition);
		}

		::Neurotec::IO::NBuffer GetAtr() const
		{
			return Interop::SCardApi::GetAtr(GetHandle());
		}

		NArrayWrapper<NString> GetReaderNames() const
		{
			return Interop::SCardApi::GetReaderNames(GetHandle());
		}

		NSizeType Transmit(const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer, ::Neurotec::IO::NBuffer& recvBuffer) const
		{
			return Interop::SCardApi::Transmit(GetHandle(), sendPci, sendBuffer, recvBuffer);
		}

		NSizeType Transmit(const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer, SCardIORequest& recvPci,
			::Neurotec::IO::NBuffer& recvBuffer) const
		{
			return Interop::SCardApi::Transmit(GetHandle(), sendPci, sendBuffer, recvPci, recvBuffer);
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2,
			const ::Neurotec::IO::NBuffer& data, ::Neurotec::IO::NBuffer& responseData, NSizeType * pNr) const
		{
			ApduStatus value;
			*pNr = Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, data.GetSize() > 255 || responseData.GetSize() > 256,
				data.GetHandle(), responseData.GetHandle(), &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2, bool isExtended,
			const ::Neurotec::IO::NBuffer& data) const
		{
			ApduStatus value;
			Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, isExtended,
				data.GetHandle(), 0, &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2, 
			const ::Neurotec::IO::NBuffer& data) const
		{
			ApduStatus value;
			Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, data.GetSize() > 255,
				data.GetHandle(), 0, &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2, bool isExtended,
			const ::Neurotec::IO::NBuffer& responseData, NSizeType * pNr) const
		{
			ApduStatus value;
			*pNr = Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, isExtended,
				0, responseData.GetHandle(), &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2,
			const ::Neurotec::IO::NBuffer& responseData, NSizeType * pNr) const
		{
			ApduStatus value;
			*pNr = Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, responseData.GetSize() > 256,
				0, responseData.GetHandle(), &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2) const
		{
			ApduStatus value;
			Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, false, 0, 0, &value);
			return value;
		}

		ApduStatus TransmitApdu(const ApduClass& apduClass, const ApduInstruction& instruction, NByte p1, NByte p2, bool isExtended,
			const ::Neurotec::IO::NBuffer& data, const ::Neurotec::IO::NBuffer& responseData, NSizeType * pNr) const
		{
			ApduStatus value;
			*pNr = Interop::SCardApi::TransmitApdu(GetHandle(), apduClass, instruction, p1, p2, isExtended,
				data.GetHandle(), responseData.GetHandle(), &value);
			return value;
		}

		void Control(NUInt controlCode) const
		{
			::Neurotec::IO::NBuffer inBuffer = ::Neurotec::IO::NBuffer::GetEmpty();
			::Neurotec::IO::NBuffer outBuffer = ::Neurotec::IO::NBuffer::GetEmpty();
			Control(controlCode, inBuffer, outBuffer);
		}

		NSizeType Control(NUInt controlCode, const ::Neurotec::IO::NBuffer& inBuffer) const
		{
			::Neurotec::IO::NBuffer outBuffer = ::Neurotec::IO::NBuffer::GetEmpty();
			return Control(controlCode, inBuffer, outBuffer);
		}

		NSizeType Control(NUInt controlCode, const ::Neurotec::IO::NBuffer& inBuffer, const ::Neurotec::IO::NBuffer& outBuffer) const
		{
			return Interop::SCardApi::Control(GetHandle(), controlCode, inBuffer.GetHandle(), outBuffer.GetHandle());
		}

		void Control(NUInt controlCode, NUInt inValue) const
		{
			Interop::SCardApi::Control(GetHandle(), controlCode, inValue, 0);
		}

		NSizeType Control(NUInt controlCode, NUInt inValue, const ::Neurotec::IO::NBuffer& outBuffer) const
		{
			return Interop::SCardApi::Control(GetHandle(), controlCode, inValue, outBuffer.GetHandle());
		}

		NUInt ControlAsDWord(NUInt controlCode) const
		{
			return Interop::SCardApi::ControlAsDWord(GetHandle(), controlCode, 0);
		}

		NUInt ControlAsDWord(NUInt controlCode, const ::Neurotec::IO::NBuffer& inBuffer) const
		{
			return Interop::SCardApi::ControlAsDWord(GetHandle(), controlCode, inBuffer.GetHandle());
		}

		NUInt ControlAsDWord(NUInt controlCode, NUInt inValue) const
		{
			return Interop::SCardApi::ControlDWordAsDWord(GetHandle(), controlCode, inValue);
		}

		NSizeType GetReaderCapabilities(NUInt tag, const ::Neurotec::IO::NBuffer& attr) const
		{
			return Interop::SCardApi::GetAttribLength(GetHandle(), tag, attr);
		}

		::Neurotec::IO::NBuffer GetReaderCapabilities(NUInt tag) const
		{
			return Interop::SCardApi::GetAttribAsBuffer(GetHandle(), tag);
		}

		NString GetReaderCapabilitiesAsString(NUInt tag) const
		{
			return Interop::SCardApi::GetAttribAsString(GetHandle(), tag);
		}

		NArrayWrapper<NString> GetReaderCapabilitiesAsStringArray(NUInt tag) const
		{
			return Interop::SCardApi::GetAttribAsStrings(GetHandle(), tag);
		}

		NByte GetReaderCapabilitiesAsByte(NUInt tag) const
		{
			return Interop::SCardApi::GetAttribAsByte(GetHandle(), tag);
		}

		NULong GetReaderCapabilitiesAsDWord(NUInt tag) const
		{
			return Interop::SCardApi::GetAttribAsLong(GetHandle(), tag);
		}

		void SetReaderCapabilities(NUInt tag) const
		{
			Interop::SCardApi::SetAttrib(GetHandle(), tag, (HNBuffer)0);
		}

		void SetReaderCapabilities(NUInt tag, const ::Neurotec::IO::NBuffer& attr) const
		{
			Interop::SCardApi::SetAttrib(GetHandle(), tag, attr.GetHandle());
		}

		void SetReaderCapabilities(NUInt tag, const NString& value) const
		{
			Interop::SCardApi::SetAttrib(GetHandle(), tag, value);
		}

		void SetReaderCapabilities(NUInt tag, const NArrayWrapper<NString>& value) const
		{
			Interop::SCardApi::SetAttrib(GetHandle(), tag, value);
		}

		void SetReaderCapabilities(NUInt tag, NByte value) const
		{
			Interop::SCardApi::SetAttrib(GetHandle(), tag, value);
		}

		SCardState GetState() const
		{
			return Interop::SCardApi::GetState(GetHandle());
		}

		SCardProtocols GetProtocol() const
		{
			return Interop::SCardApi::GetProtocol(GetHandle());
		}
	};

}}

#endif
