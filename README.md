<p align="center">
  <img src="AsaProxy.png" alt="AsaProxy"/>
</p>
<p align="center">
  <a href="https://github.com/Ark-Survival-Ascended-Server-Api/AsaProxy/actions">
    <img src="https://img.shields.io/github/actions/workflow/status/Ark-Survival-Ascended-Server-Api/AsaProxy/build.yml?branch=main&logo=github" alt="Build Status">
  </a>
  <a href="https://github.com/Ark-Survival-Ascended-Server-Api/AsaProxy/releases">
    <img src="https://img.shields.io/github/v/release/Ark-Survival-Ascended-Server-Api/AsaProxy" alt="Release">
  </a>
  <a href="https://github.com/Ark-Survival-Ascended-Server-Api/AsaProxy/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/Ark-Survival-Ascended-Server-Api/AsaProxy" alt="License">
  </a>
</p>

---

<p align="center">
  A transparent version.dll proxy enabling .NET plugin capabilities for Ark: Survival Ascended servers.
</p>

---

## Features

- 🎮 **Ark: Survival Ascended** - Specifically designed for ASA server modding
- 🔄 **Transparent Proxying** - Seamlessly forwards version.dll calls while enabling custom functionality
- 🧩 **Plugin System** - Load and execute .NET assemblies through AsaApi framework
- ⚡ **C++20 Modern** - Built with modern C++ standards and xmake build system
- 🔗 **.NET Interop** - Native C++ to .NET bridge via nethost.dll
- 🎯 **x64 Architecture** - Optimized for 64-bit Windows servers
- 🚀 **CI/CD Ready** - Automated builds and releases with GitHub Actions
- 🛡️ **Non-Intrusive** - Works alongside existing ASA server functionality

## Quick Start

### Download

Get the latest release from [GitHub Releases](https://github.com/Ark-Survival-Ascended-Server-Api/AsaProxy/releases).

### Installation

**Server Directory**
```
ArkAscendedServer.exe
├── version.dll
├── nethost.dll
└── AsaApi/
    ├── AsaApi.dll
    ├── AsaApi.runtimeconfig.json
    └── Plugins/
        └── YourPlugin/
            ├── YourPlugin.dll
            └── YourPlugin.deps.json
```

**Installation Steps:**
1. **Stop** your ASA server
2. **Extract** the release package to your server directory
3. **Copy** your AsaApi.dll and plugins to the `AsaApi/` folder
4. **Start** your server - AsaProxy will automatically load

## Building from Source

### Requirements

- **Windows 10/11** (x64)
- **Visual Studio 2022** with MSVC toolchain
- **xmake 3.0.1+** build system
- **.NET 9.0 SDK**

### Build Steps

```bash
# Clone repository
git clone https://github.com/Ark-Survival-Ascended-Server-Api/AsaProxy.git
cd AsaProxy

# Configure and build
xmake config --mode=release --arch=x64 --plat=windows
xmake build

# Install to package directory
xmake install --installdir=package
```

## How It Works

1. **DLL Interception** - ASA server loads AsaProxy version.dll instead of the system one
2. **Function Forwarding** - Standard version.dll functions are forwarded to the original Windows DLL
3. **AsaApi Loading** - .NET runtime loads AsaApi.dll from the AsaApi/ directory
4. **Plugin System** - AsaApi manages loading and execution of server plugins
5. **Seamless Integration** - Plugins can hook into ASA server functionality without modification

## Configuration

AsaProxy looks for the following files relative to the server executable:

- `AsaApi/AsaApi.dll` - Main AsaApi assembly
- `AsaApi/AsaApi.runtimeconfig.json` - .NET runtime configuration
- `AsaApi/Plugins/` - Directory containing server plugins

The proxy automatically initializes 200ms after server startup to ensure proper loading order.

## ⚠️ Important Notes

- **Server Compatibility** - Designed specifically for Ark: Survival Ascended servers
- **Architecture** - x64 only, matches ASA server requirements
- **Antivirus** - May trigger false positives due to DLL interception techniques
- **Backup** - Always backup your server before installing
- **Testing** - Test plugins thoroughly in development environments

## Troubleshooting

### Common Issues

- **DLL Not Loading**: Ensure .NET 9.0 runtime is installed
- **AsaApi Not Found**: Verify AsaApi.dll exists in the AsaApi/ directory
- **Plugin Crashes**: Check plugin dependencies and .NET version compatibility
- **Server Won't Start**: Verify all required DLLs are present and x64 architecture

## Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **[ArkServerApi/AsaApi](https://github.com/ArkServerApi/AsaApi)** - Inspiration and reference for ASA server modding techniques
- **Microsoft .NET Team** - For the excellent nethost.dll interop capabilities
- **xmake Team** - For providing a modern and efficient build system
- **ASA Modding Community** - For feedback, testing, and plugin development
- **All Contributors** - Thank you for your contributions and support

Special thanks to the AsaApi developers who pioneered server API techniques for Ark: Survival Ascended, enabling rich plugin ecosystems and server customization.

## Security

Please read our [Security Policy](SECURITY.md) for reporting vulnerabilities.

---

**⚠️ Disclaimer**: This tool uses DLL interception techniques for legitimate server plugin functionality. Designed specifically for Ark: Survival Ascended server administration. Use responsibly and only on servers you own or have explicit permission to modify.
