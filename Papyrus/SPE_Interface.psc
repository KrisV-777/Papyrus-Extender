ScriptName SPE_Interface Hidden

; Print the given String into the consosle
Function PrintConsole(String asText) native global

; Return the name of the custom menu
String Function GetMenuName() native global
; Open/close a custom menu under the given filepath
; The difference between this menu and the one provided by SKSE is that this one will *not* pause the game while open
Function OpenCustomMenu(String asFilePath) native global
Function CloseCustomMenu() native global
