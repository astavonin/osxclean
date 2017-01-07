#pragma once

#include <uninstaller.h>

namespace uninstaller
{
class app_uninstaller : public uninstaller
{
public:
    app_uninstaller( const std::string &app_name );
    virtual ~app_uninstaller();

    virtual void                uninstall() override;
    virtual std::vector<object> dry_run() override;

private:
    std::string m_app_name;
};
}
