/**
 * @file       <CGUIMainWindow.cpp>
 * @brief      This source file implements CGUIMainWindow class. 
 *             
 *             It is being used in order to create main window, that would 
 *             be populated with UI elements specific for this project.
 *
 * @author     THE_CHOODICK
 * @date       22-07-2022
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
    program_start_time = std::chrono::steady_clock::now();
    debug_handler = CGUIDebugHandler(main_debug_handler);
	if (!initialize())
    {
        debug_handler.post_log("Unable to initialize CGUI.", DEBUG_MODE_ERROR);
        close();
    }

    debug_handler.post_log("CGUI has been initialized successfully.", DEBUG_MODE_LOG);

    if (!initialize_renderer())
    {
        debug_handler.post_log("Unable to initialize renderer.", DEBUG_MODE_ERROR);
        close();
    }

    debug_handler.post_log("Renderer has been initialized successfully.", DEBUG_MODE_LOG);

    CGUIShaderCompiler tesm;

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
    return;
}

/**
 * @brief      Hides window from user.
 */
void CGUIMainWindow::hide()
{
    return;
}

/**
 * @brief      Closes window instance.
 */
void CGUIMainWindow::close()
{
    debug_handler.post_log("Window has been closed.", DEBUG_MODE_LOG);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return;
}


/********************************************************************************
 *  							    Private block 								*
 ********************************************************************************/

/**
 * @brief      Initializes window with given parameters.
 *
 * @param[opt] vertical_sync    Vertical synchronization toggle.
 * *
 * @return     Was initialization successful or not.
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
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

    main_window = glfwCreateWindow(last_window_size.x, last_window_size.y, main_window_name.c_str(), NULL, NULL);

    current_monitor = get_monitor_by_cpos(get_global_mouse_position(main_window));

    const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(current_monitor);

    last_window_position = {(monitor_video_mode->width - last_window_size.x) / 2, (monitor_video_mode->height - last_window_size.y) / 2};

    // Create invisible window in order to get mouse position
    if (full_screen)
    {
        debug_handler.post_log("Full screen window is being created.", DEBUG_MODE_LOG);
        set_fullscreen_mode();
    }
    else 
    {
        debug_handler.post_log("Normal window is being created.", DEBUG_MODE_LOG);
        set_windowed_mode();
    }

    if (main_window == NULL)
    {
        debug_handler.post_log("Unable to properly create window.", DEBUG_MODE_ERROR);
        return false;
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
    glfwSetFramebufferSizeCallback(main_window, framebuffer_size_callback);  
    glfwSetWindowSizeCallback(main_window, window_size_callback);

    debug_handler.post_log("Callback have been initialized.", DEBUG_MODE_LOG);

    glfwMakeContextCurrent(main_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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
    #if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
        shaders = new CGUIShaderCompiler(CGUI_SHADER_TRIANDLE, GBG_VERT_SHADER_0, GBG_FRAG_SHADER_0, GBG_GEOM_SHADER_0);
    #endif // Windows
    #ifdef __APPLE__
        shaders = new CGUIShaderCompiler(CGUI_SHADER_TRIANDLE, triangle_vertext_file_path, triangle_fragment_file_path, triangle_geometry_file_path);
    #endif //__APPLE__
    

    // ... VBO implementation

    return true;
}

/**
 * @brief      Updates the frame.
 */
