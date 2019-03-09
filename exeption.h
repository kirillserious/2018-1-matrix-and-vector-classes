/*  
 *
 *   (!) Придумать более понятные ошибки, мб их строковое представление
 *
 */


#ifndef EXEPTION_H_
#define EXEPTION_H_
namespace vika_lib {
enum Exeption_enum
{
    VEX_OUTOFARRAY,
    VEX_DIFFERENTSIZES,
    MEX_OUTOFARRAY,
    MEX_COORDSFROMOTHERMATRIX,
    MEX_DIFFERENTSIZES,
    MEX_POWISZEROORLESS
};

class Exeption
{
private:
    Exeption_enum _ex;
public:
    Exeption(Exeption_enum ex):
    _ex (ex)
    {}

    friend
    bool
    operator == (const Exeption &ex1, const Exeption &ex2);
    
};
}

#endif