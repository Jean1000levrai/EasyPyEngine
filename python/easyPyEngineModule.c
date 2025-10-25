#include <Python.h>
#include <SDL2/SDL.h>

#include "engine.h"


static PyObject* py_is_key_pressed(EngineObject* self, PyObject* args) {
    const char* key_name;

    // Parse Python argument (string)
    if (!PyArg_ParseTuple(args, "s", &key_name)) {
        return NULL; // error if not a string
    }

    SDL_Scancode code = SDL_GetScancodeFromName(key_name);
    if (code == SDL_SCANCODE_UNKNOWN) {
        Py_RETURN_FALSE;
    }

    // self->keyboard_state must be updated each frame
    if (self->keyboard_state[code]) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyMethodDef Engine_methods[] = {
    {"is_key_pressed", (PyCFunction)py_is_key_pressed, METH_VARARGS,
     "Check if a key is pressed"},
    {NULL, NULL, 0, NULL}  // Sentinel
};

static PyTypeObject EngineType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "easyPyEngine.Engine",
    .tp_basicsize = sizeof(EngineObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = Engine_methods,
};

static PyModuleDef enginemodule = {
    PyModuleDef_HEAD_INIT,
    "easyPyEngine",
    "My 2D Engine Module",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_easyPyEngine(void) {
    PyObject* m;

    if (PyType_Ready(&EngineType) < 0)
        return NULL;

    m = PyModule_Create(&enginemodule);
    if (!m)
        return NULL;

    Py_INCREF(&EngineType);
    PyModule_AddObject(m, "easyPyEngine", (PyObject*)&EngineType);

    return m;
}
