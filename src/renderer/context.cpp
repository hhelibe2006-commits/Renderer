#include "context.hpp"

namespace renderer {
    Context::Context() {
        m_context = std::make_unique<vk::raii::Context>();
    }

    Context::~Context() = default;

    const vk::raii::Context &Context::get() const {
        return *m_context;
    }
}
