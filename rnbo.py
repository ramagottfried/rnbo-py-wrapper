# https://nesi.github.io/perf-training/python-scatter/ctypes

import ctypes
import sys

if sys.platform == "darwin":
    rnbo = ctypes.CDLL("libRNBOExportLib.dylib")
elif sys.platform.startswith('win'):
    rnbo = ctypes.CDLL("libRNBOExportLib.dll")
# else for linux check later

def init(sampleRate, vectorSize):

    # set arg types
    rnbo.init.argtypes = [ctypes.c_int, ctypes.c_int]

    rnbo.midiEvent.argtypes = [ctypes.c_int, ctypes.c_int]

    rnbo.setParamValueById.argtypes = [ctypes.c_char_p, ctypes.c_double]
    rnbo.getParamValueById.argtypes = [ctypes.c_char_p]
    rnbo.setNormParamValueById.argtypes = [ctypes.c_char_p, ctypes.c_double]
    rnbo.convertFromNormParamValueById.argtypes = [ctypes.c_char_p, ctypes.c_double]

    rnbo.setParamValueByIdx.argtypes = [ctypes.c_int, ctypes.c_double]
    rnbo.getParamValueByIdx.argtypes = [ctypes.c_int]
    rnbo.setNormParamValueByIdx.argtypes = [ctypes.c_int, ctypes.c_double]
    rnbo.convertFromNormParamValueByIdx.argtypes = [ctypes.c_int, ctypes.c_double]

    # set return types
    rnbo.getParamValueById.restype = ctypes.c_double
    rnbo.convertFromNormParamValueById.restype = ctypes.c_double
    rnbo.getParamValueByIdx.restype = ctypes.c_double
    rnbo.convertFromNormParamValueByIdx.restype = ctypes.c_double

    # init 

    rnbo.init(sampleRate, vectorSize)
    # need to know vector size to init and setup vector return size
    rnbo.rnbo_process_vec.restype = ctypes.POINTER(ctypes.c_double * vectorSize)


def printInfo():
    rnbo.printInfo()

def midiEvent(pitch, velocity):
    # midiEvent note and velocity
    rnbo.midiEvent(pitch, velocity)


def setParamValueById(id, val):
    rnbo.setParamValueById((id).encode('utf-8'), val)

def getParamValueById(id):
    return rnbo.getParamValueById((id).encode('utf-8'))

def setNormParamValueById(id, val):
    rnbo.setNormParamValueById((id).encode('utf-8'), val)

def convertFromNormParamValueById(id, val):
    return rnbo.convertFromNormParamValueById((id).encode('utf-8'), val)


def setParamValueByIdx(idx, val):
    rnbo.setParamValueByIdx(idx, val)

def getParamValueByIdx(idx):
    return rnbo.getParamValueByIdx(idx)

def setNormParamValueByIdx(idx, val):
    rnbo.setNormParamValueByIdx(idx, val)

def convertFromNormParamValueByIdx(idx):
    return rnbo.convertFromNormParamValueByIdx(idx)

def process(): #just output for now
    return rnbo.rnbo_process_vec().contents
