#include "measurement.hpp"

#include <cppformat/ostream.h>

#include <stdexcept>
#include <iomanip>

namespace idb
{
    namespace api
    {
        namespace measurement
        {
            measurement&    measurement::operator<<(const tag &t)
            {
                m_tags.push_back(t);
                return *this;
            }
            measurement&    measurement::operator<<(tag &&t)
            {
                m_tags.emplace_back(t);
                return *this;
            }

            measurement&    measurement::operator<<(const field &f)
            {
                m_fields.push_back(f);
                return *this;
            }
            measurement&    measurement::operator<<(field &&f)
            {
                m_fields.emplace_back(f);
                return *this;
            }

            const std::string measurement::line() const
            {
                if (m_fields.empty())
                { std::runtime_error(std::string("measurement should have at least one field set.")); }

                fmt::MemoryWriter line;
                line << std::quoted(m_name);
                for (const auto &t : m_tags)
                { line << "," << std::quoted(t.key()) << "=" << std::quoted(t.value()); }
                auto count = 0;
                for (const auto &f : m_fields)
                {
                    if (count > 0)
                    { line << ","; }
                    else
                    { line << " "; }
                    line << std::quoted(f.key()) << "=" << std::quoted(f.value());
                    ++count;
                }
                return line.str();
            }
        }
    }
}
