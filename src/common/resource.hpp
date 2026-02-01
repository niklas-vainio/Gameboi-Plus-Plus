/**
 * Utility functions for loading file resources. All file operations should use
 * these functions so that paths are defined in one place.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include <filesystem>
#include <string>

namespace Gbpp::Utils
{

namespace fs = std::filesystem;

/**
 * Absolute path to the project root.
 */
inline const fs::path project_root_path = fs::absolute(".").lexically_normal();

/**
 * Path to the resources directory.
 */
inline const fs::path resources_dir_path =
    project_root_path / fs::path("resources");

/**
 * Get the absolute path of a resource with the given filename.
 *
 * @param[in] filename  Filename of the resource to lookup
 * @return The path to the file.
 */
fs::path get_resource_path(const std::string &filename)
{
    return resources_dir_path / fs::path(filename);
}

} // namespace Gbpp::Utils