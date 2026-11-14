#include "context.hpp"

namespace renderer {
    Context::Context() {
        m_context = std::make_unique<vk::raii::Context>();
    }
}
