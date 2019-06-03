#pragma once

#include <string>
using namespace std;

enum class CPUStates {
        S_USER = 1,
        S_NICE,
        S_SYSTEM,
        S_IDLE,
        S_IOWAIT,
        S_IRQ,
        S_SOFTIRQ,
        S_STEAL,
        S_GUEST,
        S_GUEST_NICE
};

class Path{
public:
    static string basePath() {
        return "/proc/";
    }

    static string cmdPath() {
        return "/cmdline";
    }

    static string statusPath() {
        return "/status";
    }

    static string statPath() {
        return "/stat";
    }

    static string upTimePath() {
        return "uptime";
    }

    static string memInfoPath() {
        return "meminfo";
    }

    static string versionPath() {
        return "version";
    }

    static string etcPasswd() {
        return "/etc/passwd";
    }

    static string cpuInfo() {
        return "cpuinfo";
    }

    static string osInfo() {
        return "/etc/os-release";
    }
};

class ParameterSize {
    public:
    static int defaultSize() {
        return 12;
    }

    static int userSize() {
        return 18;
    }

    static int cmdSize() {
        return 30;
    }
};