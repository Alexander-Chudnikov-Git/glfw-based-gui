/**
 * @file       <CGUIShaderCompiler.cpp>
 * @brief      This source file implements CGUIShaderCompiler class. 
 *             
 *             It is being used in order to compile and use shaders, 
 *             that would be later used by renderer.
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
#include "CGUIShaderCompiler.hpp"

/**
 * @brief      Constructs a new instance of shader compiler.
 */
CGUIShaderCompiler::CGUIShaderCompiler()
{
    debug_handler = new CGUIDebugHandler(false);
    debug_handler->post_log("New instance of shader compile created.", DEBUG_MODE_LOG);
}

/**
 * @brief      Constructs a new instance of shader compiler.
 *
 * @param[in]  shader_name         The shader name.
 * @param[in]  vertext_file_path   The vertext file path.
 * @param[in]  fragment_file_path  The fragment file path.
 * @param[in]  geometry_file_path  The geometry file path.
 */
CGUIShaderCompiler::CGUIShaderCompiler(const std::string& shader_name, fs::path vertext_file_path, fs::path fragment_file_path, fs::path geometry_file_path)
{
    debug_handler = new CGUIDebugHandler(false);
    debug_handler->post_log("New instance of shader compile created.", DEBUG_MODE_LOG);

    add_shader(shader_name, vertext_file_path, fragment_file_path, geometry_file_path);    
}

/**
 * @brief      Constructs a new instance of shader compiler.
 *
 * @param[in]  shader_name      The shader name.
 * @param[in]  vertex_shader    The vertex shader source.
 * @param[in]  fragment_shader  The fragment shader source.
 * @param[in]  geometry_shader  The geometry shader source.
 */
CGUIShaderCompiler::CGUIShaderCompiler(const std::string& shader_name, const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader)
{
    debug_handler = new CGUIDebugHandler(false);
    debug_handler->post_log("Shader initialization has started.", DEBUG_MODE_LOG);

    add_shader(shader_name, vertex_shader, fragment_shader, geometry_shader);
}

/**
 * @brief      Destroys shader compiler.
 */
CGUIShaderCompiler::~CGUIShaderCompiler()
{
    shader_list.clear();
}

GLuint CGUIShaderCompiler::compile_shader(const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader)
{
    GLuint compiled_vertex;
    GLuint compiled_fragment;
    GLuint compiled_geometry;

    GLuint id = glCreateProgram();

    compiled_vertex = glCreateShader(GL_VERTEX_SHADER);
    const char *source_buffer = vertex_shader.c_str();
    glad_glShaderSource(compiled_vertex, 1, &source_buffer, NULL);
    glCompileShader(compiled_vertex);
    if(!check_for_errors(compiled_vertex, "VERTEX"))
    {
        return 0;
    }

    glAttachShader(id, compiled_vertex);

    compiled_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    source_buffer = fragment_shader.c_str();
    glShaderSource(compiled_fragment, 1, &source_buffer, NULL);
    glCompileShader(compiled_fragment);
    if(!check_for_errors(compiled_vertex, "FRAGMENT"))
    {
        return 0;
    }

    glAttachShader(id, compiled_fragment);

    if (std::strcmp(geometry_shader.c_str(), "NONE") != 0)
    {
        compiled_geometry = glCreateShader(GL_GEOMETRY_SHADER);
        source_buffer = geometry_shader.c_str();
        glShaderSource(compiled_geometry, 1, &source_buffer, NULL);
        glCompileShader(compiled_geometry);
        if(!check_for_errors(compiled_vertex, "GEOMETRY"))
        {
            return 0;
        }

        glAttachShader(id, compiled_geometry);
    }

    glLinkProgram(id);

    check_for_errors(id, "PROGRAM");

    glDetachShader(id, compiled_vertex);
    glDeleteShader(compiled_vertex);
    glDetachShader(id, compiled_fragment);
    glDeleteShader(compiled_fragment);
    if (std::strcmp(geometry_shader.c_str(), "NONE") != 0)
    {
        glDetachShader(id, compiled_geometry);
        glDeleteShader(compiled_geometry);
    }

    return id;
}

/**
 * @brief      Adds a shader to map.
 *
 * @param[in]  shader_name          The shader name.
 * @param[in]  vertext_file_path    The vertex shader file path.
 * @param[in]  fragment_file_path   The fragment shader file path.
 * @param[in]  geometry_file_path   The geometry shader file path.
 */
