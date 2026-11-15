#include "tab_bar.hpp"

namespace ui {
    TabBar::TabBar() = default;

    TabBar::~TabBar() = default;

    void TabBar::render() {
        ImGui::Begin("主窗口", nullptr, ImGuiWindowFlags_NoInputs);
        if (ImGui::BeginTabBar("菜单栏")) {
            if (ImGui::BeginTabItem("文件")) {

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }
}
