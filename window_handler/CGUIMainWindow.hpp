/**
 * @file       <CGUIMainWindow.hpp>
 * @brief      This header file implements CGUIMainWindow class. 
 *             
 *             It is being used in order to create main window, that would 
 *             be populated with ui elements specific for this project.
 *
 * @author     THE_CHOODICK
 * @date       20-07-2022
 * @version    0.0.1
 * 
 * @warning    This library is under development, so it might work unstable.  
 * @bug        Currently, there are no any known bugs. 
 * 
 *             In order to submit new ones, please contact me via bug-report@choodick.com.
 * 
 * @copyright  Copyright 2022 Alexander. All rights reserved. 
 * 
 *             (Not really)
 * 
 * @license    This project is released under the GNUv3 Public License.
 * 
 * @todo       Implement the whole class.
 */
#ifndef CGUIMAINWINOW_HPP
#define CGUIMAINWINOW_HPP

/**
 * Include some important headers.
 */
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "debug_handler/CGUIDebugHandler.hpp"
#include "shader_compiler/CGUIShaderCompiler.hpp"
#include "vertex_specification/vbo_handler/CGUIVBOHandler.hpp"
#include "vertex_specification/vao_handler/CGUIVAOHandler.hpp"
#include "vertex_specification/ebo_handler/CGUIEBOHandler.hpp"

#include <sys/stat.h>
#include <chrono>
#include <thread>
#include <mutex>

#include <condition_variable>

/**
 * Some usefull defines for shader compiler.
 */
#define CGUI_SHADER_TRIANDLE "CGUI_SHADER_TRIANDLE"

/**
 * Some usefull defines for window press type.
 */
#define CGUI_PRESS_TYPE_WINDOW_MOVE                 0
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_LEFT      1
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP           2
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_RIGHT     3
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_RIGHT         4
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_RIGHT  5
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM        6
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_LEFT   7
#define CGUI_PRESS_TYPE_WINDOW_RESIZE_LEFT          8
#define CGUI_PRESS_TYPE_WINDOW_FULLSCREEN           253
#define CGUI_PRESS_TYPE_WINDOW_OUTSIDE              254
#define CGUI_PRESS_TYPE_WINDOW_NONE                 255

/**
 * @brief      This class represents creation and handling of main window. 
 *             Class is based on GLFW and glad libraries, and uses them in oreder to create/handle/render window.
 */
class CGUIMainWindow
{
public:
    CGUIMainWindow();
    CGUIMainWindow(const CGUIMainWindow&) = delete;
    ~CGUIMainWindow();

    void show();
    void hide();
    void close();

private:
    bool initialize(std::string main_window_name_arg = "CGUI Default Window", bool vertical_sync_arg = false, bool full_screen_arg = false);
    bool initialize_renderer();
    
    void update_thread();
    void render_frames();
    void update_events();
    void frame_renderer_wrapper();
    void set_fullscreen_mode();
    void set_windowed_mode();
    void switch_window_mode();

    uint8_t assert_window_press_type(glm::dvec2 press_position);

    GLFWmonitor* get_monitor_by_cpos(glm::dvec2 cursor_position);
    GLFWmonitor* get_current_monitor(GLFWwindow *window);

    bool collision(glm::ivec2 rect_tl, glm::ivec2 rect_br, glm::ivec2 point);

    glm::dvec2 get_global_mouse_position(GLFWwindow* window);

    void resize_window_rect(GLFWwindow* window, glm::ivec2 pos, glm::ivec2 size);

    //#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
    //    void windows_api_resize(GLFWwindow* window, int border);
    //#endif

private:
    static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    static void character_callback(GLFWwindow* window, unsigned int character);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void window_size_callback(GLFWwindow* window, int width, int height);

private:
    CGUIDebugHandler debug_handler;

    GLFWwindow*     main_window;
    GLFWmonitor*    current_monitor;
    GLFWcursor*     current_cursor;

    CGUIShaderCompiler* shaders;

private:
    std::string main_window_name;

    bool full_screen;
    bool vertical_sync;

    bool character_mode     = false;
    bool mouse_lb_pressed   = false;
    bool is_resized         = true;

    std::chrono::time_point<std::chrono::steady_clock> program_start_time;
    std::chrono::time_point<std::chrono::steady_clock> last_lb_press_time;

    size_t last_frame_render_time           = 0;
    size_t last_frame_event_time            = 0;
    size_t last_frames_rendered_per_second  = 0;

    size_t  window_drag_offset  = 10;
    uint8_t window_press_type   = 0;

    glm::dvec2 last_mouse_press_position;

    glm::ivec2 last_window_size     = {512, 256};
    glm::ivec2 window_size_min      = {480, 240};
    glm::ivec2 last_window_position = {0, 0};

    fs::path triangle_vertext_file_path     = "cgui_tri_vert.vs";
    fs::path triangle_fragment_file_path    = "cgui_tri_frag.fs";
    fs::path triangle_geometry_file_path    = "";                    // cgui_tri_geom.gs

    std::thread* render_thread;

    std::mutex              thread_mutex;
    std::condition_variable thread_con_v;
};

#endif // CGUIMAINWINOW_HPP