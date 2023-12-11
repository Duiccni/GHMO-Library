# GHMO-Library
Newest Lime Graphic Library

* Same things as https://github.com/Duiccni/LGL-C-Graphics-Library (Old one) BUT way more optimized and i found lot of fricking big bugs i fixed them dont worry.

### Font Anti Aliasing (Look with Magnifier.)
* ![image](https://github.com/Duiccni/GHMO-Library/assets/143947543/150fc1fb-9eb3-43a1-a077-e29b3533826f)

### Better Image File (.rbis24 or .rbis32) Options
```
graphics::surface* bad_apple
= graphics::read_binary_into_surface("image-2.bin", graphics::RBIS_24B /* graphics::RBIS_AUTO */);

// graphics::reverse_colors(*bad_apple);
graphics::black_and_white(*bad_apple);
graphics::slight_blur(*bad_apple);
```
* ![image](https://github.com/Duiccni/GHMO-Library/assets/143947543/8a4f5827-d164-4476-b04a-d0a591c96e51)

### 3D Library Option
* ``` #define _INCLUDE_3DH 1 ```
* ![image](https://github.com/Duiccni/GHMO-Library/assets/143947543/5529bb49-6c35-426a-aad2-c19b6c222bd9)
