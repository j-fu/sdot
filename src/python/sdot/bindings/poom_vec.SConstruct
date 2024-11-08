import sysconfig
import pybind11
import os

# helper to get n-th parent directory
def pdir( dir, n = 1 ):
    if n == 0:
        return dir
    return pdir( os.path.dirname( dir ), n - 1 )

# directories
cwd = os.getcwd()
bad = pdir( cwd, 2 )
print( bad )

# we're going to reference the source through a build dir
VariantDir( 'build', bad )

# arguments
args = dict( ARGLIST )

module_name = args[ 'module_name' ]
suffix = args[ 'suffix' ]

scalar_type = args[ 'scalar_type' ]
nb_dims = args[ 'nb_dims' ]
arch = args[ 'arch' ]

# includes
CPPPATH = [
    os.path.join( bad, 'src', 'cpp' ),

    os.path.join( bad, 'ext', 'tl20', 'src', 'cpp' ),
    os.path.join( bad, 'ext', 'Catch2', 'src' ),
    os.path.join( bad, 'ext', 'asimd', 'src' ),
    os.path.join( bad, 'ext', 'eigen' ),

    sysconfig.get_paths()[ 'include' ], # Python.h
    pybind11.get_include(), # pybind11.h
]


# print( subprocess.check_output( [ 'pybind11-config', '--includes' ] ).decode('utf-8').split( '-I' ))

# CXXFLAGS
CXXFLAGS = [
    f'-DSDOT_CONFIG_module_name={ module_name }',
    f'-DSDOT_CONFIG_suffix={ suffix }',

    f'-DSDOT_CONFIG_scalar_type={ scalar_type }',
    f'-DSDOT_CONFIG_nb_dims={ nb_dims }',
    f'-DSDOT_CONFIG_arch={ arch }',

    '-Wdeprecated-declarations',
    '-std=c++20',
    '-fopenmp',

    '-fdiagnostics-color=always',
    
    '-march=' + args[ 'arch' ].replace( '_', '-' ),
    '-ffast-math',
    '-O3',

    '-g3',

    '-std=c++20',
]

# LIBS
LIBS = [
    'Catch2Main',
    'Catch2',
    'gomp',
]

# LIBPATH
LIBPATH = [
    '/home/hugo.leclerc/.vfs_build/ext/Catch2/install/lib',
    '/home/leclerc/.vfs_build/ext/Catch2/install/lib'
]

# 
sources = [
    'build/src/python/sdot/bindings/sdot_bindings.cpp',

    "build/ext/tl20/src/cpp/tl/support/display/DisplayItem_Pointer.cpp",
    "build/ext/tl20/src/cpp/tl/support/display/DisplayItem_Number.cpp",
    "build/ext/tl20/src/cpp/tl/support/display/DisplayItem_String.cpp",
    "build/ext/tl20/src/cpp/tl/support/display/DisplayItem_List.cpp",

    "build/ext/tl20/src/cpp/tl/support/display/DisplayParameters.cpp",
    "build/ext/tl20/src/cpp/tl/support/display/DisplayContext.cpp",
    "build/ext/tl20/src/cpp/tl/support/display/DisplayItem.cpp",

    "build/ext/tl20/src/cpp/tl/support/string/read_arg_name.cpp",
    "build/ext/tl20/src/cpp/tl/support/string/va_string.cpp",
    "build/ext/tl20/src/cpp/tl/support/Displayer.cpp",
    # "build/ext/tl20/src/cpp/tl/support/.cpp",

    # "build/src/cpp/sdot/DiracVecFromLocallyKnownValues.cpp",
    # "build/src/cpp/sdot/DiracVec.cpp",

    # "build/src/cpp/sdot/PavingWithDiracs.cpp",
    # "build/src/cpp/sdot/RegularGrid.cpp",
    
    # "build/src/cpp/sdot/support/BigRational.cpp",
    # "build/src/cpp/sdot/Cell.cpp",

    "build/src/cpp/sdot/support/VtkOutput.cpp",
    "build/src/cpp/sdot/support/Mpi.cpp",
]


# make the library
env = Environment( CPPPATH = CPPPATH, CXXFLAGS = CXXFLAGS, LIBS = LIBS, LIBPATH = LIBPATH, SHLIBPREFIX = '' )
env.SharedLibrary( module_name + env[ 'SHLIBSUFFIX' ], sources )

