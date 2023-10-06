#pragma once

#ifdef _DEBUG
#ifdef UNICODE                                                                                      

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#else                                                                                                    

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")   

#endif                                                                                                   


#endif      
#define _WIN32_WINNT 0x0600

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN 

#include <windows.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>

#include "DxDefine.h"