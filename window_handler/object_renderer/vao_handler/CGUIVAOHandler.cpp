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
#include "CGUIVAOHandler.hpp"

CGUIVAO::CGUIVAO(bool is_buffer_static)
{
    buffer_static = is_buffer_static;

    glGenVertexArrays(1, &buffer_id);
}

// Binds the VAO
void CGUIVAO::bind()
{
    glBindVertexArray(buffer_id);
}

// Unbinds the VAO
void CGUIVAO::unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO
void CGUIVAO::destroy()
{
    glDeleteVertexArrays(1, &buffer_id);
}

void CGUIVAO::link_attributes(CGUIVBO& VBO, GLuint layout, GLuint components_number, GLenum type, GLsizeiptr byte_offset, void* offset)
{
    VBO.bind();
    glVertexAttribPointer(layout, components_number, type, GL_FALSE, byte_offset, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}
