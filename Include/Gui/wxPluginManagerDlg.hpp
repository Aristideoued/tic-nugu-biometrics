#ifndef WX_PLUGIN_MANAGER_DLG_HPP_INCLUDED
#define WX_PLUGIN_MANAGER_DLG_HPP_INCLUDED

#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/thread.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>

#include <cstring>
#include <Core/NObject.hpp>
#include <Plugins/NPluginManager.hpp>
#include <Plugins/NPlugin.hpp>
#include <Core/NModule.hpp>

#undef wxPluginManagerDlgStyle
#ifdef __WXMAC__
#define wxPluginManagerDlgStyle wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMAXIMIZE_BOX
#else
#define wxPluginManagerDlgStyle wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX
#endif

namespace Neurotec { namespace Gui {

DEFINE_EVENT_TYPE(wxEVT_PLUGIN_MANAGER_DLG)

class wxPluginManagerDlg : public wxDialog
{
private:
	class AsyncRun : public wxThread
	{
	public:
		typedef void (Neurotec::Plugins::NPlugin::*PluginFn)();
		typedef void (Neurotec::Plugins::NPluginManager::*PluginManagerFn)();

	private:
		enum Target
		{
			AddPlugin,
			PluginFunc,
			PluginManagerFunc
		};

		Target m_target;
		Neurotec::Plugins::NPlugin m_plugin;
		Neurotec::Plugins::NPluginManager m_pluginManager;
		PluginFn m_pluginFn;
		PluginManagerFn m_pluginManagerFn;
		wxString m_param;

		AsyncRun(PluginManagerFn function, Neurotec::Plugins::NPluginManager manager)
			: wxThread(), m_target(PluginManagerFunc), m_plugin(NULL), m_pluginManager(manager), m_pluginFn(NULL), m_pluginManagerFn(function), m_param(wxEmptyString)
		{
		}

		AsyncRun(PluginFn function, Neurotec::Plugins::NPlugin plugin)
			: wxThread(), m_target(PluginFunc), m_plugin(plugin), m_pluginManager(NULL), m_pluginFn(function), m_pluginManagerFn(NULL), m_param(wxEmptyString)
		{
		}

		AsyncRun(Neurotec::Plugins::NPluginManager manager, wxString param)
			: wxThread(), m_target(AddPlugin), m_plugin(NULL), m_pluginManager(manager), m_pluginFn(NULL), m_pluginManagerFn(NULL), m_param(param)
		{
		}

	public:
		virtual void* Entry()
		{
			switch(m_target)
			{
			case AddPlugin:
				m_pluginManager.GetPlugins().Add(m_param);
				break;
			case PluginFunc:
				(m_plugin.*m_pluginFn)();
				break;
			case PluginManagerFunc:
				(m_pluginManager.*m_pluginManagerFn)();
				break;
			default:
				break;
			}
			return NULL;
		}

