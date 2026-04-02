#include <wlr/types/wlr_output_layout.h>
#include "input.h"
#include "server.h"
#include "window.h"
#include <stdio.h>


struct kinetic_server server; // <--- 关键！这行绝对不能删，这是实体的“根”


void server_new_output(struct wl_listener *listener, void *data) {
    struct wlr_output *output = data;

    // --- 强制固定分辨率 1920x1200 ---
    wlr_output_set_custom_mode(output, 1920, 1200, 60000); 
    
    wlr_output_init_render(output, server.allocator, server.renderer);
    
    // 将这个显示器放入我们的 1920x1200 布局中
    wlr_output_layout_add_auto(server.output_layout, output);

    // 渲染回调（保持你之前的 Braun 灰清屏逻辑）
    // ...
    wlr_output_commit(output);
}

int main() {
   server.wl_display = wl_display_create();
    server.backend = wlr_backend_autocreate(server.wl_display, NULL);
    server.renderer = wlr_renderer_autocreate(server.backend);
    server.allocator = wlr_allocator_autocreate(server.backend, server.renderer);

    // 2. 创建 1920x1200 布局
    server.output_layout = wlr_output_layout_create();

    // 3. 初始化场景图 (Scene Graph) - 只写一次！
    server.scene = wlr_scene_create();
    wlr_scene_attach_output_layout(server.scene, server.output_layout);

    // 4. 调用你的窗口模块 (这一行就替代了之前所有的 shell 初始化代码)
    kinetic_window_init(&server);

    // 5. 初始化输入
    kinetic_input_init(&server);

    // 6. 设置显示器监听
    server.new_output.notify = server_new_output;
    wl_signal_add(&server.backend->events.new_output, &server.new_output);

    // 7. 启动并运行
    const char *socket = wl_display_add_socket_auto(server.wl_display);
    wlr_backend_start(server.backend);
    printf("Kinetic Compositor 运行中！Socket: %s\n", socket);
    wl_display_run(server.wl_display);

    return 0;
}