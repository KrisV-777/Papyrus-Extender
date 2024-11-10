Scriptname SPE_Form Hidden

; Get all references that are currently in possession of the given form
ObjectReference[] Function GetContainer(Form akForm) native global

; Given a leveled list, return a single array containing all possible drops from this list
; The function recursively finds all items, including those contained in other leveled lists of any depth
; That is, it is guaranteed that the returned Form[] array will no longer contain any LeveledItem objects
Form[] Function FlattenLeveledList(LeveledItem akList) native global