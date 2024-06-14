#pragma once

  namespace Papyrus::Interface
	{
		void PrintConsole(RE::StaticFunctionTag*, RE::BSFixedString a_msg);
		RE::BSFixedString GetMenuName(RE::StaticFunctionTag*);
		bool OpenCustomMenu(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::string_view a_filepath);
		void CloseCustomMenu(RE::StaticFunctionTag*);

		inline bool Register(VM* a_vm)
		{
			REGISTERFUNC(PrintConsole, "SPE_Interface", true);
			REGISTERFUNC(GetMenuName, "SPE_Interface", true);
			REGISTERFUNC(OpenCustomMenu, "SPE_Interface", true);
			REGISTERFUNC(CloseCustomMenu, "SPE_Interface", true);

      return true;
		};
	};