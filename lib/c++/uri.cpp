/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <c++/uri.hpp>
#include <cstring>

constexpr const size_t kUriSz = 1024U;
constexpr const char kUriSeparator = '\a';

namespace system
{
    uri_parser::uri_parser(const char* protocol) : m_protocol(protocol) {}

    uri_parser::~uri_parser() = default;

    std::string uri_parser::get(const uri_accessor offset) noexcept
    {
        if (m_data.empty())
            return (m_protocol + "invalid");

        std::string uri;

        for (size_t i = 0; i < m_data.size(); i++)
        {
            if (m_data[offset] == kUriSeparator)
            break;

            uri.push_back(m_data[i]);
        }

        return uri;
    }

    uri_parser& uri_parser::operator/=(const std::string& uri)
    {
        this->operator/=(uri.c_str());

        return *this;
    }

    uri_parser& uri_parser::operator/=(const char* uri)
    {
        if (!uri ||
            *uri == 0)
            return *this;

        if (!std::strstr(const_cast<char*>(uri), m_protocol.c_str()))
            return *this;

        int32_t count = 0;

        for (size_t i = strnlen(m_protocol.c_str(), kUriSz); i < strlen(uri); ++i)
        {
            if (uri[i] == '\\' || uri[i] == '/')
                m_data.push_back(kUriSeparator);
            else
                m_data.push_back(uri[i]);
        }

        return *this;
    }

    uri_parser& uri_error::get() { return m_uri; }
}
