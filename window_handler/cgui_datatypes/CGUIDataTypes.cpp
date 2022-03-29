/**
 * @file       <CGUIDataTypes.cpp>
 * @brief      This source file implements CGUIDataTypes class. 
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

#include "CGUIDataTypes.hpp"


/********************************************************************************
 *                            CGUIPointi structure                              *
 ********************************************************************************/

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointi CGUIPointi::operator+=(CGUIPointi const& right_value)
{
    x += right_value.x;
    y += right_value.y;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointi CGUIPointi::operator+=(CGUIPointd const& right_value)
{
    x += right_value.x;
    y += right_value.y;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv int.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointi CGUIPointi::operator+=(int& right_value)
{
    x += right_value;
    y += right_value;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv double.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointi CGUIPointi::operator+=(double& right_value)
{
    x += right_value;
    y += right_value;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv CGUIPointi
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointi CGUIPointi::operator-=(CGUIPointi const& right_value)
{
    x -= right_value.x;
    y -= right_value.y;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv CGUIPointd
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointi CGUIPointi::operator-=(CGUIPointd const& right_value)
{
    x -= right_value.x;
    y -= right_value.y;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv int
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointi CGUIPointi::operator-=(int& right_value)
{
    x -= right_value;
    y -= right_value;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv double
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointi CGUIPointi::operator-=(double& right_value)
{
    x -= right_value;
    y -= right_value;
    return *this;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition
 */
CGUIPointi operator+(CGUIPointi left_value, CGUIPointi right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x + right_value.x;
    ret_val.y = left_value.y + right_value.y;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition
 */
CGUIPointi operator+(CGUIPointi left_value, CGUIPointd right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x + right_value.x;
    ret_val.y = left_value.y + right_value.y;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv int.
 *
 * @return     The result of the addition
 */
CGUIPointi operator+(CGUIPointi left_value, int right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x + right_value;
    ret_val.y = left_value.y + right_value;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv double.
 *
 * @return     The result of the addition
 */
CGUIPointi operator+(CGUIPointi left_value, double right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x + right_value;
    ret_val.y = left_value.y + right_value;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition
 */
CGUIPointi operator-(CGUIPointi left_value, CGUIPointi right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x - right_value.x;
    ret_val.y = left_value.y - right_value.y;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition
 */
CGUIPointi operator-(CGUIPointi left_value, CGUIPointd right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x - right_value.x;
    ret_val.y = left_value.y - right_value.y;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv int.
 *
 * @return     The result of the addition
 */
CGUIPointi operator-(CGUIPointi left_value, int right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x - right_value;
    ret_val.y = left_value.y - right_value;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv double.
 *
 * @return     The result of the addition
 */
CGUIPointi operator-(CGUIPointi left_value, double right_value)
{
    CGUIPointi ret_val;
    ret_val.x = left_value.x - right_value;
    ret_val.y = left_value.y - right_value;
    return ret_val;
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the equality
 */
bool operator==(CGUIPointi left_value, CGUIPointi right_value)
{
    return (left_value.x == right_value.x) && (left_value.y == right_value.y);
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the equality
 */
bool operator==(CGUIPointi left_value, CGUIPointd right_value)
{
    return (left_value.x == right_value.x) && (left_value.y == right_value.y);
}

/**
 * @brief      Inequality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the inequality
 */
bool operator!=(CGUIPointi left_value, CGUIPointi right_value)
{
    return (left_value.x != right_value.x) || (left_value.y != right_value.y);
}

/**
 * @brief      Inequality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointi.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the inequality
 */
bool operator!=(CGUIPointi left_value, CGUIPointd right_value)
{
    return (left_value.x != right_value.x) || (left_value.y != right_value.y);
}

/********************************************************************************
 *                            CGUIPointd structure                              *
 ********************************************************************************/

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointd CGUIPointd::operator+=(CGUIPointi const& right_value)
{
    x += right_value.x;
    y += right_value.y;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointd CGUIPointd::operator+=(CGUIPointd const& right_value)
{
    x += right_value.x;
    y += right_value.y;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv int.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointd CGUIPointd::operator+=(int& right_value)
{
    x += right_value;
    y += right_value;
    return *this;
}

/**
 * @brief      Addition assignment operator for CGUIPointi.
 *
 * @param      right_value  Value of rv double.
 *
 * @return     The result of the addition assignment.
 */
CGUIPointd CGUIPointd::operator+=(double& right_value)
{
    x += right_value;
    y += right_value;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv CGUIPointi
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointd CGUIPointd::operator-=(CGUIPointi const& right_value)
{
    x -= right_value.x;
    y -= right_value.y;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv CGUIPointd
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointd CGUIPointd::operator-=(CGUIPointd const& right_value)
{
    x -= right_value.x;
    y -= right_value.y;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv int
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointd CGUIPointd::operator-=(int& right_value)
{
    x -= right_value;
    y -= right_value;
    return *this;
}

/**
 * @brief      Subtraction assignment operator.
 *
 * @param      right_value  Value of rv double
 *
 * @return     The result of the subtraction assignment
 */
CGUIPointd CGUIPointd::operator-=(double& right_value)
{
    x -= right_value;
    y -= right_value;
    return *this;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition
 */
CGUIPointd operator+(CGUIPointd left_value, CGUIPointi right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x + right_value.x;
    ret_val.y = left_value.y + right_value.y;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition
 */
CGUIPointd operator+(CGUIPointd left_value, CGUIPointd right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x + right_value.x;
    ret_val.y = left_value.y + right_value.y;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv int.
 *
 * @return     The result of the addition
 */
CGUIPointd operator+(CGUIPointd left_value, int right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x + right_value;
    ret_val.y = left_value.y + right_value;
    return ret_val;
}

/**
 * @brief      Addition operator overload.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv double.
 *
 * @return     The result of the addition
 */
CGUIPointd operator+(CGUIPointd left_value, double right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x + right_value;
    ret_val.y = left_value.y + right_value;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the addition
 */
CGUIPointd operator-(CGUIPointd left_value, CGUIPointi right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x - right_value.x;
    ret_val.y = left_value.y - right_value.y;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the addition
 */
CGUIPointd operator-(CGUIPointd left_value, CGUIPointd right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x - right_value.x;
    ret_val.y = left_value.y - right_value.y;
    return ret_val;
}


/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv int.
 *
 * @return     The result of the addition
 */
CGUIPointd operator-(CGUIPointd left_value, int right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x - right_value;
    ret_val.y = left_value.y - right_value;
    return ret_val;
}

/**
 * @brief      Substraction operator overlad.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv double.
 *
 * @return     The result of the addition
 */
CGUIPointd operator-(CGUIPointd left_value, double right_value)
{
    CGUIPointd ret_val;
    ret_val.x = left_value.x - right_value;
    ret_val.y = left_value.y - right_value;
    return ret_val;
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the equality
 */
bool operator==(CGUIPointd left_value, CGUIPointi right_value)
{
    return (left_value.x == right_value.x) && (left_value.y == right_value.y);
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the equality
 */
bool operator==(CGUIPointd left_value, CGUIPointd right_value)
{
    return (left_value.x == right_value.x) && (left_value.y == right_value.y);
}

/**
 * @brief      Inequality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointi.
 *
 * @return     The result of the inequality
 */
bool operator!=(CGUIPointd left_value, CGUIPointi right_value)
{
    return (left_value.x != right_value.x) || (left_value.y != right_value.y);
}

/**
 * @brief      Inequality operator.
 *
 * @param[in]  left_value   Value of lv CGUIPointd.
 * @param[in]  right_value  Value of rv CGUIPointd.
 *
 * @return     The result of the inequality
 */
bool operator!=(CGUIPointd left_value, CGUIPointd right_value)
{
    return (left_value.x != right_value.x) || (left_value.y != right_value.y);
}

