/**
 * Simple wrapper class to allow loading ROM files (read-only) from disk.
 *
 * Future implementations on different platforms (e.g. embedded systems) can
 * change this implementation for different loading behavior.
 *
 * @author Niklas Vainio
 * @date 2026-02-07
 */

#pragma once

#include "common/logging.hpp"
#include <string>
#include <vector>

namespace Gbpp::Backend
{

class RomFile
{
public:
    RomFile() = default;

    /**
     * Disallow copy and move.
     */
    RomFile(const RomFile &) = delete;
    RomFile &operator=(const RomFile &) = delete;
    RomFile(RomFile &&) = delete;
    RomFile &operator=(RomFile &&) = delete;

    /**
     * Load data from the specified file path.
     *
     * @return True on success, false otherwise.
     */
    bool load(const std::string &rom_path);

    /**
     * Read-only accessor to the underlying data.
     */
    uint8_t operator[](std::size_t i) const
    {
        LogDebug("Reading from ROM at address %04X", i);
        return loaded ? data.at(i) : 0xff;
    }

    /**
     * Getter method for the size of the file. Will return zero if no file has
     * been loaded.
     */
    std::size_t size() const
    {
        return data.size();
    }

private:
    /**
     * Whether a file has been loaded. Reads will return 0xFF if no file has
     * been loaded.
     */
    bool loaded{};

    /**
     * Internal vector holding the file data. Data is populated when load is
     * called.
     */
    std::vector<uint8_t> data{};
};

} // namespace Gbpp::Backend