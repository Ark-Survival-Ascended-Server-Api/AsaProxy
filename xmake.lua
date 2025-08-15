includes("thirdparty")

set_xmakever("3.0.1")
set_project("AsaProxy")
set_version("1.0.0")

set_languages("cxx20")
set_exceptions("cxx")
set_warnings("all")

set_allowedplats("windows")
set_allowedmodes("debug", "release")
set_allowedarchs("x64")

add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

add_requires("dotnet-runtime", "spdlog")

target("AsaProxy", function()
    set_kind("shared")
    set_filename("version.dll")

    add_includedirs("include")
    add_headerfiles("include/**.hpp")

    add_files("src/**.cpp")
    add_files("src/**.def")
    add_files("src/**.asm")

    add_rules("asm")
    set_values("asm.ml", "ml64.exe")

    add_packages("dotnet-runtime", "spdlog")

    add_defines("UNICODE", "_UNICODE")

    if is_mode("debug") then
        set_symbols("debug")
        set_optimize("none")
        set_runtimes("MDd")
        add_defines("DEBUG")
    else
        set_symbols("hidden")
        set_optimize("fastest")
        set_runtimes("MD")
        add_defines("NDEBUG")
    end
end)