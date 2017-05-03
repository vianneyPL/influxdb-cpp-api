#pragma once

#include "measurement/tag.hpp"
#include "measurement/field.hpp"

#include <string>
#include <vector>

namespace idb
{
    namespace api
    {
        namespace measurement
        {
            class measurement
            {
                public:
                    measurement() = delete;
                    measurement(const std::string &name) : m_name(name) {}
                    measurement(const measurement &) = default;
                    measurement(measurement &&) = default;

                    measurement&    operator<<(const tag &t);
                    measurement&    operator<<(tag &&t);

                    measurement&    operator<<(const field &v);
                    measurement&    operator<<(field &&v);

                    const std::string line() const;

                    inline const std::string &name() const;

                private:
                    const std::string   m_name;
                    std::vector<tag>    m_tags;
                    std::vector<field>  m_fields;
                    
            };

            const std::string &measurement::name() const
            { return m_name; }
        }
    }
}