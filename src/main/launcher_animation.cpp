#include "banjo_launcher.h"

struct LauncherContext {
    recompui::Element *background_svg = nullptr;
} launcher_context;

void banjo::launcher_animation_setup(recompui::LauncherMenu *menu) {
    menu->set_launcher_background_svg("SuperSmashBrosn64BoxArt.svg");
    
    for (auto option : menu->get_game_options_menu()->get_options()) {
        option->set_font_family("Suplexmentary Comic NC");
        option->set_enabled(true);
        option->set_padding(24.0f);
        option->set_color({0x00, 0x92, 0x45, 0xFF});
        option->hover_style.set_color({0xE6, 0x00, 0x12, 0xFF});
        option->focus_style.set_color({0xE6, 0x00, 0x12, 0xFF});
        option->apply_styles();
        
        auto label = option->get_label();
        label->set_font_size(56.0f);
        label->set_letter_spacing(4.0f);
    }
}

void banjo::launcher_animation_update(recompui::LauncherMenu *menu) {
}