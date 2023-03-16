# RNBO Python Wrapper

a simple wrapper to evaluate RNBO patches from python.

## to use:

1. Export C++ files from Max RNBO, setting the source file name to be rnbo_source.cpp (or you can also edit the file name in the CMakeList.txt)
2. make a build folder, and cd to it in the terminal
3. run cmake from the build folder, with paths to this folder holing the wrapper, and setting the RNBO export folder, for example:
```
cmake ../rnbo-py-wrapper -D RNBO_EXPORT_FOLDER='/path/to/RNBO/export/folder'
```
4. then run `make` to build the `libRNBOExportLib.dylib`(on Mac, .dll on Windows)
5. the script will copy the `rnbo.py` and `import-test.py` files to the build folder.
6. see the `import-test.py`
