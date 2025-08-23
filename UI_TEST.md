# UI Launch Attempt

An attempt was made to run the compiled binary in this repository:

```
./build/linux/speckle
```

The launch failed because the Qt Charts runtime library was missing:

```
libQt6Charts.so.6: cannot open shared object file: No such file or directory
```

As a result, the Qt-based user interface could not be verified in this environment.

