import sys

sys.path.append("/Users/jeansalomon/Documents/projects/easyPyEngine/build/lib.macosx-15.0-arm64-cpython-314")
import easyPyEngine 

e = easyPyEngine.easyPyEngine("jf", 800, 500)
if e.is_key_pressed("w"):
    print("W is pressed")