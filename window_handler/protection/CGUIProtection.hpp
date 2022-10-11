/**
 * @file       <CGUIProtection.hpp>
 * @brief      This header file implements CGUIProtection class. 
 *             
 *             It is being used in order to protect program from basic 
 * 		       ways of reverse engineering.
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
#ifndef CGUIPROTECTION_HPP
#define CGUIPROTECTION_HPP

#include <memory>
#include <cmath>
#include <array>


class CGUIObfuscatedString
{
public:
    CGUIObfuscatedString();
    ~CGUIObfuscatedString();

    /**
     * @brief      Generation of random line with length of n by using uniform distribution
     *
     * @tparam     N     Length of generated line
     *
     * @return     Pseuorandom line with the lenght of N
     */
    template<typename T, std::size_t N, std::size_t LINE>
        static constexpr const std::array<T, N> cgi_r()
        {
            std::array<T, N> key {0};

            constexpr auto distribution = uniform_distribution<int, N>(0, 255, LINE);

            for (std::size_t i = 0; i < N; ++i) 
            {
                key[i] = distribution.at(i);
            }

            return key;
        }

    /**
     * @brief       Constexpr uniform distribuion as an array
     *              
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @param[in]   min   Minimum distribution value
     * @param[in]   max   Maximum distribution value
     *
     * @tparam      T     Typename of min/max value
     * @tparam      SIZE  Size of normalized uniform distribution
     *
     * @return      std::array of uniformely distributed values in the range of [min, max] 
     */
    template <typename T, std::size_t SIZE>
        static constexpr std::array<T, SIZE> uniform_distribution(T min, T max, std::size_t line)
        {
            std::array<T, SIZE> distribution{};
            auto previous = constexpr_seed(line);
            for (auto &element : distribution) 
            {
                element = static_cast<T>(uniform_distribution_n(previous) * (max - min) + min);
            }
            
            return distribution;
        }

    /**
     * @brief       Constexpr normal distribuion as an array
     *              
     *              Normal distribution is being approximated by the Irwin-Hall distribution
     *
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @param[in]  mean         Irwin-Hall mean
     * @param[in]  sigma        Irwin-Hall sigma
     *
     * @tparam     T            Typename of min/max value
     * @tparam     SIZE         Size of normalized uniform distribution
     * @tparam     IRWIN_NUM    Irwin distribution numbers
     *
     * @return     { description_of_the_return_value }
     */
    template <typename T, std::size_t SIZE, std::size_t IRWIN_NUM = 12>
        static constexpr std::array<T, SIZE> normal_distribution()
        {
            std::array<T, SIZE> distribution{};
            auto previous = constexpr_seed(0);
            for (auto &element : distribution) 
            {
                double value = 0;
                for (std::size_t i = 0; i < IRWIN_NUM; ++i)
                {
                    value += uniform_distribution_n(previous);
                }

                element = value / std::sqrt(IRWIN_NUM / 12.0f) - IRWIN_NUM / 2.0f;
            }

            return distribution;
        }

    /**
     * @brief      Encrypts string at comple time
     *
     * @param      initial_string  The initial string
     * @param      string_length   Length on the initial string
     * 
     * @tparam     key             The key for encryption
     * @tparam     key_length      Length on the encryption key
     *
     * @return     Encrypted string
     */
    template <std::size_t STRING_LENGTH, std::size_t KEY_LENGTH>
        static constexpr const std::array<char, STRING_LENGTH + 2 + (STRING_LENGTH % 2)> string_encrypt(const char* initial_string, std::array<char, KEY_LENGTH> key)
        {
            std::size_t new_buffer_length = STRING_LENGTH + (2 + (STRING_LENGTH % 2));

            std::array<char, STRING_LENGTH + 2 + (STRING_LENGTH % 2)> encryptred_data{0};
            std::array<char, STRING_LENGTH + 2 + (STRING_LENGTH % 2)> encryption_buffer{0};

            for(std::size_t index = 0; index < new_buffer_length; ++index)
            {
                if (index >= STRING_LENGTH)
                {
                    encryption_buffer[index] = key[new_buffer_length % KEY_LENGTH] ^ key[0];
                }
                else 
                {
                    encryption_buffer[index] = initial_string[index];
                }
            }

            for(std::size_t index = 0; index < new_buffer_length; index += 2)
            {
                encryptred_data[index]      = (encryption_buffer[index] & 0b10101010) + (encryption_buffer[index + 1] & 0b01010101);
                encryptred_data[index + 1]  = (encryption_buffer[index] & 0b01010101) + (encryption_buffer[index + 1] & 0b10101010);
            }

            for(std::size_t index = 0; index < new_buffer_length; ++index)
            {
                encryptred_data[index] = encryptred_data[index] ^ (key[index % (KEY_LENGTH / sizeof(char))] + index);
            }

            return encryptred_data;
        }

    /**
     * @brief       Decrypts string at comple time
     *
     * @param       initial_string  The initial string
     * @param       string_length   Length on the initial string 
     * 
     * @tparam      key             The key for decryption
     * @tparam      key_length      Length on the decryption key
     *
     * @return      Decrypts string
     */
    template <std::size_t STRING_LENGTH, std::size_t KEY_LENGTH>
        static inline const std::array<char, STRING_LENGTH> string_decrypt(std::array<char, STRING_LENGTH + 2 + (STRING_LENGTH % 2)> initial_string, std::array<char, KEY_LENGTH> key)
        {
            std::size_t new_buffer_length = STRING_LENGTH + 2 + (STRING_LENGTH % 2);

            std::array<char, STRING_LENGTH> decryptred_data{0};
            char* decryptred_buffer = new char[new_buffer_length]; 
            char* decryptred_mid_buffer = new char[new_buffer_length]; 

            for(std::size_t index = 0; index < new_buffer_length; ++index)
            {
                decryptred_buffer[index] = initial_string[index] ^ (key[index % (KEY_LENGTH / sizeof(char))] + index);
            }

            for(std::size_t index = 0; index < new_buffer_length; index += 2)
            {
                decryptred_mid_buffer[index]        = (decryptred_buffer[index] & 0b10101010) + (decryptred_buffer[index + 1] & 0b01010101);
                decryptred_mid_buffer[index + 1]    = (decryptred_buffer[index] & 0b01010101) + (decryptred_buffer[index + 1] & 0b10101010);
            }

            for(std::size_t index = 0; index < new_buffer_length; ++index)
            {
                if (index >= STRING_LENGTH)
                {
                    if (decryptred_mid_buffer[index] != (key[new_buffer_length % KEY_LENGTH] ^ key[0]))
                    {
                        auto temp = CGUIObfuscatedString::cgi_r<char, STRING_LENGTH, STRING_LENGTH>();

                        for(std::size_t index_inside = 0; index_inside < STRING_LENGTH; ++index_inside)
                        {
                            decryptred_data[index_inside] = temp[index_inside];
                        }
                        break;
                    }
                }
                else 
                {
                    decryptred_data[index] = decryptred_mid_buffer[index];
                }
            }

            delete[] decryptred_buffer;
            delete[] decryptred_mid_buffer;

            decryptred_mid_buffer = nullptr;
            decryptred_buffer     = nullptr;

            return decryptred_data;
        }

