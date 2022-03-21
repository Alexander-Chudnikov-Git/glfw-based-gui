/**
 * @file       <CGUIDataTypes.hpp>
 * @brief      This header file implements all of the CGUIDataTypes's structures. 
 *             
 *             It is being used in order to add some custom datatypes for easier 
 *             glfw usage.
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
 * @copyright  Copyright 2022 Alexande. All rights reserved. 
 * 
 *             (Not really)
 * 
 * @license    This project is released under the GNUv3 Public License.
 * 
 * @todo       Implement the whole class.
 */

struct CGUIPointd;

/**
 * @brief      Structure for integer points 
 */
struct CGUIPointi
{
    int x;
    int y;

    CGUIPointi operator+=(CGUIPointi const& right_value);
    CGUIPointi operator+=(CGUIPointd const& right_value);
    CGUIPointi operator+=(int& right_value);
    CGUIPointi operator+=(double& right_value);

    CGUIPointi operator-=(CGUIPointi const& right_value);
    CGUIPointi operator-=(CGUIPointd const& right_value);
    CGUIPointi operator-=(int& right_value);
    CGUIPointi operator-=(double& right_value);
};

/**
 * @brief      Structure for double points
 */
struct CGUIPointd
{
    double x;
    double y;

    CGUIPointd operator+=(CGUIPointi const& right_value);
    CGUIPointd operator+=(CGUIPointd const& right_value);
    CGUIPointd operator+=(int& right_value);
    CGUIPointd operator+=(double& right_value);

    CGUIPointd operator-=(CGUIPointi const& right_value);
    CGUIPointd operator-=(CGUIPointd const& right_value);
    CGUIPointd operator-=(int& right_value);
    CGUIPointd operator-=(double& right_value);
};

CGUIPointi operator+(CGUIPointi left_value, CGUIPointi right_value);
CGUIPointi operator+(CGUIPointi left_value, CGUIPointd right_value);
CGUIPointi operator+(CGUIPointi left_value, int right_value);
CGUIPointi operator+(CGUIPointi left_value, double right_value);

CGUIPointi operator-(CGUIPointi left_value, CGUIPointi right_value);
CGUIPointi operator-(CGUIPointi left_value, CGUIPointd right_value);
CGUIPointi operator-(CGUIPointi left_value, int right_value);
CGUIPointi operator-(CGUIPointi left_value, double right_value);

bool operator==(CGUIPointi left_value, CGUIPointi right_value);
bool operator==(CGUIPointi left_value, CGUIPointd right_value);

bool operator!=(CGUIPointi left_value, CGUIPointi right_value);
bool operator!=(CGUIPointi left_value, CGUIPointd right_value);

CGUIPointd operator+(CGUIPointd left_value, CGUIPointi right_value);
CGUIPointd operator+(CGUIPointd left_value, CGUIPointd right_value);
CGUIPointd operator+(CGUIPointd left_value, int right_value);
CGUIPointd operator+(CGUIPointd left_value, double right_value);

CGUIPointd operator-(CGUIPointd left_value, CGUIPointi right_value);
CGUIPointd operator-(CGUIPointd left_value, CGUIPointd right_value);
CGUIPointd operator-(CGUIPointd left_value, int right_value);
CGUIPointd operator-(CGUIPointd left_value, double right_value);

bool operator==(CGUIPointd left_value, CGUIPointi right_value);
bool operator==(CGUIPointd left_value, CGUIPointd right_value);

bool operator!=(CGUIPointd left_value, CGUIPointi right_value);
bool operator!=(CGUIPointd left_value, CGUIPointd right_value);