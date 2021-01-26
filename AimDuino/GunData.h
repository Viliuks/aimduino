#pragma once
#include <string>
#include <vector>
#include "Structs.h"
namespace GunData
{

    struct data
    {
        std::string type;
        std::vector<Vector2D> bullet_loc;
        float bullet_timeout;
        int bullet_amt;
    };

    data assault_rifle{
        "Assault Rifle",
        {{1.390706, -2.003941},
        {-0.214273, -1.840234},
        {2.210737, -1.672510},
        {1.699878, -1.500770},
        {0.007140, -1.325012},
        {-0.668176, -1.145237},
        {-1.175558, -0.961445},
        {-1.515004, -0.773636},
        {-1.686516, -0.581810},
        {-1.690092, -0.385967},
        {-1.525734, -0.396569},
        {-1.193441, -0.733642},
        {-0.693213, -1.000503},
        {-0.037107, -1.189752},
        {0.600735, -1.301389},
        {1.107362, -1.335417},
        {1.482968, -1.291832},
        {1.727553, -1.170637},
        {1.841117, -0.971832},
        {1.823660, -0.695412},
        {1.675181, -0.341383},
        {1.395682, -0.198849},
        {0.985162, -0.556116},
        {0.443621, -0.837492},
        {-0.480163, -1.025957},
        {-1.448433, -1.121513},
        {-1.946427, -1.124163},
        {-1.973433, -1.033903},
        {-1.529451, -0.850737}},
        133.3333333333,//119.99999999997//133.3333333333 //132.3333 
        30
    };
    data m249{
        "M249",
        {{0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004},
        {0, -2.7500000000000004}},
        116,//119.99999731779099
        100
    };


    data lr_rifle{
        "LR300 Assault-Rifle",
        {{0.098365, -1.004928},
        {0.248588, -1.243594},
        {0.404267, -1.326823},
        {0.575667, -1.254616},
        {0.631181, -1.028647},
        {0.569555, -0.828739},
        {0.390789, -0.712323},
        {0.089350, -0.605972},
        {-0.365843, -0.509685},
        {-0.691274, -0.423460},
        {-0.806332, -0.347301},
        {-0.711016, -0.281203},
        {-0.405327, -0.226662},
        {0.017535, -0.198184},
        {0.223004, -0.178030},
        {0.372370, -0.160197},
        {0.486685, -0.144685},
        {0.565951, -0.131492},
        {0.619331, -0.112067},
        {0.593446, -0.105835},
        {0.532511, -0.101924},
        {0.436526, -0.100332},
        {0.305490, -0.101062},
        {0.135575, -0.104112},
        {-0.538737, -0.109481},
        {-1.225084, -0.117171},
        {-1.448371, -0.127181},
        {-1.208600, -0.139512}},
        120.0,
        30
    };

    data mp5{
        "MP5",
        {{0.000000, -0.868838},
        {0.000000, -1.173380},
        {-0.000000, -1.328222},
        {-0.510388, -1.333363},
        {-1.176909, -1.188803},
        {-1.312047, -0.894541},
        {-0.915804, -0.524294},
        {-0.033171, -0.431041},
        {0.723751, -0.384924},
        {0.996136, -0.341315},
        {0.789709, -0.300215},
        {0.149808, -0.261623},
        {-0.309771, -0.225539},
        {-0.555951, -0.191964},
        {-0.672225, -0.160897},
        {-0.658592, -0.132338},
        {-0.515054, -0.106288},
        {-0.241609, -0.082746},
        {0.057219, -0.061711},
        {0.215329, -0.043186},
        {0.340328, -0.027168},
        {0.434668, -0.013659},
        {0.498350, -0.002659},
        {0.531373, 0.005835},
        {0.533738, 0.011818},
        {0.505444, 0.015294},
        {0.446492, 0.016261},
        {0.356881, 0.014721},
        {0.236612, 0.010672}},
        100.0,
        30
    };
}