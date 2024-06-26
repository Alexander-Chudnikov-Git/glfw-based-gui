/**
 * @file       <CGUIShaderCompiler.cpp>
 * @brief      This source file implements CGUIShaderCompiler class. 
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
#include "CGUIShaderCompiler.hpp"
#include <filesystem>

/**
 * @brief      Constructs a new instance of shader compiler.
 */
CGUIShaderCompiler::CGUIShaderCompiler()
{
    debug_handler = CGUIDebugHandler(main_debug_handler);
    debug_handler.post_log("New instance of shader compile created.", DEBUG_MODE_LOG);
}

/**
 * @brief      Constructs a new instance of shader compiler.
 *
 * @param[in]  shader_name         The shader name.
 * @param[in]  vertext_file_path   The vertex file path.
 * @param[in]  fragment_file_path  The fragment file path.
 * @param[in]  geometry_file_path  The geometry file path.
 */
CGUIShaderCompiler::CGUIShaderCompiler(const std::string& shader_name, fs::path vertext_file_path, fs::path fragment_file_path, fs::path geometry_file_path)
{
    debug_handler = CGUIDebugHandler(main_debug_handler);
    debug_handler.post_log("New instance of shader compile created.", DEBUG_MODE_LOG);

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
    debug_handler = CGUIDebugHandler(main_debug_handler);
    debug_handler.post_log("Shader initialization has started.", DEBUG_MODE_LOG);

    add_shader(shader_name, vertex_shader, fragment_shader, geometry_shader);
}

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
    /**
     * @brief      Constructs a new instance of shader compiler.
     *
     * @param[in]  shader_name          The shader name.
     * @param[in]  vertex_shader_rsid   The vertex shader resource id.
     * @param[in]  fragment_shader_rsid The fragment shader resource id.
     * @param[in]  geometry_shader_rsid The geometry shader resource id.
     */
    CGUIShaderCompiler::CGUIShaderCompiler(const std::string& shader_name, unsigned int vertex_shader_rsid, unsigned int fragment_shader_rsid, unsigned int geometry_shader_rsid)
    {
        debug_handler = CGUIDebugHandler(main_debug_handler);
        debug_handler.post_log("Shader initialization has started.", DEBUG_MODE_LOG);

        add_shader(shader_name, vertex_shader_rsid, fragment_shader_rsid, geometry_shader_rsid);
    }
#endif // Windows

/**
 * @brief      Destroys shader compiler.
 */
CGUIShaderCompiler::~CGUIShaderCompiler()
{
    shader_list.clear();
}


/**
 * @brief      Compiles a new instance of shader program.
 *
 * @param[in]  vertex_shader_rsid   The vertex shader source.
 * @param[in]  fragment_shader_rsid The fragment shader source.
 * @param[in]  geometry_shader_rsid The geometry shader source.
 */
