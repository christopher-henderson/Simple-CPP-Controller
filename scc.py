from clang.cindex import Index
from clang.cindex import Config
from subprocess import check_output
from distutils.spawn import find_executable


def get_llvm_bin_dir():
    for path in (None, '/usr/local/opt/llvm/bin', '/opt/llvm/bin'):
        lib = find_executable('llvm-config', path=path)
        if lib:
            break
    return lib


def get_lib_path():
    llvm_config = get_llvm_bin_dir()
    try:
        return check_output([llvm_config, "--libdir"], shell=False)[0:-1]
    except Exception as e:
        raise e

Config.set_library_path(get_lib_path())
index = Index.create()
tu = index.parse("example/main.c")
for