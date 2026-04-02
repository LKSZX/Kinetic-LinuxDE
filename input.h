#ifndef KINETIC_INPUT_H
#define KINETIC_INPUT_H

#include <wayland-server-core.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include <wlr/types/wlr_scene.h> // 需要包含 scene 以认识 wlr_scene_tree

// 1. 定义状态
enum kinetic_cursor_mode {
    KINETIC_CURSOR_PASSTHROUGH, // 正常滑动模式
    KINETIC_CURSOR_MOVE,        // 拖拽窗口模式
};

struct kinetic_server; // 声明

struct kinetic_input {
    struct wlr_cursor *cursor;
    struct wlr_xcursor_manager *cursor_mgr;
    struct wl_listener cursor_motion;
    struct wl_listener cursor_motion_absolute;
    struct wl_listener new_input;
    
    struct wl_listener cursor_button; // <-- 新增：监听鼠标按键

    // 2. 拖拽状态数据
    enum kinetic_cursor_mode cursor_mode;
    struct wlr_scene_tree *grabbed_tree; // 当前被抓取的窗口树
    double grab_x, grab_y;               // 抓取点相对窗口左上角的偏移量
};

void kinetic_input_init(struct kinetic_server *server);

#endif