void CGUIShaderCompiler::add_shader(const std::string &shader_name, fs::path vertext_file_path, fs::path fragment_file_path, fs::path geometry_file_path)
{
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;
    std::ifstream geometry_shader_file;

    std::stringstream vertex_shader_stream;
    std::stringstream fragment_shader_stream;
    std::stringstream geometry_shader_stream;

    vertex_shader_file.exceptions   (std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    geometry_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try 
    {
        // Load vertex shader
        vertex_shader_file.open(vertext_file_path);
        vertex_shader_stream << vertex_shader_file.rdbuf();
        vertex_shader_file.close();

        // Load fragment shader
        fragment_shader_file.open(fragment_file_path);
        fragment_shader_stream << fragment_shader_file.rdbuf();
        fragment_shader_file.close();
        
        // Load geometry shader
        if(geometry_file_path != "")
        {
            geometry_shader_file.open(geometry_file_path);
            geometry_shader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
        }
        else 
        {
            geometry_shader_stream << "NONE";
        }
    }
    catch (std::ifstream::failure& e)
    {
        debug_handler->post_log(std::string("Shaders cannot be loaded properly: ") + e.what(), DEBUG_MODE_ERROR);
        return;
    }

    vertex_shader_file.close();
    fragment_shader_file.close();
    geometry_shader_file.close();

    add_shader(shader_name, vertex_shader_stream.str(), fragment_shader_stream.str(), geometry_shader_stream.str());
}

/**
 * @brief      Adds a shader to map.
 *
 * @param[in]  shader_name      The shader name.
 * @param[in]  vertex_shader    The vertex shader sorce.
 * @param[in]  fragment_shader  The fragment shader sorce.
 * @param[in]  geometry_shader  The geometry shader sorce.
 */
void CGUIShaderCompiler::add_shader(const std::string &shader_name, const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader)
{
    GLuint new_shader_id = compile_shader(vertex_shader, fragment_shader, geometry_shader);
    if (new_shader_id == 0)
    {
        debug_handler->post_log(std::string("Unable to initialize shader: ") + shader_name, DEBUG_MODE_ERROR);
        return;
    }

    debug_handler->post_log(std::string("Shader has been successfully initialized: ") + shader_name, DEBUG_MODE_LOG);
    shader_list.insert(std::pair<std::string, GLuint>(shader_name, new_shader_id));
}

/**
 * @brief      Deletes a shader by its name.
 *
 * @param[in]  shader_name  The shader name.
 */
void CGUIShaderCompiler::del_shader(const std::string &shader_name)
{   
    GLuint shader_id;
    auto shader_iterator = shader_list.find(shader_name);

    if (shader_iterator != shader_list.end())
    {
        shader_id = shader_iterator->second;
        glDeleteProgram(shader_id);
        shader_list.erase(shader_name);
        debug_handler->post_log(std::string("Shader was successfully removed: ") + shader_name, DEBUG_MODE_LOG);
    }
    else
    {
        debug_handler->post_log(std::string("Unable to find shader: ") + shader_name, DEBUG_MODE_ERROR);
    }
}

/**
 * @brief      Applies shaders to renderer.
 *
 * @param[in]  shader_name  The shader name.
 */
void CGUIShaderCompiler::use_shader(const std::string &shader_name)
{
    GLuint shader_id;
    auto shader_iterator = shader_list.find(shader_name);

    if (shader_iterator != shader_list.end())
    {
        shader_id = shader_iterator->second;
        glUseProgram(shader_id);
        debug_handler->post_log(std::string("Shader was successfully applied: ") + shader_name, DEBUG_MODE_LOG);
    }
    else
    {
        debug_handler->post_log(std::string("Unable to find shader: ") + shader_name, DEBUG_MODE_ERROR);
    }
}

/**
 * @brief      Checks for errors in shader compilation.
 *
 * @param[in]  shader_id    The shader identifier.
 * @param[in]  shader_type  The shader type.
 *
 * @return     Status of compilation.
 */
bool CGUIShaderCompiler::check_for_errors(GLuint shader_id, std::string shader_type)
{
    GLint success;
    GLchar info_log[1024];
    if(shader_type != "PROGRAM")
    {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
            debug_handler->post_log(std::string("Unable to compile shader: id:") + std::to_string(shader_id) + std::string(" - ") + shader_type, DEBUG_MODE_ERROR);
            debug_handler->post_log(std::string("Shader error log: ") + info_log, DEBUG_MODE_ERROR);
            return false;
        }
    }
    else
    {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
            debug_handler->post_log(std::string("Unable to link shader: id:") + std::to_string(shader_id) + std::string(" - ") + shader_type, DEBUG_MODE_ERROR);
            debug_handler->post_log(std::string("Shader error log: ") + info_log, DEBUG_MODE_ERROR);
            return false;
        }
    }
    return true;
}