		static void AddPluginAsync(Neurotec::Plugins::NPluginManager manager, wxString plugin)
		{
			AsyncRun * target = new AsyncRun(manager, plugin);
			target->Run();
		}
		static void PlugAllAsync(Neurotec::Plugins::NPluginManager manager)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPluginManager::PlugAll, manager);
			target->Run();
		}
		static void UnplugAllAsync(Neurotec::Plugins::NPluginManager manager)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPluginManager::UnplugAll, manager);
			target->Run();
		}
		static void RefreshAsync(Neurotec::Plugins::NPluginManager manager)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPluginManager::Refresh, manager);
			target->Run();
		}
		static void PlugAsync(Neurotec::Plugins::NPlugin plugin)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPlugin::Plug, plugin);
			target->Run();
		}
		static void UnplugAsync(Neurotec::Plugins::NPlugin plugin)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPlugin::Unplug, plugin);
			target->Run();
		}
		static void EnableAsync(Neurotec::Plugins::NPlugin plugin)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPlugin::Enable, plugin);
			target->Run();
		}
		static void DisableAsync(Neurotec::Plugins::NPlugin plugin)
		{
			AsyncRun * target = new AsyncRun(&Neurotec::Plugins::NPlugin::Disable, plugin);
			target->Run();
		}
	};

	class NPluginManagerVirtualList : public wxListCtrl
	{
	private:

		bool m_sortAscending;
		bool m_changeSortingOrder;
		int m_columnClicked;

		std::vector<Neurotec::Plugins::NPlugin> m_plugins;
		std::vector<long> m_orderedIndices;

		enum m_list_Columns
		{
			TitleCollumn,
			VersionCollumn,
			CopyrightCollumn,
			StateCollumn,
			LoadTimeCollumn,
			PlugTimeCollumn,
			InterfaceVersionCollumn,
			NameCollumn,
			FileNameCollumn,
			InterfaceTypeCollumn,
			InterfaceVersionsCollumn,
			PriorityCollumn,
			IncompatiblePluginsCollumn,
			__ListCollumnMAX
		};

		wxString InterfaceVersionsToString(const NArrayWrapper<Neurotec::NVersionRange> versions) const
		{
			wxString value = wxT("");

			for (int i = 0; i < versions.GetCount(); i++)
			{
				if (value.length() != 0)
				{
					value.append(wxT(", "));
				}
				value.append(static_cast<wxString>(versions[i].ToString()));
			}
			return value;
		}

		long getFirstSelectedIndex()
		{
			return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		}

		long findIndexOfDataIndex(long dataIndex)
		{
			return std::find(m_orderedIndices.begin(), m_orderedIndices.end(), dataIndex) - m_orderedIndices.begin();
		}

		void sortList()
		{
			bool ascending = this->m_sortAscending;

			std::sort(m_orderedIndices.begin(), m_orderedIndices.end(), [this, ascending](long index1, long index2)
			{
				auto plugin1 = this->m_plugins[index1];
				auto plugin2 = this->m_plugins[index2];

				const Neurotec::Plugins::NPluginModule module1 = plugin1.GetModule();
				const Neurotec::Plugins::NPluginModule module2 = plugin2.GetModule();

				wxString s1;
				wxString s2;

				switch (this->m_columnClicked)
				{
				case TitleCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : (wxString)module1.GetTitle();
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : (wxString)module2.GetTitle();
					break;
				case VersionCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) :
						wxString::Format(wxT("%d.%d.%d.%d"), module1.GetVersionMajor(), module1.GetVersionMinor(), module1.GetVersionBuild(), module1.GetVersionRevision());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) :
						wxString::Format(wxT("%d.%d.%d.%d"), module1.GetVersionMajor(), module2.GetVersionMinor(), module2.GetVersionBuild(), module2.GetVersionRevision());
					break;
				case CopyrightCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module1.GetCopyright());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module2.GetCopyright());
					break;
				case StateCollumn:
					s1 = NPluginStateToString(plugin1.GetState());;
					s2 = NPluginStateToString(plugin2.GetState());;
					break;
				case LoadTimeCollumn:
					s1 = wxString::Format(wxT("%2.2f s"), plugin1.GetLoadTime().GetTotalSeconds());
					s2 = wxString::Format(wxT("%2.2f s"), plugin2.GetLoadTime().GetTotalSeconds());
					break;
				case PlugTimeCollumn:
					s1 = wxString::Format(wxT("%2.2f s"), plugin1.GetPlugTime().GetTotalSeconds());
					s2 = wxString::Format(wxT("%2.2f s"), plugin2.GetPlugTime().GetTotalSeconds());
					break;
				case InterfaceVersionCollumn:
					s1 = static_cast<wxString>(plugin1.GetSelectedInterfaceVersion().ToString());
					s2 = static_cast<wxString>(plugin2.GetSelectedInterfaceVersion().ToString());
					break;
				case NameCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module1.GetPluginName());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module2.GetPluginName());
					break;
				case FileNameCollumn:
					s1 = static_cast<wxString>(plugin1.GetFileName());
					s2 = static_cast<wxString>(plugin2.GetFileName());
					break;
				case InterfaceTypeCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module1.GetInterfaceType());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module2.GetInterfaceType());
					break;
				case InterfaceVersionsCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : this->InterfaceVersionsToString(module1.GetInterfaceVersions());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : this->InterfaceVersionsToString(module2.GetInterfaceVersions());
					break;
				case PriorityCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : wxString::Format(wxT("%d"), module1.GetPriority());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : wxString::Format(wxT("%d"), module2.GetPriority());
					break;
				case IncompatiblePluginsCollumn:
					s1 = module1.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module1.GetIncompatiblePlugins());
					s2 = module2.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module2.GetIncompatiblePlugins());
					break;
				default:
					return false;
				}

				return ascending ? s1 < s2 : s1 > s2;
			});
		}

	public:

		NPluginManagerVirtualList(wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
			: wxListCtrl(parent, id, pos, size, style), m_sortAscending(true), m_changeSortingOrder(true)
		{
			this->InsertColumn(TitleCollumn, wxT("Title"));
			this->InsertColumn(VersionCollumn, wxT("Version"));
			this->InsertColumn(CopyrightCollumn, wxT("Copyright"));
			this->InsertColumn(StateCollumn, wxT("State"));
			this->InsertColumn(LoadTimeCollumn, wxT("Load time"));
			this->InsertColumn(PlugTimeCollumn, wxT("Plug time"));
			this->InsertColumn(InterfaceVersionCollumn, wxT("Selected interface version"));
			this->InsertColumn(NameCollumn, wxT("Name"));
			this->InsertColumn(FileNameCollumn, wxT("File name"));
			this->InsertColumn(InterfaceTypeCollumn, wxT("Interface type"));
			this->InsertColumn(InterfaceVersionsCollumn, wxT("Interface versions"));
			this->InsertColumn(PriorityCollumn, wxT("Priority"));
			this->InsertColumn(IncompatiblePluginsCollumn, wxT("Incompatible plugins"));
			this->SetSizeHints(700, 250);

			this->m_columnClicked = TitleCollumn;

			this->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &evt)
			{
				m_changeSortingOrder = true;

				auto selectedListIndex = getFirstSelectedIndex();
				long selectedDataIndex = -1;

				if (selectedListIndex != -1)
				{
					selectedDataIndex = this->m_orderedIndices[selectedListIndex];

					// deselecting old index
					this->SetItemState(selectedListIndex, 0, wxLIST_STATE_SELECTED);
				}

				this->m_columnClicked = evt.GetColumn();
				// refresh + sort
				this->RefreshListAfterUpdate();

				if (selectedListIndex != -1)
				{
					auto listIndexToSelect = findIndexOfDataIndex(selectedDataIndex);
					this->SetItemState(listIndexToSelect, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
					this->EnsureVisible(listIndexToSelect);
				}
			});
		}

		virtual wxString OnGetItemText(long item, long column) const override
		{
			Neurotec::Plugins::NPlugin plugin = m_plugins[m_orderedIndices[item]];
			const Neurotec::Plugins::NPluginModule module = plugin.GetModule();

			switch (column)
			{
			case TitleCollumn:
				return ((wxString)module.GetTitle()).c_str();
			case VersionCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : wxString::Format(wxT("%d.%d.%d.%d"), module.GetVersionMajor(), module.GetVersionMinor(), module.GetVersionBuild(), module.GetVersionRevision());
			case CopyrightCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module.GetCopyright());
			case StateCollumn:
				return NPluginStateToString(plugin.GetState());
			case LoadTimeCollumn:
				return plugin.GetLoadTime().IsValid() ? wxString::Format(wxT("%2.2f s"), plugin.GetLoadTime().GetTotalSeconds()) : wxString(wxEmptyString);
			case PlugTimeCollumn:
				return plugin.GetPlugTime().IsValid() ? wxString::Format(wxT("%2.2f s"), plugin.GetPlugTime().GetTotalSeconds()) : wxString(wxEmptyString);
			case InterfaceVersionCollumn:
				return static_cast<wxString>(plugin.GetSelectedInterfaceVersion().ToString());
			case NameCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module.GetPluginName());
			case FileNameCollumn:
				return  static_cast<wxString>(plugin.GetFileName());
			case InterfaceTypeCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module.GetInterfaceType());
			case InterfaceVersionsCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : this->InterfaceVersionsToString(module.GetInterfaceVersions());
			case PriorityCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : wxString::Format(wxT("%d"), module.GetPriority());
			case IncompatiblePluginsCollumn:
				return module.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(module.GetIncompatiblePlugins());
			default:
				return "";
			}
		}

		void RefreshListAfterUpdate()
		{
			if (!m_changeSortingOrder)
				this->m_sortAscending = !this->m_sortAscending;

			this->sortList();

			this->SetItemCount(m_orderedIndices.size());
			this->Refresh();

			this->SetColumnWidth(TitleCollumn, wxLIST_AUTOSIZE);
			this->SetColumnWidth(VersionCollumn, wxLIST_AUTOSIZE);

			this->m_sortAscending = !this->m_sortAscending;

			this->m_changeSortingOrder = false;
		}

		void PushBackPlugin(Neurotec::Plugins::NPlugin plugin)
		{
			this->m_plugins.push_back(plugin);
			this->m_orderedIndices.push_back(m_orderedIndices.size());
		}

		Neurotec::Plugins::NPlugin * GetPlugin(long index)
		{
			if (index < 0)
				return nullptr;

			if (index >= (long)m_orderedIndices.size())
				return nullptr;

			if (m_orderedIndices[index] >= (long)m_plugins.size())
				return nullptr;

			return &m_plugins[m_orderedIndices[index]];
		}

		void RemoveAllPluginsPropertyChangedCallbacks()
		{
			for (auto plugin : m_plugins)
				plugin.RemovePropertyChangedCallback(&wxPluginManagerDlg::PluginChanged, this);
		}
	};

