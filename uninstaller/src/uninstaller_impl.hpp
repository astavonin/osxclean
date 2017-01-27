#pragma once

#include <uninstaller.h>

namespace uninstaller
{
class uninstaller_base : public uninstaller
{
public:
    uninstaller_base();
    virtual ~uninstaller_base();

    virtual objects_list uninstall( const objects_list &objs ) override;
};
}
