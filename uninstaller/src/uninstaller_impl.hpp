#pragma once

#include <uninstaller.hpp>

namespace uninstaller
{
class uninstaller_impl : public uninstaller
{
public:
    uninstaller_impl();
    virtual ~uninstaller_impl();

    virtual void                uninstall() override;
    virtual std::vector<object> do_dry_run() override;
};
}
