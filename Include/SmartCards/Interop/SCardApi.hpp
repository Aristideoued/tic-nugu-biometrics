#ifndef S_CARD_API_HPP_INCLUDED
#define S_CARD_API_HPP_INCLUDED

#include <SmartCards/NSmartCardsCommands.hpp>
#include <vector>

namespace Neurotec { namespace SmartCards {

	enum SCardScope
	{
		scsUser = 0,
		scsTerminal = 1,
		scsSystem = 2
	};

	enum SCardStates
	{
		scsfUnaware = 0x00000000,
		scsfIgnore = 0x00000001,
		scsfChanged = 0x00000002,
		scsfUnknown = 0x00000004,
		scsfUnavailable = 0x00000008,
		scsfEmpty = 0x00000010,
		scsfPresent = 0x00000020,
		scsfAtrMatch = 0x00000040,
		scsfExclusive = 0x00000080,
		scsfInUse = 0x00000100,
		scsfMute = 0x00000200,
		scsfUnpowered = 0x00000400
	};

	class SCardReaderState
	{
	private:
#ifdef N_APPLE
		typedef SCARD_READERSTATE_A ReaderState;
#else
		typedef SCARD_READERSTATE ReaderState;
#endif

		ReaderState * pState;

	public:
		SCardReaderState()
		{
			pState = new ReaderState();
		}

		SCardReaderState(const SCardReaderState& state)
		{
			pState = new ReaderState();
			memcpy(pState, state.GetPtr(), sizeof(ReaderState));
		}

		~SCardReaderState()
		{
			if (pState) delete pState;
		}

		SCardReaderState operator=(const SCardReaderState& state)
		{
			if (*this != state)
			{
				memcpy(pState, state.GetPtr(), sizeof(ReaderState));
			}
			return *this;
		}

		bool operator==(const SCardReaderState& state)
		{
			return memcmp(pState, state.GetPtr(), sizeof(ReaderState)) == 0;
		}

		bool operator!=(const SCardReaderState& state)
		{
			return memcmp(pState, state.GetPtr(), sizeof(ReaderState)) != 0;
		}

		NString GetReader() const
		{
			return NString(pState->szReader);
		}

		void SetReader(const NString& reader)
		{
			pState->szReader = reader.GetBuffer();
		}

		SCardStates GetEventSate() const
		{
			return (SCardStates)pState->dwEventState;
		}

		void SetEventState(SCardStates state)
		{
			pState->dwEventState = state;
		}

		SCardStates GetCurrentSate() const
		{
			return (SCardStates)pState->dwCurrentState;
		}

		void SetCurrentState(SCardStates state)
		{
			pState->dwCurrentState = state;
		}

		::Neurotec::IO::NBuffer GetAtr() const
		{
			return ::Neurotec::IO::NBuffer(pState->rgbAtr, pState->cbAtr, false);
		}

		void SetAtr(const ::Neurotec::IO::NBuffer& atr)
		{
			if (atr.GetSize() > sizeof(pState->rgbAtr)) throw NError(N_E_ARGUMENT_OUT_OF_RANGE, "atr size is greater than expected");
			memcpy(pState->rgbAtr, atr.GetPtr(), atr.GetSize());
			pState->cbAtr = (DWORD)atr.GetSize();
		}

		void * GetPtr() const
		{
			return (void*)pState;
		}
	};

	enum SCardShare
	{
		scsExclusive = 1,
		scsShared = 2,
		scsDirect = 3
	};

	enum SCardAction
	{
		scaLeave = 0,
		scaReset = 1,
		scaUnpower = 2,
		scaEject = 3
	};

	enum SCardProtocols
	{
		scpUndefined = 0,
		scpT0 = 1,
		scpT1 = 2,
		scpTx = (scpT0|scpT1),
		scpAny = scpTx,
#ifdef N_WINDOWS
		scpRaw = 0x00010000,
		scpDefault = 0x80000000,
		scpOptimal = 0
#else
		scpRaw = 4,
		scpT15 = 8,
		scpUnset = scpUndefined
#endif
	};

	enum SCardState
	{
#ifdef N_WINDOWS
		scsUnknown = 0,
		scsAbsent = 1,
		scsPresent = 2,
		scsSwallowed = 3,
		scsPowered = 4,
		scsNegotiable = 5,
		scsSpecific = 6
#else
		scsUnknown = 0x0001,
		scsAbsent = 0x0002,
		scsPresent = 0x0004,
		scsSwallowed = 0x0008,
		scsPowered = 0x0010,
		scsNegotiable = 0x0020,
		scsSpecific = 0x0040
#endif
	};

	class SCardIORequest
	{
	private:
		LPCSCARD_IO_REQUEST pIORequest;
		bool ownsPtr;

		SCardIORequest(LPCSCARD_IO_REQUEST pIOReq, bool owns)
			: pIORequest(pIOReq),
			ownsPtr(owns)
		{
		}

	public:
		static SCardIORequest GetT0Pci()
		{
			LPCSCARD_IO_REQUEST value = 0;
			NCheck(SCardGetT0Pci(&value));
			return SCardIORequest(value, false);
		}

		static SCardIORequest GetT1Pci()
		{
			LPCSCARD_IO_REQUEST value = 0;
			NCheck(SCardGetT1Pci(&value));
			return SCardIORequest(value, false);
		}

