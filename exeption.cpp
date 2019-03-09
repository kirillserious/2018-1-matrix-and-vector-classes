#include "exeption.h"
namespace vika_lib {
bool
operator == (const Exeption &ex1, const Exeption &ex2)
{
    if (ex1._ex == ex2._ex) return true;
    else return false;
}
}