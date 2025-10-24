

class Engine:
    def __init__(self, title: str, width: int, height: int):
        """
        Initialize SDL2, create the window and renderer.

        :param title: Window title
        :param width: Window width in pixels
        :param height: Window height in pixels
        """
        pass

    def run(self, update_callback):
        """
        Start the main loop. Calls update_callback(self, dt) once per frame.
        Handles timing, input, clearing, and presenting automatically.
        """
        pass

    def clear(self, color: tuple[int, int, int] = (0, 0, 0)):
        """
        Clear the screen with the given RGB color.
        """
        pass

    def draw_rect(self, x: int, y: int, w: int, h: int, color: tuple[int, int, int]):
        """
        Draw a filled rectangle with the specified color.

        :param x: X coordinate
        :param y: Y coordinate
        :param w: Width in pixels
        :param h: Height in pixels
        :param color: RGB tuple (0-255)
        """
        pass

    def draw_sprite(self, sprite, x: int, y: int):
        """
        Draw a loaded sprite (texture) at the given position.

        :param sprite: A Sprite object
        :param x: X coordinate
        :param y: Y coordinate
        """
        pass

    def is_key_pressed(self, key: str) -> bool:
        """
        Check if the specified key is currently pressed.
        """
        pass

    def quit(self):
        """
        Close the window and free SDL resources.
        """
        pass


class Sprite():
    def __init__(self, path: str, x: int = 0, y: int = 0, w: int = 0, h: int = 0):
        """
        Load a texture from the given path.
        """
        pass

    def free(self):
        """
        Free the texture.
        """
        pass


if __name__ == "__main__":
    engine = Engine("My Game", 800, 600) # creates the window

    sprite = Sprite("path/to/texture.png", x=100, y=100, w=100, h=100)

    engine.draw_rect(100, 100, 100, 100, (255, 0, 0))
    engine.draw_sprite(sprite, 200, 200)

    def move(sprite, dt):
        if engine.is_key_pressed("w"):
            Sprite.x += 1 * dt
        if engine.is_key_pressed("s"):
            Sprite.x -= 1 * dt
        if engine.is_key_pressed("a"):
            Sprite.y += 1 * dt
        if engine.is_key_pressed("d"):
            Sprite.y -= 1 * dt


    def update(engine, dt):
        engine.clear()

        # draw the background
        # draw a tree

        move(sprite, dt)
        engine.draw_sprite(sprite, Sprite.x, Sprite.y, Sprite.w, Sprite.h)

    engine.run(update)  # run the update() function each frame
    