		static SCardIORequest GetRawPci()
		{
			LPCSCARD_IO_REQUEST value = 0;
			NCheck(SCardGetRawPci(&value));
			return SCardIORequest(value, false);
		}

		SCardIORequest(SCardProtocols protocol, NInt pciLength)
		{
			LPSCARD_IO_REQUEST request = new SCARD_IO_REQUEST();
			request->cbPciLength = pciLength;
			request->dwProtocol = protocol;
			pIORequest = request;
			ownsPtr = true;
		}

		SCardIORequest(const SCardIORequest& request)
		{
			pIORequest = new SCARD_IO_REQUEST();
			memcpy((void*)pIORequest, request.GetPtr(), sizeof(SCARD_IO_REQUEST));
			ownsPtr = true;
		}

		~SCardIORequest()
		{
			if (pIORequest && ownsPtr) delete pIORequest;
		}

		SCardIORequest operator=(const SCardIORequest& request)
		{
			if (*this != request)
			{
				memcpy((void*)pIORequest, request.GetPtr(), sizeof(SCARD_IO_REQUEST));
			}
			return *this;
		}

		bool operator==(const SCardIORequest& request)
		{
			return memcmp(pIORequest, request.GetPtr(), sizeof(SCARD_IO_REQUEST)) == 0;
		}

		bool operator!=(const SCardIORequest& request)
		{
			return memcmp(pIORequest, request.GetPtr(), sizeof(SCARD_IO_REQUEST)) != 0;
		}

		SCardProtocols GetProtocol() const
		{
			return (SCardProtocols)pIORequest->dwProtocol;
		}

		NSizeType GetPciLength() const
		{
			return pIORequest->cbPciLength;
		}

		void * GetPtr() const
		{
			return (void*)pIORequest;
		}
	};
}}

#if defined(N_WINDOWS)
#pragma comment(lib, "winscard.lib")
#endif

namespace Neurotec { namespace SmartCards { namespace Interop {

