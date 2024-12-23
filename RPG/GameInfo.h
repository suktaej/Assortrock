#pragma once
#include <iostream>
#define SAFE_DELETE(p) if(p) {delete p;p=nullptr;}
