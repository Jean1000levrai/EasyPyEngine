import sys
sys.path.append("/Users/jeansalomon/Documents/projects/easyPyEngine/python/easyPyEngine")

import easyPyEngine as epe


engine = epe.Engine("My Game", 800, 600)
sprite = epe.Sprite()
sprite.add_image(engine, "../assets/profilePicV1.2.png", 100, 100)
sp2 = epe.Sprite()
sp2.add_rect(100, 100, (255, 0, 0), 1)
x: int = 100
y: int = 400
speed: int = 200

def update(dt):
    global x, y

    engine.clear(color=(135, 206, 235))
    engine.draw_rect(0, 500, 800, 600, (124, 252, 0), 1)
    sp2.draw(engine, 100, 400)
    # engine.draw_sprite(sprite, x, y)
    sprite.draw(engine, x, y)
    if engine.is_key_pressed("w"):
        sprite.height += 2
    if engine.is_key_pressed("s"):
        sprite.height -= 2
    if engine.is_key_pressed("a"):
        x -= speed * dt
    if engine.is_key_pressed("d"):
        x += speed * dt

engine.run(update)
engine.quit()