	class SCardApi
	{
	private:
		static void SCardApiAppendError(LONG scardError, const NAChar * szMessage, const NAChar * szExternalCallStack)
		{
			NResult code;
			switch ((ULONG)scardError)
			{
		#if defined(SCARD_E_UNEXPECTED) && defined(N_WINDOWS)
			case SCARD_E_UNEXPECTED:
		#endif
			case SCARD_F_UNKNOWN_ERROR:
				code = N_E_EXTERNAL; break;
			case SCARD_E_INVALID_ATR:
			case SCARD_E_INVALID_CHV:
			case SCARD_E_INVALID_HANDLE:
			case SCARD_E_INVALID_PARAMETER:
			case SCARD_E_INVALID_TARGET:
			case SCARD_E_INVALID_VALUE:
			case SCARD_E_PROTO_MISMATCH:
				code = N_E_ARGUMENT; break;
			case SCARD_E_BAD_SEEK:
			case SCARD_E_INSUFFICIENT_BUFFER:
			case SCARD_E_PCI_TOO_SMALL:
		#ifdef SCARD_W_CACHE_ITEM_TOO_BIG
			case SCARD_W_CACHE_ITEM_TOO_BIG:
		#endif
				code = N_E_ARGUMENT_OUT_OF_RANGE; break;
			case SCARD_E_NO_DIR:
			case SCARD_E_DIR_NOT_FOUND:
				code = N_E_DIRECTORY_NOT_FOUND; break;
			case SCARD_E_NO_KEY_CONTAINER:
				code = N_E_KEY_NOT_FOUND; break;
			case SCARD_E_NO_MEMORY:
				code = N_E_OUT_OF_MEMORY; break;
			case SCARD_E_NO_READERS_AVAILABLE:
				code = N_E_NOT_IMPLEMENTED; break;
			case SCARD_E_TIMEOUT:
			case SCARD_F_WAITED_TOO_LONG:
				code = N_E_TIMEOUT; break;
			case SCARD_F_COMM_ERROR:
			case SCARD_E_COMM_DATA_LOST:
				code = N_E_COM; break;
		#ifdef N_WINDOWS
			case ERROR_BROKEN_PIPE:
		#endif
			case SCARD_F_INTERNAL_ERROR:
			case SCARD_E_SERVICE_STOPPED:
			case SCARD_P_SHUTDOWN:
			case SCARD_E_ICC_CREATEORDER:
			case SCARD_E_ICC_INSTALLATION:
			case SCARD_E_CANT_DISPOSE:
				code = N_E_CORE; break;
			case SCARD_W_CANCELLED_BY_USER:
			case SCARD_E_SYSTEM_CANCELLED:
			case SCARD_E_CANCELLED:
				code = N_E_OPERATION_CANCELED; break;
			case SCARD_W_EOF:
				code = N_E_END_OF_STREAM; break;
			case SCARD_E_NO_FILE:
			case SCARD_E_FILE_NOT_FOUND:
		#ifdef SCARD_W_CACHE_ITEM_NOT_FOUND
			case SCARD_W_CACHE_ITEM_NOT_FOUND:
		#endif
		#ifdef SCARD_E_NO_PIN_CACHE
			case SCARD_E_NO_PIN_CACHE:
		#endif
		#ifdef SCARD_E_PIN_CACHE_EXPIRED
			case SCARD_E_PIN_CACHE_EXPIRED:
		#endif
		#ifdef SCARD_W_CACHE_ITEM_STALE
			case SCARD_W_CACHE_ITEM_STALE:
		#endif
				code = N_E_FILE_NOT_FOUND; break;
			case SCARD_W_UNSUPPORTED_CARD:
			case SCARD_E_UNKNOWN_CARD:
			case SCARD_E_UNKNOWN_READER:
			case SCARD_E_UNKNOWN_RES_MNG:
		#ifdef SCARD_E_UNSUPPORTED_FEATURE
			case SCARD_E_UNSUPPORTED_FEATURE:
		#endif
			case SCARD_E_CARD_UNSUPPORTED:
			case SCARD_E_CERTIFICATE_UNAVAILABLE:
			case SCARD_E_DUPLICATE_READER:
			case SCARD_E_READER_UNSUPPORTED:
				code = N_E_NOT_SUPPORTED; break;
			case SCARD_W_REMOVED_CARD:
			case SCARD_W_RESET_CARD:
			case SCARD_W_UNPOWERED_CARD:
			case SCARD_W_UNRESPONSIVE_CARD:
			case SCARD_E_WRITE_TOO_MANY:
			case SCARD_E_NOT_TRANSACTED:
			case SCARD_E_NO_SERVICE:
			case SCARD_E_NO_SMARTCARD:
			case SCARD_E_NOT_READY:
			case SCARD_E_SERVER_TOO_BUSY:
			case SCARD_E_SHARING_VIOLATION:
			case SCARD_E_READER_UNAVAILABLE:
		#ifdef SCARD_E_READ_ONLY_CARD
			case SCARD_E_READ_ONLY_CARD:
		#endif
				code = N_E_IO; break;
			case SCARD_W_WRONG_CHV:
			case SCARD_W_SECURITY_VIOLATION:
			case SCARD_W_CARD_NOT_AUTHENTICATED:
			case SCARD_W_CHV_BLOCKED:
			case SCARD_E_NO_ACCESS:
			case SCARD_E_NO_SUCH_CERTIFICATE:
				code = N_E_SECURITY; break;
			default: 
				code = N_E_EXTERNAL; break;
			}

		#ifdef PCSCLITE_VERSION_NUMBER
			szMessage = pcsc_stringify_error(scardError);
		#endif

			if(!szMessage)
			{
				switch ((ULONG)scardError)
				{
			#ifdef N_WINDOWS
				case ERROR_BROKEN_PIPE:					szMessage = "The client attempted a smart card operation in a remote session, such as a client session running on a terminal server, and the operating system in use does not support smart card redirection."; break;
			#endif
			#ifdef SCARD_E_NO_PIN_CACHE
				case SCARD_E_NO_PIN_CACHE:				szMessage = "The smart card PIN cannot be cached."; break;
			#endif
			#ifdef SCARD_E_PIN_CACHE_EXPIRED
				case SCARD_E_PIN_CACHE_EXPIRED:			szMessage = "The smart card PIN cache has expired."; break;
			#endif
			#ifdef SCARD_E_PIN_CACHE_EXPIRED
				case SCARD_E_READ_ONLY_CARD:			szMessage = "The smart card is read-only and cannot be written to."; break;
			#endif
			#if defined(SCARD_E_UNEXPECTED) && defined(N_WINDOWS)
				case SCARD_E_UNEXPECTED:				szMessage = "An unexpected card error has occurred."; break;
			#endif
			#ifdef SCARD_W_CACHE_ITEM_NOT_FOUND
				case SCARD_W_CACHE_ITEM_NOT_FOUND:		szMessage = "The requested item could not be found in the cache."; break;
			#endif
			#ifdef SCARD_W_CACHE_ITEM_STALE
				case SCARD_W_CACHE_ITEM_STALE:			szMessage = "The requested cache item is too old and was deleted from the cache."; break;
			#endif
			#ifdef SCARD_W_CACHE_ITEM_TOO_BIG
				case SCARD_W_CACHE_ITEM_TOO_BIG:		szMessage = "The new cache item exceeds the maximum per-item size defined for the cache."; break;
			#endif
				case SCARD_E_BAD_SEEK:					szMessage = "An error occurred in setting the smart card file object pointer."; break;
				case SCARD_E_CANCELLED:					szMessage = "The action was canceled by an SCardCancel request."; break;
				case SCARD_E_CANT_DISPOSE:				szMessage = "The system could not dispose of the media in the requested manner."; break;
				case SCARD_E_CARD_UNSUPPORTED:			szMessage = "The smart card does not meet minimal requirements for support."; break;
				case SCARD_E_CERTIFICATE_UNAVAILABLE:	szMessage = "The requested certificate could not be obtained."; break;
				case SCARD_E_COMM_DATA_LOST:			szMessage = "A communications error with the smart card has been detected."; break;
				case SCARD_E_DIR_NOT_FOUND:				szMessage = "The specified directory does not exist in the smart card."; break;
				case SCARD_E_DUPLICATE_READER:			szMessage = "The reader driver did not produce a unique reader name."; break;
				case SCARD_E_FILE_NOT_FOUND:			szMessage = "The specified file does not exist in the smart card."; break;
				case SCARD_E_ICC_CREATEORDER:			szMessage = "The requested order of object creation is not supported."; break;
				case SCARD_E_ICC_INSTALLATION:			szMessage = "No primary provider can be found for the smart card."; break;
				case SCARD_E_INSUFFICIENT_BUFFER:		szMessage = "The data buffer for returned data is too small for the returned data."; break;
				case SCARD_E_INVALID_ATR:				szMessage = "An ATR string obtained from the registry is not a valid ATR string."; break;
				case SCARD_E_INVALID_CHV:				szMessage = "The supplied PIN is incorrect."; break;
				case SCARD_E_INVALID_HANDLE:			szMessage = "The supplied handle was not valid."; break;
				case SCARD_E_INVALID_PARAMETER:			szMessage = "One or more of the supplied parameters could not be properly interpreted."; break;
				case SCARD_E_INVALID_TARGET:			szMessage = "Registry startup information is missing or not valid."; break;
				case SCARD_E_INVALID_VALUE:				szMessage = "One or more of the supplied parameter values could not be properly interpreted."; break;
				case SCARD_E_NO_ACCESS:					szMessage = "Access is denied to the file."; break;
				case SCARD_E_NO_DIR:					szMessage = "The supplied path does not represent a smart card directory."; break;
				case SCARD_E_NO_FILE:					szMessage = "The supplied path does not represent a smart card file."; break;
				case SCARD_E_NO_KEY_CONTAINER:			szMessage = "The requested key container does not exist on the smart card."; break;
				case SCARD_E_NO_MEMORY:					szMessage = "Not enough memory available to complete this command."; break;
				case SCARD_E_NO_READERS_AVAILABLE:		szMessage = "No smart card reader is available."; break;
				case SCARD_E_NO_SERVICE:				szMessage = "The smart card resource manager is not running."; break;
				case SCARD_E_NO_SMARTCARD:				szMessage = "The operation requires a smart card, but no smart card is currently in the device."; break;
				case SCARD_E_NO_SUCH_CERTIFICATE:		szMessage = "The requested certificate does not exist."; break;
				case SCARD_E_NOT_READY:					szMessage = "The reader or card is not ready to accept commands."; break;
				case SCARD_E_NOT_TRANSACTED:			szMessage = "An attempt was made to end a nonexistent transaction."; break;
				case SCARD_E_PCI_TOO_SMALL:				szMessage = "The PCI receive buffer was too small."; break;
				case SCARD_E_PROTO_MISMATCH:			szMessage = "The requested protocols are incompatible with the protocol currently in use with the card."; break;
				case SCARD_E_READER_UNAVAILABLE:		szMessage = "The specified reader is not currently available for use."; break;
				case SCARD_E_READER_UNSUPPORTED:		szMessage = "The reader driver does not meet minimal requirements for support."; break;
				case SCARD_E_SERVER_TOO_BUSY:			szMessage = "The smart card resource manager is too busy to complete this operation."; break;
				case SCARD_E_SERVICE_STOPPED:			szMessage = "The smart card resource manager has shut down."; break;
				case SCARD_E_SHARING_VIOLATION:			szMessage = "The smart card cannot be accessed because of other outstanding connections."; break;
				case SCARD_E_SYSTEM_CANCELLED:			szMessage = "The action was canceled by the system, presumably to log off or shut down."; break;
				case SCARD_E_TIMEOUT:					szMessage = "The user-specified time-out value has expired."; break;
				case SCARD_E_UNKNOWN_CARD:				szMessage = "The specified smart card name is not recognized."; break;
				case SCARD_E_UNKNOWN_READER:			szMessage = "The specified reader name is not recognized."; break;
				case SCARD_E_UNKNOWN_RES_MNG:			szMessage = "An unrecognized error code was returned."; break;
				case SCARD_E_UNSUPPORTED_FEATURE:		szMessage = "This smart card does not support the requested feature."; break;
				case SCARD_E_WRITE_TOO_MANY:			szMessage = "An attempt was made to write more data than would fit in the target object."; break;
				case SCARD_F_COMM_ERROR:				szMessage = "An internal communications error has been detected."; break;
				case SCARD_F_INTERNAL_ERROR:			szMessage = "An internal consistency check failed."; break;
				case SCARD_F_UNKNOWN_ERROR:				szMessage = "An internal error has been detected, but the source is unknown."; break;
				case SCARD_F_WAITED_TOO_LONG:			szMessage = "An internal consistency timer has expired."; break;
				case SCARD_P_SHUTDOWN:					szMessage = "The operation has been aborted to allow the server application to exit."; break;
				case SCARD_W_CANCELLED_BY_USER:			szMessage = "The action was canceled by the user."; break;
				case SCARD_W_CARD_NOT_AUTHENTICATED:	szMessage = "No PIN was presented to the smart card."; break;
				case SCARD_W_CHV_BLOCKED:				szMessage = "The card cannot be accessed because the maximum number of PIN entry attempts has been reached."; break;
				case SCARD_W_EOF:						szMessage = "The end of the smart card file has been reached."; break;
				case SCARD_W_REMOVED_CARD:				szMessage = "The smart card has been removed, so further communication is not possible."; break;
				case SCARD_W_RESET_CARD:				szMessage = "The smart card was reset."; break;
				case SCARD_W_SECURITY_VIOLATION:		szMessage = "Access was denied because of a security violation."; break;
				case SCARD_W_UNPOWERED_CARD:			szMessage = "Power has been removed from the smart card, so that further communication is not possible."; break;
				case SCARD_W_UNRESPONSIVE_CARD:			szMessage = "The smart card is not responding to a reset."; break;
				case SCARD_W_UNSUPPORTED_CARD:			szMessage = "The reader cannot communicate with the card, due to ATR string configuration conflicts."; break;
				case SCARD_W_WRONG_CHV:					szMessage = "The card cannot be accessed because the wrong PIN was presented."; break;
				default:								szMessage = "Unknown smart card error occured."; break;
				}
			}

			NError::SetLast(N_E_EXTERNAL, szMessage, "", scardError, szExternalCallStack, (code == N_E_EXTERNAL ? NE_NO_CALL_STACK : 0) | NE_SKIP_ONE_FRAME);
			if (code != N_E_EXTERNAL)
			{
				NError::SetLast(code, szMessage, "", 0, "", NE_PRESERVE_INNER_ERROR | NE_SKIP_ONE_FRAME);
			}
		}

#define SCARD_NOT_IMPLEMENTED_MESSAGE N_T("Current OS family smart cards support is not implemented")

#define SCARD_API_SUCCESS(res) (res) == SCARD_S_SUCCESS

#define SCARD_API_FAILED(res) (res) != SCARD_S_SUCCESS

#define SCARD_API_CHECK(func, res) \
	{ \
		LONG scard_error_code = (res); \
		if(SCARD_API_FAILED(scard_error_code)) \
		{ \
			SCardApiAppendError(scard_error_code, NULL, N_ERROR_MAKE_EXTERNALL_CALL_STACKA(func)); \
			throw NError::GetLast(); \
		} \
	}

