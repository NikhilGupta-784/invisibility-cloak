#pragma once

#ifndef CLOTH_H
#define CLOTH_H

#include <iostream>
#include <vector>
#include <string>

class cloth
{
    int Hmin, Smin, Vmin;
    int Hmax, Smax, Vmax;
public:
    std::vector<int> setcloth();
    std::vector<int> setcloth(std::string path);
};

#endif // CLOTH_H
