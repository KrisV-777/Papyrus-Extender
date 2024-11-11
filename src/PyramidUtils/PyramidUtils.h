#include "Hooks.h"
#include "Serialize.h"

namespace PyramidUtils {
  inline void Init()
  {

    const auto serialization = SKSE::GetSerializationInterface();
    serialization->SetUniqueID(Serialize::UtilRecord);
    serialization->SetSaveCallback(Serialize::Save);
    serialization->SetLoadCallback(Serialize::Load);
    serialization->SetRevertCallback(Serialize::Revert);
  }
}