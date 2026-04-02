#ifndef KINETIC_SERVER_H
#define KINETIC_SERVER_H


#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/render/allocator.h>
#include <wlr/types/wlr_output_layout.h>
#include "input.h" // 确保能看到 input 结构
#include <wlr/types/wlr_scene.h> // 必须包含这个头文件
#include <wlr/types/wlr_xdg_shell.h>



struct kinetic_server {
    struct wl_display *wl_display;
    struct wlr_backend *backend;
    struct wlr_renderer *renderer;
    struct wlr_allocator *allocator;
    struct wlr_output_layout *output_layout;
    
    struct kinetic_input input; 
    struct wl_listener new_output;
    struct wlr_xdg_shell *xdg_shell;
    struct wl_list toplevels; // 用于追踪所有打开的窗口
    struct wl_listener new_xdg_toplevel;
    struct wlr_scene *scene;
};



#endif
