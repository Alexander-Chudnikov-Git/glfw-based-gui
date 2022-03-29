/**
 * @file       <CGUIMainWindow.cpp>
 * @brief      This source file implements CGUIMainWindow class. 
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
#include "CGUIMainWindow.hpp"
#include "glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include "glm/glm/fwd.hpp"


/********************************************************************************
 *  							     Public block 								*
 ********************************************************************************/

/**
 * @brief      Constructs a new instance of CGUIMainWindow class.
 */
CGUIMainWindow::CGUIMainWindow()
{
	if (!initialize())
    {
        debug_handler.post_log("Unable to initialize CGUI.", DEBUG_MODE_ERROR);
        close();
    }

    debug_handler.post_log("CGUI has been initialized successfuly.", DEBUG_MODE_LOG);

    if (!initialize_renderer())
    {
        debug_handler.post_log("Unable to initialize renderer.", DEBUG_MODE_ERROR);
        close();
    }

    debug_handler.post_log("Renderer has been initialized successfuly.", DEBUG_MODE_LOG);

    update_thread();

    close();
}

/**
 * @brief      Destroys the CGUIMainWindow instance.
 */
CGUIMainWindow::~CGUIMainWindow()
{
    close();
}

/**
 * @brief      Shows window to user.
 */
void CGUIMainWindow::show()
{

}

/**
 * @brief      Hides window from user.
 */
void CGUIMainWindow::hide()
{

}

/**
 * @brief      Closes window instance.
 */
