/**
 * @file       <CGUIMainWindow.hpp>
 * @brief      This header file implements CGUIMainWindow class. 
 *             
 *             It is being used in order to create main window, that would 
 *             be populated with ui elements specific for this project.
 *
 * @author     THE_CHOODICK
 * @date       23-02-2022
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
#include "cgui_datatypes/CGUIDataTypes.hpp"
#include "shader_compiler/CGUIShaderCompiler.hpp"
#include "vertex_specification/vbo_handler/CGUIVBOHandler.hpp"
#include "vertex_specification/vao_handler/CGUIVAOHandler.hpp"
#include "vertex_specification/ebo_handler/CGUIEBOHandler.hpp"

#include <sys/stat.h>
#include <thread>
#include <mutex>

/**
 * Some usefull defines for shader compiler.
 */
#define CGUI_SHADER_TRIANDLE "CGUI_SHADER_TRIANDLE"

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


    GLFWmonitor* get_monitor_by_cpos(CGUIPointd cursor_position);

    CGUIPointd get_global_mouse_position(GLFWwindow* window);

private:
    static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    static void character_callback(GLFWwindow* window, unsigned int character);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

private:
    CGUIDebugHandler debug_handler;

    GLFWwindow*     main_window;
    GLFWmonitor*    current_monitor;

private:
    std::string main_window_name;

    bool full_screen;
    bool vertical_sync;

    bool character_mode     = false;
    bool mouse_lb_pressed   = false;

    CGUIPointd last_mouse_press_position;

    CGUIShaderCompiler* shaders;

    fs::path triangle_vertext_file_path     = "./cgui_tri_vert.vs";
    fs::path triangle_fragment_file_path    = "./cgui_tri_frag.fs";
    fs::path triangle_geometry_file_path    = "";                   // ./cgui_tri_geom.gs

    std::thread* render_thread;

    std::recursive_mutex thread_mutex;
};

#endif // CGUIMAINWINOW_HPP