	public:
#if defined(N_WINDOWS)|| defined(N_APPLE) || defined(N_LINUX)
		typedef SCARDCONTEXT HSCardManager;
		typedef SCARDHANDLE HSCard;
#else
		typedef void* HSCardManager;
		typedef void* HSCard;
#endif

	private:
		static NArrayWrapper<NString> PtrToStrings(NChar * ptr, NSizeType size)
		{
			if (size == 0)
			{
				return NArrayWrapper<NString>(0);
			}

			NString target((NChar*)ptr, (NInt)size);
			if(target.GetLength() == 0)
			{
				return NArrayWrapper<NString>(0);
			}

			NUInt count = 0;
			for(NSizeType i = 0; i < size; i++)
			{
				if (ptr[i] == '\0')
					count++;
			}

			if (count == 0)
			{
				NArrayWrapper<NString> ar(1);
				ar[0] = target;
				return ar;
			}
			else
			{
				NInt splitCount = 0;
				NString * pAr = target.Split(N_T("\0"), 1, &splitCount, true);
				return NArrayWrapper<NString>(reinterpret_cast<HNString*>(pAr), splitCount);
			}
		}
		
		static NArrayWrapper<NGuid> BufferToInterfaces(const ::Neurotec::IO::NBuffer& buffer)
		{
			NInt count = 0;
			NInt length = (NInt)buffer.GetSize();
			NByte * ptr = (NByte*)buffer.GetPtr();

			std::vector<NGuid> ar;

			for(NInt i=0; i < length; i++)
			{
				count++;
				if(count == sizeof(NGuid_))
				{
					NGuid_ guid;
					memcpy(&guid, ptr, sizeof(NGuid_));
					ar.push_back(NGuid(guid));
					ptr += sizeof(NGuid_);
					count = 0;
				}
			}

			return NArrayWrapper<NGuid>(ar.begin(), ar.end());
		}

