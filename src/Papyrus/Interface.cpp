#include "Interface.h"

#include "Interface/CustomMenu.h"

namespace Papyrus::Interface
{
	void PrintConsole(RE::StaticFunctionTag*, RE::BSFixedString a_msg)
	{
		RE::ConsoleLog::GetSingleton()->Print(a_msg.c_str());
	}

	RE::BSFixedString GetMenuName(RE::StaticFunctionTag*)
	{
		return Internal::Interface::CustomMenu::NAME;
	}

	bool OpenCustomMenu(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::string a_filepath)
	{
		if (a_filepath.empty()) {
			a_vm->TraceStack("File path to swf file is empty", a_stackID);
			return false;
		}
		if (a_filepath.ends_with(".swf")) {
			a_filepath = a_filepath.substr(0, a_filepath.size() - 4);
		}
		if (!fs::exists(std::format("Data\\Interface\\{}.swf", a_filepath))) {
			a_vm->TraceStack("File path does not lead to a valid file", a_stackID);
			return false;
		}

		if (Internal::Interface::CustomMenu::IsOpen()) {
			return false;
		}
		try {
			Internal::Interface::CustomMenu::SetSwfPath(a_filepath);
			Internal::Interface::CustomMenu::Show();
			return true;
		} catch (const std::exception& e) {
			a_vm->TraceStack(e.what(), a_stackID);
			return false;
		}
	}

	void CloseCustomMenu(RE::StaticFunctionTag*)
	{
		Internal::Interface::CustomMenu::Hide();
	}

}
