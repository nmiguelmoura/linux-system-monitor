#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "constants.h"
#include "utils.h"
#include "processParser.h"
#include "sys_info.h"
#include "process.h"
#include "processContainer.h"
#include <curses.h>

void printLine(WINDOW* win, std::string str, int y = 2, int x = 2, std::string type = "mvwprintw") {
    char char_array[str.length() + 1];
    strcpy(char_array, str.c_str());

    if(type == "mvwprintw") {
        mvwprintw(win, y, x, char_array);
    } else {
        wprintw(win, char_array);
    }
    
}

void writeSysInfoToConsole(SysInfo sys, WINDOW* sys_win) {
    sys.setAttributes();

    wattron(sys_win, COLOR_PAIR(1));
    string temp = "OS: " + sys.getOSName();
    printLine(sys_win, temp, 2, 2);


    temp = "Kernel Version: " + sys.getKernelVersion();
    printLine(sys_win, temp, 3, 2);

    temp = "CPU: ";
    printLine(sys_win, temp, 4, 2);

    wattron(sys_win, COLOR_PAIR(2));
    temp = Utils::getProgressbar(sys.getCpuPercent());
    printLine(sys_win, temp, 0, 0, "wprintw");

    wattron(sys_win, COLOR_PAIR(1));
    temp = "Other cores: ";
    printLine(sys_win, temp, 5, 2);

    std::vector<std::string> val = sys.getCoreStats();
    wattron(sys_win, COLOR_PAIR(2));
    for(int a = 0; a < val.size(); a++) {
        temp = val[a];
        printLine(sys_win, val[a], 6 + a, 2);
    }

    wattron(sys_win, COLOR_PAIR(1));
    temp = "Memory: ";
    printLine(sys_win, temp, 10, 2);
    
    wattron(sys_win, COLOR_PAIR(2));
    temp = Utils::getProgressbar(sys.getMemPercent());
    printLine(sys_win, temp, 0, 0, "wprintw");

    wattron(sys_win, COLOR_PAIR(1));
    temp = "Total processes: " + sys.getTotalProc();
    printLine(sys_win, temp, 11, 2);

    temp = "Running Processes: " + sys.getRunningProc();
    printLine(sys_win, temp, 12, 2);

    temp = "Up Time: " + Utils::convertToTime(sys.getUptime());
    printLine(sys_win, temp, 13, 2);
}

void getProcessListToConsole(ProcessContainer procs, WINDOW* procs_win) {
    procs.refreshList();

    wattron(procs_win, COLOR_PAIR(3));
    int col = 2;
    printLine(procs_win, "PID", 1, 2);

    col += ParameterSize::defaultSize();
    printLine(procs_win, "User", 1, col);

    col += ParameterSize::userSize();
    printLine(procs_win, "CPU (%)", 1, col);

    col += ParameterSize::defaultSize();
    printLine(procs_win, "RAM (MB)", 1, col);

    col += ParameterSize::defaultSize();
    printLine(procs_win, "Up Time", 1, col);

    col += ParameterSize::defaultSize();
    printLine(procs_win, "CMD", 1, col);

    std::vector<std::string> list = procs.getList();
    for(int a = 0; a < list.size(); a++) {
        printLine(procs_win, list[a], a + 2, 2);
    }
}

void printMain(SysInfo sys, ProcessContainer procs) {
    initscr();
    noecho();
    cbreak();
    start_color();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *sys_win = newwin(17, xMax - 1, 0, 0);
    WINDOW *procs_win = newwin(15, xMax - 1, 18, 0);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    while(true) {
        box(sys_win, 0, 0);
        box(procs_win, 0, 0);
        writeSysInfoToConsole(sys, sys_win);
        getProcessListToConsole(procs, procs_win);
        wrefresh(sys_win);
        wrefresh(procs_win);
        refresh();
        sleep(1);
    }

    endwin();
}

int main() {

    ProcessContainer procs;

    SysInfo sys;

    printMain(sys, procs);

    return 0;
}