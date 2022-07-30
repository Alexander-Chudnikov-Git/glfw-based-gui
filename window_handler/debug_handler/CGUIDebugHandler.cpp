/**
 * @file       <CGUIDebugHandler.cpp>
 * @brief      This source file implements CGUIDebugHandler class. 
 *             
 *             It is being used in order to handle basic debug functionality,
 *             also it is being used as log library.
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
#include "CGUIDebugHandler.hpp"
#include <filesystem>
#include <iostream>
#include <streambuf>

CGUIDebugHandler main_debug_handler = CGUIDebugHandler();

/**
 * @brief      Constructs debug handler instance.
 * 
 * @param[opt]  clear_base_dir  Flag for removal of old log files.
 * @param[opt]  full_file_path  Full file path to debug log.
 */
CGUIDebugHandler::CGUIDebugHandler(bool clear_base_dir, std::string full_file_path) 
{
    if (full_file_path != "") 
    {
        debug_file_path = fs::path(full_file_path);
    } 
    else 
    {
        #if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
            debug_file_path = fs::current_path();
        #endif // Windows
        #if defined(__unix__) || defined(__linux__)
            debug_file_path = fs::path("/Users/" + std::string(getenv("USERNAME")) +"/Library/Application Support/CGUI");
        #endif // Unix
        #if defined(__APPLE__)
            debug_file_path = fs::path("/Users/" + std::string(getenv("USER")) +"/Library/Application Support/CGUI");
        #endif // Apple

        debug_file_path += fs::path("/log/debug_log_default.log");
    }

    fs::create_directories(debug_file_path.parent_path());

    if (clear_base_dir)
    {
        clear_log(debug_file_path);
    }

    struct stat debug_buffer;   
    if (stat(debug_file_path.string().c_str(), &debug_buffer) != 0)
    {

        debug_file_out.open(debug_file_path.string().c_str(), std::ios::app);
        if(!debug_file_out.good())
        {
            std::cerr << "Unable to initialize debug handler with this name : " << debug_file_path;
        }
        else 
        {
            debug_disabled = false;
            debug_file_out << "[LOADER DEBUG LOG]" << "\n";
            debug_file_out.close();
        }
    }
}

/**
 * @brief      Constructs a copy debugger handler instance.
 *
 * @param[in]  debug_handler  Debug handler to copy.
 */
CGUIDebugHandler::CGUIDebugHandler(const CGUIDebugHandler& debug_handler)
{
    debug_file_path = debug_handler.debug_file_path;
    debug_disabled = debug_handler.debug_disabled;
    struct stat debug_buffer;   
    if (stat(debug_file_path.string().c_str(), &debug_buffer) != 0)
    {

        debug_file_out.open(debug_file_path.string().c_str(), std::ios::app);
        if(!debug_file_out.good())
        {
            std::cerr << "Unable to initialize debug handler with this name : " << debug_file_path;
        }
        else 
        {
            debug_disabled = false;
            debug_file_out << "[LOADER DEBUG LOG]" << "\n";
            debug_file_out.close();
        }
    }
}

/**
 * @brief      Destructs debug handler instance.
 */
CGUIDebugHandler::~CGUIDebugHandler()
{
    if(debug_file_out.is_open())
    {
        debug_file_out.close();
    }
}

/**
 * @brief      Posts a log into file in string mode.
 *
 * @param[in]  message  Message to post.
 * @param[in]  mode     Prefix that would be posted before message.
 */
void CGUIDebugHandler::post_log(std::string message, size_t mode)
{
    post_log(str_to_wstr(message), mode);
}

/**
 * @brief      Posts a log into file in wstring mode.
 *
 * @param[in]  message  Message to post.
 * @param[in]  mode     Prefix that would be posted before message.
 */
