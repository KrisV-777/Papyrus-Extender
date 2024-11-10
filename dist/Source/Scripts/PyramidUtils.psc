Scriptname PyramidUtils Hidden 

; Actor
Function SetActorCalmed(Actor akActor, bool abCalmed) global native
Function SetActorFrozen(Actor akTarget, bool abFrozen) global native
Actor[] Function GetDetectedBy(Actor akActor) global native
Keyword[] Function WornHasKeywords(Actor akActor, Keyword[] akKwds) global native
Keyword[] Function WornHasKeywordStrings(Actor akActor, String[] akKwds) global native
Function Dismount(Actor akTarget) global native

; Inventory Processing
Form[] Function GetItemsByKeyword(ObjectReference akContainer, Keyword[] akKeywords, bool abMatchAll = false) global native
Form[] Function FilterFormsByKeyword(Form[] akForms, Keyword[] akKeywords, bool abMatchAll = false, bool abInvert = false) global native
Form[] Function FilterFormsByGoldValue(Form[] akForms, int aiValue, bool abGreaterThan = true, bool abEqual = true) global native
Form[] Function FilterByEnchanted(ObjectReference akContainer, Form[] akForms, bool abEnchanted = true) global native
Form[] Function FilterByEquippedSlot(Form[] akForms, int[] aiSlots, bool abAll = false) global native
Int Function RemoveForms(ObjectReference akFromCont, Form[] akForms, ObjectReference akToCont = none) global native

; Form Processing
bool Function FormHasKeyword(Form akItem, Keyword[] akKwds, bool abAll = false) global native
bool Function FormHasKeywordStrings(Form akItem, String[] akKwds, bool abAll = false) global native

; Player
Actor Function GetPlayerSpeechTarget() global native

; String Processing
String Function ReplaceAt(String asStr, int aiIndex, String asReplace) global native

; Input
String Function GetButtonForDXScanCode(int aiCode) global native
Function RegisterForAllAlphaNumericKeys(Form akForm) global
  akForm.RegisterForKey(57)
  int i = 2
  While (i < 12)
    akForm.RegisterForKey(i)
    i += 1
  EndWhile
  i = 16
  While (i < 26)
    akForm.RegisterForKey(i)
    i += 1
  EndWhile
  i = 30
  While i < 39
    akForm.RegisterForKey(i)
    i += 1
  EndWhile
  i = 44
  While (i < 51)
    akForm.RegisterForKey(i)
    i += 1
  EndWhile
EndFunction

Form[] Function GetInventoryNamedObjects(ObjectReference akContainer, String[] asNames) global native

; unlike ObjecReference.GetItemHealthPercent, this will work on items in a container (range: 0.0-1.6)
float Function GetTemperFactor(ObjectReference akContainer, Form akItem) global native

; geography
ObjectReference Function GetQuestMarker(Quest akQuest) global native

; if cell is exterior gets worldspace like normal, if interior looks for external doors and their worldspace
WorldSpace[] Function GetExteriorWorldSpaces(Cell akCell) global native
Location[] Function GetExteriorLocations(Cell akCell) global native

; unlike GetDistance this works even when one or both refs are in an interior or another cell
float Function GetTravelDistance(ObjectReference akRef1, ObjectReference akRef2) global native

; uses worldspace offsets to get absolute position on external refs
float Function GetAbsPosX(ObjectReference akRef) global native
float Function GetAbsPosY(ObjectReference akRef) global native
float Function GetAbsPosZ(ObjectReference akRef) global native

; misc 
GlobalVariable Function GetGlobal(String asEditorID) global native

; custom console proxy functions - ignore these
String Function ConsoleGetAbsPos(Form akRef) global
  Debug.Trace("ConsoleGetAbsPos - " + akRef)
  ObjectReference ref = akRef as ObjectReference
  If (!ref)
    return "not a valid ref"
  endIf
  float x = GetAbsPosX(ref)
  float y = GetAbsPosY(ref)
  float z = GetAbsPosZ(ref)
  Location loc = ref.GetCurrentLocation()
  String msg = ""
  While (loc)
    msg += loc.GetName() + "\n"
    Location parLoc = SPE_Location.GetParentLocation(loc)
    If (parLoc != loc)
      loc = parLoc
    Else
      loc = none
    EndIf
  EndWhile
  msg += "Position: (" + x + ", " + y + ", " + z + ")"
  return msg
EndFunction

String Function ConsoleGetPlayerAbsDist(Form akRef) global
  ObjectReference ref = akRef as ObjectReference
  If (!ref)
    return "not a valid ref"
  endIf
  return GetTravelDistance(Game.GetPlayer(), ref)
EndFunction

; Script Version Number
; This will no longer change and is only meant for backwards compatibility with mods made while this script was a standalone mod
Float Function GetVersion() global
  return 0.002010
EndFunction