void CGUIMainWindow::update_thread()
{
    // Set GLFW context to NULL in order to render window in separate thread 
    glfwMakeContextCurrent(NULL);

    render_thread = new std::thread(&CGUIMainWindow::frame_renderer_wrapper, this);
    render_thread->detach();
    
    update_events();

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
    std::chrono::time_point<std::chrono::steady_clock> last_second_time_interval = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> last_frame_render_time_start = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> last_frame_render_time_end = std::chrono::steady_clock::now();
    size_t frame_counter = 0;

    while(!glfwWindowShouldClose(main_window))
    {
        last_frame_render_time_start = std::chrono::steady_clock::now();
        
        float framebuffer_ratio;
        glm::ivec2 framebuffer_size;
        
        {
            std::unique_lock thread_lock(thread_mutex);
            if (!is_resized)
            {
                thread_con_v.wait(thread_lock, [this]{return is_resized;});
            }

            glfwGetFramebufferSize(main_window, &framebuffer_size.x, &framebuffer_size.y);
            framebuffer_ratio = framebuffer_size.x / (float) framebuffer_size.y;

            glViewport(0, 0, framebuffer_size.x, framebuffer_size.y);
            glClearColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (vertical_sync)
            {
                glFinish();
            }
            
            glfwSwapBuffers(main_window);
            
            if (vertical_sync)
            {
                glFinish();
            }
            glfwPostEmptyEvent();

            thread_lock.unlock();
        }

        last_frame_render_time_end = std::chrono::steady_clock::now();
        last_frame_render_time = std::chrono::duration_cast<std::chrono::milliseconds>(last_frame_render_time_end - last_frame_render_time_start).count();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(last_frame_render_time_end - last_second_time_interval).count() > 1000)
        {
            last_second_time_interval = last_frame_render_time_end;
            last_frames_rendered_per_second = frame_counter;
            frame_counter = 0;
        }
        frame_counter++;
    }
    return;
}

/**
 * @brief      Updates Pool Event function.
 */
void CGUIMainWindow::update_events()
{
    std::chrono::time_point<std::chrono::steady_clock> last_frame_event_time_start = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> last_frame_event_time_end = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(main_window))
    {
        last_frame_event_time_start = std::chrono::steady_clock::now();
        glfwWaitEvents();
        last_frame_event_time_end = std::chrono::steady_clock::now();
        last_frame_event_time = std::chrono::duration_cast<std::chrono::milliseconds>(last_frame_event_time_end - last_frame_event_time_start).count();
    }
    return;
}

/**
 * @brief      Frame renderer wrapper.
 */
void CGUIMainWindow::frame_renderer_wrapper()
{
    //std::lock_guard<std::mutex> lock(thread_mutex);
    
    glfwMakeContextCurrent(this->main_window);

    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();

    this->debug_handler.post_log(std::string("Renderer wrapper has been assigned to thread: ") + std::to_string(std::stoi(thread_id.str())), DEBUG_MODE_LOG);

    this->render_frames();
    return;
}

/**
 * @brief      Switches window mode to fullscreen
 */
void CGUIMainWindow::set_fullscreen_mode()
{
    glfwGetWindowSize(main_window, &last_window_size.x, &last_window_size.y);
    glfwGetWindowPos(main_window, &last_window_position.x, &last_window_position.y);
    debug_handler.post_log("Window mode has been set to fullscreen.", DEBUG_MODE_LOG);
    full_screen = true;

    current_monitor = get_monitor_by_cpos(get_global_mouse_position(main_window));

    const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(current_monitor);

    glfwSetWindowMonitor(main_window, current_monitor, 0, 0, monitor_video_mode->width, monitor_video_mode->height, monitor_video_mode->refreshRate);
}

/**
 * @brief      Switches window mode to windowed
 */
void CGUIMainWindow::set_windowed_mode()
{   
    glfwHideWindow(main_window);
    debug_handler.post_log("Window mode has been set to windowed.", DEBUG_MODE_LOG);
    full_screen = false;

    current_monitor = get_monitor_by_cpos(get_global_mouse_position(main_window));

    const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(current_monitor);

    glfwSetWindowMonitor(main_window, NULL, last_window_position.x, last_window_position.y, last_window_size.x, last_window_size.y, monitor_video_mode->refreshRate);
    glfwShowWindow(main_window);
}

/**
 * @brief      Switches window mode
 */
void CGUIMainWindow::switch_window_mode()
{
    if (!full_screen)
    {
        set_fullscreen_mode();
    }
    else 
    {
        set_windowed_mode();
    }
}

/**
 * @brief      Gets the selected monitor.
 * 
 * @param      cursor_position   Position of a cursor.
 * 
 * @return     Focused  window pointer.
 */
