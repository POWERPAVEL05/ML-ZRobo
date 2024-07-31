#include "Gantry.hpp"

void Gantry::setTool(Tool tool)
{
    // maybe second servo for tool switch

    // dummy implementation
    use.write(180*(tool==PEN));
}
