#include <Python.h>
#include <SDL2/SDL.h>

#include "engine.h"
#include "graphics.h"
#include "sprite.h"
#include "input.h"



// -----------------------------------------
// ---- P Y T H O N   F U N C T I O N S ----
// -----------------------------------------

// INIT
// tp_new
static PyObject* Engine_new(PyTypeObject* type, PyObject *args, PyObject *kwds){
    EngineObject* self;
    self = (EngineObject*)type->tp_alloc(type, 0);
    if (self != NULL){
        self->window = NULL;
        self->renderer = NULL;
        self->running = 0;
        self->keyboard_state = NULL;
    }
    return (PyObject*)self;
} 

// tp_init
static int Engine_init(EngineObject* self, PyObject* args, PyObject* kwds){
    const char* title;
    int width, height;

    if (!PyArg_ParseTuple(args, "sii", &title, &width, &height)){
        return -1;
    }
    engine_init(self, (char*)title, width, height);
    return 0;
}

// MAIN LOOP

void call_python_callback(EngineObject* engine, float dt){
    if (!engine->update_callback) return;

    PyObject* arglist = Py_BuildValue("(f)", dt);  // wrap dt as a Python float
    PyObject* result = PyObject_CallObject(engine->update_callback, arglist);
    Py_DECREF(arglist);

    if (!result) {
        PyErr_Print();
        return;
    }
    Py_DECREF(result);
}

static PyObject* py_engine_run(PyObject* self, PyObject* args){
    // not sure on how this works but it works
    PyObject* py_callback;

    if (!PyArg_ParseTuple(args, "O", &py_callback)){
        return NULL;
    }
    if (!PyCallable_Check(py_callback)){
        PyErr_SetString(PyExc_TypeError, "Callback must be callable");
        return NULL;
    }

    EngineObject* engine = (EngineObject *)self;
    Py_XINCREF(py_callback);
    engine->update_callback = py_callback;

    engine_run(engine, call_python_callback);
    Py_RETURN_NONE;
}

// QUIT
static PyObject* py_engine_quit(PyObject* self, PyObject* args){
    EngineObject* engine = (EngineObject *)self;
    engine_quit(engine);
    Py_RETURN_NONE;
}

// CLEAR
static PyObject* py_engine_clear(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"color", NULL};
    PyObject* py_color = NULL;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O",kwlist, &py_color)){
        return NULL;
    }
    
    int r = 0, g = 0, b = 0;  // default color: black
    if (py_color && PyTuple_Check(py_color) && PyTuple_Size(py_color) == 3) {
        r = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 0));
        g = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 1));
        b = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 2));
    }


    EngineObject* engine = (EngineObject *)self;
    engine_clear(engine, r, g, b);
    Py_RETURN_NONE;
}

// DRAW RECT
static PyObject* py_draw_rect(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"x", "y", "width", "height", "color", "filled", NULL};
    PyObject* py_color = NULL;
    int x, y, w, h;
    int f = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "iiii|Oi", kwlist, &x, &y, &w, &h, &py_color, &f)){
        return NULL;
    }
    int r = 255, g = 255, b = 255; // default white
    if (py_color && PyTuple_Check(py_color) && PyTuple_Size(py_color) == 3) {
        r = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 0));
        g = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 1));
        b = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 2));
    }

    EngineObject* engine = (EngineObject *)self;
    draw_rect(engine, x, y, w, h, r, g, b, f);

    Py_RETURN_NONE;
}

// DRAW LINE
static PyObject* py_draw_line(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"x1", "y1", "x2", "y2", "color", NULL};
    PyObject* py_color = NULL;
    int x1, y1, x2, y2;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "iiii|O", kwlist, &x1, &y1, &x2, &y2, &py_color)){
        return NULL;
    }
    int r = 255, g = 255, b = 255; // default white
    if (py_color && PyTuple_Check(py_color) && PyTuple_Size(py_color) == 3) {
        r = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 0));
        g = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 1));
        b = (int)PyLong_AsLong(PyTuple_GetItem(py_color, 2));
    }

    EngineObject* engine = (EngineObject *)self;
    draw_line(engine, x1, y1, x2, y2, r, g, b);

    Py_RETURN_NONE;
}