GLFWmonitor* CGUIMainWindow::get_monitor_by_cpos(glm::dvec2 cursor_position)
{
    int monitor_count;
    glm::ivec2 monitor_position;
    glm::ivec2 monitor_size;

    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    for (int current_monitor_id = 0; current_monitor_id < monitor_count; ++current_monitor_id)
    {   
        const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(monitors[current_monitor_id]);

        monitor_size = {monitor_video_mode->width, monitor_video_mode->height};

        glfwGetMonitorPos(monitors[current_monitor_id], &monitor_position.x, &monitor_position.y);
        
        if (collision(glm::ivec2(monitor_position.x, monitor_position.y), glm::ivec2(monitor_position.x + monitor_video_mode->width, monitor_position.y + monitor_video_mode->height), glm::ivec2(cursor_position.x, cursor_position.y)))
        {
            return monitors[current_monitor_id];  
        }
        //debug_handler.post_log(std::string("Monitor: ") + glfwGetMonitorName(monitors[current_monitor_id]) + std::string(" position: x-") + std::to_string(cursor_position.x) + std::string(" y-") + std::to_string(cursor_position.y), DEBUG_MODE_LOG);
    }
    return NULL;
}

/**
 * @brief      Gets the current monitor.
 *
 * @param      window   Window pointer.
 * 
 * @return     Current window pointer.
 */
GLFWmonitor* CGUIMainWindow::get_current_monitor(GLFWwindow *window)
{
    int monitor_count, overlap_factor; 
    int best_overlap_factor = 0;
    glm::ivec2 monitor_position, window_position;
    glm::ivec2 monitor_size, window_size;

    glfwGetWindowPos(window, &window_position.x, &window_position.y);
    glfwGetWindowSize(window, &window_size.x, &window_size.y);

    GLFWmonitor* best_current_monitor = NULL;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    for (int current_monitor_id = 0; current_monitor_id < monitor_count; ++current_monitor_id)
    {   
        const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(monitors[current_monitor_id]);

        monitor_size = {monitor_video_mode->width, monitor_video_mode->height};

        glfwGetMonitorPos(monitors[current_monitor_id], &monitor_position.x, &monitor_position.y);

        overlap_factor = std::max(0, std::min(window_position.x + window_size.x, monitor_position.x + monitor_size.x) - std::max(window_position.x, monitor_position.x)) * std::max(0, std::min(window_position.y + window_size.y, monitor_position.y + monitor_size.y) - std::max(window_position.y, monitor_position.y));

        if (best_overlap_factor < overlap_factor) 
        {
            best_overlap_factor = overlap_factor;
            best_current_monitor = monitors[current_monitor_id];
        }
        
        //debug_handler.post_log(std::string("Monitor: ") + glfwGetMonitorName(monitors[current_monitor_id]) + std::string(" position: x-") + std::to_string(cursor_position.x) + std::string(" y-") + std::to_string(cursor_position.y), DEBUG_MODE_LOG);
    }
    return best_current_monitor;
}

/**
 * @brief      Gets the global mouse position.
 *
 * @param      window   Window pointer.
 *
 * @return     Global   mouse position.
 */
glm::dvec2 CGUIMainWindow::get_global_mouse_position(GLFWwindow* window)
{
    glm::dvec2 cursor_position;
    glm::ivec2 window_position;
    glfwGetCursorPos(window, &cursor_position.x, &cursor_position.y);
    glfwGetWindowPos(window, &window_position.x, &window_position.y);

    cursor_position += window_position;  

    //debug_handler.post_log(std::string("Global mouse position: x-") + std::to_string(cursor_position.x) + std::string(" y-") + std::to_string(cursor_position.y), DEBUG_MODE_LOG);

    return cursor_position;
}

/**
 * @brief      Basic collision detection for point and rectangle.
 *
 * @param[in]  rect_tl  Top left point of rectangle.
 * @param[in]  rect_br  Bottom right point of rectangle.
 * @param[in]  point    Point, that should be checked for collision.
 *
 * @return     Is rectangle given by first 2 arguments collides with point, given as third parameter.
 */
bool CGUIMainWindow::collision(glm::ivec2 rect_tl, glm::ivec2 rect_br, glm::ivec2 point)
{
    return (point.x < rect_br.x && point.x > rect_tl.x && point.y < rect_br.y && point.y > rect_tl.y);
}