public:
	wxPluginManagerDlg(wxWindow *parent, wxWindowID id, ::Neurotec::Plugins::NPluginManager manager, ::Neurotec::Plugins::NPlugin selectedPlugin = ::Neurotec::Plugins::NPlugin(NULL), const wxString& windowTitle = wxT("Plugin Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxPluginManagerDlgStyle)
		: wxDialog(parent, id, windowTitle, pos, size, style), m_pluginManager(manager)
	{
		InitGUI();

		OnPluginManagerChanged();
		m_pListActivated->SetFocus();
		OnSetSelectedPlugin(selectedPlugin);

		this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(wxPluginManagerDlg::OnClose), NULL, this);
		this->Connect(ID_BUTTON_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnAddClick), NULL, this);
		this->Connect(ID_BUTTON_BROWSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnBrowseClick), NULL, this);
		this->Connect(ID_BUTTON_DISABLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnDisableClick), NULL, this);
		this->Connect(ID_BUTTON_ENABLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnEnableClick), NULL, this);
		this->Connect(ID_BUTTON_PLUG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnPlugClick), NULL, this);
		this->Connect(ID_BUTTON_PLUGALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnPlugAllClick), NULL, this);
		this->Connect(ID_BUTTON_UNPLUG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnUnplugClick), NULL, this);
		this->Connect(ID_BUTTON_UNPLUGALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnUnplugAllClick), NULL, this);
		this->Connect(ID_BUTTON_REFRESH, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnRefreshClick), NULL, this);
		this->Connect(ID_LIST_PLUGINS, wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(wxPluginManagerDlg::OnListItemSelected), NULL, this);
		this->Connect(ID_LIST_PLUGINS, wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(wxPluginManagerDlg::OnListItemDeselected), NULL, this);
		this->Connect(wxEVT_PLUGIN_MANAGER_DLG, wxCommandEventHandler(wxPluginManagerDlg::OnPluginManagerEvent), NULL, this);
	}
	~wxPluginManagerDlg()
	{
		this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(wxPluginManagerDlg::OnClose), NULL, this);
		this->Disconnect(ID_BUTTON_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnAddClick), NULL, this);
		this->Disconnect(ID_BUTTON_BROWSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnBrowseClick), NULL, this);
		this->Disconnect(ID_BUTTON_DISABLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnDisableClick), NULL, this);
		this->Disconnect(ID_BUTTON_ENABLE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnEnableClick), NULL, this);
		this->Disconnect(ID_BUTTON_PLUG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnPlugClick), NULL, this);
		this->Disconnect(ID_BUTTON_PLUGALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnPlugAllClick), NULL, this);
		this->Disconnect(ID_BUTTON_UNPLUG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnUnplugClick), NULL, this);
		this->Disconnect(ID_BUTTON_UNPLUGALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnUnplugAllClick), NULL, this);
		this->Disconnect(ID_BUTTON_REFRESH, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxPluginManagerDlg::OnBtnRefreshClick), NULL, this);
		this->Disconnect(ID_LIST_PLUGINS, wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(wxPluginManagerDlg::OnListItemSelected), NULL, this);
		this->Disconnect(ID_LIST_PLUGINS, wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(wxPluginManagerDlg::OnListItemDeselected), NULL, this);
		this->Disconnect(wxEVT_PLUGIN_MANAGER_DLG, wxCommandEventHandler(wxPluginManagerDlg::OnPluginManagerEvent), NULL, this);

		if(m_pluginManager.GetHandle())
		{
			m_pListPlugins->RemoveAllPluginsPropertyChangedCallbacks();
			
			m_pluginManager.GetPlugins().RemoveCollectionChangedCallback(&wxPluginManagerDlg::PluginManager_PluginAdded, this);
			m_pluginManager.GetDisabledPlugins().RemoveCollectionChangedCallback(&wxPluginManagerDlg::PluginManager_DisabledPluginCanged, this);
		}
	}
