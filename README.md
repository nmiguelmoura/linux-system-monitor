# Linux System Monitor
Utility to monitor linux system through command line.

### Libraries needed
Ncurses library is needed to run the program.To install run:
`sudo apt-get install libncurses5-dev libncursesw5-dev`

### Running instructions with CMAKE
1. Navigate to project folder and add a folder `./build`;
2. Navigate to `./build` folder and run the command `cmake ..`;
3. Run the command `make && ./system_monitor` to run the program.

## Running instructions without CMAKE
1. Navigate to project folder;
2. Run the command `g++ main.cpp utils.cpp process_parser.cpp sys_info.cpp process.cpp process_container.cpp -lncurses && ./a.out`.