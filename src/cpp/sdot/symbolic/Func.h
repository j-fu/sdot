#pragma once

#include <sdot/support/BigRational.h>
#include "Inst.h"

namespace sdot {

/** */
class Func : public Inst {
public:
    static RcPtr<Inst> from_operands( const Str &name, Vec<std::pair<RcPtr<Inst>,BigRational>> operands );
    static RcPtr<Inst> from_operands( const Str &name, Vec<RcPtr<Inst>> operands );

    virtual void       display      ( Displayer &ds ) const override;
    virtual int        type         () const override { return type_Func; }
       
    Vec<BigRational>   coefficients; ///<
    Str                name;         ///<
};

}