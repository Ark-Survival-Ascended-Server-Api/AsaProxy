#include "Asm.hpp"
#include "Dotnet.hpp"

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID)
{
    switch (fdw_reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinst_dll);

        initialize_version_dll();
        initialize_dotnet();
        break;

    case DLL_PROCESS_DETACH:
        free_dotnet();
        free_version_dll();
        break;

    default:
        break;
    }

    return TRUE;
}
