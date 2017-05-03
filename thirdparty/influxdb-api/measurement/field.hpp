#pragma once

#include <string>
#include <utility>

namespace idb
{
    namespace api
    {
        namespace measurement
        {
            class field
            {
                public:
                    field() = delete;
                    field(const std::string &f, const std::string &v) : m_key(f), m_value(v) {}
                    field(std::string &&f, std::string &&v) : m_key(std::move(f)), m_value(std::move(v)) {}
                    field(const field &f) : m_key(f.m_key), m_value(f.m_value) {}
                    field(field &&f) : m_key(std::move(f.m_key)), m_value(std::move(f.m_value)) {}

                    inline const std::string &key() const
                    { return m_key; }

                    inline const std::string &value() const
                    { return m_value; }

                private:
                    const std::string m_key;
                    const std::string m_value;
            };
        }
    }
}