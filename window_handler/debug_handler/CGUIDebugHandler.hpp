/**
 * @file       <CGUIDebugHandler.hpp>
 * @brief      This header file implements CGUIDebugHandler class. 
 *             
 *             It is being used in order to handle basic debug functionality,
 *             also it is being used as log library.
 *
 * @author     THE_CHOODICK
 * @date       21-07-2022
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
#ifndef CGUIDEBUGHANDLER_HPP
#define CGUIDEBUGHANDLER_HPP

/**
 * CGUI log prefix list
 */
#define DEBUG_MODE_ERROR            0 
#define DEBUG_MODE_WARNING          1
#define DEBUG_MODE_MESSAGE          2
#define DEBUG_MODE_LOG              3
#define DEBUG_MODE_GLFW_CALLBACK    4
#define DEBUG_MODE_NONE             255

/**
 * GLFW callback codes.
 */
#define GLFW_NO_ERROR               0
#define GLFW_NOT_INITIALIZED        0x00010001
#define GLFW_NO_CURRENT_CONTEXT     0x00010002
#define GLFW_INVALID_ENUM           0x00010003
#define GLFW_INVALID_VALUE          0x00010004
#define GLFW_OUT_OF_MEMORY          0x00010005
#define GLFW_API_UNAVAILABLE        0x00010006
#define GLFW_VERSION_UNAVAILABLE    0x00010007
#define GLFW_PLATFORM_ERROR         0x00010008
#define GLFW_FORMAT_UNAVAILABLE     0x00010009
#define GLFW_NO_WINDOW_CONTEXT      0x0001000A


// Headers for string aligment and stuff
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

// Headers for fs interaction
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <filesystem>

// Headers for time 
#include <ctime>


#ifdef __APPLE__
    //#include <CoreFoundation/CoreFoundation.h>
    namespace fs = std::__fs::filesystem;
#endif //__APPLE__
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
    namespace fs = std::filesystem;
#endif // Windows
#if defined(__unix__) || defined(__linux__)
    namespace fs = std::filesystem;
#endif // Unix


/**
 * @brief      This class implements the whole debug functionality of CGUI project. 
 *             Class is based on standart io libraries, that are being used in order to produce log files.
 */
class CGUIDebugHandler
{
public:
    CGUIDebugHandler(bool clear_base_dir = true, std::string full_file_path = "");
    CGUIDebugHandler(const CGUIDebugHandler&);
    ~CGUIDebugHandler();

    void post_log(std::string message, size_t mode = DEBUG_MODE_NONE);
    void post_log(std::wstring message, size_t mode = DEBUG_MODE_NONE);
    static void glfw_error_callback(int error, const char* description);

    CGUIDebugHandler& operator=(CGUIDebugHandler&& debug_handler);

private:
    void clear_log(fs::path log_file_directory = "");

    std::string fill_zeros(int input_num, int num_offset);

    std::wstring str_to_wstr(std::string message);

private: 
    fs::path debug_file_path;

    std::wofstream debug_file_out;

    bool debug_disabled = true;
    
};

extern CGUIDebugHandler main_debug_handler;

#endif // CGUIDEBUGHANDLER_HPP