void CGUIDebugHandler::post_log(std::wstring message, size_t mode)
{
    if (debug_disabled)
    {
        return;
    }

    std::wstring error_tag;
    switch (mode)
    {
        case DEBUG_MODE_ERROR:
        {
            error_tag = L"[ERROR]";
            std::wcerr << message;
        }
        break;

        case DEBUG_MODE_WARNING:
        {
            error_tag = L"[WARNING]";
        }
        break;

        case DEBUG_MODE_MESSAGE:
        {
            error_tag = L"[MESSAGE]";
        }
        break;

        case DEBUG_MODE_LOG:
        {
            error_tag = L"[LOG]";
        }
        break;

        case DEBUG_MODE_GLFW_CALLBACK:
        {
            error_tag = L"[GLFW]";
        }
        break;

        case DEBUG_MODE_NONE:
        {
            error_tag = L"";
        }
        break;

        default:
        {
            error_tag = L"[UNDEFINED]";
        }
        break;
    }

    std::time_t time_current = std::time(0);
    std::tm* time_struct = std::localtime(&time_current);

    debug_file_out.open(debug_file_path.string().c_str(), std::ios::app);
    debug_file_out << std::setw(24) << std::left << str_to_wstr("[" + fill_zeros(time_struct->tm_year + 1900, 4) + "-" + fill_zeros(time_struct->tm_mon + 1, 2) + "-" +  fill_zeros(time_struct->tm_mday, 2) + "-" + fill_zeros(time_struct->tm_hour, 2) + "-" + fill_zeros(time_struct->tm_min, 2) + "-" +  fill_zeros(time_struct->tm_sec, 2) + "]") << std::setw(14) << std::left << error_tag << L" " << message << L"\n";
    debug_file_out.close();
}


/**
 * @brief      Posts GLFW error into log file.
 *
 * @param[in]  error        GLFW error code.
 * @param[in]  description  GLFW error description.
 */
void CGUIDebugHandler::glfw_error_callback(int error, const char* description)
{
    std::string error_prefix;
    switch (error) 
    {
        case GLFW_NO_ERROR:
        {
            error_prefix = "[NO ERROR]";
        }
        break;

        case GLFW_NOT_INITIALIZED:
        {
            error_prefix = "[NOT INITIALIZED]";
        }
        break;

        case GLFW_NO_CURRENT_CONTEXT:
        {
            error_prefix = "[NO CURRENT CONTEXT]";
        }
        break;

        case GLFW_INVALID_ENUM:
        {
            error_prefix = "[INVALID ENUM]";
        }
        break;

        case GLFW_INVALID_VALUE:
        {
            error_prefix = "[INVALID VALUE]";
        }
        break;

        case GLFW_OUT_OF_MEMORY:
        {
            error_prefix = "[OUT OF MEMORY]";
        }
        break;

        case GLFW_API_UNAVAILABLE:
        {
            error_prefix = "[API UNAVAILABLE]";
        }
        break;

        case GLFW_VERSION_UNAVAILABLE:
        {
            error_prefix = "[VERSION UNAVAILABLE]";
        }
        break;

        case GLFW_PLATFORM_ERROR:
        {
            error_prefix = "[PLATFORM ERROR]";
        }
        break;

        case GLFW_FORMAT_UNAVAILABLE:
        {
            error_prefix = "[FROMAT UNAVAILABLE]";
        }
        break;

        case GLFW_NO_WINDOW_CONTEXT:
        {
            error_prefix = "[NO WINDOW CONTEXT]";
        }
        break;

        default:
        {
            error_prefix = "[UNDEFINED ERROR]";
        }
    }
    std::stringstream formated_error;
    formated_error << std::setw(14) << std::left << error_prefix << " " << description << "\n";
    CGUIDebugHandler temp(false);
    temp.post_log(formated_error.str(), 4);
}

CGUIDebugHandler& CGUIDebugHandler::operator=(CGUIDebugHandler&& debug_handler)
{
    this->~CGUIDebugHandler();
    return *new(this) CGUIDebugHandler(std::move(debug_handler));
}

/********************************************************************************
 *                                  Private block                               *
 ********************************************************************************/

/**
 * @brief      Clears debug log folder.
 *
 * @param[in]  log_file_directory  The log file directory.
 */
void CGUIDebugHandler::clear_log(fs::path log_file_directory)
{
    for (const auto &file : fs::directory_iterator(log_file_directory.parent_path())) 
    {
        if (file.path().string().find("debug_log_") != std::string::npos) 
        {
            fs::remove(file.path());
        }
    }
}

/**
 * @brief      Fills number with leading zeros for offset.
 *
 * @param[in]  input_num   Input number.
 * @param[in]  num_offset  Number of symbols to offset.
 *
 * @return     Number filled with leading zeros.
 */
std::string CGUIDebugHandler::fill_zeros(int input_num, int num_offset)
{
    std::stringstream converted_number;
    converted_number << std::setw(num_offset) << std::setfill('0') << input_num;
    return converted_number.str();
}

/**
 * @brief      Converts string to wstring.
 *
 * @param[in]  message  Initial message.
 *
 * @return     Converted message.
 */
std::wstring CGUIDebugHandler::str_to_wstr(std::string message)
{
    std::wstring message_wstr(message.begin(), message.end());
    return message_wstr;
}