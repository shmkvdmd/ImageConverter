- Поддерживается конвертация BMP/JPEG/PPM<br />
Для работы необходим пакет LibJPEG<br />
Пример расположения пакета:<br />
libjpeg/<br />
├── include/<br />
│  &emsp; ├── jconfig.h<br />
│  &emsp; ├── jerror.h<br />
│  &emsp; ├── jmorecfg.h<br />
│  &emsp; └── jpeglib.h<br />
└── lib/<br />
   &emsp; ├── Debug<br />
   &emsp; │   └── libjpeg.a<br />
   &emsp; └── Release<br />
     &emsp; &emsp;   └── libjpeg.a<br />
```
mkdir debug
cd debug
cmake ../ImgConverter -DCMAKE_BUILD_TYPE=Debug -DLIBJPEG_DIR=<путь к пакету libjpeg>
cmake --build .
imgconv first_sample.jpg second_sample.ppm
```