GLuint CGUIShaderCompiler::compile_shader(const std::string& vertex_shader, const std::string& fragment_shader, const std::string& geometry_shader)
{
    int init_status = 0;

    GLuint compiled_vertex;
    GLuint compiled_fragment;
    GLuint compiled_geometry;

    // debug_handler.post_log("\n" + std::string(vertex_shader.begin(), vertex_shader.end()));
    // debug_handler.post_log("\n" + std::string(fragment_shader.begin(), fragment_shader.end()));
    // debug_handler.post_log("\n" + std::string(geometry_shader.begin(), geometry_shader.end()));

    GLuint id = glCreateProgram();

    compiled_vertex = glCreateShader(GL_VERTEX_SHADER);
    const char *source_buffer = vertex_shader.c_str();
    glad_glShaderSource(compiled_vertex, 1, (const GLchar**)&source_buffer, NULL);
    glCompileShader(compiled_vertex);
    if(check_for_errors(compiled_vertex, "VERTEX"))
    {
        glAttachShader(id, compiled_vertex);

        init_status = 1;

        compiled_fragment = glCreateShader(GL_FRAGMENT_SHADER);
        source_buffer = fragment_shader.c_str();
        glShaderSource(compiled_fragment, 1, (const GLchar**)&source_buffer, NULL);
        glCompileShader(compiled_fragment);
        if(check_for_errors(compiled_fragment, "FRAGMENT"))
        {
            glAttachShader(id, compiled_fragment);

            init_status = 2;

            compiled_geometry = glCreateShader(GL_GEOMETRY_SHADER);
            if (std::strcmp(geometry_shader.c_str(), "NONE") != 0)
            {
                source_buffer = geometry_shader.c_str();
                glShaderSource(compiled_geometry, 1, (const GLchar**)&source_buffer, NULL);
                glCompileShader(compiled_geometry);
                if(check_for_errors(compiled_geometry, "GEOMETRY"))
                {
                    glAttachShader(id, compiled_geometry);

                    init_status = 3;
                }
                else 
                {
                    id = 0;
                }          
            }
        }
        else 
        {
            id = 0;
        }
    }
    else 
    {
        id = 0;
    }
    glDeleteShader(compiled_vertex);
    
    if (id != 0)
    {
        glLinkProgram(id);

        if(!check_for_errors(id, "PROGRAM"))
        {
           id = 0;
        }
    }

    if (init_status == 1)
    {
        glDetachShader(id, compiled_vertex);
        glDeleteShader(compiled_vertex);
    }
    if (init_status == 2)
    {
        glDetachShader(id, compiled_fragment);
        glDeleteShader(compiled_fragment);
    }
    if (init_status == 3)
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

    std::string vertex_shader_string;
    std::string fragment_shader_string;
    std::string geometry_shader_string;

    try 
    {
        // Load vertex shader
        vertex_shader_file.open(fs::absolute(vertext_file_path));
        if (vertex_shader_file.is_open())
        {
            vertex_shader_string = std::string((std::istreambuf_iterator<char>(vertex_shader_file)), std::istreambuf_iterator<char>());
            vertex_shader_file.close();
            vertex_shader_string += "\0";
        }
        else 
        {
            debug_handler.post_log(std::string("Unable to open vertex shader file: ") + fs::absolute(vertext_file_path).string(), DEBUG_MODE_ERROR);
        }

        // Load fragment shader
        fragment_shader_file.open(fs::absolute(fragment_file_path));
        if (fragment_shader_file.is_open())
        {
            fragment_shader_string = std::string((std::istreambuf_iterator<char>(fragment_shader_file)), std::istreambuf_iterator<char>());
            fragment_shader_file.close();
            fragment_shader_string += "\0";
        }
        else 
        {
            debug_handler.post_log(std::string("Unable to open fragment shader file: ") + fs::absolute(fragment_file_path).string(), DEBUG_MODE_ERROR);
        }
        
        // Load geometry shader
        if(geometry_file_path != "")
        {
            geometry_shader_file.open(fs::absolute(geometry_file_path));
            if (geometry_shader_file.is_open())
            {
                geometry_shader_string = std::string((std::istreambuf_iterator<char>(geometry_shader_file)), std::istreambuf_iterator<char>());
                geometry_shader_file.close();
                geometry_shader_string += "\0";
            }
            else 
            {
                debug_handler.post_log(std::string("Unable to open geometry shader file: ") + fs::absolute(geometry_file_path).string(), DEBUG_MODE_ERROR);
            }
        }
        else 
        {
            geometry_shader_string = "NONE";
        }
    }
    catch (std::ifstream::failure& e)
    {
        debug_handler.post_log(std::string("Shaders cannot be loaded properly: ") + e.what(), DEBUG_MODE_ERROR);
        return;
    }

    vertex_shader_file.close();
    fragment_shader_file.close();
    geometry_shader_file.close();

    add_shader(shader_name, vertex_shader_string, fragment_shader_string, geometry_shader_string);
}

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
    /**
     * @brief      Adds a shader to map.
     *
     * @param[in]  shader_name          The shader name.
     * @param[in]  vertex_shader_rsid   The vertex shader resource id.
     * @param[in]  fragment_shader_rsid The fragment shader resource id.
     * @param[in]  geometry_shader_rsid The geometry shader resource id.
     */
    void CGUIShaderCompiler::add_shader(const std::string& shader_name, unsigned int vertex_shader_rsid, unsigned int fragment_shader_rsid, unsigned int geometry_shader_rsid)
    {
        std::string vertex_shader_string;
        std::string fragment_shader_string;
        std::string geometry_shader_string;

        HRSRC vertex_shader_resource_object = FindResource(NULL, MAKEINTRESOURCE(vertex_shader_rsid), (LPCSTR)SHADERS);
        if (vertex_shader_resource_object == NULL)
        {
            debug_handler.post_log(std::string("Unable to open vertex shader resource: ") + std::to_string(vertex_shader_rsid) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
        }
        else 
        {
            HGLOBAL vertex_shader_resource = LoadResource(NULL, vertex_shader_resource_object);
            if (vertex_shader_resource == NULL)
            {
                char* error_object = (char*)(LPVOID)vertex_shader_resource_object; 
                debug_handler.post_log(std::string("Unable to load vertex shader resource: ") + std::string(error_object) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
            }
            else 
            {
                LPVOID vertex_shader_void = LockResource(vertex_shader_resource);
                if (vertex_shader_void == NULL)
                {
                    char* error_object = (char*)(LPVOID)vertex_shader_resource;
                    debug_handler.post_log(std::string("Unable to lock vertex shader resource: ") + std::string(error_object) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
                }
                else 
                {
                    DWORD vertex_shader_string_size = SizeofResource(NULL, vertex_shader_resource_object);
                    vertex_shader_string = std::string(static_cast<const char *>(vertex_shader_void), vertex_shader_string_size);
                    vertex_shader_string += "\n";
                }
            }
            FreeResource(vertex_shader_resource);
        }

        HRSRC fragment_shader_resource_object = FindResource(NULL, MAKEINTRESOURCE(fragment_shader_rsid), (LPCSTR)SHADERS);
        if (fragment_shader_resource_object == NULL)
        {
            debug_handler.post_log(std::string("Unable to open fragment shader resource: ") + std::to_string(fragment_shader_rsid) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
        }
        else
        {
            HGLOBAL fragment_shader_resource = LoadResource(NULL, fragment_shader_resource_object);
            if (fragment_shader_resource == NULL)
            {
                char* error_object = (char*)(LPVOID)fragment_shader_resource_object; 
                debug_handler.post_log(std::string("Unable to load fragment shader resource: ") +  std::string(error_object) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
            }
            else 
            {
                LPVOID fragment_shader_void = LockResource(fragment_shader_resource);
                if (fragment_shader_void == NULL)
                {
                    char* error_object = (char*)(LPVOID)fragment_shader_resource; 
                    debug_handler.post_log(std::string("Unable to lock fragment shader resource: ") + std::string(error_object)  + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
                }
                else 
                {
                    DWORD fragment_shader_string_size = SizeofResource(NULL, fragment_shader_resource_object);
                    fragment_shader_string = std::string(static_cast<const char *>(fragment_shader_void), fragment_shader_string_size);
                    fragment_shader_string += "\n";
                }
            }
            FreeResource(fragment_shader_resource);
        }

        if (geometry_shader_rsid == 0)
        {
            geometry_shader_string = "NONE";
        }
        else 
        {
            HRSRC geometry_shader_resource_object = FindResource(NULL, MAKEINTRESOURCE(geometry_shader_rsid), (LPCSTR)SHADERS);
            if (geometry_shader_resource_object == NULL)
            {
                debug_handler.post_log(std::string("Unable to open geometry shader resource: ") + std::to_string(geometry_shader_rsid) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
            }
            else
            {
                HGLOBAL geometry_shader_resource = LoadResource(NULL, geometry_shader_resource_object);
                if (geometry_shader_resource == NULL)
                {
                    char* error_object = (char*)(LPVOID)geometry_shader_resource_object; 
                    debug_handler.post_log(std::string("Unable to load geometry shader resource: ") +  std::string(error_object) + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
                }
                else 
                {
                    LPVOID geometry_shader_void = LockResource(geometry_shader_resource);
                    if (geometry_shader_void == NULL)
                    {
                        char* error_object = (char*)(LPVOID)geometry_shader_resource; 
                        debug_handler.post_log(std::string("Unable to lock geometry shader resource: ") + std::string(error_object)  + " Error code: " + std::to_string(GetLastError()), DEBUG_MODE_ERROR);
                    }
                    else 
                    {
                        DWORD geometry_shader_string_size = SizeofResource(NULL, geometry_shader_resource_object);
                        geometry_shader_string = std::string(static_cast<const char *>(geometry_shader_void), geometry_shader_string_size);
                        geometry_shader_string += "\n";
                    }
                }
                FreeResource(geometry_shader_resource);
            }
        }

        add_shader(shader_name, vertex_shader_string, fragment_shader_string, geometry_shader_string);
    }
#endif // Windows

/**
 * @brief      Adds a shader to map.
 *
 * @param[in]  shader_name      The shader name.
 * @param[in]  vertex_shader    The vertex shader source.
 * @param[in]  fragment_shader  The fragment shader source.
 * @param[in]  geometry_shader  The geometry shader source.
 */
void CGUIShaderCompiler::add_shader(const std::string &shader_name, const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader)
{
    GLuint new_shader_id = compile_shader(vertex_shader, fragment_shader, geometry_shader);
    if (new_shader_id == 0)
    {
        debug_handler.post_log(std::string("Unable to initialize shader with id: ") + std::to_string(new_shader_id) + std::string(" : ") + shader_name, DEBUG_MODE_ERROR);
        return;
    }

    debug_handler.post_log(std::string("Shader with id: ") + std::to_string(new_shader_id) + std::string(" has been successfully initialized: ") + shader_name, DEBUG_MODE_LOG);
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
        debug_handler.post_log(std::string("Shader was successfully removed: ") + shader_name, DEBUG_MODE_LOG);
    }
    else
    {
        debug_handler.post_log(std::string("Unable to find shader: ") + shader_name, DEBUG_MODE_ERROR);
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
        debug_handler.post_log(std::string("Shader was successfully applied: ") + shader_name, DEBUG_MODE_LOG);
    }
    else
    {
        debug_handler.post_log(std::string("Unable to find shader: ") + shader_name, DEBUG_MODE_ERROR);
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
    if(shader_type != "PROGRAM")
    {
        debug_handler.post_log(std::string("Shader is being checked: ") + std::to_string(shader_id), DEBUG_MODE_LOG);
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE)
        {
            debug_handler.post_log(std::string("Unable to compile shader id: ") + std::to_string(shader_id) + std::string(" - ") + shader_type, DEBUG_MODE_ERROR);
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &success);
            std::vector<GLchar> info_log(success);

            glGetShaderInfoLog(shader_id, success, NULL, &info_log[0]);
            debug_handler.post_log(std::string("Shader error log: ") + "\n" + std::string(info_log.begin(), info_log.end()), DEBUG_MODE_ERROR);
            return false;
        }
    }
    else
    {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if(success == GL_FALSE)
        {
            debug_handler.post_log(std::string("Unable to link program id: ") + std::to_string(shader_id) + std::string(" - ") + shader_type, DEBUG_MODE_ERROR);
            glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &success);
            std::vector<GLchar> info_log(success);

            glGetProgramInfoLog(shader_id, success, NULL, &info_log[0]);
            debug_handler.post_log(std::string("Program error log: ") + "\n" + std::string(info_log.begin(), info_log.end()), DEBUG_MODE_ERROR);
            return false;
        }
    }
    return true;
}