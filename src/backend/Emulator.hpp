
#include <string>

namespace Gbpp::Backend
{

class Emulator
{

public:
    void set_controller_inputs();

    void load_cartridge(const std::string &file_name);

    void emulate_instruction();
    void emulate_frame();

    const int *get_framebuffer() const;
    const int *pop_audio_samples();
    auto get_debug_info() const;
};

} // namespace Gbpp::Backend