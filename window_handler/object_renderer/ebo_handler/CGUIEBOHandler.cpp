/**
 * @file       <CGUIEBOHandler.cpp>
 * @brief      This source file implements CGUIEBOHandler class. 
 *             
 *             It is being used in order to initialize eiter static or dynamic 
 *             vbo, that later can be used in order to draw objects via GLFW.
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
#include "CGUIEBOHandler.hpp"


/**
 * @brief      Constructs a new EBO.
 *
 * @param      indices           Vector of indices.
 * @param[in]  is_buffer_static  Indicates if buffer static
 */
CGUIEBO::CGUIEBO(std::vector<GLuint>& indices, bool is_buffer_static)
{
    buffer_static = is_buffer_static;

    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), (buffer_static == true) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}


/**
 * @brief      Binds EBO.
 */
void CGUIEBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

/**
 * @brief      Unbinds EBO.
 */
void CGUIEBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * @brief      Deletes EBO.
 */
void CGUIEBO::destroy()
{
    glDeleteBuffers(1, &buffer_id);
}

/**
 * @brief      Determines if EBO is static.
 *
 * @return     True if static, False otherwise.
 */
bool CGUIEBO::is_static()
{
    return buffer_static;
}

