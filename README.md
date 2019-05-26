# Linux System Monitor
Utility to monitor linux system through command line.

### Running instructions with CMAKE
1. Navigate to project folder and add a folder `./build`;
2. Navigate to `./build` folder and run the command `cmake ..`;
3. Run the command `make && ./system_monitor` to run the program.

## Running instructions without CMAKE
1. Navigate to project folder;
2. Run the command `g++ main.cpp process_parser.cpp utils.cpp && ./a.out`. 