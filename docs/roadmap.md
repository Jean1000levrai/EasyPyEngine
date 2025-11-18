done 😎
in dev 😰
to do 🤡

## Make it functional
### step 1: api stub + window creation 😎

- api stub 😎
- window creation 😎
- renderer 😎
- event loop 😎
- shutdown 😎

### step 2: rendering features (~5-8 hours) 😎

- render a square 😎
- render a sprite 😎
- texture loader with path to an image 😎

### step 3: inputs + deltatime (~3 hours) 🤡

- is_key_pressed -> returns the key self->keyboardState 😎
- key_pressed -> print input
- mouse
- add delta time 😎

## Enhancement

### sprites
- flip
- rotate

### physics 🤡

- vector2
- movement (velocity * dt)
- collision
- gravity

### misc
- mob pathing (go from A to B wait a bit, then loop)
- procedural gen

### UI
- buttons
- text

### audio
- play a sound
- loop

### Shaders
- shader (GLSL)

### camera
- zoom
- rotation

### particle system

## documentation & wrap to python
### to do once
- write doc

### to do for each version
- add autocompletion support
- c python api -> wrap module to python

### wrap guide
**for each function you want to implement**
1. write a wrapper function
    - convert C to python
    - calls C functions
    - convert C returns to python objects

2. Add it to the **method table** `PyMethodDef`

3. Attach the method table to your `Python type` (EngineType)

4. make sure the type is registered in the module (PyInit_EasyPyEngine)

5. 
```bash
python3 python/setup.py build
```






