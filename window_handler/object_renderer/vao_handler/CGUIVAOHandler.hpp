/**
 * @file       <CGUIVAOHandler.hpp>
 * @brief      This header file implements CGUIVAOHandler class.
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
#ifndef CGUIVAOHANDLER_HPP
#define CGUIVAOHANDLER_HPP

/**
 * Include GLFW and GLAD for window handling.
 */
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../vbo_handler/CGUIVBOHandler.hpp"

class CGUIVAO
{
public:
    CGUIVAO(bool is_buffer_static = false);
    ~CGUIVAO();

    void bind();
    void unbind();
    void destroy();

    bool is_static();

    void link_attributes(CGUIVBO& VBO, GLuint layout, GLuint components_number, GLenum type, GLsizeiptr byte_offset, void* offset);

private:
    bool    buffer_static;
    GLuint  buffer_id;
};

#endif // CGUIVAOHANDLER_HPP
