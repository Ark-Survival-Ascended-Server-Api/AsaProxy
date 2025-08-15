#pragma once

#include <filesystem>
#include <Windows.h>

namespace fs = std::filesystem;

inline fs::path get_exe_path()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    return fs::path(buffer).parent_path();
}

inline fs::path get_asa_directory()
{
    return get_exe_path() / "AsaApi";
}

inline fs::path get_asa_dll_path()
{
    return get_asa_directory() / "AsaApi.dll";
}

inline fs::path get_asa_runtime_config_path()
{
    return get_asa_directory() / "AsaApi.runtimeconfig.json";
}

inline fs::path get_system_directory()
{
    wchar_t buffer[MAX_PATH];
    GetSystemDirectoryW(buffer, MAX_PATH);
    return buffer;
}

inline fs::path get_system_version_dll_path()
{
    return get_system_directory() / "version.dll";
}
