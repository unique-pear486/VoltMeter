# MicroView VoltMeter

## Description

Arduino sketch for the [Microview](http://learn.microview.io/) that displays the current voltage and a scanning graph of historical voltages

## Required Libraries

1. [MicroView Arduino Library](https://github.com/geekammo/MicroView-Arduino-Library)

## Installation

As this project uses a custom font, you need to place 24x9_Font.h in the MicroView library folder and change a couple of lines in MicroView.cpp:

```diff
@@ -31,9 +31,10 @@
 #include <space01.h>
 #include <space02.h>
 #include <space03.h>
+#include <24x9_Font.h>
 
 // Change the total fonts included
-#define TOTALFONTS		7
+#define TOTALFONTS		8
 #define recvLEN			100
 char serInStr[recvLEN];		// TODO - need to fix a value so that this will not take up too much memory.
 uint8_t serCmd[recvLEN];
@@ -47,6 +48,7 @@
    ,space01
    ,space02
    ,space03
+   ,font9x24
 };
 
 // TODO - Need to be able to let user add custom fonts from outside of the library
```

## History


