from .bindings.loader import module_for
# from types import ModuleType
import numpy as np

class Expr:
    """ wrapper around cpp sdot::Expr class to store symbolic expressions """

    def __init__( self, value = None ):
        """ 
        """
        self._module = module_for( 'generic_objects' )
        self._expr = self._module.Expr( value )
    
    @staticmethod
    def list_from_compact_repr( crepr ):
        _module = module_for( 'generic_objects' )
        return _module.expr_list_from_compact_repr( crepr )
    
    @staticmethod
    def as_expr( expr ):
        if expr is None:
            return Expr( "0" )
        if isinstance( expr, Expr ):
            return expr
        if isinstance( expr, list ):
            return [ Expr.as_expr( v ) for v in expr ]
        return Expr( expr )

    @staticmethod
    def ct_rt_split_of_list( expr_list ):
        module = module_for( 'generic_objects' )
        return module.ct_rt_split_of_list( [ Expr.as_expr( e )._expr for e in expr_list ] )

    def ct_repr( self ):
        return self._expr.ct_repr()

    def rt_data( self ):
        return self._expr.rt_data()

    def __repr__( self ):
        return self._expr.__repr__()

    def __add__( self, that ):
        if not isinstance( that, Expr ):
            that = Expr( that )
        return self._expr.add( that._expr )

    def __sub__( self, that ):
        if not isinstance( that, Expr ):
            that = Expr( that )
        return self._expr.sub( that._expr )

    def __mul__( self, that ):
        if not isinstance( that, Expr ):
            that = Expr( that )
        return self._expr.mul( that._expr )

    def __truediv__( self, that ):
        if not isinstance( that, Expr ):
            that = Expr( that )
        return self._expr.div( that._expr )
    
    def __pow__( self, that ):
        if not isinstance( that, Expr ):
            that = Expr( that )
        return self._expr.pow( that._expr )

