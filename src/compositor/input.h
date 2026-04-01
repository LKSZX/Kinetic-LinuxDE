#ifndef KINETIC_INPUT_H
#define KINETIC_INPUT_H

#include <wayland-server-core.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>


// 引用 main.c 里的 server 结构体声明
struct kinetic_server;

struct kinetic_input {
    struct wlr_cursor *cursor;
    struct wlr_xcursor_manager *cursor_mgr;
    struct wl_listener cursor_motion;
    struct wl_listener cursor_motion_absolute;
    struct wl_listener new_input; 
};

// 初始化函数：在 main.c 中调用
void kinetic_input_init(struct kinetic_server *server);

#endif