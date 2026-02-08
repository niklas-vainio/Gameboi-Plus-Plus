/**
 * Simple wrapper class to allow loading ROM files (read-only) from disk.
 *
 * Future implementations on different platforms (e.g. embedded systems) can
 * change this implementation for different loading behavior.
 *
 * @author Niklas Vainio
 * @date 2026-02-07
 */

#include "RomFile.hpp"

#include "common/abort.hpp"
#include <fstream>

namespace Gbpp::Backend
{

bool RomFile::load(const std::string &rom_path)
{
    /*
     * Open the file.
     */
    std::ifstream f(rom_path, std::ios::binary);
    AbortIfNot(f, false, "Failed loading rom file %s", rom_path.c_str());

    /*
     * Get file size.
     */
    f.seekg(0, std::ios::end);
    const auto end = f.tellg();
    AbortIf(end < 0, false, "tellg failed on rom file %s", rom_path.c_str());

    const auto size = static_cast<std::size_t>(end);

    /*
     * Allocate space in the vector.
     */
    data.resize(size);

    /*
     * Load data into a vector and return it.
     */
    if (size > 0)
    {
        f.seekg(0, std::ios::beg);
        AbortIfNot(f.read(reinterpret_cast<char *>(data.data()),
                          static_cast<std::streamsize>(data.size())),
                   false,
                   "Failed reading rom file %s",
                   rom_path.c_str());
    }

    loaded = true;
    return true;
}

} // namespace Gbpp::Backend
