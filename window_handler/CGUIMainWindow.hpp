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
 * @copyright  Copyright 2022 Alexande. All rights reserved. 
 * 
 *             (Not really)
 * 
 * @license    This project is released under the GNUv3 Public License.
 * 
 * @todo       Implement the whole class.
 */
#ifndef CGUIMAINWINOW_HPP
#define CGUIMAINWINOW_HPP

/**<
 * Include GLFW and GLAD for window handling.
 */
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "debug_handler/CGUIDebugHandler.hpp"
#include "cgui_datatypes/CGUIDataTypes.hpp"
#include "shader_compiler/CGUIShaderCompiler.hpp"

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
    
    void update_frame();
    void render_frame();

    GLFWmonitor* get_monitor_by_cpos(CGUIPointd cursor_position);

    CGUIPointd get_global_mouse_position(GLFWwindow* window);

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void character_callback(GLFWwindow* window, unsigned int character);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    CGUIDebugHandler debug_handler;

    GLFWwindow*     main_window;
    GLFWmonitor*    current_monitor;

private:
    std::string main_window_name;

    bool full_screen;
    bool vertical_sync;

    bool character_mode = false;
    bool mouse_lb_pressed = false;

    CGUIPointd last_mouse_press_position;

    CGUIShaderCompiler shaders;
};

#endif // CGUIMAINWINOW_HPP