#pragma once

#include <tl/support/containers/Void.h>
#include <tl/support/containers/Opt.h>

#include "support/MapOfUniquePISortedArray.h"
#include "support/RangeOfClasses.h"
// #include "support/BigRational.h"
#include "support/SimdTensor.h"
// #include "PrevCutInfo.h"
// #include "VtkOutput.h"
#include "Cut.h"

namespace sdot {

/**
 * @brief 
 *
 */
template<class Arch,class TF,int nb_dims,class CutInfo=Void,class CellInfo=Void>
class Cell {
public:
    using           LI                     = PI32; ///< local index, e.g. for num cut, num vertex, ...
    using           Pt                     = Vec<TF,nb_dims>;
    using           Pr                     = Vec<LI,nb_dims>;

    /**/            Cell                   ( CellInfo &&info = {} );

    // modifications
    void            remove_inactive_cuts   (); ///< 
    void            get_data_from          ( const Cell &cell ); ///< allows to make a copy without reallocating memory (it takes the vectors from the current instance)
    void            cut                    ( const Pt &dir, TF off, CutInfo &&cut_info = {} ); ///< 

    // output info
    PI              nb_stored_cuts         () const; ///< may be different from nb_active_cuts if remove_inactive_cuts has not been called
    PI              nb_active_cuts         () const; ///< if _may_have_unused_cuts == true, this function will have to read _vertex_cut_lists to compute the result. _may_have_unused_cuts can be canceled using remove_inactive_cuts
    
    PI              nb_vertices_true_dim   () const; ///< 
    PI              nb_vertices            () const; ///< nb vertices for dim == nb_dim. For instance, 2 (non parallel) cuts in 3D leave an edge and no vertex, but the cell will have true_dimensionality == 2, and a vertex in the 2D projected cell (nb_vertices_true_dim = 1)

    T_i Vec<TF,i>   vertex_coord           ( PI num_vertex, CtInt<i> choosen_nb_dims ) const;
    Pt              vertex_coord           ( PI num_vertex ) const;

    T_i Vec<LI,i>   vertex_refs            ( PI num_vertex, CtInt<i> choosen_nb_dims ) const;
    Pr              vertex_refs            ( PI num_vertex ) const;

    void            display                ( Displayer &ds ) const;

    //
    T_i Vec<TF,i+1> ray_dir                ( const Vec<LI,i> &edge_refs, LI base_vertex ) const;


    // utility
    auto            with_ct_dim            ( auto &&func ) const;
    auto            with_ct_dim            ( auto &&func );

    // user info
    CellInfo        info;                  ///< used defined aditional info

private:
    T_i struct      _RefMapForDim          { MapOfUniquePISortedArray<i,LI,PI> map; };
    using           _RefMap                = RangeOfClasses<_RefMapForDim,0,nb_dims>;
    using           _Cut                   = Cut<TF,nb_dims,CutInfo>;
           
    using           _VertexCoords          = SimdTensor<TF,nb_dims>;
    using           _VertexRefs            = Vec<Vec<LI,nb_dims>>;
    using           _BaseVecs              = Vec<Pt,nb_dims>;
    using           _Cuts                  = Vec<_Cut>;

    //
    void            _for_each_ray_and_edge ( auto &&ray_func, auto &&edge_func, auto td );
    T_i void        _remove_inactive_cuts  ( CtInt<i> ); ///< 
    PI              _new_coid_ref_map      ( PI size );
    void            _unbounded_cut         ( const Pt &dir, TF off, CutInfo &&cut_info ); ///< 
    void            _bounded_cut           ( const Pt &dir, TF off, CutInfo &&cut_info ); ///< 
    void            _update_sps            ( const Pt &dir, TF off, auto td );

    T_i  auto       _with_ct_dim           ( auto &&func, CtInt<i> min_td, CtInt<i> max_td ) const;
    T_ij auto       _with_ct_dim           ( auto &&func, CtInt<i> min_td, CtInt<j> max_td ) const;
    T_i  auto       _with_ct_dim           ( auto &&func, CtInt<i> min_td, CtInt<i> max_td );
    T_ij auto       _with_ct_dim           ( auto &&func, CtInt<i> min_td, CtInt<j> max_td );

    // output data
    int             _true_dimensionality;  ///<
    _VertexCoords   _vertex_coords;        ///<
    _VertexRefs     _vertex_refs;          ///< list of cut indices for each vertex
    _BaseVecs       _base_vecs;            ///< used if _true_dimensionality < nb_dims
    _Cuts           _cuts;

    // intermediate data
    mutable PI      _coid_ref_map;         ///< curr op id for num_cut_map
    mutable _RefMap _ref_map;              ///<
    Vec<TF>         _sps;                  ///< scalar products for each vertex
 
    // flags  
    bool            _may_have_unused_cuts; ///< 
    bool            _bounded;              ///<
    bool            _empty;                ///<
};

/// 
template<class Arch,class TF,class CutInfo,class CellInfo>
class Cell<Arch,TF,0,CutInfo,CellInfo> {
public:
};

} // namespace sdot

#include "Cell.cxx" // IWYU pragma: export
