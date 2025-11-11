mkdir build
Copy-Item src/ -Destination build/ -Recurse
Copy-Item config/ -Destination build/ -Recurse
cd build
cmake ..