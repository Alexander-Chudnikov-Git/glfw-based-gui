/**
 * @file       <CGUIVBOHandler.hpp>
 * @brief      This header file implements CGUIVBOHandler class. 
 *             
 *             It is being used in order to initialize eiter static or dynamic 
 *             vbo, that later can be used in order to draw objects via GLFW.
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
#ifndef CGUIVBOHANDLER_HPP
#define CGUIVBOHANDLER_HPP

/**
 * Include GLFW and GLAD for window handling.
 */
#include "../../glad/glad.h"
#include "../../glfw/include/GLFW/glfw3.h"
#include "../../glm/glm/glm.hpp"


/**
 * Standart vretex, that is being used universaly.
 */
struct CGUIVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 tx_position;
};


class CGUIVBO 
{
public:
    CGUIVBO(bool buffer_static = false); 
    CGUIVBO(const CGUIVBO&) = delete;
    ~CGUIVBO();


};

#endif // CGUIVBOHANDLER_HPP