void CGUIMainWindow::close()
{
    debug_handler.post_log("Window has been closed.", DEBUG_MODE_LOG);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


/********************************************************************************
 *  							    Private block 								*
 ********************************************************************************/

/**
 * @brief      Initializes window with given parameters.
 *
 * @param[opt] vertical_sync Vertical synchronization toggle.
 * *
 * @return     Was initialization successfull or not.
 */
bool CGUIMainWindow::initialize(std::string main_window_name_arg, bool vertical_sync_arg, bool full_screen_arg)
{
    main_window_name = main_window_name_arg;
    vertical_sync = vertical_sync_arg;
    full_screen = full_screen_arg;

    debug_handler.post_log("CGUI Initialization has started.", DEBUG_MODE_LOG);

    // Add ini settings loader 
    debug_handler.post_log("Ini file has been loaded.", DEBUG_MODE_LOG);

    glfwSetErrorCallback(CGUIDebugHandler::glfw_error_callback);

    if (!glfwInit())
    {
        debug_handler.post_log("Unable to initialize GLWF.", DEBUG_MODE_ERROR);
        return false;
    }

    debug_handler.post_log("GLFW has been initialized.", DEBUG_MODE_LOG);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    #if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_TRUE);
        glfwWindowHintString(GLFW_COCOA_FRAME_NAME, "CGUI Autosaved Frame");
    #endif // __APPLE__

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    debug_handler.post_log("Window hints have been set.", DEBUG_MODE_LOG);

    // Create invisible window in order to get mouse position
    if (full_screen)
    {
        debug_handler.post_log("Full screen window is being created.", DEBUG_MODE_LOG);

        current_monitor = glfwGetPrimaryMonitor();
        main_window = glfwCreateWindow(100, 100, main_window_name.c_str(), current_monitor, NULL);

        debug_handler.post_log("Temporary window created.", DEBUG_MODE_LOG);
        
        current_monitor = get_monitor_by_cpos(get_global_mouse_position(main_window));

        debug_handler.post_log(std::string("Current monitor is: ") + glfwGetMonitorName(current_monitor), DEBUG_MODE_LOG);

        const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(current_monitor);
        CGUIPointi window_size = {512, 256};

        glfwSetWindowMonitor(main_window, current_monitor, (monitor_video_mode->width - window_size.x) / 2, (monitor_video_mode->height - window_size.y) / 2, window_size.x, window_size.y, monitor_video_mode->refreshRate);
    }
    else 
    {
        debug_handler.post_log("Normal window is being created.", DEBUG_MODE_LOG);
        main_window = glfwCreateWindow(512, 256, main_window_name.c_str(), NULL, NULL);
    }

    glfwShowWindow(main_window);

    glfwSetWindowShouldClose(main_window, GLFW_FALSE);

    debug_handler.post_log("Window has been created.", DEBUG_MODE_LOG);

    glfwSetWindowUserPointer(main_window, reinterpret_cast<void *>(this));

    glfwSetInputMode(main_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glfwSetKeyCallback(main_window, key_callback);
    glfwSetCharCallback(main_window, character_callback);
    glfwSetCursorPosCallback(main_window, cursor_position_callback);
    glfwSetCursorEnterCallback(main_window, cursor_enter_callback);
    glfwSetMouseButtonCallback(main_window, mouse_button_callback);
    glfwSetScrollCallback(main_window, scroll_callback);

    debug_handler.post_log("Callback have been initialized.", DEBUG_MODE_LOG);

    glfwMakeContextCurrent(main_window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        debug_handler.post_log("Unable to properly initialize GLAD.", DEBUG_MODE_ERROR);
        return false;
    }

    if (vertical_sync)
    { 
        glfwSwapInterval(1);
    }

    return true;
}

/**
 * @brief      Initializes the renderer.
 *
 * @return     Status of initialization.
 */
bool CGUIMainWindow::initialize_renderer()
{
    return true;
}

/**
 * @brief      Updates the frame.
 */
void CGUIMainWindow::update_thread()
{
    render_thread = new std::thread(&CGUIMainWindow::frame_renderer_wrapper, main_window);

    update_events();

    render_thread->detach();

    while (!glfwWindowShouldClose(main_window))
    {
        if (render_thread->joinable())
        {
            render_thread->join(); 
        }
    }
    return;
}

/**
 * @brief      Renders the frame.
 */
void CGUIMainWindow::render_frames()
{
    while(!glfwWindowShouldClose(main_window))
    {
        thread_mutex.lock();
        float framebuffer_ratio;
        CGUIPointi framebuffer_size;

        glfwGetFramebufferSize(main_window, &framebuffer_size.x, &framebuffer_size.y);
        framebuffer_ratio = framebuffer_size.x / (float) framebuffer_size.y;

        glViewport(0, 0, framebuffer_size.x, framebuffer_size.y);
        glClearColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(main_window);
        glfwPostEmptyEvent();
        thread_mutex.unlock();
    }
    return;
}

/**
 * @brief      Updates Pool Event function.
 */
void CGUIMainWindow::update_events()
{
    while(!glfwWindowShouldClose(main_window))
    {
        glfwWaitEvents();
    }
    return;
}

/**
 * @brief      Gets the selected monitor.
 *
 * @return     Focused window pointer.
 */
GLFWmonitor* CGUIMainWindow::get_monitor_by_cpos(CGUIPointd cursor_position)
{
    int monitor_count;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    for (int current_monitor = 0; current_monitor < monitor_count; ++current_monitor)
    {   
        CGUIPointi monitor_position;
        glfwGetMonitorPos(monitors[current_monitor], &monitor_position.x, &monitor_position.y);

        debug_handler.post_log(std::string("Monitor: ") + glfwGetMonitorName(monitors[current_monitor]) + std::string(" position: x-") + std::to_string(cursor_position.x) + std::string(" y-") + std::to_string(cursor_position.y), DEBUG_MODE_LOG);

        const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(monitors[current_monitor]);
        if (
            (cursor_position.x >= monitor_position.x) ||
            (cursor_position.x <= (monitor_position.x + monitor_video_mode->width)) ||
            (cursor_position.y >= monitor_position.y) ||
            (cursor_position.y <= (monitor_position.y + monitor_video_mode->height))
        ) 
        {
            return monitors[current_monitor];  
        }
    }
    return NULL;
}

/**
 * @brief      Gets the global mouse position.
 *
 * @param      window  Window pointer.
 *
 * @return     Global mouse position.
 */
CGUIPointd CGUIMainWindow::get_global_mouse_position(GLFWwindow* window)
{
    CGUIPointd cursor_position;
    CGUIPointi window_position;
    glfwGetCursorPos(window, &cursor_position.x, &cursor_position.y);
    glfwGetWindowPos(window, &window_position.x, &window_position.y);

    cursor_position += window_position;  

    debug_handler.post_log(std::string("Global mouse position: x-") + std::to_string(cursor_position.x) + std::string(" y-") + std::to_string(cursor_position.y), DEBUG_MODE_LOG);

    return cursor_position;
}

/********************************************************************************
 *                                 Callback block                               *
 ********************************************************************************/

/**
 * @brief      Key callback handler function.
 *
 * @param      window    Window pointer.
 * @param[in]  key       Key code.
 * @param[in]  scancode  Scancode.
 * @param[in]  action    Key action type.
 * @param[in]  mods      key action modifiers.
 */
void CGUIMainWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS:
        {
            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                {
                    glfwSetWindowShouldClose(main_window_handler->main_window, GLFW_TRUE);
                    main_window_handler->debug_handler.post_log("Escape has been pressed, window will be closed.", DEBUG_MODE_LOG);
                }
                break;

                default:
                {
                    return;
                }
            }
        }
        break;

        case GLFW_REPEAT:
        {
            // Add later if needed
        }
        break;

        case GLFW_RELEASE:
        {
            // add later if needed
        }
        break;

        case GLFW_KEY_UNKNOWN:
        {
            // Handles unknown key presses, add later if needed
        }
        break;

        default:
        {
            main_window_handler->debug_handler.post_log("Invalid key callback action: " + std::to_string(action), DEBUG_MODE_ERROR);
            return;
        }
    }
    return;
}

