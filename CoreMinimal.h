#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include <random>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;
using namespace this_thread;
using namespace chrono;
typedef unsigned int u_int;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define SLEEP(_duration, _time) sleep_for(_duration(_time));
#define STRING(_value) to_string(_value)
#define UTF8

#define INLINE inline

#ifdef UTF8
#define InitUTF8 SetConsoleOutputCP(CP_UTF8)
#else
#define InitUTF8 locale::global(locale("fr-FR"));
#endif





