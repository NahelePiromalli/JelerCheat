#include <windows.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <random>
#include <chrono>
#include <thread>
#include <TlHelp32.h>

namespace fs = std::filesystem;

// Função para delay aleatório entre min e max ms
void randomSleep(int minMs = 100, int maxMs = 300) {
    static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(minMs, maxMs);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));
}

// Anti-debug simples
bool isBeingDebugged() {
    return IsDebuggerPresent() || CheckRemoteDebuggerPresent(GetCurrentProcess(), nullptr);
}

// Anti-sandbox simples (verifica tempo de boot)
bool isSandboxed() {
    DWORD tickCount = GetTickCount();
    return (tickCount < 10000); // menos de 10s de boot é estranho
}

// Estrutura para armazenar timestamps e caminho do arquivo
struct FileTimestamps {
    FILETIME creationTime;
    FILETIME lastAccessTime;
    FILETIME lastWriteTime;
    fs::path filePath;
};

std::vector<FileTimestamps> backupTimestampsPrefetch(const std::wstring& prefetchPath) {
    std::vector<FileTimestamps> backup;
    for (const auto& entry : fs::directory_iterator(prefetchPath)) {
        if (entry.is_regular_file() && entry.path().extension() == L".pf") {
            std::wstring filename = entry.path().filename().wstring();
            if (filename.find(L"SETTINGS") == 0) continue;  // Ignora SETTINGS*.pf

            HANDLE hFile = CreateFileW(entry.path().c_str(), GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                nullptr, OPEN_EXISTING, 0, nullptr);
            if (hFile == INVALID_HANDLE_VALUE) continue;

            FILETIME cTime, aTime, wTime;
            if (GetFileTime(hFile, &cTime, &aTime, &wTime)) {
                backup.push_back({ cTime, aTime, wTime, entry.path() });
            }
            CloseHandle(hFile);
        }
    }
    return backup;
}

void restaurarTimestampsEForcarEvento(const std::vector<FileTimestamps>& backup) {
    for (const auto& ft : backup) {
        std::wstring filename = ft.filePath.filename().wstring();
        if (filename.find(L"SETTINGS") == 0) continue;  // Ignora SETTINGS*.pf

        HANDLE hFile = CreateFileW(ft.filePath.c_str(),
            FILE_WRITE_ATTRIBUTES | GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr, OPEN_EXISTING, 0, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) continue;

        SetFileTime(hFile, &ft.creationTime, &ft.lastAccessTime, &ft.lastWriteTime);
        char buffer[1]; DWORD bytesRead;
        ReadFile(hFile, buffer, 1, &bytesRead, nullptr);
        CloseHandle(hFile);
    }
}

DWORD crc32(const std::wstring& filename) {
    DWORD crc = 0xFFFFFFFF;
    for (wchar_t c : filename) {
        crc ^= (BYTE)c;
        for (int i = 0; i < 8; ++i)
            crc = (crc >> 1) ^ (0xEDB88320 & -static_cast<int>(crc & 1));
    }
    return ~crc;
}

void spoofPrefetch() {
    std::wstring prefetchPath = L"C:\\Windows\\Prefetch";
    std::vector<fs::path> pfLegitimos;
    fs::path pfSettings;

    for (const auto& entry : fs::directory_iterator(prefetchPath)) {
        if (entry.path().extension() == L".pf") {
            std::wstring name = entry.path().filename().wstring();
            if (name.find(L"SETTINGS") == 0) pfSettings = entry.path();
            else if (name.find(L"DISCORD") == 0 || name.find(L"OBS") == 0 || name.find(L"STEAM") == 0)
                pfLegitimos.push_back(entry.path());
        }
    }

    if (!pfSettings.empty() && !pfLegitimos.empty()) {
        std::ifstream src(pfLegitimos[0], std::ios::binary);
        std::ofstream dst(pfSettings, std::ios::binary);
        dst << src.rdbuf();
        src.close(); dst.close();

        std::wstring newName = pfSettings.stem().wstring();
        size_t pos = newName.find(L"SETTINGS");
        if (pos != std::wstring::npos) {
            newName = L"OBS" + newName.substr(8);
            DWORD hash = crc32(newName);
            std::wstringstream ss;
            ss << L"OBS-" << std::hex << std::uppercase << hash << L".pf";
            fs::rename(pfSettings, prefetchPath + L"\\" + ss.str());
        }
    }
}

void clearUSNJournal() {
    HANDLE hVolume = CreateFileW(L"\\\\.\\C:", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
    if (hVolume == INVALID_HANDLE_VALUE) return;

    DWORD br;
    CREATE_USN_JOURNAL_DATA cujd = { 0 };
    USN_JOURNAL_DATA usd;

    if (DeviceIoControl(hVolume, FSCTL_QUERY_USN_JOURNAL, nullptr, 0, &usd, sizeof(usd), &br, nullptr)) {
        DELETE_USN_JOURNAL_DATA dujd;
        dujd.UsnJournalID = usd.UsnJournalID;
        dujd.DeleteFlags = USN_DELETE_FLAG_DELETE;

        DeviceIoControl(hVolume, FSCTL_DELETE_USN_JOURNAL, &dujd, sizeof(dujd), nullptr, 0, &br, nullptr);
        DeviceIoControl(hVolume, FSCTL_CREATE_USN_JOURNAL, &cujd, sizeof(cujd), nullptr, 0, &br, nullptr);
    }
    CloseHandle(hVolume);
}

void Prefetch_Cleaner() {
    std::wstring prefetchPath = L"C:\\Windows\\Prefetch";
    auto backups = backupTimestampsPrefetch(prefetchPath);
    clearUSNJournal();
    spoofPrefetch();
    restaurarTimestampsEForcarEvento(backups);
}

void deleteSpecificPrefetchFiles() {
    Prefetch_Cleaner();
}

int main() {
    if (isBeingDebugged() || isSandboxed()) return 1;
    deleteSpecificPrefetchFiles();
    return 0;
}
