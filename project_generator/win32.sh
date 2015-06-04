set -e

rm -rf ../proj.win32
mkdir ../proj.win32
cd ../proj.win32
cmake ../ -G "Visual Studio 12 2013"

