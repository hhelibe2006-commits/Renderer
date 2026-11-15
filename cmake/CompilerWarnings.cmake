add_library(renderer_warnings INTERFACE)
add_library(Renderer::warnings ALIAS renderer_warnings)

target_compile_options(renderer_warnings INTERFACE
        "$<$<COMPILE_LANGUAGE:CXX>:
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wno-missing-field-initializers>"
        "$<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->>"
        "$<$<COMPILE_LANGUAGE:C>:
        $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>"
        "$<$<C_COMPILER_ID:MSVC>:/W4>>"
)