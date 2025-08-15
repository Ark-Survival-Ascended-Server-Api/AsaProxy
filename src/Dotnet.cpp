#include "Dotnet.hpp"

#include <Windows.h>
#include <nethost.h>

dotnet::dotnet(const fs::path& dotnet_runtime_config_path)
{
    std::lock_guard lock(mutex_);

    wchar_t buffer[MAX_PATH];
    size_t buffer_size = sizeof(buffer) / sizeof(wchar_t);

    if (const auto rc = get_hostfxr_path(buffer, &buffer_size, nullptr); rc != 0)
        throw std::runtime_error("Failed to get hostfxr path");

    const auto lib = LoadLibraryW(buffer);

    if (!lib)
        throw std::runtime_error("Failed to load hostfxr");

    init_f_ptr_ = (hostfxr_initialize_for_runtime_config_fn)GetProcAddress(lib, "hostfxr_initialize_for_runtime_config");
    get_delegate_f_ptr_ = (hostfxr_get_runtime_delegate_fn)GetProcAddress(lib, "hostfxr_get_runtime_delegate");
    close_f_ptr_ = (hostfxr_close_fn)GetProcAddress(lib, "hostfxr_close");

    if (!init_f_ptr_ || !get_delegate_f_ptr_ || !close_f_ptr_)
        throw std::runtime_error("Failed to get hostfxr functions");

    if (const auto rc = init_f_ptr_(dotnet_runtime_config_path.wstring().c_str(), nullptr, &cxt_); rc != 0 || cxt_ == nullptr)
        throw std::runtime_error("Failed to initialize hostfxr");

    if (const auto rc = get_delegate_f_ptr_(cxt_, hdt_load_assembly_and_get_function_pointer, (void**)&load_assembly_and_get_function_pointer_); rc != 0 || load_assembly_and_get_function_pointer_ == nullptr)
        throw std::runtime_error("Failed to get runtime delegate");
}

dotnet::~dotnet()
{
    std::lock_guard lock(mutex_);

    if (cxt_ && close_f_ptr_)
    {
        close_f_ptr_(cxt_);
        cxt_ = nullptr;
    }
}

[[noreturn]]
void dotnet::call_function_with_unmanaged_callers_only(const std::wstring& assembly_path, const std::string& type_name, const std::string& method_name) const
{
    std::lock_guard lock(mutex_);

    const auto assembly_path_str = std::wstring(assembly_path.begin(), assembly_path.end());
    const auto type_name_str = std::wstring(type_name.begin(), type_name.end());
    const auto method_name_str = std::wstring(method_name.begin(), method_name.end());

    const main_fn fn = nullptr;

    const auto rc = load_assembly_and_get_function_pointer_(
                assembly_path_str.c_str(),
                type_name_str.c_str(),
                method_name_str.c_str(),
                UNMANAGEDCALLERSONLY_METHOD,
                nullptr,
                reinterpret_cast<void**>(fn));

    if (rc != 0 || *fn == nullptr)
        throw std::runtime_error("Failed to load assembly or get function pointer");

    fn();
}