private:
	void InitGUI()
	{
		m_pSizer = new wxBoxSizer(wxVERTICAL);
		SetSizer(m_pSizer);
		SetAutoLayout(true);

		wxBoxSizer * bSizerTop = new wxBoxSizer(wxHORIZONTAL);

		wxBoxSizer * bSizerLeft = new wxBoxSizer(wxVERTICAL);

		m_pLblInterfaceType = new wxStaticText(this, wxID_ANY, wxT("Interface type:"));
		bSizerLeft->Add(m_pLblInterfaceType, 1, wxALL | wxEXPAND, 1);

		m_pLblInterfaceVersion = new wxStaticText(this, wxID_ANY, wxT("Interface versions:"));
		bSizerLeft->Add(m_pLblInterfaceVersion, 1, wxALL | wxEXPAND, 1);

		m_pLblSearchPath = new wxStaticText(this, wxID_ANY, wxT("Plugin search path:"));
		bSizerLeft->Add(m_pLblSearchPath, 1, wxALL | wxEXPAND, 1);

		bSizerLeft->AddStretchSpacer(1);

		bSizerTop->Add(bSizerLeft, 0, wxALL | wxEXPAND, 1);

		wxBoxSizer * bSizerRight = new wxBoxSizer(wxVERTICAL);
		m_pLblInterfaceTypeValue = new wxStaticText(this, wxID_ANY, wxT("Type"));
		bSizerRight->Add(m_pLblInterfaceTypeValue, 1, wxALL | wxEXPAND, 1);

		m_pLblInterfaceVersionValue = new wxStaticText(this, wxID_ANY, wxT("Versions"));
		bSizerRight->Add(m_pLblInterfaceVersionValue, 1, wxALL | wxEXPAND, 1);

		wxBoxSizer * bSizer1 = new wxBoxSizer(wxHORIZONTAL);
		m_pTbSearchPath = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
		bSizer1->Add(m_pTbSearchPath, 1, wxALL | wxEXPAND, 1);

		m_pBtnBrowse = new wxButton(this, ID_BUTTON_BROWSE, wxT("..."));
		bSizer1->Add(m_pBtnBrowse, 0, wxALL | wxEXPAND, 1);
		bSizerRight->Add(bSizer1, 1, wxALL | wxEXPAND, 1);

		wxBoxSizer * bSizer2 = new wxBoxSizer(wxHORIZONTAL);
		bSizer2->AddStretchSpacer(1);

		m_pBtnAdd = new wxButton(this, ID_BUTTON_ADD, wxT("&Add ..."));
		bSizer2->Add(m_pBtnAdd, 0, wxALL | wxEXPAND, 1);

		m_pBtnRefresh = new wxButton(this, ID_BUTTON_REFRESH, wxT("&Refresh"));
		bSizer2->Add(m_pBtnRefresh, 0, wxALL | wxEXPAND, 1);

		m_pBtnPlugAll = new wxButton(this, ID_BUTTON_PLUGALL, wxT("&Plug all"));
		bSizer2->Add(m_pBtnPlugAll, 0, wxALL | wxEXPAND, 1);

		m_pBtnUnplugAll = new wxButton(this, ID_BUTTON_UNPLUGALL, wxT("&Unplug all"));
		bSizer2->Add(m_pBtnUnplugAll, 0, wxALL | wxEXPAND, 1);

		bSizerRight->Add(bSizer2, 0, wxALL | wxEXPAND, 1);
		bSizerTop->Add(bSizerRight, 1, wxALL | wxEXPAND, 1);
		m_pSizer->Add(bSizerTop, 0, wxALL | wxEXPAND, 1);

		wxStaticText * text4 = new wxStaticText(this, wxID_ANY, wxT("Plugins:"));
		m_pSizer->Add(text4, 0, wxALL | wxEXPAND, 1);

		m_pListPlugins = new NPluginManagerVirtualList(this, ID_LIST_PLUGINS, wxDefaultPosition, wxDefaultSize, wxLC_VIRTUAL | wxLC_REPORT);
		m_pSizer->Add(m_pListPlugins, 1, wxALL | wxEXPAND, 5);

		wxBoxSizer * bSizer3 = new wxBoxSizer(wxHORIZONTAL);
		m_pNotebook = new wxNotebook(this, wxID_ANY);

		m_pTextError = new wxTextCtrl(m_pNotebook, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP | wxTE_MULTILINE);
		m_pTextError->SetEditable(false);
		m_pNotebook->AddPage(m_pTextError, wxT("Error"), true);

		m_pListActivated = new wxListCtrl(m_pNotebook, wxID_ANY);
		m_pListActivated->InsertColumn(0, wxT("Component"));
		m_pListActivated->InsertColumn(1, wxT("Value"));
		m_pNotebook->AddPage(m_pListActivated, wxT("Activated"));

		bSizer3->Add(m_pNotebook, 1, wxALL | wxEXPAND, 5);

		wxBoxSizer * bSizer4 = new wxBoxSizer(wxVERTICAL);
		m_pBtnPlug = new wxButton(this, ID_BUTTON_PLUG, wxT("P&lug"));
		bSizer4->Add(m_pBtnPlug, 0, wxALL | wxEXPAND, 5);

		m_pBtnUnplug = new wxButton(this, ID_BUTTON_UNPLUG, wxT("U&nplug"));
		bSizer4->Add(m_pBtnUnplug, 0, wxALL | wxEXPAND, 5);

		m_pBtnEnable = new wxButton(this, ID_BUTTON_ENABLE, wxT("&Enable"));
		bSizer4->Add(m_pBtnEnable, 0, wxALL | wxEXPAND, 5);

		m_pBtnDisable = new wxButton(this, ID_BUTTON_DISABLE, wxT("&Disable"));
		bSizer4->Add(m_pBtnDisable, 0, wxALL | wxEXPAND, 5);

		bSizer3->Add(bSizer4, 0, wxALL | wxEXPAND, 5);
		m_pSizer->Add(bSizer3, 0, wxALL | wxEXPAND, 5);

		wxBoxSizer * bSizerBottom = new wxBoxSizer(wxHORIZONTAL);
		m_pLblTotalInfo = new wxStaticText(this, wxID_ANY, wxT("Total info"));
		bSizerBottom->Add(m_pLblTotalInfo, 1, wxALL | wxEXPAND, 5);

		m_pBtnOk = new wxButton(this, wxID_OK, wxT("OK"));
		bSizerBottom->Add(m_pBtnOk, 0, wxALL | wxEXPAND, 5);

		m_pSizer->Add(bSizerBottom, 0, wxALL | wxEXPAND, 5);

		SetIcon(wxNullIcon);
		SetBackgroundColour(wxColour(255, 255, 255));
		GetSizer()->Layout();
		GetSizer()->Fit(this);
		GetSizer()->SetSizeHints(this);
		Center();
	}


	wxBoxSizer * m_pSizer;

	wxStaticText * m_pLblInterfaceTypeValue;
	wxStaticText * m_pLblInterfaceType;
	wxStaticText * m_pLblInterfaceVersionValue;
	wxStaticText * m_pLblInterfaceVersion;
	wxStaticText * m_pLblSearchPath;
	wxStaticText * m_pLblTotalInfo;
	wxTextCtrl * m_pTbSearchPath;
	wxButton * m_pBtnBrowse;
	wxButton * m_pBtnAdd;
	wxButton * m_pBtnRefresh;
	wxButton * m_pBtnPlugAll;
	wxButton * m_pBtnUnplugAll;
	wxButton * m_pBtnEnable;
	wxButton * m_pBtnDisable;
	wxButton * m_pBtnPlug;
	wxButton * m_pBtnUnplug;
	wxButton * m_pBtnOk;
	wxListCtrl * m_pListActivated;
	wxNotebook * m_pNotebook;
	NPluginManagerVirtualList * m_pListPlugins;
	wxTextCtrl * m_pTextError;

	Neurotec::Plugins::NPluginManager m_pluginManager;