		static NArrayWrapper<SCARD_READERSTATE> GetReaderStates(const NArrayWrapper<SCardReaderState>& readerStates)
		{
			NInt count = readerStates.GetCount();
			std::vector<SCARD_READERSTATE> ar;
			for(NInt i=0; i<count; i++)
			{
				ar.push_back(*(SCARD_READERSTATE*)(readerStates[i].GetPtr()));
			}

			return NArrayWrapper<SCARD_READERSTATE>(ar.begin(), ar.end());
		}

	public:
#if defined(N_WINDOWS) || defined(N_APPLE) || defined(N_LINUX)
		static HSCardManager EstablishContext(SCardScope scope)
		{
			HSCardManager hContext;
			SCARD_API_CHECK(SCardEstablishContext, SCardEstablishContext(scope, 0, 0, &hContext));
			return hContext;
		}

		static bool ReleaseContext(HSCardManager hContext)
		{
			return SCARD_API_SUCCESS(SCardReleaseContext(hContext));
		}

		static bool IsValidContext(HSCardManager hContext)
		{
			LONG res = SCardIsValidContext(hContext);
			if(res == SCARD_E_INVALID_HANDLE
#ifdef N_WINDOWS
			|| res == ERROR_INVALID_HANDLE ||res == E_HANDLE
#endif
			) return false;
			SCARD_API_CHECK(SCardIsValidContext, res);
			return true;
		}

		static NArrayWrapper<NString> ListReaderGoups(HSCardManager hContext)
		{
			DWORD size = 0;
			SCARD_API_CHECK(SCardListReaderGroups, SCardListReaderGroups(hContext, 0, &size));
			::Neurotec::IO::NBuffer buffer(size * sizeof(NChar));
			SCARD_API_CHECK(SCardListReaderGroups, SCardListReaderGroups(hContext, (LPTSTR)buffer.GetPtr(), &size));
			return PtrToStrings((NChar*)buffer.GetPtr(), size);
		}