private:
    /**
     * @brief       Constexpr implemenatation of ctoi
     * 
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @param[in]   str     String, that shoild be converted to ineger
     * @param[in]   offset  String offset
     *
     * @return      Converted integer
     */
    static constexpr unsigned int constexpr_ctoi(const char* str, int offset)
    {
        return static_cast<std::uint32_t>(str[offset] - '0') * 10 + static_cast<std::uint32_t>(str[offset + 1] - '0');
    }

    /**
     * @brief       Constexpr implemenatation of creating seed from __TIME__ and __DATE__
     * 
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @return      Seed for pseudorandom generator
     */
    static constexpr unsigned int constexpr_seed(std::size_t line)
    {
        auto compile_time = __TIME__;
        auto compile_date = __DATE__;
        return constexpr_ctoi(compile_time, 0) * 60 * 60 + constexpr_ctoi(compile_time, 3) * 60 + constexpr_ctoi(compile_time, 6) + constexpr_ctoi(compile_date, 5) * 24 * 60 * 60 - line;
    }

    /**
     * @brief       Constexpr uniform distribuion
     *              
     *              Previous value is passed by refeerence due to the lack of static values
     *              
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @param[in]   previous    Previous value
     *
     * @return      Uniformely distributed value in the range of [0, 714025]
     */
    static constexpr std::uint32_t uniform_distribution(std::uint32_t &previous)
    {
        previous = ((lce_a * previous + lce_c) % lce_m);
        return previous;
    }

    /**
     * @brief       Constexpr normalzed uniform distribuion
     * 
     *              Previous value is passed by refeerence due to the lack of static values
     *              
     *              All credit goes to Mikhail Klimenko and his article "Constexpr pseudorandom numbers"
     *              https://mklimenko.github.io/english/2018/06/04/constexpr-random/
     *
     * @param       previous    Previous value
     *
     * @return      Uniformely distributed value in the range of [0.0, 1.0]
     */
    static constexpr double uniform_distribution_n(std::uint32_t &previous)
    {
        auto distribution = uniform_distribution(previous);
        return static_cast<double>(distribution) / lce_m;
    }

protected:

    constexpr static const std::uint32_t lce_a = 4096;
    constexpr static const std::uint32_t lce_c = 150889;
    constexpr static const std::uint32_t lce_m = 714025;
};

#ifndef __CGUI_OBF_KEY__
    #define __CGUI_OBF_KEY__ CGUIObfuscatedString::cgi_r<char, 64, 0>()
#endif

#ifndef __CGUI_OBF_KEY_C__
    #define __CGUI_OBF_KEY_C__(line) CGUIObfuscatedString::cgi_r<char, 64, line>()
#endif

#define __CGUI_OBF_GENERIC__(data, key) \
    []() -> std::string { \
        constexpr auto str_len = (__builtin_strlen(data)); \
        constexpr auto key_len = key.size(); \
        constexpr auto encrypted_data = CGUIObfuscatedString::string_encrypt<str_len, key_len>(data, key); \
        thread_local auto obfuscated_data = CGUIObfuscatedString::string_decrypt<str_len, key_len>(encrypted_data, key); \
        return std::string(obfuscated_data.cbegin(), obfuscated_data.cend()); \
    }()

// Those defines are only usable with static strings, it is not sutable for encrypting runtime variables
#define __CGUI_OBF__(data) __CGUI_OBF_GENERIC__(data, __CGUI_OBF_KEY__)
#define __CGUI_OBF_S__(data) __CGUI_OBF_GENERIC__(data, __CGUI_OBF_KEY_C__(__COUNTER__ + 1))
#endif // CGUIPROTECTION_HPP