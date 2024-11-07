#pragma once

#include "../local_weight_bounds/LocalWeightBounds.h"
#include "AffineTransformation.h"

#include <tl/support/containers/Opt.h>

namespace sdot {

/**
 * @brief 
 * 
 */
template<class TCell>
class RegularGrid {
public:
    using                Pt                = TCell::Pt;
    using                TF                = Pt::value_type;
    static constexpr int nb_dims           = Pt::ct_size;

    using                Trans              = AffineTransformation<TF,nb_dims>; ///< transformation matrix + translation
    using                Nd                 = Vec<PI,nb_dims>;
                  
    /**/                 RegularGrid        ( const auto &points, const Vec<Trans> &transformations, TF nb_diracs_per_box = 30 );
              
    PI                   max_nb_threads     () const;
    int                  for_each_cell      ( const TCell &base_cell, const LocalWeightBounds<TCell> &weights_bounds, auto &&f ); ///< return the first non null value of `f( cell, num_thread )`, or 0
    void                 display            ( Displayer &ds ) const;
               
private:
    void                 make_cuts_from     ( PI b0, PI n0, TCell &cell, Vec<PI> &buf, const LocalWeightBounds<TCell> &weights );
    PI                   end_index          () const;
    PI                   index              ( const Pt &pos, int dim ) const;
    PI                   index              ( const Pt &pos ) const;
         
    PI                   nb_base_points;    ///<     
    PI                   nb_glob_points;    ///<     
    Nd                   nb_divs;           ///<
    Vec<Pt,2>            limits;            ///< min and max pos
    Pt                   steps;             ///<
           
    Vec<Trans>           transformations;   ///<
    Vec<PI>              offsets;           ///<
    Vec<Pt>              points;            ///<
    Vec<PI>              inds;              ///<
};         
         
} // namespace sdot

#include "RegularGrid.cxx"  // IWYU pragma: export
