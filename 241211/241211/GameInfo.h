#pragma once

#include <iostream>
#include <ctime>

#define SAFE_DELETE(p) if(p) {delete p; p=nullptr;}