		static NArrayWrapper<NString> ListReaders(HSCardManager hContext)
		{
			DWORD size = 0;
			LONG res = SCardListReaders(hContext, 0, 0, &size);
			if(res == SCARD_E_NO_READERS_AVAILABLE)
			{
				return NArrayWrapper<NString>(0);
			}
			SCARD_API_CHECK(SCardListReaders, res);
			::Neurotec::IO::NBuffer buffer(size * sizeof(NChar));
			memset(buffer.GetPtr(), 0, size * sizeof(NChar));
			SCARD_API_CHECK(SCardListReaders, SCardListReaders(hContext, 0, (LPTSTR)buffer.GetPtr(), &size));
			return PtrToStrings((NChar*)buffer.GetPtr(), size);
		}

		static NArrayWrapper<NString> ListReaders(HSCardManager hContext, const NArrayWrapper<NString>& groups)
		{
			NString rg = NString::Join(N_T("\0"), (NString*)groups.GetPtr(), groups.GetCount());
			DWORD size = 0;
			LONG res = SCardListReaders(hContext, (LPTSTR)rg.GetBuffer(), 0, &size);
			if(res == SCARD_E_NO_READERS_AVAILABLE)
			{
				return NArrayWrapper<NString>(0);
			}
			SCARD_API_CHECK(SCardListReaders, res);
			::Neurotec::IO::NBuffer buffer(size * sizeof(NChar));
			SCARD_API_CHECK(SCardListReaders, SCardListReaders(hContext, (LPTSTR)rg.GetBuffer(), (LPTSTR)buffer.GetPtr(), &size));
			return PtrToStrings((NChar*)buffer.GetPtr(), size);
		}

		static void GetStatusChange(HSCardManager hContext, NULong timeout, const NArrayWrapper<SCardReaderState>& readerStates)
		{
			NArrayWrapper<SCARD_READERSTATE> states = GetReaderStates(readerStates);
			SCARD_API_CHECK(SCardGetStatusChange, SCardGetStatusChange(hContext, (DWORD)timeout, states.GetPtr(), (DWORD)states.GetCount()));
		}

		static void Cancel(HSCardManager hContext)
		{
			SCARD_API_CHECK(SCardCancel, SCardCancel(hContext));
		}

		static HSCard Connect(HSCardManager hContext, const NString& reader, SCardShare shareMode, SCardProtocols preferredProtocols, SCardProtocols * activeProtocol)
		{
			HSCard hCard;
			SCARD_API_CHECK(SCardConnect, SCardConnect(hContext, reader.GetBuffer(), shareMode, preferredProtocols, &hCard, (LPDWORD)activeProtocol));
			return hCard;
		}

		static SCardProtocols Reconnect(HSCard hCard, SCardShare shareMode, SCardProtocols preferredProtocols, SCardAction initialization)
		{
			SCardProtocols activeProtocol;
			SCARD_API_CHECK(SCardReconnect, SCardReconnect(hCard, (DWORD)shareMode, (DWORD)preferredProtocols, (DWORD)initialization, (LPDWORD)&activeProtocol));
			return activeProtocol;
		}

		static void Disconnect(HSCard hCard, SCardAction disposition)
		{
			SCARD_API_CHECK(SCardDisconnect, SCardDisconnect(hCard, disposition));
		}

		static void BeginTransaction(HSCard hCard)
		{
			SCARD_API_CHECK(SCardBeginTransaction, SCardBeginTransaction(hCard));
		}

		static void EndTransaction(HSCard hCard, SCardAction disposition)
		{
			SCARD_API_CHECK(SCardEndTransaction, SCardEndTransaction(hCard, disposition));
		}

