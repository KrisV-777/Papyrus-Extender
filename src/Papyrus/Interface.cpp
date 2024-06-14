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

	bool OpenCustomMenu(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::string_view a_filepath)
	{
		if (a_filepath.empty()) {
			a_vm->TraceStack("File path to swf file is empty", a_stackID);
			return false;
		} else if (!fs::exists(fmt::format("Data\\Interface\\{}.swf", a_filepath))) {
			a_vm->TraceStack("File path does not lead to a valid file", a_stackID);
			return false;
		}

		if (Internal::Interface::CustomMenu::IsOpen()) {
			return false;
		}

		Internal::Interface::CustomMenu::SetSwfPath(a_filepath);
		Internal::Interface::CustomMenu::Show();
		return true;
	}

	void CloseCustomMenu(RE::StaticFunctionTag*)
	{
		Internal::Interface::CustomMenu::Hide();
	}

}