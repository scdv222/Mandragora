#pragma once

#define NOMINMAX

#pragma warning(push, 0)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>
#include <DbgHelp.h>
#include <tlhelp32.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#undef  WIN32_LEAN_AND_MEAN

#ifndef PCH_H
#define PCH_H

#include "globals/globals.h"
#include "game/offsets/offsets.h"
#include "game/game.h"
#include "game/object_manager.h"
#endif