		static ::Neurotec::IO::NBuffer GetAtr(HSCard hCard)
		{
			DWORD size = 0;
			SCardState state;
			SCardProtocols protocols;
			DWORD atrLength = 0;
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, 0, &size, (LPDWORD)&state, (LPDWORD)&protocols, 0, &atrLength));
			::Neurotec::IO::NBuffer buffer(atrLength);
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, 0, &size, (LPDWORD)&state, (LPDWORD)&protocols, (LPBYTE)buffer.GetPtr(), &atrLength));
			if(atrLength != buffer.GetSize()) throw NError(N_E_INVALID_OPERATION, "ATR length is not equal to buffer size.");
			return buffer;
		}

		static NArrayWrapper<NString> GetReaderNames(HSCard hCard)
		{
			DWORD size = 0;
			SCardState state;
			SCardProtocols protocols;
			DWORD atrLength = 0;
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, 0, &size, (LPDWORD)&state, (LPDWORD)&protocols, 0, &atrLength));
			if (size == 0) return NArrayWrapper<NString>(0);
			::Neurotec::IO::NBuffer buffer(size * sizeof(NUShort));
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, (LPTSTR)buffer.GetPtr(), &size, (LPDWORD)&state, (LPDWORD)&protocols, 0, &atrLength));
			return PtrToStrings((NChar*)buffer.GetPtr(), size);
		}

		static SCardState GetState(HSCard hCard)
		{
			DWORD size = 0;
			SCardState state;
			SCardProtocols protocol;
			DWORD atrLength = 0;
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, 0, &size, (LPDWORD)&state, (LPDWORD)&protocol, 0, &atrLength));
			return state;
		}

		static SCardProtocols GetProtocol(HSCard hCard)
		{
			DWORD size = 0;
			SCardState state;
			SCardProtocols protocol;
			DWORD atrLength = 0;
			SCARD_API_CHECK(SCardStatus, SCardStatus(hCard, 0, &size, (LPDWORD)&state, (LPDWORD)&protocol, 0, &atrLength));
			return protocol;
		}

		static NSizeType Transmit(HSCard hCard, const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer,
			SCardIORequest& recvPci, ::Neurotec::IO::NBuffer& recvBuffer)
		{
			NSizeType value = 0;
			NCheck(SCardTransmitN(hCard, (LPCSCARD_IO_REQUEST)sendPci.GetPtr(),
				sendBuffer.GetHandle(), (LPSCARD_IO_REQUEST)recvPci.GetPtr(), recvBuffer.GetHandle(), &value));
			return value;
		}

		static NSizeType Transmit(HSCard hCard, const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer,
			::Neurotec::IO::NBuffer& recvBuffer)
		{
			NSizeType value = 0;
			NCheck(SCardTransmitN(hCard, (LPCSCARD_IO_REQUEST)sendPci.GetPtr(), sendBuffer.GetHandle(), 0,
				recvBuffer.GetHandle(), &value));
			return value;
		}

		static NSizeType TransmitApdu(HSCard hCard, const ApduClass& apdu, const ApduInstruction& instruction, NByte p1, NByte p2, bool isExtended,
			HNBuffer data, HNBuffer resData, ApduStatus * status)
		{
			NSizeType value = 0;
			NCheck(SCardTransmitApduN(hCard, reinterpret_cast<const ApduClass_&>(apdu), reinterpret_cast<const ApduInstruction_&>(instruction),
				p1, p2, isExtended, data, resData, &value, reinterpret_cast<ApduStatus_*>(status)));
			return value;
		}

		static NSizeType Control(HSCard hCard, NInt controlCode, HNBuffer hInBuffer, HNBuffer hOutBuffer)
		{
			NSizeType value = 0;
			NCheck(SCardControlN(hCard, (DWORD)controlCode, hInBuffer, hOutBuffer, &value));
			return value;
		}

		static NSizeType Control(HSCard hCard, NUInt controlCode, NUInt inValue, HNBuffer hBuffer)
		{
			NSizeType value = 0;
			NCheck(SCardControlDWordN(hCard, (DWORD)controlCode, (DWORD)inValue, hBuffer, &value));
			return value;
		}

		static NUInt ControlAsDWord(HSCard hCard, NUInt controlCode, HNBuffer hBuffer)
		{
			NUInt value = 0;
			NCheck(SCardControlAsDWordN(hCard, (DWORD)controlCode, hBuffer, (LPDWORD)&value));
			return value;
		}

		static NUInt ControlDWordAsDWord(HSCard hCard, NUInt controlCode, NUInt inValue)
		{
			NUInt value = 0;
			NCheck(SCardControlDWordAsDWord(hCard, (DWORD)controlCode, (DWORD)inValue, (LPDWORD)&value));
			return value;
		}

		static NSizeType GetAttribLength(HSCard hCard, NUInt attrId, const ::Neurotec::IO::NBuffer& buffer)
		{
			NSizeType value = 0;
			NCheck(SCardGetAttribN(hCard, (DWORD)attrId, buffer.GetHandle(), &value));
			return value;
		}

		static ::Neurotec::IO::NBuffer GetAttribAsBuffer(HSCard hCard, NUInt attrId)
		{
			::Neurotec::IO::HNBuffer hBuffer;
			NCheck(SCardGetAttribAsBufferN(hCard, (DWORD)attrId, &hBuffer));
			return ::Neurotec::IO::NBuffer(hBuffer);
		}

		static NString GetAttribAsString(HSCard hCard, NUInt attrId)
		{
			NInt length = 0;
			NCheck(SCardGetAttribAsString(hCard, (DWORD)attrId, 0, &length));
			::Neurotec::IO::NBuffer buffer(length * sizeof(NUShort));

			NCheck(SCardGetAttribAsString(hCard, (DWORD)attrId, (NChar*)buffer.GetPtr(), &length));
			return NString((NChar*)buffer.GetPtr(), (NInt)buffer.GetSize());
		}

		static NArrayWrapper<NString> GetAttribAsStrings(HSCard hCard, NUInt attrId)
		{
			NInt size = 0;
			NCheck(SCardGetAttribAsString(hCard, (DWORD)attrId, 0, &size));
			::Neurotec::IO::NBuffer buffer(size * sizeof(NUShort));
			NCheck(SCardGetAttribAsString(hCard, (DWORD)attrId, (NChar*)buffer.GetPtr(), &size));
			return PtrToStrings((NChar*)buffer.GetPtr(), size);
		}

		static NByte GetAttribAsByte(HSCard hCard, NUInt attrId)
		{
			NByte value = 0;
			NCheck(SCardGetAttribAsByte(hCard, (DWORD)attrId, &value));
			return value;
		}

		static NUInt GetAttribAsLong(HSCard hCard, NUInt attrId)
		{
			NUInt value = 0;
			NCheck(SCardGetAttribAsDWord(hCard, (DWORD)attrId, (LPDWORD)&value));
			return value;
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, HNBuffer hAttr)
		{
			NCheck(SCardSetAttribN(hCard, (DWORD)attrId, hAttr));
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, NByte attr)
		{
			NCheck(SCardSetAttribAsByte(hCard, (DWORD)attrId, (BYTE)attr));
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, NUInt attr)
		{
			NCheck(SCardSetAttribAsDWord(hCard, (DWORD)attrId, (DWORD)attr));
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, const NString& attr)
		{
			NCheck(SCardSetAttribAsString(hCard, (DWORD)attrId, attr.GetBuffer(), attr.GetLength()));
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, const NArrayWrapper<NString>& attr)
		{
			NString strAttr = NString::Join(N_T("\0"), (NString*)attr.GetPtr(), attr.GetCount());
			NInt length = strAttr.GetLength();
			NCheck(SCardGetAttribAsString(hCard, (DWORD)attrId, (NChar*)strAttr.GetBuffer(), &length));
		}
