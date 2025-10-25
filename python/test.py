import sys

sys.path.append("/Users/jeansalomon/Documents/projects/easyPyEngine/build/lib.macosx-15.0-arm64-cpython-314")
import easyPyEngine 


engine = easyPyEngine.Engine("My Game", 800, 600)

def update(dt):
    engine.draw_rect(100, 200, 100, 100, 255, 255, 0, 1)

engine.run(update)