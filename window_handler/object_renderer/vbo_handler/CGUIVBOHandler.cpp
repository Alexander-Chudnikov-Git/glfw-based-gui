/**
 * @file       <CGUIVBOHandler.cpp>
 * @brief      This source file implements CGUIVBOHandler class. 
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
#include "CGUIVBOHandler.hpp"

/**
 * @brief      Constructs a new VBO.
 *
 * @param      vertices          Vertecies vector
 * @param[in]  is_buffer_static  Indicates if buffer is static
 */
CGUIVBO::CGUIVBO(std::vector<CGUIVertex>& vertices, bool is_buffer_static)
{
    buffer_static = is_buffer_static;
    
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGUIVertex), vertices.data(), (buffer_static == true) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

/**
 * @brief      Binds VBO.
 */
void CGUIVBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

/**
 * @brief      Unbinds VBO.
 */
void CGUIVBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * @brief      Deletes VBO.
 */
void CGUIVBO::destroy()
{
    glDeleteBuffers(1, &buffer_id);
}

/**
 * @brief      Determines if VBO is static.
 *
 * @return     True if static, False otherwise.
 */
bool CGUIVBO::is_static()
{
    return buffer_static;
}