# Usage

This guide will help you throughout your journey of developping with EasyPyEngine. This is where every features and syntax info that you need would hopefully be.

# Contents

- [Import](#import) 

- [Window](#window)
    - [Creation](#window-creation)
    - [Drawing](#drawing)
    - [Mainloop](#mainloop--run)
    - [Quit](#quit)
    - [Clear](#clear)
    - [Input](#input)

- [Sprite](#sprite)
    - [Create](#create-a-sprite)
    - [Draw](#draw-sprite)

- [Example](#example-of-code)

- [Collisions](#collisions)


## Consider checking this part of the documentation

- [ReadMe](../README.md)
- [Getting Started](getting_started.md)

---


# Import
Read [Getting Started](getting_started.md) 
and import like any other python library
```python
import easyPyEngine
import easyPyEngine as epe
from easyPyEngine import *
```

### Convention
The imported module is often shortened to `epe`. 

<br><br>

# Window

## Window creation

```python
engine = easyPyEngine.Engine(<title>: str, width: int, height: int)
```

example:

```python title="example"
engine = easyPyEngine.Engine("My Game", 800, 600)
```

### Convention
The window is often called `engine`. 

## Drawing

### To draw a rectangle on the screen:
```python
engine.draw_rect(<x1>: int, <y1>: int, <x2>: int, <y2>: int, (r, g, b), <filled>: int)  # filled should be 1 for filled or O for hollow
```

example:   
This code draws a red filled rectangle at these coordinates
```python title="example"
engine.draw_rect(0, 500, 800, 600, (255, 0, 0), 1)
```
  
### To draw a line:
```python
engine.draw_line(<x1>: int, <y1>: int, <x2>: int, <y2>: int, (r, g, b))
```

```python title="example"
engine.draw_line(0, 500, 800, 600, (124, 252, 0))
```

### To draw a sprite
checkout [Sprite](#sprite) section.

```python
engine.draw_sprite(<sprite_name>, x, y)
```

## Mainloop / Run

The mainloop function will execute a function each frame. The given function must take a single parameter `delta time`.  
`delta time`is the time elapsed between two consecutive frames or updates, used to make movement and animations framerate–independent.

#### Convention
- the mainloop function is called `update`. 
- the delta time parameter is called `dt`. 

```python
engine.run(<function>)
```   
In this example, the `update` function will be executed each frame.

```python
def update(dt):
    pass

engine.run(update)
```

## Quit

Use this function to quit safely the app you created. 
```python
engine.quit()
```

## Clear

Use this function to clear the screen
```python
engine.clear((r, g, b))
```

## Input

Use this function in the `update` function. Takes the key code in parameter and returns `True` if the key is pressed or `False` if the key is not being pressed. 
```python
engine.is_key_pressed(<KeyCode>: str)
```
### !---- IN DEV / DOES NOT WORK ----!
### Alternative

Use this function in the `update` function. Returns the `key code` of the currently pressed key. 
```python
engine.key_pressed()
```

So to know the key code:
```python
print(engine.key_pressed())
```

Other usage:
```python
if engine.key_pressed() in ['w', 'z']:
    pass
```


<br><br>

# Sprite

## Create a sprite
Only works with .png or .jpg files
```python
sprite = easyPyEngine.Sprite()
```

Add it a texture. 
```python
Sprite.add_image(engine: Engine, path: str, x: int, y: int)
```
This design choice has been made to able to create sprites without giving it a .png or .jpg file so that you could create one with a rectangle drawn from the engine texture.  

example:
```python title="example"
sprite = easyPyEngine.Sprite()
sprite.add_image(engine, "path/to/image.png", 100, 100)
```

## Draw sprite

```python
sprite.draw(engine: Engine, x: int, y: int)
```

example:
```python title="example"
sprite.draw(engine, 200, 500)
```

<br><br>

# Example of Code

**Note**: 
- We could have used a class to represent the sprite.
- This code is purposely over commented. 

```python title="example"
import easyPyEngine as epe

engine = epe.Engine("My Game", 800, 600)    # creates the window
sprite = epe.Sprite(engine, "assets/profilePicV1.2.png", 100, 100)  # creates the sprite
# sprite's info
x: int = 100
y: int = 400
speed: int = 200

def update(dt):
    global x, y

    engine.clear(color=(135, 206, 235))    # clears the screen with a blue sky colour
    engine.draw_rect(0, 500, 800, 600, (124, 252, 0), 1) # draws a green rectangle
    engine.draw_sprite(sprite, x, y) # draws the sprite
    if engine.is_key_pressed("w"):   # handles input
        x += speed * dt     # use delta time for movement, else it will behave differently on other machines
engine.run(update)  # mainloop
engine.quit()   # quits the engine safely
```

<br><br>

# Collisions

## IN DEV! IT IS A FUTURE FEATURE! NOT CURRENTLY WORKING!

This will make 2 sprites collide with each other
```python
collision(<window_name>, <sprite1>, <sprite2>)
```
example:
```python title="example"
collision(engine, ground, sprite)
```  
If you need create collisions between a sprite and a rectangle or 2 rectangles.  

```python title="example"
class Ground:
    def __init__(self, engine: Engine, x: int, y: int, w: int, h: int):
        self.sprite = easyPyEngine.Sprite(engine, "", x, y, w, h)
        engine.draw_sprite(self.sprite, x, y)
        engine.draw_rect(x, y, w, h, (r, g, b), 1)
        self.x = x
        self.y = y

ground = Ground(engine, 0, 500, 800, 600)
sprite = easyPyEngine.Sprite(engine, "assets/sprite.png", 100, 100)
collision(engine, sprite, ground.sprite)
```

