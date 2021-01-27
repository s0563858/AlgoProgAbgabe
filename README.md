# Programmierkonzepte und Algorithmen: Projekt (Aufgabe 4)

## RGB ZU GRAYSCALE, HISTOGRAMM, HELLIGKEIT

### Projektstruktur

Im Ordner *Documentation* findet man die Dokumentation zum Projekt. Ordner *src* enthählt den Quellcode des Projekts. Im Ordner *test* sind Skripts enthalten, mit denen die Anwendung getestet wurde.

### Kompilierung 

Die gegebene Anwendung wurde in C++ implementiert. Abhängigkeiten: OpenMP und OpenCV. Wenn OpenCV in folgenden Ordnern installiert wurde: 

`/usr/local/Cellar/opencv/4.4.0_2/lib` und `/usr/local/Cellar/opencv/4.4.0_2/include/opencv4`
, dann kann die Anwendung unter **macOS** wie folgt kompiliert werden:

`clang++  -I /usr/local/Cellar/opencv/4.4.0_2/include/opencv4 -L /usr/local/Cellar/opencv/4.4.0_2/lib -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -Xpreprocessor -fopenmp -lomp -std=c++11 -fasm-blocks main.cpp -o yourFileProgram`

Unter **Windows** kann die Anwendung mit Visual Studio leider nicht kompiliert werden. Das hat zwei Gründe:

1. Der Visual Studio Compiler unterstützt folgende OpenMP-Anweisung nicht: `reduction(max: variableName)` (wird erst ab OpenMP 3.1 unterstützt - MSVC nutzt aber OpenMP 2.0)
2. MSVC verbietet die Nutzung von Inline-Assembler in parallelen Code-Abschnitten 


Um die Anwendung dennoch demonstrieren zu können, wurden Videos aufgenommen auf denen die Anwendung demonstriert wurde. Im ersten Video werden die wichtigsten Funktionalitäten gezeigt: RgbToGrayscale, Brightness und Histogram.

![](Documentation/mainFeatures.mov)

Im zweiten Video wird die Ausführungszeit der RgbToGrayscale Operation ohne Assembler (*-cpp* Argument) und mit Assembler verglichen. 

![](Documentation/cppAsm.mov)
