/**
 * @file       <CGUIVertexSpecification.hpp>
 * @brief      This source file implements CGUIVertexSpecification class. 
 *             
 *             It is being used in order to create main window, that would 
 *             be populated with UI elements specific for this project.
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
#ifndef CGUIVERTEXSPECIFICATION_HPP
#define CGUIVERTEXSPECIFICATION_HPP

#include "./ebo_handler/CGUIEBOHandler.hpp"
#include "./vao_handler/CGUIVAOHandler.hpp"


class CGUIObjectRenderer
{
public:
    CGUIObjectRenderer();

    void add_object(CGUIObject new_object);
    void draw();


private:

};

#endif // CGUIVERTEXSPECIFICATION_HPP