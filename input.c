#define _POSIX_C_SOURCE 200809L
#ifndef WLR_USE_UNSTABLE
#define WLR_USE_UNSTABLE
#endif

#include <wlr/types/wlr_pointer.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include "server.h"
#include "input.h"

extern struct kinetic_server server;

// 1. 光标移动逻辑 (注意结构体名字和调用的变化)
void server_cursor_motion(struct wl_listener *listener, void *data) {
    // 0.17 专属命名
    struct wlr_pointer_motion_event *event = data; 
    
    // 0.17 中，device 被移到了 event->pointer 里
    wlr_cursor_move(server.input.cursor, &event->pointer->base, 
                    event->delta_x, event->delta_y);
}

// 2. 新增：拦截新插入的输入设备
void server_new_input(struct wl_listener *listener, void *data) {
    struct wlr_input_device *device = data;
    // 如果发现插入的是鼠标，才把它挂载到光标上
    if (device->type == WLR_INPUT_DEVICE_POINTER) {
        wlr_cursor_attach_input_device(server.input.cursor, device);
    }
}

// 3. 初始化模块
void kinetic_input_init(struct kinetic_server *server) {
    server->input.cursor = wlr_cursor_create();
    
    server->input.cursor_mgr = wlr_xcursor_manager_create(NULL, 24);
    wlr_xcursor_manager_load(server->input.cursor_mgr, 1.0);

    // 绑定鼠标移动
    server->input.cursor_motion.notify = server_cursor_motion;
    wl_signal_add(&server->input.cursor->events.motion, &server->input.cursor_motion);

    // 核心改动：监听后端设备插入，替代被废弃的 attach_backend
    server->input.new_input.notify = server_new_input;
    wl_signal_add(&server->backend->events.new_input, &server->input.new_input);
}