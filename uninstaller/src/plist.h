#pragma once

#include <map>
#include <string>

namespace uninstaller
{
class plist
{
public:
    plist( const std::string &path );

    inline std::string get_value( const std::string &name ) const
    {
        return m_nodes.at( name );
    }

private:
    std::map<std::string, std::string> m_nodes;
};
}
