# Compilation and running instructions

1. Go into WSL Ubuntu by opening the command line and running `start ubuntu.exe`
2. Navigate to the assignment's directory by entering `cd /mnt/d/School/BCIT/COMP8042/Assignments/...`
3. Create a `build` directory by entering `mkdir build`
4. Navigate to the `build` directory
5. Use `cmake` to create a `make` file from the project's `CMakeLists.txt` file by entering `cmake ..`
6. Build the project by entering `make`
7. Run the build by entering `./[Project Name]`, where `[Project Name]` is what is specified in the `project()` parameter of the `CMakeLists.txt` file