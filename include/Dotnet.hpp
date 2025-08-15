#pragma once

#include <filesystem>
#include <mutex>
#include <memory>
#include <atomic>
#include <thread>
#include <hostfxr.h>
#include <coreclr_delegates.h>

#include "Path.hpp"

namespace fs = std::filesystem;

typedef void (CORECLR_DELEGATE_CALLTYPE* main_fn)();

class dotnet
{
public:
    explicit dotnet(const fs::path& dotnet_runtime_config_path);

    dotnet(const dotnet&) = delete;

    dotnet& operator=(const dotnet&) = delete;

    dotnet(dotnet&&) = delete;

    dotnet& operator=(dotnet&&) = delete;

    ~dotnet();

    void call_function_with_unmanaged_callers_only(const std::wstring& assembly_path, const std::string& type_name, const std::string& method_name) const;

private:
    mutable std::mutex mutex_;
    hostfxr_handle cxt_;
    load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer_;
    hostfxr_initialize_for_runtime_config_fn init_f_ptr_;
    hostfxr_get_runtime_delegate_fn get_delegate_f_ptr_;
    hostfxr_close_fn close_f_ptr_;
};

inline std::unique_ptr<dotnet> g_dotnet;
inline std::atomic<bool> g_dotnet_initialized;
inline std::thread g_init_thread;
inline std::mutex g_init_mutex;

inline void start_dotnet()
{
    Sleep(200);

    const auto asa_dll_path = get_asa_dll_path();
    const auto asa_runtime_config_path = get_asa_runtime_config_path();

    if (!fs::exists(asa_dll_path))
        throw std::runtime_error("ASA DLL not found: " + asa_dll_path.string());

    if (!fs::exists(asa_runtime_config_path))
        throw std::runtime_error("ASA runtime config not found: " + asa_runtime_config_path.string());

    {
        std::lock_guard lock(g_init_mutex);
        g_dotnet = std::make_unique<dotnet>(asa_runtime_config_path);
    }

    g_dotnet->call_function_with_unmanaged_callers_only(asa_dll_path.wstring(), "AsaApi.Program, AsaApi", "Main");
    g_dotnet_initialized = true;
}

inline void initialize_dotnet()
{
    if (auto expected = false; g_dotnet_initialized.compare_exchange_strong(expected, true))
    {
        g_init_thread = std::thread(start_dotnet);
        g_init_thread.detach();
    }
}

inline void free_dotnet()
{
    std::lock_guard lock(g_init_mutex);

    if (g_dotnet)
        g_dotnet.reset();
}