#else
		static HSCardManager EstablishContext(SCardScope scope)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static bool ReleaseContext(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static bool IsValidContext(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListReaderGoups(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListReaders(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListReaders(HSCardManager hContext, const NArrayWrapper<NString>& groups)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListCards(HSCardManager hContext, ::Neurotec::IO::NBuffer& atr, const NArrayWrapper<NGuid>& interfaces)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListCards(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> ListCards(HSCardManager hContext, ::Neurotec::IO::NBuffer& atr, NGuid * pGuid, NSizeType count)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NGuid> ListInterfaces(HSCardManager hContext, const NString& card)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NGuid GetProviderId(HSCardManager hContext, const NString& card)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NString GetCardTypeProviderName(HSCardManager hContext, const NString& cardName, SCardProvider provider)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void IntroduceReaderGroup(HSCardManager hContext, const NString& groupName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void ForgetReaderGroup(HSCardManager hContext, const NString& groupName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void IntroduceReader(HSCardManager hContext, const NString& readerName, const NString& deviceName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void ForgetReader(HSCardManager hContext, const NString& readerName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void AddReaderToGroup(HSCardManager hContext, const NString& readerName, const NString& groupName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void RemoveReaderFromGroup(HSCardManager hContext, const NString& readerName, const NString& groupName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void IntroduceCardType(HSCardManager hContext, const NString& cardName, const NGuid& primaryProvider,
			const NArrayWrapper<NGuid>& interfaces, SCardAtrMask& atrMask)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void IntroduceCardType(HSCardManager hContext, const NString& cardName, SCardAtrMask& atrMask)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void IntroduceCardType(HSCardManager hContext, const NString& cardName, const NGuid& primaryProvider,
			NGuid * pGuid, NSizeType count, SCardAtrMask& atrMask)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void ForgetCardType(HSCardManager hContext, const NString& cardName)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetCardTypeProviderName(HSCardManager hContext, const NString& cardName, SCardProvider provider, const NString& value)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void LocateCards(HSCardManager hContext, const NArrayWrapper<NString>& cards, const NArrayWrapper<SCardReaderState>& readerStates)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void GetStatusChange(HSCardManager hContext, NULong timeout, const NArrayWrapper<SCardReaderState>& readerStates)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void Cancel(HSCardManager hContext)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static HSCard Connect(HSCardManager hContext, const NString& reader, SCardShare shareMode, SCardProtocols preferredProtocols, SCardProtocols * activeProtocol)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static SCardProtocols Reconnect(HSCard hCard, SCardShare shareMode, SCardProtocols preferredProtocols, SCardAction initialization)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static bool Disconnect(HSCard hCard, SCardAction disposition)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void BeginTransaction(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void EndTransaction(HSCard hCard, SCardAction disposition)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void CancelTransaction(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static ::Neurotec::IO::NBuffer GetAtr(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> GetReaderNames(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static SCardState GetState(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static SCardProtocols GetProtocol(HSCard hCard)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType Transmit(HSCard hCard, const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer,
			SCardIORequest& recvPci, ::Neurotec::IO::NBuffer& recvBuffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType Transmit(HSCard hCard, const SCardIORequest& sendPci, const ::Neurotec::IO::NBuffer& sendBuffer,
			::Neurotec::IO::NBuffer& recvBuffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType TransmitApdu(HSCard hCard, const ApduClass& apdu, const ApduInstruction& instruction, NByte p1, NByte p2, bool isExtended,
			HNBuffer data, HNBuffer resData, ApduStatus * status)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType Control(HSCard hCard, NInt controlCode, HNBuffer hInBuffer, HNBuffer hOutBuffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType Control(HSCard hCard, NUInt controlCode, NUInt inValue, HNBuffer hBuffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NUInt ControlAsDWord(HSCard hCard, NUInt controlCode, HNBuffer hBuffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NUInt ControlDWordAsDWord(HSCard hCard, NUInt controlCode, NUInt inValue)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NSizeType GetAttribLength(HSCard hCard, NUInt attrId, const ::Neurotec::IO::NBuffer& buffer)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static ::Neurotec::IO::NBuffer GetAttribAsBuffer(HSCard hCard, NUInt attrId)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NString GetAttribAsString(HSCard hCard, NUInt attrId)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NArrayWrapper<NString> GetAttribAsStrings(HSCard hCard, NUInt attrId)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NByte GetAttribAsByte(HSCard hCard, NUInt attrId)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static NUInt GetAttribAsLong(HSCard hCard, NUInt attrId)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, HNBuffer hAttr)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, NByte attr)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, NUInt attr)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, const NString& attr)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}

		static void SetAttrib(HSCard hCard, NUInt attrId, const NArrayWrapper<NString>& attr)
		{
			throw NError(N_E_NOT_IMPLEMENTED, SCARD_NOT_IMPLEMENTED_MESSAGE);
		}
#endif
	};

}}}

#endif