// DRAW SPRITE
static PyObject* py_draw_sprite_from_engine(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"sprite", "x", "y", NULL};
    EngineObject* engine = (EngineObject *)self;
    SpriteObject* sprite;
    float x, y;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Off",kwlist, &sprite, &x, &y)){
        return NULL;
    }
    draw_sprite(engine, sprite, x, y);
    Py_RETURN_NONE;
}

// KEY PRESS
static PyObject* py_is_key_pressed(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"key", NULL};
    EngineObject* engine = (EngineObject *)self;
    char* key;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &key)){
        return NULL;
    }
    int is_pressed = is_key_pressed(engine, key);
    return PyLong_FromLong(is_pressed);
}

// ---- SPRITE ----

// tp_new
static PyObject* Sprite_new(PyTypeObject* type, PyObject *args, PyObject *kwds){
    SpriteObject* self = (SpriteObject*)type->tp_alloc(type, 0);
    if (self){
        self->texture = NULL;
        self->x = 0;
        self->y = 0;
        self->width = 0;
        self->height = 0;
    }
    return (PyObject*)self;
}

// loading helper
static SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path) {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

// tp_init
static int Sprite_init(SpriteObject* self, PyObject* args, PyObject* kwds){

    return 0;
}

// tp_dealloc
static void Sprite_dealloc(SpriteObject* self) {
    if (self->texture) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// Add Image
static PyObject* py_add_image(SpriteObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"engine", "path", "width", "height", NULL};
    PyObject* py_engine = NULL;
    const char* path = NULL;
    int w = 0, h = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Os|ii", kwlist,
                                     &py_engine, &path, &w, &h)) {
        Py_RETURN_NONE;
    }
    EngineObject* engine = (EngineObject*)py_engine;
    if (!engine->renderer) {
        PyErr_SetString(PyExc_RuntimeError, "Engine renderer not initialized");
        Py_RETURN_NONE;
    }

    SDL_Texture *texture = load_texture(engine->renderer, path);
    if (!texture) {
        printf("ERROR: failed to load texture %s: %s\n", path, SDL_GetError());
        PyErr_SetString(PyExc_RuntimeError, "Failed to load texture");
        Py_RETURN_NONE;
    }

    // Assign texture and dimensions
    self->texture = texture;
    if (w <= 0 || h <= 0) {
        int tex_w, tex_h;
        SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
        self->width = tex_w;
        self->height = tex_h;
    } else {
        self->width = w;
        self->height = h;
    }

    // Do NOT destroy texture here! It will be destroyed in Sprite_dealloc
    Py_RETURN_NONE;
}

// DRAW SPRITE
static PyObject* py_draw_sprite(PyObject* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {"engine", "x", "y", NULL};
    EngineObject* engine;
    SpriteObject* sprite = (SpriteObject *)self;
    float x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Off", kwlist, &engine, &x, &y)){
        return NULL;
    }
    draw_sprite(engine, sprite, x, y);
    Py_RETURN_NONE;
}


// -----------------------------
// ---- A T T R I B U T E S ----
// -----------------------------

// --- GETTERS / SETTERS ---

// S P R I T E

// sprite width getter
static PyObject* Sprite_get_width(SpriteObject* self) {
    return PyLong_FromLong(self->width);
}

// sprite width setter
static int Sprite_set_width(SpriteObject* self, PyObject* value) {
    if (!PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "width must be an integer");
        return -1;
    }
    self->width = (int)PyLong_AsLong(value);
    return 0;
}

// sprite height getter
static PyObject* Sprite_get_height(SpriteObject* self) {
    return PyLong_FromLong(self->height);
}

// sprite height setter
static int Sprite_set_height(SpriteObject* self, PyObject* value) {
    if (!PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "height must be an integer");
        return -1;
    }
    self->height = (int)PyLong_AsLong(value);
    return 0;
}

// sprite x getter
static PyObject* Sprite_get_x(SpriteObject* self) {
    return PyLong_FromLong(self->x);
}

// sprite x setter
static int Sprite_set_x(SpriteObject* self, PyObject* value) {
    if (!PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "x must be an integer");
        return -1;
    }
    self->x = (int)PyLong_AsLong(value);
    return 0;
}

