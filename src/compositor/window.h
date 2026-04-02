#ifndef KINETIC_WINDOW_H
#define KINETIC_WINDOW_H

#include "server.h"

// 在 main.c 中调用，初始化 xdg_shell 并绑定信号
void kinetic_window_init(struct kinetic_server *server);

// 处理新窗口创建的回调函数
void server_new_xdg_toplevel(struct wl_listener *listener, void *data);

#endif