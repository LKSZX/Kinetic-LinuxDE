#include <stdlib.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/types/wlr_scene.h>
#include "window.h"
#include "server.h"

static int next_window_offset = 50;

void server_new_xdg_toplevel(struct wl_listener *listener, void *data) {
    struct kinetic_server *server = wl_container_of(listener, server, new_xdg_toplevel);
    // 注意：在 new_surface 信号中，data 其实是 struct wlr_xdg_surface*
    struct wlr_xdg_surface *xdg_surface = data;

    // 只有当它是顶级窗口（Toplevel）时我们才处理
    if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
        return;
    }

    struct wlr_scene_tree *scene_tree = 
        wlr_scene_xdg_surface_create(&server->scene->tree, xdg_surface);
    
    wlr_scene_node_set_position(&scene_tree->node, 100, 100);

    // 1. 使用动态坐标设置窗口位置
    wlr_scene_node_set_position(&scene_tree->node, next_window_offset, next_window_offset);
    
    // 2. 每次弹出一个新窗口，偏移量增加 30 像素
    next_window_offset += 30;
    
    // 3. 如果偏移得太远了，就重置回左上角
    if (next_window_offset > 300) {
        next_window_offset = 50;
    }

    xdg_surface->data = scene_tree;
}

void kinetic_window_init(struct kinetic_server *server) {
    server->xdg_shell = wlr_xdg_shell_create(server->wl_display, 3);
    server->new_xdg_toplevel.notify = server_new_xdg_toplevel;
    // 关键：这里使用 new_surface 信号
    wl_signal_add(&server->xdg_shell->events.new_surface, &server->new_xdg_toplevel);
}