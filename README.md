<h1>QMaths</h1>
This C++ maths library imnplements vectors, matricies and quaternions and is intended for use with QGraphics to do the required maths for translation, rotation and scaling of objects in 3D graphics.

<h2>Getting Started in Visual Studio</h2>
Clone this repo from the main page my clicking Code -> Download ZIP.

Unzip the folder, open the project and build it.

Open the project you want to include the library in, and open the project properties (Project -> Properties on the menu bar).
In the C++ section, add 'FOLDER\QMaths\QMaths;' to the Additional Include Directories, replacing FOLDER with the location you unzipped to.

In the Linker section, add 'FOLDER\QMaths\bin\Debug-x64\QMaths' to the Additional Library Directories.

You can now use the library in any CPP file simply by adding

#include <QMaths.h>

to the top of the file.