// sprite y getter
static PyObject* Sprite_get_y(SpriteObject* self){
    return PyLong_FromLong(self->y);
}

// sprite y setter
static int Sprite_setter_y(SpriteObject* self, PyObject* value){
    if (!PyLong_Check(value)){
        PyErr_SetString(PyExc_TypeError, "y must be an integer");
        return -1;
    }
    self->y = (int)PyLong_AsLong(value);
    return 0;
}

// E N G I N E



// --- TABLE ---

static PyGetSetDef Sprite_getset[] = {
    {"width", (getter)Sprite_get_width, (setter)Sprite_set_width, NULL, NULL},
    {"height", (getter)Sprite_get_height, (setter)Sprite_set_height, NULL, NULL},
    {"x", (getter)Sprite_get_x, (setter)Sprite_set_x, NULL, NULL},
    {"y", (getter)Sprite_get_y, (setter)Sprite_setter_y, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL}
};


// ---------------------------------
// ---- M E T H O D   T A B L E ----
// ---------------------------------

static PyMethodDef Engine_methods[] = {
    {"draw_rect", (PyCFunction)py_draw_rect, METH_VARARGS | METH_KEYWORDS, "Draw a Rectangle"},
    {"run", py_engine_run, METH_VARARGS, "The main loop of the Engine"},
    {"quit", py_engine_quit, METH_VARARGS, "Quit the Engine"},
    {"clear", (PyCFunction)py_engine_clear, METH_VARARGS | METH_KEYWORDS, "Clear the screen"},
    {"draw_line", (PyCFunction)py_draw_line, METH_VARARGS | METH_KEYWORDS, "Draw a Line"},
    {"draw_sprite", (PyCFunction)py_draw_sprite_from_engine, METH_VARARGS | METH_KEYWORDS, "Draw a Sprite"},
    {"is_key_pressed", (PyCFunction)py_is_key_pressed, METH_VARARGS | METH_KEYWORDS, "Check if a key is pressed"},
    // ...

    {NULL, NULL, 0, NULL}
};

static PyMethodDef Sprite_methods[] = {
    {"draw", (PyCFunction)py_draw_sprite, METH_VARARGS | METH_KEYWORDS, "Draw a Sprite"},
    {"add_image", (PyCFunction)py_add_image, METH_VARARGS | METH_KEYWORDS, "Add a Texture"},
    // ...
    {NULL, NULL, 0, NULL}
};


// -------------------------------------
// ---- P Y T H O N   O B J E C T S ----
// -------------------------------------

static PyTypeObject EngineType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "easyPyEngine.Engine",
    .tp_basicsize = sizeof(EngineObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Engine Object",  // Documentation string
    .tp_methods = Engine_methods,
    .tp_new = Engine_new,
    .tp_init = (initproc)Engine_init,
};

static PyTypeObject SpriteType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "easyPyEngine.Sprite",
    .tp_basicsize = sizeof(SpriteObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Sprite Object",  // Documentation string
    .tp_methods = Sprite_methods,
    .tp_getset = Sprite_getset,
    .tp_new = Sprite_new,
    .tp_init = (initproc)Sprite_init,
    .tp_dealloc = (destructor)Sprite_dealloc
};


// ---------------------------------------------
// ---- I N I T   P Y T H O N   M O D U L E ----
// ---------------------------------------------

static struct PyModuleDef easyPyEngine_module = {
    PyModuleDef_HEAD_INIT,
    "easyPyEngine",
    "An awesomely easy to use 2D game engine for python",
    -1,
    NULL,
    NULL,NULL,NULL,NULL
};

PyMODINIT_FUNC PyInit_easyPyEngine(void) {
    if (PyType_Ready(&EngineType) < 0)
        return NULL;
    if (PyType_Ready(&SpriteType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&easyPyEngine_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&EngineType);
    PyModule_AddObject(m, "Engine", (PyObject *)&EngineType);

    Py_INCREF(&SpriteType);
    PyModule_AddObject(m, "Sprite", (PyObject *)&SpriteType);

    return m;
}
