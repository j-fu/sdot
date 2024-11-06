from sdot import PowerDiagram
import pytest
import numpy

def test_PowerDiagram():
    pd = PowerDiagram( positions = [ [ 0.25, 0.5 ], [ 0.75, 0.5 ] ] )
    pd.for_each_cell( print )
    assert 0