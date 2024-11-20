#include "Location.h"

namespace Papyrus::Location
{
	RE::BGSLocation* GetParentLocation(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSLocation* a_location)
  {
    if (!a_location) {
      a_vm->TraceStack("Location is none", a_stackID);
      return nullptr;
    }
    return a_location->parentLoc;
  }

} // namespace Papyrus::Location
