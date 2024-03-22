ScriptName SPE_Utility Hidden

; Reorder every element in the array
Function Shuffle_Int(int[] arr) global native
Function Shuffle_Float(float[] arr) global native
Function Shuffle_String(String[] arr) global native

; Sort based on a comparison function (lua code)
bool Function Sort_Int(StackID a_stackID, int[] arr, String lua) global native
bool Function Sort_Float(StackID a_stackID, float[] arr, String lua) global native
bool Function Sort_String(StackID a_stackID, String[] arr, String lua) global native

; Find the first element satisfying the predicate (lua code)
int Function FindIf_Int(StackID a_stackID, int[] arr, String lua) global native
int Function FindIf_Float(StackID a_stackID, float[] arr, String lua) global native
int Function FindIf_String(StackID a_stackID, String[] arr, String lua) global native

; Create a new array [push, arr[0], arr[1], ... arr[N-1]]
int[] Function PushFrontInt(int[] arr, int push) global native
bool[] Function PushFrontBool(bool[] arr, bool push) global native
float[] Function PushFrontFloat(float[] arr, float push) global native
String[] Function PushFrontString(String[] arr, String push) global native