/**
 * @brief      Assertion of press type.
 *
 * @param[in]  press_position  The press position.
 *
 * @return     Asserts press type for given point.
 */
uint8_t CGUIMainWindow::assert_window_press_type(glm::dvec2 press_position)
{
    uint8_t press_type = CGUI_PRESS_TYPE_WINDOW_OUTSIDE;
    if (!full_screen)
    {
        if (press_position.x < window_drag_offset)
        {
            if (press_position.y < window_drag_offset)
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_LEFT;
            }
            else if (press_position.y > last_window_size.y - window_drag_offset)
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_LEFT;
            }
            else 
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_LEFT;
            }
        }
        else if (press_position.x > last_window_size.x - window_drag_offset)
        {
            if (press_position.y < window_drag_offset)
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_RIGHT;
            }
            else if (press_position.y  > last_window_size.y - window_drag_offset)
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_RIGHT;
            }
            else 
            {
                press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_RIGHT;
            }
        }
        else if (press_position.y  < window_drag_offset)
        {
            press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP;
        }
        else if (press_position.y  > last_window_size.y - window_drag_offset)
        {
            press_type = CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM;
        }
        else
        {
            press_type = CGUI_PRESS_TYPE_WINDOW_MOVE;
        }
    }
    else 
    {
        press_type = CGUI_PRESS_TYPE_WINDOW_FULLSCREEN;
    }
    return press_type;
}

/**
 * @brief      Implementation for simultaneous resize of position and size of the window.
 *
 * @param[in]  pos   New position.
 * @param[in]  size  New size.
 */
void CGUIMainWindow::resize_window_rect(GLFWwindow* window, glm::ivec2 pos, glm::ivec2 size)
{
    is_resized = false;

    {
        std::lock_guard lock_resize(thread_mutex);

        if (!full_screen)
        {
            #if defined(__APPLE__)
                debug_handler.post_log(std::string("Window position: x=" + std::to_string(pos.x) + " y=" + std::to_string(pos.y) + " size: x=" + std::to_string(size.x) + " y=" + std::to_string(size.y)), DEBUG_MODE_ERROR);
                // Fix apple about page padding 
                // [IMPORTANT]
                if (pos.y < 25)
                {
                    size.y -= (25 - pos.y);
                    pos.y = 25;
                }
            #endif
            const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(current_monitor);
            glfwSetWindowMonitor(window, NULL, pos.x, pos.y, size.x, size.y, monitor_video_mode->refreshRate);
        }
        else
        {
            debug_handler.post_log("Resize during fullscreen is not only viable, but also possible.", DEBUG_MODE_ERROR);
        }

        is_resized = true;
    }

    thread_con_v.notify_all();

    return;
}

/********************************************************************************
 *                                 Callback block                               *
 ********************************************************************************/

/**
 * @brief      Key callback handler function.
 *
 * @param      window       Window pointer.
 * @param[in]  key          Key code.
 * @param[in]  scan_code    Scan code.
 * @param[in]  action       Key action type.
 * @param[in]  mods         key action modifiers.
 */
