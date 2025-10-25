#include <Python.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "engine.h"
#include "graphics.h"
#include "input.h"
#include "sprite.h"



// ---- P Y T H O N   F U N C T I O N S ----

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






// DRAW RECT
static PyObject* py_draw_rect(PyObject* self, PyObject* args){
    int x, y, w, h;
    int r, g, b;
    int f;

    if (!PyArg_ParseTuple(args, "iiiiiiii", &x, &y, &w, &h, &r, &g, &b, &f)){
        return NULL;
    }

    EngineObject* engine = (EngineObject *)self;
    draw_rect(engine, x, y, w, h, r, g, b, f);

    Py_RETURN_NONE;
}



// ---- M E T H O D   T A B L E ----

static PyMethodDef Engine_methods[] = {
    {"draw_rect", py_draw_rect, METH_VARARGS, "Draw a Rectangle"},
    {"run", py_engine_run, METH_VARARGS, "The main loop of the Engine"},
    // ...

    {NULL, NULL, 0, NULL}
};



// ---- P Y T H O N   O B J E C T S ----

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


// ---- I N I T   P Y T H O N   M O D U L E ----

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

    PyObject *m = PyModule_Create(&easyPyEngine_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&EngineType);
    PyModule_AddObject(m, "Engine", (PyObject *)&EngineType);

    return m;
}
