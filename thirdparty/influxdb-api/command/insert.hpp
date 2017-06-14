#pragma once

#include "../command.hpp"

namespace idb
{
namespace api
{
namespace command
{
class insert : public command<insert>
{
public:
    using tag = execution_tag::post;
    insert(const std::string & base_uri) : command(base_uri)
    {
    }
    inline void setPath()
    {
        m_url += "/write";
        m_request->SetOption(m_url);
    }
    inline void prepareStatement(const std::string & dbname, const measurement::measurement & measurement)
    {
        auto line = measurement.line();
        auto body = cpr::Body{line};
        auto header = cpr::Header{{"Content-Length", std::to_string(line.size())}};
        auto parameters = cpr::Parameters{{"db", dbname}};
        std::cout << "body: " << body << "\n";
        m_request->SetOption(header);
        m_request->SetOption(parameters);
        m_request->SetOption(body);
    }
    inline void prepareStatement(const std::string & dbname, const measurement::measurements & measurements)
    {
        auto line = measurements.line();
        auto body = cpr::Body(line);
        auto header = cpr::Header{{"Content-Length", std::to_string(line.size())}};
        auto parameters = cpr::Parameters{{"db", dbname}};
        std::cout << "body s: " << body << "\n";
        m_request->SetOption(header);
        m_request->SetOption(parameters);
        m_request->SetOption(body);
    }
};
}
}
}