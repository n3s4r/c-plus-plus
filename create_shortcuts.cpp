Shell32.lib Ole32.lib

#include <windows.h> #include <shlobj.h> #include <shobjidl.h> #include
<objbase.h> #include #include #include

namespace fs = std::filesystem;

std::wstring GetDesktopPath() { PWSTR path = nullptr; if
(SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, KF_FLAG_DEFAULT, NULL,
&path))) { std::wstring desk(path); CoTaskMemFree(path); return desk; }
return L”“; }

bool CreateShortcut(const std::wstring& targetPath, const std::wstring&
shortcutPath, const std::wstring& description = L”“) { bool result =
false; IShellLinkW* pShellLink = nullptr; IPersistFile* pPersistFile =
nullptr;

    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pShellLink)))) {
        if (SUCCEEDED(pShellLink->SetPath(targetPath.c_str()))) {
            pShellLink->SetDescription(description.c_str());
            if (SUCCEEDED(pShellLink->QueryInterface(IID_PPV_ARGS(&pPersistFile)))) {
                if (SUCCEEDED(pPersistFile->Save(shortcutPath.c_str(), TRUE))) {
                    result = true;
                }
                pPersistFile->Release();
            }
        }
        pShellLink->Release();
    }
    return result;

}

int wmain(int argc, wchar_t* argv[]) { std::wcout << L”Create shortcuts
program“; if (argc < 2) { std::wcout << L”Usage: create_shortcuts
[–recursive]“; return 1; }

    std::wstring folder = argv[1];
    bool recursive = false;
    if (argc >= 3 && std::wstring(argv[2]) == L"--recursive") recursive = true;

    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::wcerr << L"Error: folder not found or not a directory: " << folder << L"\n";
        return 1;
    }

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        std::wcerr << L"COM init failed.\n";
        return 1;
    }

    std::wstring desktop = GetDesktopPath();
    if (desktop.empty()) {
        std::wcerr << L"Could not determine Desktop path.\n";
        CoUninitialize();
        return 1;
    }

    std::wcout << L"Desktop: " << desktop << L"\n";
    size_t created = 0;

    auto processEntry = [&](const fs::directory_entry& de) {
        if (!de.is_regular_file()) return;
        std::wstring target = de.path().wstring();

        std::wstring name = de.path().stem().wstring();
        std::wstring shortcut = desktop + L"\\" + name + L".lnk";

        int suffix = 1;
        std::wstring finalShortcut = shortcut;
        while (fs::exists(finalShortcut)) {
            finalShortcut = desktop + L"\\" + name + L" (" + std::to_wstring(suffix) + L").lnk";
            ++suffix;
        }

        std::wstring desc = L"Shortcut to " + de.path().filename().wstring();
        if (CreateShortcut(target, finalShortcut, desc)) {
            ++created;
            std::wcout << L"Created: " << finalShortcut << L"\n";
        } else {
            std::wcerr << L"Failed to create shortcut for: " << target << L"\n";
        }
    };

    if (recursive) {
        for (auto& de : fs::recursive_directory_iterator(folder)) {
            processEntry(de);
        }
    } else {
        for (auto& de : fs::directory_iterator(folder)) {
            processEntry(de);
        }
    }

    std::wcout << L"Shortcuts created: " << created << L"\n";

    CoUninitialize();
    return 0;

}
