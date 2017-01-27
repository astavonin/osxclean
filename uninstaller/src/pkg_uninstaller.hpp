#pragma once

#include "uninstaller_impl.hpp"

namespace uninstaller
{
class pkg_uninstaller : public uninstaller
{
public:
    pkg_uninstaller( const std::string &pkg_name, bool is_regexp = false );
    virtual ~pkg_uninstaller();

    virtual objects_list uninstall( const objects_list &objs ) override;
    virtual objects_list dry_run() override;

private:
    void load_pkg_info( const std::string pkg_name );

private:
    fs::path    m_pkg_location;
    std::string m_pkg_name;
    bool        m_is_regexp;
};
}