/**
 * @brief      Character callback for input fields.
 *
 * @param      window     Window pointer.
 * @param[in]  character  Character pressed.
 */
void CGUIMainWindow::character_callback(GLFWwindow* window, unsigned int character)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    if (main_window_handler->character_mode)
    {
        wchar_t* input = new wchar_t[1];
        input[0] = character;
        std::wstring charater(input);
        main_window_handler->debug_handler.post_log(std::wstring(L"Character: ") + charater, DEBUG_MODE_LOG);
        delete [] input;
    }
    return;
}

/**
 * @brief      Cursor position callback handler.
 *
 * @param      window  Window pointer.
 * @param[in]  xpos    X coodriante mouse position.
 * @param[in]  ypos    Y coordinate mouse position.
 */
void CGUIMainWindow::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    if (main_window_handler->mouse_lb_pressed)
    {
        CGUIPointd new_mouse_press_position = main_window_handler->get_global_mouse_position(window);

        if (new_mouse_press_position != main_window_handler->last_mouse_press_position)
        {
            CGUIPointi window_position;
            glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
            glfwSetWindowPos(main_window_handler->main_window, window_position.x + (new_mouse_press_position.x - main_window_handler->last_mouse_press_position.x), window_position.y + (new_mouse_press_position.y - main_window_handler->last_mouse_press_position.y));
            main_window_handler->last_mouse_press_position = new_mouse_press_position;
        }
    }
}

/**
 * @brief      Cursor hover callback handler.
 *
 * @param      window   Window pointer.
 * @param[in]  entered  Hover mode.
 */
void CGUIMainWindow::cursor_enter_callback(GLFWwindow* window, int entered)
{

}

/**
 * @brief      Mouse button callback handler.
 *
 * @param      window  Window pointer.
 * @param[in]  button  Mouse button.
 * @param[in]  action  Mouse action type.
 * @param[in]  mods    Mouse action modifiers.
 */
void CGUIMainWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS:
        {
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                {
                    main_window_handler->mouse_lb_pressed = true;

                    CGUIPointd new_mouse_press_position = main_window_handler->get_global_mouse_position(window);
                    main_window_handler->last_mouse_press_position = new_mouse_press_position;

                    main_window_handler->debug_handler.post_log("Left button has been pressed.", DEBUG_MODE_LOG);
                }
                break;

                default:
                {
                    return;
                }
            }
        }
        break;

        case GLFW_RELEASE:
        {
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                {
                    main_window_handler->mouse_lb_pressed = false;
                    main_window_handler->debug_handler.post_log("Left button has been released.", DEBUG_MODE_LOG);
                }
                break;

                default:
                {
                    return;
                }
            }
        }
        break;

        default:
        {
            main_window_handler->debug_handler.post_log("Invalid key callback action: " + std::to_string(action), DEBUG_MODE_ERROR);
            return;
        }
    }
    return;
}

/**
 * @brief      Mouse scroll handler.
 *
 * @param      window   Window pointer.
 * @param[in]  xoffset  X axis scroll offset.
 * @param[in]  yoffset  Y axis scroll offset.
 */
void CGUIMainWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    return;
}

/**
 * @brief      Frame renderer wrapper.
 *
 * @param      window    Window pointer.
 */
void CGUIMainWindow::frame_renderer_wrapper(GLFWwindow* window)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));

    glfwMakeContextCurrent(main_window_handler->main_window);

    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();

    main_window_handler->thread_mutex.lock();

    main_window_handler->debug_handler.post_log(std::string("Renderer wrapper has been assigned to thread: ") + std::to_string(std::stoi(thread_id.str())), DEBUG_MODE_LOG);
    
    main_window_handler->thread_mutex.unlock();

    main_window_handler->render_frames();
    return;
}