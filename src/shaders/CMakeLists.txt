find_program(SLANGC_EXECUTABLE NAMES slangc slangc.exe)
if (NOT SLANGC_EXECUTABLE)
    message(FATAL_ERROR "未找到slangc")
endif ()

file(GLOB SHADER_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.slang")

set(SPV_OUTPUTS)
foreach(SHADER ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)
    set(SPV "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.spv")

    add_custom_command(
            OUTPUT  ${SPV}
            COMMAND ${SLANGC_EXECUTABLE} "${SHADER}"
            -target spirv
            -o "${SPV}"
            DEPENDS "${SHADER}"
            COMMENT "Compiling ${SHADER_NAME}.slang -> ${SHADER_NAME}.spv"
            VERBATIM
    )
    list(APPEND SPV_OUTPUTS ${SPV})
endforeach()

add_custom_target(shaders ALL DEPENDS ${SPV_OUTPUTS})