add_library(renderer_warnings INTERFACE)
add_library(Renderer::warnings ALIAS renderer_warnings)

target_compile_options(renderer_warnings INTERFACE
        $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wno-missing-field-initializers>
        $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4;/permissive->
        $<$<COMPILE_LANG_AND_ID:C,GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>
        $<$<COMPILE_LANG_AND_ID:C,MSVC>:/W4>
)