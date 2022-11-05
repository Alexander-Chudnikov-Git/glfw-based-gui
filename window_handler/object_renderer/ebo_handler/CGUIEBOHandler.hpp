/**
 * @file       <CGUIEBOHandler.hpp>
 * @brief      This header file implements CGUIEBOHandler class. 
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
#ifndef CGUIEBOHANDLER_HPP
#define CGUIEBOHANDLER_HPP

#include <vector> 

/**
 * Include GLFW and GLAD for window handling.
 */
#include "../../glad/glad.h"
#include "../../glfw/include/GLFW/glfw3.h"

class CGUIEBO 
{
public:
    CGUIEBO(std::vector<GLuint>& indices, bool is_buffer_static = false);
    ~CGUIEBO();

    void bind();
    void unbind();
    void destroy();

    bool is_static();

private:
    bool    buffer_static;
    GLuint  buffer_id;

};

#endif // CGUIEBOHANDLER_HPP