private:
	void OnClose(wxCloseEvent&)
	{
		Destroy();
	}

	wxString GetInterfaceVersionsString()
	{
		if(!m_pluginManager.GetHandle())
		{
			return wxEmptyString;
		}

		NArrayWrapper<Neurotec::NVersionRange> versions = m_pluginManager.GetInterfaceVersions();
		return InterfaceVersionsToString(versions);
	}

	wxString GetInterfaceVersionsString(Neurotec::Plugins::NPluginModule module)
	{
		if(!module.GetHandle())
		{
			return wxEmptyString;
		}

		NArrayWrapper<Neurotec::NVersionRange> versions = module.GetInterfaceVersions();
		return InterfaceVersionsToString(versions);
	}

	wxString InterfaceVersionsToString(const NArrayWrapper<Neurotec::NVersionRange> versions)
	{
		wxString value = wxT("");

		for(int i = 0; i < versions.GetCount(); i++)
		{
			if(value.length() != 0)
			{
				value.append(wxT(", "));
			}
			value.append(static_cast<wxString>(versions[i].ToString()));
		}
		return value;
	}

	wxString GetModuleVersion(Neurotec::NModule module)
	{
		if(!module.GetHandle())
		{
			return wxEmptyString;
		}
		return wxString::Format(wxT("%d.%d.%d.%d"), module.GetVersionMajor(), module.GetVersionMinor(), module.GetVersionBuild(), module.GetVersionRevision());
	}
	
	void OnPluginManagerEvent(wxCommandEvent& event)
	{
		if(event.GetId() == ID_PLUGINMANAGER_PLUGIN_ADDED)
		{
			OnPluginAdded(reinterpret_cast<Neurotec::Plugins::HNPlugin>(event.GetClientData()));
		}
		else if(event.GetId() == ID_PLUGINMANAGER_DISABLED_PLUGINS_CHANGED)
		{
			UpdateTotalInfo();
		}
		else if(event.GetId() == ID_PLUGINMANAGER_PLUGIN_CHANGED)
		{
			m_pListPlugins->RefreshListAfterUpdate();
			OnSelectedPluginChanged();
		}
	}

	static void PluginChanged(Neurotec::Plugins::NPlugin::PropertyChangedEventArgs args)
	{
		wxPluginManagerDlg * dialog = reinterpret_cast<wxPluginManagerDlg*>(args.GetParam());
		wxCommandEvent event;
		event.SetEventType(wxEVT_PLUGIN_MANAGER_DLG);
		event.SetId(ID_PLUGINMANAGER_PLUGIN_CHANGED);
		event.SetClientData(args.GetObject<Neurotec::Plugins::NPlugin>().RefHandle());
		wxPostEvent(dialog, event);
	}

	void AddPlugin(Neurotec::Plugins::NPlugin plugin)
	{
		m_pListPlugins->PushBackPlugin(plugin);
		m_pListPlugins->RefreshListAfterUpdate();
		
		try
		{
			plugin.AddPropertyChangedCallback(&wxPluginManagerDlg::PluginChanged, this);
		}
		catch(...){}
	}

	void UpdateTotalInfo()
	{
		if(m_pluginManager.GetHandle())
		{
			Neurotec::NTimeSpan loadTime(0, 0, 0, 0, 0);
			Neurotec::NTimeSpan plugTime(0, 0, 0, 0, 0);
			int unpluggedCount = 0;
			int unusedCount = 0;
			int count = 0;
			{
				NArrayWrapper< ::Neurotec::Plugins::NPlugin> currentPlugins = m_pluginManager.GetPlugins().GetAll();
				for (int i = 0; i < currentPlugins.GetCount(); i++)
				{
					::Neurotec::Plugins::NPlugin plugin = currentPlugins[i];
					loadTime = loadTime + plugin.GetLoadTime();
					plugTime = plugTime + plugin.GetPlugTime();
					if(plugin.GetState() == Neurotec::Plugins::npsUnplugged) unpluggedCount++;
					else if(plugin.GetState() == Neurotec::Plugins::npsUnused) unusedCount++;
				}

				count = currentPlugins.GetCount();
			}
			wxString strDisabledPlugins = wxEmptyString;
			{
				NArrayWrapper<NString> disabledPlugins = m_pluginManager.GetDisabledPlugins().GetAll();
				for (int i = 0; i < disabledPlugins.GetCount(); i++)
				{
					strDisabledPlugins.append(strDisabledPlugins.length() == 0? wxT(". Disabled: ") : wxT(", "));
					strDisabledPlugins.append(static_cast<wxString>(disabledPlugins[i]));
				}
			}
			Neurotec::NTimeSpan totalTime = loadTime + plugTime;
			wxString parse = wxT("Total time: %.2f s (Load: %2.2f s. Plug: %2.2f s). Total plugins: %d (Unplugged: %d. Unused: %d)%s");
			m_pLblTotalInfo->SetLabel(wxString::Format(parse, totalTime.GetTotalSeconds(), loadTime.GetTotalSeconds(), plugTime.GetTotalSeconds(),
				count, unpluggedCount, unusedCount, strDisabledPlugins.c_str()));
		}
		else
		{
			m_pLblTotalInfo->SetLabel(wxEmptyString);
		}
	}

	void OnListItemSelected(wxCommandEvent&)
	{
		OnSelectedPluginChanged();
	}

	void OnListItemDeselected(wxCommandEvent&)
	{
		OnSelectedPluginChanged();
	}

	void OnBtnUnplugClick(wxCommandEvent&)
	{
		try
		{
			this->Enable(false);
			long item = -1;
			while ((item = m_pListPlugins->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin = m_pListPlugins->GetPlugin(item);
				if (pPlugin == nullptr)
					continue;

				AsyncRun::UnplugAsync(*pPlugin);
			}
		}
		catch (...) { }
		this->Enable(true);
	}

	void OnBtnUnplugAllClick(wxCommandEvent&)
	{
		if(!m_pluginManager.GetHandle()) return;
		AsyncRun::UnplugAllAsync(m_pluginManager);
	}

	void OnBtnRefreshClick(wxCommandEvent&)
	{
		if(!m_pluginManager.GetHandle()) return;
		AsyncRun::RefreshAsync(m_pluginManager);
	}

	void OnBtnPlugAllClick(wxCommandEvent&)
	{
		if(!m_pluginManager.GetHandle()) return;
		AsyncRun::PlugAllAsync(m_pluginManager);
	}

	void OnBtnPlugClick(wxCommandEvent&)
	{
		try
		{
			this->Enable(false);
			long item = -1;
			while ((item = m_pListPlugins->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin = m_pListPlugins->GetPlugin(item);
				if (pPlugin == nullptr)
					continue;

				AsyncRun::PlugAsync(*pPlugin);
			}
		}
		catch (...) { }
		this->Enable(true);
	}
	
	void OnBtnEnableClick(wxCommandEvent&)
	{
		try
		{
			this->Enable(false);
			long item = -1;
			while ((item = m_pListPlugins->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin = m_pListPlugins->GetPlugin(item);
				if (pPlugin == nullptr)
					continue;

				AsyncRun::EnableAsync(*pPlugin);
			}
		}
		catch (...) { }
		this->Enable(true);
	}

	void OnBtnDisableClick(wxCommandEvent&)
	{
		try
		{
			this->Enable(false);
			long item = -1;
			while ((item = m_pListPlugins->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin = m_pListPlugins->GetPlugin(item);
				if (pPlugin == nullptr)
					continue;

				AsyncRun::DisableAsync(*pPlugin);
			}
		}
		catch (...) { }
		this->Enable(true);
	}

	void OnBtnBrowseClick(wxCommandEvent&)
	{
		if(m_pluginManager.GetHandle())
		{
			wxString folder;
			wxDirDialog dialog(this, wxT("Select folder"), m_pluginManager.GetPluginSearchPath());
			if(dialog.ShowModal() == wxID_OK)
			{
				m_pluginManager.SetPluginSearchPath(dialog.GetPath());
				OnPluginSearchPathChanged();
			}
		}
	}

	void OnBtnAddClick(wxCommandEvent&)
	{
		if(!m_pluginManager.GetHandle()) return;
		wxArrayString paths;
		wxFileDialog dialog(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);
		if(dialog.ShowModal() == wxID_OK)
		{
			dialog.GetPaths(paths);
			if(paths.Count() > 0)
			{
				this->Enable(false);
				try
				{
					for(wxArrayString::iterator it = paths.begin(); it != paths.end(); it++)
					{
						AsyncRun::AddPluginAsync(m_pluginManager, *it);
					}
				}
				catch(...){}
				this->Enable(true);
			}
		}
	}
	
	void OnSetSelectedPlugin(Neurotec::Plugins::NPlugin select)
	{
		int index = -1;
		while((index = m_pListPlugins->GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1)
		{
			m_pListPlugins->SetItemState(index, 0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
		}
		if(select.GetHandle())
		{
			index = -1;
			while((index = m_pListPlugins->GetNextItem(index, wxLIST_NEXT_ALL)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin = m_pListPlugins->GetPlugin(index);
				if (pPlugin == nullptr)
					continue;

				if(pPlugin->Equals(select))
				{
					m_pListPlugins->SetItemState(index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
					OnSelectedPluginChanged();
					break;
				}
			}
		}
	}
	
	void OnPluginManagerChanged()
	{
		m_pLblInterfaceTypeValue->SetLabel(m_pluginManager.GetHandle()? static_cast<wxString>(m_pluginManager.GetInterfaceType()) : wxString(wxEmptyString));
		m_pLblInterfaceVersionValue->SetLabel(GetInterfaceVersionsString());
		bool enable = m_pluginManager.GetHandle() != NULL;
		m_pLblInterfaceType->Enable(enable);
		m_pLblInterfaceVersion->Enable(enable);
		m_pListPlugins->Enable(enable);
		m_pLblSearchPath->Enable(enable);
		m_pTbSearchPath->Enable(enable);
		m_pTbSearchPath->SetEditable(false);
		m_pBtnBrowse->Enable(enable);
		m_pBtnUnplugAll->Enable(enable && m_pluginManager.AllowsUnplug());
		m_pBtnUnplug->Enable(enable && m_pluginManager.AllowsUnplug());
		m_pBtnAdd->Enable(enable);
		m_pBtnRefresh->Enable(enable);
		m_pBtnPlugAll->Enable(enable);
		OnPluginSearchPathChanged();

		if(m_pluginManager.GetHandle())
		{
			NArrayWrapper<Neurotec::Plugins::NPlugin> currentPlugins = m_pluginManager.GetPlugins().GetAll();
			for (int i = 0; i < currentPlugins.GetCount(); i++)
			{
				m_pListPlugins->PushBackPlugin(currentPlugins[i]);
			}

			m_pluginManager.GetDisabledPlugins().AddCollectionChangedCallback(&wxPluginManagerDlg::PluginManager_DisabledPluginCanged, this);
			m_pluginManager.GetPlugins().AddCollectionChangedCallback(&wxPluginManagerDlg::PluginManager_PluginAdded, this);
		}

		m_pListPlugins->RefreshListAfterUpdate();
		UpdateTotalInfo();
		OnSelectedPluginChanged();
	}

	void OnSelectedPluginChanged()
	{
		int count = m_pListPlugins->GetSelectedItemCount();
		long item;
		Neurotec::Plugins::NPlugin * pPlugin = nullptr;
		if(count == 1)
		{
			item = m_pListPlugins->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			pPlugin = m_pListPlugins->GetPlugin(item);
		}

		if (pPlugin == nullptr)
			return;

		m_pListActivated->DeleteAllItems();

		Neurotec::Plugins::NPluginModule module = pPlugin->GetHandle() == NULL? NULL : pPlugin->GetModule();
		if (module.GetHandle())
		{
			long index;
			wxArrayString strings = wxStringTokenize(static_cast<wxString>(module.GetActivated()), wxT(":,"), wxTOKEN_STRTOK);
			for (size_t i = 0; i < strings.Count() / 2; ++i)
			{
				index = m_pListActivated->InsertItem(m_pListActivated->GetItemCount(), strings[i * 2].Trim(false));
				m_pListActivated->SetItem(index, 1, strings[i * 2 + 1].Trim(false));
			}
		}

		m_pTextError->SetValue(wxEmptyString);
		if(pPlugin->GetHandle())
		{
			Neurotec::NError error = pPlugin->GetError();
			if(error.GetHandle())
			{
				m_pTextError->SetValue(static_cast<wxString>(error.ToString()));
			}
		}
		m_pBtnUnplug->Enable(count > 0 && m_pluginManager.AllowsUnplug());
		m_pBtnPlug->Enable(count > 0);
		m_pBtnEnable->Enable(count > 0);
		m_pBtnDisable->Enable(count > 0);
	}

	void OnPluginSearchPathChanged()
	{
		m_pTbSearchPath->SetValue(m_pluginManager.GetHandle() == NULL ? wxString(wxEmptyString) : static_cast<wxString>(m_pluginManager.GetPluginSearchPath()));
		m_pTbSearchPath->SetEditable(true);
	}

	void OnPluginAdded(Neurotec::Plugins::NPlugin plugin)
	{
		if (plugin.GetHandle())
		{
			long index = -1;
			while((index = m_pListPlugins->GetNextItem(index, wxLIST_NEXT_ALL)) != -1)
			{
				Neurotec::Plugins::NPlugin * pPlugin= m_pListPlugins->GetPlugin(index);
				if (pPlugin == nullptr)
					continue;

				if(pPlugin->Equals(plugin)) return;
			}

			AddPlugin(plugin);
			OnSetSelectedPlugin(plugin);
			UpdateTotalInfo();
		}
	}

	static void PluginManager_PluginAdded(::Neurotec::Collections::CollectionChangedEventArgs< ::Neurotec::Plugins::NPlugin> args)
	{
		if (args.GetAction() == Neurotec::Collections::nccaAdd)
		{
			wxPluginManagerDlg * dialog = reinterpret_cast<wxPluginManagerDlg*>(args.GetParam());
			for (int i = 0; i < args.GetNewItems().GetCount(); i++)
			{
				wxCommandEvent event;
				event.SetEventType(wxEVT_PLUGIN_MANAGER_DLG);
				event.SetId(ID_PLUGINMANAGER_PLUGIN_ADDED);
				event.SetClientData(args.GetNewItems()[i].RefHandle());
				wxPostEvent(dialog, event);
			}
		}
	}

	static void PluginManager_DisabledPluginCanged(::Neurotec::Collections::CollectionChangedEventArgs< ::Neurotec::NString> args)
	{
		wxPluginManagerDlg * dialog = reinterpret_cast<wxPluginManagerDlg*>(args.GetParam());
		wxCommandEvent event;
		event.SetEventType(wxEVT_PLUGIN_MANAGER_DLG);
		event.SetId(ID_PLUGINMANAGER_DISABLED_PLUGINS_CHANGED);
		wxPostEvent(dialog, event);
	}

	static wxString NModuleOptionsToString(NModuleOptions options)
	{
		wxString value = wxEmptyString;
		if((options & nmoDebug) == nmoDebug)
			value = wxT("Debug");
		if((options  & nmoProtected) == nmoProtected)
		{
			value = value.IsEmpty() ? value : value.append(wxT(", "));
			value.append(wxT("Protected"));
		}
		if((options & nmoUnicode) == nmoUnicode)
		{
			value = value.IsEmpty()? value : value.append(wxT(", "));
			value.append(wxT("Unicode"));
		}
		if((options & nmoNoAnsiFunc) == nmoNoAnsiFunc)
		{
			value = value.IsEmpty()? value : value.append(wxT(", "));
			value.append(wxT("NoAnsiFunc"));
		}
		if((options & nmoNoUnicode) == nmoNoUnicode)
		{
			value = value.IsEmpty()? value : value.append(wxT(", "));
			value.append(wxT("NoUnicode"));
		}
		if((options & nmoLib) == nmoLib)
		{
			value = value.IsEmpty()? value : value.append(wxT(", "));
			value.append(wxT("Lib"));
		}
		if((options & nmoExe) == nmoExe)
		{
			value = value.IsEmpty()? value : value.append(wxT(", "));
			value.append(wxT("Exe"));
		}

		return value.IsEmpty()? wxT("None") : value;
	}

	static wxString NPluginStateToString(Neurotec::Plugins::NPluginState state)
	{
		switch(state)
		{
		case Neurotec::Plugins::npsNone: return wxT("None");
		case Neurotec::Plugins::npsLoadError: return wxT("LoadError");
		case Neurotec::Plugins::npsNotRecognized: return wxT("NotRecognized");
		case Neurotec::Plugins::npsInvalidModule: return wxT("InvalidModule");
		case Neurotec::Plugins::npsInterfaceTypeMismatch: return wxT("InterfaceTypeMismatch");
		case Neurotec::Plugins::npsInterfaceVersionMismatch: return wxT("InterfaceVersionMismatch");
		case Neurotec::Plugins::npsInvalidInterface: return wxT("InvalidInterface");
		case Neurotec::Plugins::npsUnplugged: return wxT("Unplugged");
		case Neurotec::Plugins::npsUnused: return wxT("Unused");
		case Neurotec::Plugins::npsDisabled: return wxT("Disabled");
		case Neurotec::Plugins::npsDuplicate: return wxT("Duplicate");
		case Neurotec::Plugins::npsIncompatibleWithOtherPlugins: return wxT("IncompatibleWithOtherPlugins");
		case Neurotec::Plugins::npsPluggingError: return wxT("PluggingError");
		case Neurotec::Plugins::npsPlugged: return wxT("Plugged");
		default: return wxT("Unknown");
		}
	}

	enum
	{
		ID_BUTTON_BROWSE = 1000,
		ID_BUTTON_ADD,
		ID_BUTTON_REFRESH,
		ID_BUTTON_PLUGALL,
		ID_BUTTON_UNPLUGALL,
		ID_BUTTON_ENABLE,
		ID_BUTTON_DISABLE,
		ID_BUTTON_PLUG,
		ID_BUTTON_UNPLUG,
		ID_LIST_PLUGINS,
		ID_LIST_COMPONENTS,
		
		ID_PLUGINMANAGER_PLUGIN_ADDED,
		ID_PLUGINMANAGER_PLUGIN_CHANGED,
		ID_PLUGINMANAGER_DISABLED_PLUGINS_CHANGED,
	};
};
	
}}


#endif // !WX_PLUGIN_MANAGER_DLG_HPP_INCLUDED
