#include "memory.h"

#include <Windows.h>
#include <vector>
#include <stdexcept>

void m::Setup()
{
    //sigs.glowObjectManager = Scan("client", "0F 11 05 ? ? ? ? 83 C8 01") + 3;
    //sigs.allocKeyValuesEngine = RelativeToAbsolute(reinterpret_cast<std::uintptr_t>(Scan("engine", "E8 ? ? ? ? 83 C4 08 84 C0 75 10 FF 75 0C")) + 1) + 74;
}

uint8_t* m::Scan(const char* module, const char* pattern)
{
    const auto handle = ::GetModuleHandle(module);

    if (!handle)
        throw std::runtime_error("Failed to get " + std::string(module) + " module handle.");

    static auto patternToByte = [](const char* pattern)
    {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
            {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };


    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = patternToByte(pattern);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {

                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    throw std::runtime_error("Outdated pattern \"" + std::string(pattern) + "\"");
}