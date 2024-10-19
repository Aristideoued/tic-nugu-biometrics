#ifndef S_CARD_MANAGER_HPP_INCLUDED
#define S_CARD_MANAGER_HPP_INCLUDED

#include <SmartCards/SCard.hpp>

namespace Neurotec { namespace SmartCards { namespace Interop {

	class HSCardManager
	{
	public:
		typedef SCardApi::HSCardManager HandleType;

	private:
		typedef std::map<HandleType, NSizeType> RefMap;

		HandleType handle_;
		NBool isDisposed_;

	protected:
		HSCardManager(HandleType handle)
			: handle_(handle),
			isDisposed_(NTrue)
		{
			Ref();
		}

		virtual ~HSCardManager() 
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
					SCardApi::ReleaseContext(handle_);
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

		void Dispose()
		{
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

	class SCardManager : public Interop::HSCardManager
	{
	public:
		SCardManager(SCardScope scope)
			: HSCardManager(Interop::SCardApi::EstablishContext(scope))
		{
		}

		SCardManager(HandleType handle)
			: HSCardManager(handle)
		{
		}

		SCardManager(const SCardManager& manager)
			: HSCardManager(manager.GetHandle())
		{
		}

#ifdef N_CPP11
		SCardManager(const SCardManager&& manager)
			: HSCardManager(manager.GetHandle())
		{
		}
#endif

		bool operator==(const SCardManager& manager) const
		{
			return GetHandle() == manager.GetHandle();
		}

		bool operator!=(const SCardManager& manager) const
		{
			return GetHandle() != manager.GetHandle();
		}

		SCardManager operator=(const SCardManager& manager)
		{
			SetHandle(manager.GetHandle());
			return *this;
		}

		NArrayWrapper<NString> ListReaders() const
		{
			return Interop::SCardApi::ListReaders(GetHandle());
		}

		NArrayWrapper<NString> ListReaders(const NArrayWrapper<NString>& readerGroups) const
		{
			return Interop::SCardApi::ListReaders(GetHandle(), readerGroups);
		}

		NArrayWrapper<NString> ListReaderGroups() const
		{
			return Interop::SCardApi::ListReaderGoups(GetHandle());
		}

		void GetStatusChange(const NArrayWrapper<SCardReaderState>& readerStates, NInt timeout) const
		{
			if (timeout < -1) throw NError(N_E_ARGUMENT_OUT_OF_RANGE, "timeout", "timeout is less than -1");
			Interop::SCardApi::GetStatusChange(GetHandle(), timeout, readerStates);
		}

		SCard Connect(const NString& reader, SCardShare shareMode, SCardProtocols preferredProtocols, SCardProtocols * activeProtocol) const
		{
			return SCard(GetHandle(), reader, shareMode, preferredProtocols, activeProtocol);
		}

		SCard Connect(const NString& reader, SCardShare shareMode, SCardProtocols preferredProtocols) const
		{
			SCardProtocols activeProtocol;
			return Connect(reader, shareMode, preferredProtocols, &activeProtocol);
		}

		bool IsValid() const
		{
			return Interop::SCardApi::IsValidContext(GetHandle());
		}
	};
}}

#endif