void CGUIMainWindow::key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods)
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

                case GLFW_KEY_I:
                {
                    if (mods & GLFW_MOD_CONTROL && mods & GLFW_MOD_SHIFT)
                    {
                        glm::ivec2 window_position, window_size, global_mouse_position;
                        glm::dvec2 local_mouse_position;
                        glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                        glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);
                        glfwGetCursorPos(main_window_handler->main_window, &local_mouse_position.x, &local_mouse_position.y);
                        global_mouse_position = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                        main_window_handler->debug_handler.post_log("", DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log("/ DEBUG INFO START", DEBUG_MODE_MESSAGE);
                        main_window_handler->debug_handler.post_log(std::string("| Time passed since program started: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - main_window_handler->program_start_time).count()) + "ms"), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Time required to process last events: " + std::to_string(main_window_handler->last_frame_event_time) + "ms"), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Time required to render last frame: " + std::to_string(main_window_handler->last_frame_render_time) + "ms"), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Rough estimation of fps: " + std::to_string(1000.0f / main_window_handler->last_frame_render_time) + "fps"), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Real amount of fps: " + std::to_string(main_window_handler->last_frames_rendered_per_second) + "fps"), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| GLFW version string: " + std::string(glfwGetVersionString())), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current monitor: " + std::string(glfwGetMonitorName(main_window_handler->get_current_monitor(main_window_handler->main_window)))), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window position: x=" + std::to_string(window_position.x) + " y=" + std::to_string(window_position.y)), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window size: x=" + std::to_string(window_size.x) + " y=" + std::to_string(window_size.y)), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current cursor local position: x=" + std::to_string(local_mouse_position.x) + " y=" + std::to_string(local_mouse_position.y)), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current cursor global position: x=" + std::to_string(global_mouse_position.x) + " y=" + std::to_string(global_mouse_position.y)), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window mode: " + std::string((main_window_handler->full_screen == true) ? "Fullscreen" : "Windowed")), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window decoration: " + std::string((glfwGetWindowAttrib(main_window_handler->main_window, GLFW_DECORATED) == true) ? "Decorated" : "Not Decorated")), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window floating: " + std::string((glfwGetWindowAttrib(main_window_handler->main_window, GLFW_FLOATING) == true) ? "Floating" : "Not Floating")), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window visible: " + std::string((glfwGetWindowAttrib(main_window_handler->main_window, GLFW_VISIBLE) == true) ? "Visible" : "Not Visible")), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log(std::string("| Current window resizable: " + std::string((glfwGetWindowAttrib(main_window_handler->main_window, GLFW_RESIZABLE) == true) ? "Resizable" : "Not Resizable")), DEBUG_MODE_NONE);
                        main_window_handler->debug_handler.post_log("\\ DEBUG INFO END", DEBUG_MODE_MESSAGE);
                        main_window_handler->debug_handler.post_log("", DEBUG_MODE_NONE);
                    }
                }
                break;

                case GLFW_KEY_F1:
                {
                    if (mods & GLFW_MOD_CONTROL && mods & GLFW_MOD_SHIFT)
                    {
                        main_window_handler->switch_window_mode();
                    }
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
 * @param      window       Window pointer.
 * @param[in]  character    Character pressed.
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
 * @param[in]  xpos    X coordinate mouse position.
 * @param[in]  ypos    Y coordinate mouse position.
 */
void CGUIMainWindow::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    glm::dvec2 new_mouse_press_position = {xpos, ypos};

    if (!main_window_handler->mouse_lb_pressed)
    {
        main_window_handler->window_press_type = main_window_handler->assert_window_press_type((glm::ivec2)new_mouse_press_position);
    }

    switch (main_window_handler->window_press_type)
    {
        case CGUI_PRESS_TYPE_WINDOW_MOVE: 
        {   
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                glm::ivec2 window_position;
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwSetWindowPos(main_window_handler->main_window, window_position.x + (new_mouse_press_position.x - (int)main_window_handler->last_mouse_press_position.x), window_position.y + (new_mouse_press_position.y - (int)main_window_handler->last_mouse_press_position.y));
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_LEFT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                glm::ivec2 window_position, window_position_temp, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                window_position_temp = window_position;
                if (window_size.x - (mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    window_position_temp.x = mouse_press_pos.x;
                }
                if (window_size.y - (mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    window_position_temp.y = mouse_press_pos.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position_temp.x, window_position_temp.y}, {window_size.x - (window_position_temp.x - window_position.x), window_size.y - (window_position_temp.y - window_position.y)});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_RIGHT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                glm::ivec2 window_position, window_size_temp, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                window_size_temp = window_size;
                if ((mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    window_size_temp.x = mouse_press_pos.x - window_position.x;
                }
                if ((mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    window_size_temp.y = mouse_press_pos.y - window_position.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position.x, window_position.y}, {window_size_temp.x, window_size_temp.y});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP_RIGHT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                glm::ivec2 window_position, window_geom_temp, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                window_geom_temp = {window_size.x, window_position.y};
                if ((mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    window_geom_temp.x = mouse_press_pos.x - window_position.x;
                }
                if (window_size.y - (mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    window_geom_temp.y = mouse_press_pos.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position.x, window_geom_temp.y}, {window_geom_temp.x, window_size.y - (window_geom_temp.y - window_position.y)});
            }
        }
        break; 

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM_LEFT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                glm::ivec2 window_position, window_geom_temp, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                window_geom_temp = {window_position.x, window_size.y};
                if (window_size.x - (mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    window_geom_temp.x = mouse_press_pos.x;
                }
                if ((mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    window_geom_temp.y = mouse_press_pos.y - window_position.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_geom_temp.x, window_position.y}, {window_size.x - (window_geom_temp.x - window_position.x), window_geom_temp.y});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_TOP:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NS_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                int y_size;
                glm::ivec2 window_position, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                y_size = window_position.y;

                if (window_size.y - (mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    y_size = mouse_press_pos.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position.x, y_size}, {window_size.x, window_size.y - (y_size - window_position.y)});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_BOTTOM:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_NS_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                int y_size;
                glm::ivec2 window_position, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                y_size = window_size.y;

                if ((mouse_press_pos.y - window_position.y) > main_window_handler->window_size_min.y)
                {
                    y_size = mouse_press_pos.y - window_position.y;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position.x, window_position.y}, {window_size.x, y_size});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_RIGHT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_EW_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                int x_size;
                glm::ivec2 window_position, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                x_size = window_size.x;
                if ((mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    x_size = mouse_press_pos.x - window_position.x;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {window_position.x, window_position.y}, {x_size, window_size.y});
            }
        }
        break;

        case CGUI_PRESS_TYPE_WINDOW_RESIZE_LEFT:
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_RESIZE_EW_CURSOR);
            if (new_mouse_press_position != main_window_handler->last_mouse_press_position && main_window_handler->mouse_lb_pressed)
            {
                int x_size;
                glm::ivec2 window_position, window_size;
                glm::ivec2 mouse_press_pos = main_window_handler->get_global_mouse_position(main_window_handler->main_window);
                glfwGetWindowPos(main_window_handler->main_window, &window_position.x, &window_position.y);
                glfwGetWindowSize(main_window_handler->main_window, &window_size.x, &window_size.y);

                x_size = window_position.x;
                if (window_size.x - (mouse_press_pos.x - window_position.x) > main_window_handler->window_size_min.x)
                {
                    x_size = mouse_press_pos.x;
                }
                main_window_handler->resize_window_rect(main_window_handler->main_window, {x_size, window_position.y}, {window_size.x - (x_size - window_position.x), window_size.y});
            }
        }
        break;

        default :
        {
            main_window_handler->current_cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        }
    }

    glfwSetCursor(window, main_window_handler->current_cursor);
    
    return;
}

