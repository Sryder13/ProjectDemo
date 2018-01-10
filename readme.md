This is a demo meant to work with my "Ryd3ngine" project, add the library that is compiled to libs/Ryd3ngine/lib and the header files to libs/Ryd3ngine/include to be able to compile

Compile Instructions
Linux:
1.	Ensure that the needed make systems are installed on the system:
a.	C++ compilation environment
b.	CMake
Note: Cmake can be obtained on Debian Stretch with the command:
apt install cmake
2.	Ensure that the needed Libraries are installed on the system:
a.	SDL2
b.	SDL2_Image
c.	SDL2_Mixer
d.	AssImp
e.	GLEW
Note: These can be obtained on Debian Stretch for compilation with the command:
apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libassimp-dev libglew-dev
3.	Ensure that the GLM library headers are located within the libs/glm/ directory of the project folder
4.	Ensure that the Ryd3ngine library headers are located with the libs/Ryd3ngine/include/ directory, and the Ryd3ngine static library is located within the libs/Ryd3nging/lib/ directory
5.	Navigate to the base folder of the project in a terminal
6.	Run the command: cmake .
7.	Run the command: make
8.	The compilation will complete and the binary will be output in the bin/ directory

Windows (Visual Studio 2017)
1.	Ensure that the needed make systems are installed on the system:
a.	CMake
b.	Microsoft Visual C++ compiler
2.	Download the needed libraries and place them in a directory of your choice with the correct file paths (library files in lib\ and header files in include\) for example, can use C:\CPPLibraries
a.	SDL2
b.	SDL2_Image
c.	SDL2_Mixer
d.	AssImp
e.	GLEW
3.	Ensure that the GLM library headers are located within the libs/glm/ directory of the project folder
4.	Ensure that the Ryd3ngine library headers are located in the libs/Ryd3ngine/include/ directory, and the Ryd3ngine static library is located within the libs/Ryd3nging/lib/ directory
5.	Open the CMake GUI and navigate the source code to the base Project Directory, and choose another directory of your choice for where to build the binaries
6.	Add an Entry for CMAKE_PREFIX_PATH and set the path to be where you placed the other libraries
7.	Select Configure and select the version of Microsoft Visual Studio you are using, make sure to select the correct version depending on whether the libraries you installed were 32-bit or 64-bit to match the version you want to create.
8.	If any libraries are not found, their location can be set manually in the CMake GUI now, with Configure being pressed again afterwards
9.	Select Generate
10.	Open the created Project File, and Build the Project
11.	The output directory will be where you selected in the CMake GUI in the bin folder.
