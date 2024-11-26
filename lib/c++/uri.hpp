/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _CXX_URI_H
#define _CXX_URI_H

#include <c++/own_ptr.hpp>
#include <c++/print.hpp>

#include <stdexcept>
#include <vector>
#include <string>

namespace system
{
    // Accessors are like iterators, but with an offset.
    using uri_accessor = int32_t;

    class uri_parser final
    {
    public:
        explicit uri_parser(const char* protocol);
        virtual ~uri_parser();

        uri_parser& operator=(const uri_parser&) = default;
        uri_parser(const uri_parser&) = default;

        std::string get(const uri_accessor offset = 0) noexcept;

    public:
        uri_parser& operator/=(const std::string& uri);
        uri_parser& operator/=(const char* uri);

    private:
        std::string m_protocol;
        std::vector<char> m_data;

    };

    class uri_error final : public std::runtime_error
    {
    public:
        explicit uri_error(uri_parser& uri) : std::runtime_error("uri_error"), m_uri(uri) {}
        ~uri_error() = default; // let the ABI define that.

        uri_error& operator=(const uri_error&) = default;
        uri_error(const uri_error&) = default;

        uri_parser& get();

    private:
        uri_parser m_uri;

    };
}

#endif /* ifndef _CXX_URI_H */
