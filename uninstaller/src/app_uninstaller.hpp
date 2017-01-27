#pragma once

#include "uninstaller_impl.hpp"

namespace uninstaller
{
class app_uninstaller : public uninstaller_base
{
public:
    app_uninstaller( const std::string &app_name );
    virtual ~app_uninstaller();

    virtual objects_list uninstall( const objects_list &objs ) override;
    virtual objects_list dry_run() override;

private:
    std::string m_app_name;
};
}
