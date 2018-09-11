#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

#include <Carbon/Carbon.h>

struct scratchpad_window
{
    bool is_visible;
    uint32_t window_id;
    char *process;
    char *name;
    CGRect origin_frame;
};

#endif
