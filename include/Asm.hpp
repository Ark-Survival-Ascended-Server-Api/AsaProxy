#pragma once

#include "Path.hpp"
#include "Windows.h"

extern "C" UINT_PTR version_dll_proc_addresses[17]{};

extern "C"
{
    void get_file_version_info_a_wrapper();

    void get_file_version_info_by_handle_wrapper();

    void get_file_version_info_ex_a_wrapper();

    void get_file_version_info_ex_w_wrapper();

    void get_file_version_info_size_a_wrapper();

    void get_file_version_info_size_ex_a_wrapper();

    void get_file_version_info_size_ex_w_wrapper();

    void get_file_version_info_size_w_wrapper();

    void get_file_version_info_w_wrapper();

    void ver_find_file_a_wrapper();

    void ver_find_file_w_wrapper();

    void ver_install_file_a_wrapper();

    void ver_install_file_w_wrapper();

    void ver_language_name_a_wrapper();

    void ver_language_name_w_wrapper();

    void ver_query_value_a_wrapper();

    void ver_query_value_w_wrapper();
}

inline HINSTANCE g_hinst_version_dll;

inline LPCSTR g_import_names[] = {
    "GetFileVersionInfoA",
    "GetFileVersionInfoByHandle",
    "GetFileVersionInfoExA",
    "GetFileVersionInfoExW",
    "GetFileVersionInfoSizeA",
    "GetFileVersionInfoSizeExA",
    "GetFileVersionInfoSizeExW",
    "GetFileVersionInfoSizeW",
    "GetFileVersionInfoW",
    "VerFindFileA",
    "VerFindFileW",
    "VerInstallFileA",
    "VerInstallFileW",
    "VerLanguageNameA",
    "VerLanguageNameW",
    "VerQueryValueA",
    "VerQueryValueW"
};

inline void initialize_version_dll()
{
    const auto version_dll_path = get_system_version_dll_path();

    g_hinst_version_dll = LoadLibraryW(version_dll_path.wstring().c_str());

    if (g_hinst_version_dll == nullptr)
        throw std::runtime_error("Failed to load version.dll");

    for (int i = 0; i < 17; i++)
    {
        const auto proc_address = reinterpret_cast<UINT_PTR>(GetProcAddress(g_hinst_version_dll, g_import_names[i]));

        if (proc_address == 0)
            throw std::runtime_error("Failed to get address of " + std::string(g_import_names[i]));

        version_dll_proc_addresses[i] = proc_address;
    }
}

inline void free_version_dll()
{
    if (g_hinst_version_dll)
        {
            FreeLibrary(g_hinst_version_dll);
            g_hinst_version_dll = nullptr;
        }
}
