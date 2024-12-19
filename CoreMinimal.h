#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>
#include <random>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <regex>

using namespace std;
using namespace this_thread;
using namespace chrono;

typedef unsigned int u_int;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define SLEEP(_duration, _time) sleep_for(_duration(_time))
#define STRING(value) to_string(value)
#define INLINE inline

#define UTF8
#ifdef UTF8
#define InitUTF8 SetConsoleOutputCP(CP_UTF8)
#else
#define InitUTF8 locale::global(locale("fr-FR"))
#endif