/**
 * @brief      Cursor hover callback handler.
 *
 * @param      window   Window pointer.
 * @param[in]  entered  Hover mode.
 */
void CGUIMainWindow::cursor_enter_callback(GLFWwindow* window, int entered)
{
    return;
}

/**
 * @brief      Mouse button callback handler.
 *
 * @param      window   Window pointer.
 * @param[in]  button   Mouse button.
 * @param[in]  action   Mouse action type.
 * @param[in]  mods     Mouse action modifiers.
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
                    main_window_handler->last_lb_press_time = std::chrono::steady_clock::now();
                    main_window_handler->mouse_lb_pressed = true;

                    glm::dvec2 new_mouse_press_position;
                    glfwGetCursorPos(window, &new_mouse_press_position.x, &new_mouse_press_position.y);
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
                    main_window_handler->debug_handler.post_log(std::string("Left button has been released, it was held for: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - main_window_handler->last_lb_press_time).count()) + "ms"), DEBUG_MODE_LOG);
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
 * @brief      Frame buffer resize handler.
 * 
 * @param      window   Window pointer.
 * @param[in]  width    Frame buffer width.
 * @param[in]  height   Frame buffer height.
 */
void CGUIMainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void CGUIMainWindow::window_size_callback(GLFWwindow* window, int width, int height)
{
    CGUIMainWindow* main_window_handler = reinterpret_cast<CGUIMainWindow*>(glfwGetWindowUserPointer(window));
    if (!main_window_handler->full_screen)
    {
        main_window_handler->last_window_size = {width, height};
    }
}