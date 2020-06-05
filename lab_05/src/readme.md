# Build and run

## With Qt Creator

Open file `CMakeLists.txt` in Qt Creator

## With make

```
$ mkdir build
$ cd build
$ cmake -S .. -B .
$ make
$ ./lab_05
```

## With ninja

```
$ mkdir build
$ cd build
$ cmake -S .. -B . -G Ninja
$ ninja
$ ./lab_05
```
