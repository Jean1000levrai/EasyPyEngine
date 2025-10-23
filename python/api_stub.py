

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
    def __init__(self, path: str):
        """
        Load a texture from the given path.
        """
        pass
    