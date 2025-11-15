import easyPyEngine.easyPyEngine as epe

engine = epe.Engine("My Game", 800, 600)
sprite = epe.Sprite(engine, "assets/profilePicV1.2.png", 100, 100)
# sprite1 = epe.Sprite(engine, "", 100, 100)
x: int = 100
y: int = 400
speed: int = 200


def update(dt):
    global x, y

    engine.clear(color=(135, 206, 235))
    engine.draw_rect(0, 500, 800, 600, (124, 252, 0), 1)
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