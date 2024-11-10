ScriptName SPE_Utility Hidden

; Randomly reorder every element in the array, the array is modified in-place
Function Shuffle_Int(int[] arr) global native
Function Shuffle_Float(float[] arr) global native
Function Shuffle_String(String[] arr) global native

; Sort arr using a comparison function: "compare(a, b)" in place, the array is modified in-place, returns true on success
; Example: Sort_Int(arr, "function compare(a, b) return a <= b end") would sort arr in descending order
; "lua" can also be a filepath to a .lua file containing the function, relative to Skyrim.exe
bool Function Sort_Int(int[] arr, String lua) global native
bool Function Sort_Float(float[] arr, String lua) global native
bool Function Sort_String(String[] arr, String lua) global native

; Find the first element satisfying the function "predicate(a)"
; Returns the index of the element, -1 if no such element exists, -2 if an error occursed
; Example: FindIf_Int(arr, "function predicate(a) return a > 5 end") returns the index of the first element > 5
; "lua" can also be a filepath to a .lua file containing the function, relative to Skyrim.exe
int Function FindIf_Int(int[] arr, String lua) global native
int Function FindIf_Float(float[] arr, String lua) global native
int Function FindIf_String(String[] arr, String lua) global native

; Remove all occurences satisfying the predicate function, return the filtered array
; Example: RemoveIf_Int(arr, "function predicate(a) return a > 5 end") removes all elements that are > 5
; "lua" can also be a filepath to a .lua file containing the function, relative to Skyrim.exe
int[] Function RemoveIf_Int(int[] arr, String lua) native global
float[] Function RemoveIf_Float(Form[] arr, String lua) native global
String[] Function RemoveIf_String(Form[] arr, String lua) native global

; Remove any objects from arr that are present in filter, return the filtered array
Form[] Function FilterArray_Form(Form[] arr, Form[] filter) native global
int[] Function FilterArray_Int(int[] arr, int[] filter) native global
float[] Function FilterArray_Float(float[] arr, float[] filter) native global
String[] Function FilterArray_String(String[] arr, String[] filter) native global

; Create a new array [push, arr[0], arr[1], ..., arr[N-1]]
int[] Function PushFront_Int(int[] arr, int push) global native
float[] Function PushFront_Float(float[] arr, float push) global native
String[] Function PushFront_String(String[] arr, String push) global native
