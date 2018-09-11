#include "scratchpad.h"

#include "../../common/accessibility/display.h"
#include "../../common/accessibility/application.h"
#include "../../common/accessibility/window.h"

#include <vector>

std::vector<scratchpad_window> scratchpad;

static char *
copy_string(char *str)
{
    int length = strlen(str);
    char *result = (char *)malloc(length + 1);
    memcpy(result, str, length);
    result[length] = 0;
    return result;
}

static bool
scratchpad_match_process()
{
    return true;
}

static bool
scratchpad_match_name()
{
    return true;
}

void scratchpad_add_window(macos_window *window)
{
    scratchpad_window sp_window;
    sp_window.is_visible = false;
    sp_window.window_id = window->Id;
    sp_window.process = copy_string(window->Owner->Name);
    sp_window.name = copy_string(window->Name);
}

static struct scratchpad_window *
scratchpad_find_window()
{
    for (int i = 0; i < scratchpad.size(); ++i) {
        scratchpad_window *sp_window = &scratchpad[i];
        if ((scratchpad_match_process(sp_window->process, process)) &&
            (scratchpad_match_name(sp_window->name, name))) {
            return sp_window;
        }
    }
}

void scratchpad_show_window(scratchpad_window *sp_window)
{
    if (sp_window->is_visible) return;

    macos_space *space = ActiveSpace();
    AXLibSpaceMoveWindow(space->Id, sp_window->id);
    sp_window->is_visible = true;
    // normalize window dimension to resolution of the current space
    // CGRect new_frame = AXLibGetDisplayBounds(space);
    // normalize_window_dimensions(sp_window->id, sp_window->origin_frame, new_frame);
    // sp_window->origin_frame = new_frame;
}

void scratchpad_hide_window(scratchpad_window *sp_window)
{
    if (!sp_window->is_visible) return;

    AXLibSpaceMoveWindow(0, sp_window->id);
    sp_window->is_visible = false;
}
