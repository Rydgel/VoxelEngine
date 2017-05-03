project (Dear_ImGui)

set(IMGUI_SOURCES
        "imgui.cpp"
        "imgui_demo.cpp"
        "imgui_draw.cpp")

set(IMGUI_HEADERS
        "imconfig.h"
        "imgui.h"
        "imgui_internal.h"
        "stb_rect_pack.h"
        "stb_textedit.h"
        "stb_truetype.h")

add_library(ImGui ${IMGUI_SOURCES} ${IMGUI_HEADERS})