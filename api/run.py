import subprocess, os
from argparse import ArgumentParser

def run(cmd):
    print(cmd)
    res = subprocess.run(cmd)
    if res.returncode:
        exit()

def install():
    if os.path.exists("build"):
        os.rmdir("build")
    cmd = ["conan", "install", ".", "--build", "missing", "-s", "compiler.cppstd=gnu20", "--output-folder=build"]
    run(cmd)
        
def build_cmake():
    if not os.path.exists("build/conan_toolchain.cmake"):
        install()
    cmd = ["cmake", ".", "-DCMAKE_TOOLCHAIN_FILE=./build/conan_toolchain.cmake", "-DCMAKE_BUILD_TYPE=Release", "-B", "build"]
    run(cmd)
    
def build():
    if not os.path.exists("build/Makefile"):
        build_cmake()
    cmd = ["cmake", "--build", "build"]
    run(cmd)
    
def start():
    if not os.path.exists("build/API"):
        build()
    cmd = ["./build/API"]
    run(cmd)

actions = {
    "install": install,
    "build_cmake": build_cmake,
    "build": build,
    "start": start
}

args = ArgumentParser()

args.add_argument(
    '-a', '--action',
    help='Действие', 
    required=True, 
    choices=list(actions))

args = args.parse_args()

if actions.get(args.action):
    actions[args.action]()
    
