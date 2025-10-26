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

- key pressed -> returns the key self->keyboardState 😎
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

### UI
- buttons
- text

### audio
- play a sound
- loop

### Shaders

### camera
- zoom
- rotation

### particle system

## documentation & wrap to python
### to do once
- write one

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






