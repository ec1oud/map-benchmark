# map-benchmark

A comparison of various ways to handle int-to-object maps in C++ with Qt and STL.

To check the runtime, just build and run it.
You can also give an argument: map, unorderedMap, QHash or QMap

To check memory usage you can use [gperftools](https://github.com/gperftools/gperftools).

```HEAPPROFILE=/tmp/heapprof ./map-benchmark QHash```

and optionally afterwards

```pprof ./map-benchmark /tmp/heapprof.0001.heap```

Results on a Core i7 machine with current dev branch (post-5.7):

```
void mapBench() creation: elapsed 1765
   foreach: elapsed 1016
   range-based for: elapsed 208
   find: elapsed 855
void unorderedMapBench() creation: elapsed 1002
   foreach: elapsed 841
   range-based for: elapsed 40
   find: elapsed 134
void qHashBench() creation: elapsed 773
   foreach: elapsed 188
   qAsConst foreach: elapsed 189
   range-based for: elapsed 187
   qAsConst range-based for: elapsed 188
   find: elapsed 123
void qMapBench() creation: elapsed 2908
   foreach: elapsed 213
   qAsConst foreach: elapsed 212
   range-based for: elapsed 215
   qAsConst range-based for: elapsed 209
   find: elapsed 1325
   value: elapsed 1373

$ HEAPPROFILE=/tmp/heapprof ./map-benchmark map
Starting tracking the heap
Dumping heap profile to /tmp/heapprof.0001.heap (100 MB currently in use)
Dumping heap profile to /tmp/heapprof.0002.heap (200 MB currently in use)
Dumping heap profile to /tmp/heapprof.0003.heap (300 MB currently in use)
Dumping heap profile to /tmp/heapprof.0004.heap (400 MB currently in use)
void mapBench() creation: elapsed 3208
Dumping heap profile to /tmp/heapprof.0005.heap (500 MB currently in use)
Dumping heap profile to /tmp/heapprof.0006.heap (600 MB currently in use)
Dumping heap profile to /tmp/heapprof.0007.heap (700 MB currently in use)
Dumping heap profile to /tmp/heapprof.0008.heap (800 MB currently in use)
Dumping heap profile to /tmp/heapprof.0009.heap (900 MB currently in use)
   foreach: elapsed 2843
   range-based for: elapsed 208
   find: elapsed 856
Dumping heap profile to /tmp/heapprof.0010.heap (Exiting, 3 kB in use)

$ HEAPPROFILE=/tmp/heapprof ./map-benchmark unorderedMap
Starting tracking the heap
Dumping heap profile to /tmp/heapprof.0001.heap (100 MB currently in use)
Dumping heap profile to /tmp/heapprof.0002.heap (200 MB currently in use)
Dumping heap profile to /tmp/heapprof.0003.heap (406 MB currently in use)
void unorderedMapBench() creation: elapsed 2430
Dumping heap profile to /tmp/heapprof.0004.heap (506 MB currently in use)
Dumping heap profile to /tmp/heapprof.0005.heap (606 MB currently in use)
Dumping heap profile to /tmp/heapprof.0006.heap (706 MB currently in use)
   foreach: elapsed 2748
   range-based for: elapsed 36
   find: elapsed 134
Dumping heap profile to /tmp/heapprof.0007.heap (Exiting, 3 kB in use)

$ HEAPPROFILE=/tmp/heapprof ./map-benchmark QHash
Starting tracking the heap
Dumping heap profile to /tmp/heapprof.0001.heap (112 MB currently in use)
Dumping heap profile to /tmp/heapprof.0002.heap (224 MB currently in use)
Dumping heap profile to /tmp/heapprof.0003.heap (448 MB currently in use)
void qHashBench() creation: elapsed 2176
   foreach: elapsed 256
   qAsConst foreach: elapsed 256
   range-based for: elapsed 256
   qAsConst range-based for: elapsed 256
   find: elapsed 127
Dumping heap profile to /tmp/heapprof.0004.heap (Exiting, 3 kB in use)

$ HEAPPROFILE=/tmp/heapprof ./map-benchmark QMap
Starting tracking the heap
Dumping heap profile to /tmp/heapprof.0001.heap (100 MB currently in use)
Dumping heap profile to /tmp/heapprof.0002.heap (200 MB currently in use)
Dumping heap profile to /tmp/heapprof.0003.heap (300 MB currently in use)
void qMapBench() creation: elapsed 4226
   foreach: elapsed 220
   qAsConst foreach: elapsed 218
   range-based for: elapsed 223
   qAsConst range-based for: elapsed 214
   find: elapsed 1325
   value: elapsed 1365
Dumping heap profile to /tmp/heapprof.0004.heap (Exiting, 3 kB in use)
```
