#pragma once

#include <uninstaller.hpp>

namespace uninstaller
{
class uninstaller_impl : public uninstaller
{
public:
    uninstaller_impl( const std::string &filter, filter_type type,
                      bool isRegexp );
    virtual ~uninstaller_impl();

    virtual void                uninstall() override;
    virtual std::vector<object> dry_run() override;
};
}
