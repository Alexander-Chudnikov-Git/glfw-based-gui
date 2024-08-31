/**
 * @file       <CGUIShaderCompiler.hpp>
 * @brief      This header file implements CGUIShaderCompiler class.
 *
 *             It is being used in order to compile and use shaders,
 *             that would be later used by renderer.
 *
 * @author     THE_CHOODICK
 * @date       30-07-2022
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
#ifndef CGUISHADERCOMPILER_HPP
#define CGUISHADERCOMPILER_HPP

//#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
//    #define GLFW_EXPOSE_NATIVE_WIN32
//#endif

/**<
 * Include GLFW and GLAD for window handling.
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
//    #include "../glfw/include/GLFW/glfw3native.h"
//    #include <windows.h>
//#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../debug_handler/CGUIDebugHandler.hpp"

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
    #include "../../resources/resources.hpp"

    #include <windows.h>
#endif // Windows

#include <unordered_map>
#include <cstring>
#include <vector>

class CGUIShaderCompiler
{
public:
    CGUIShaderCompiler();
    CGUIShaderCompiler(const std::string& shader_name, fs::path vertext_file_path, fs::path fragment_file_path, fs::path geometry_file_path);
    CGUIShaderCompiler(const std::string& shader_name, const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader);
    #if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
        CGUIShaderCompiler(const std::string& shader_name, unsigned int vertex_shader_rsid, unsigned int fragment_shader_rsid, unsigned int geometry_shader_rsid);
    #endif // Windows
    ~CGUIShaderCompiler();

    GLuint compile_shader(const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader);

    void add_shader(const std::string& shader_name, fs::path vertext_file_path, fs::path fragment_file_path, fs::path geometry_file_path);
    void add_shader(const std::string& shader_name, const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader);
    #if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
        void add_shader(const std::string& shader_name, unsigned int vertex_shader_rsid, unsigned int fragment_shader_rsid, unsigned int geometry_shader_rsid);
    #endif // Windows
    void del_shader(const std::string& shader_name);
    void use_shader(const std::string& shader_name);

    bool check_for_errors(GLuint shader_id, std::string shader_type);

    std::string* get_shader_names();

private:
    std::unordered_map<std::string, GLuint> shader_list;

    CGUIDebugHandler debug_handler = CGUIDebugHandler(false);
};

#endif //CGUISHADERCOMPILER_HPP
