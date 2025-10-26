import sys
sys.path.append("/Users/jeansalomon/Documents/projects/easyPyEngine/build/lib.macosx-15.0-arm64-cpython-314")

import easyPyEngine 

engine = easyPyEngine.Engine("My Game", 800, 600)
sprite = easyPyEngine.Sprite(engine, "assets/profilePicV1.2.png", 100, 100)
x: int = 100
y: int = 400
speed: int = 3

def update(dt):
    global x, y
    engine.clear(color=(135, 206, 235))
    engine.draw_rect(0, 500, 800, 600, (124, 252, 0), 1)
    engine.draw_sprite(sprite, x, y)
    if engine.is_key_pressed("w"):
        # y -= speed
        sprite.height += speed
    if engine.is_key_pressed("s"):
        # y += speed
        sprite.height -= speed
    if engine.is_key_pressed("a"):
        x -= speed
    if engine.is_key_pressed("d"):
        x += speed

engine.run(update)
engine.quit()