import sys
sys.path.append("/Users/jeansalomon/Documents/projects/easyPyEngine/build/lib.macosx-15.0-arm64-cpython-314")

import easyPyEngine 

engine = easyPyEngine.Engine("My Game", 800, 600)
sprite = easyPyEngine.Sprite(engine, "assets/profilePicV1.2.png", 100, 100)
print(sprite.width)
sprite.width = 50
print(sprite.width)

def update(dt):
    engine.draw_rect(100, 200, 100, 100)
    engine.draw_line(100, 100, 500, 500, (255, 0, 0))
    

engine.run(update)