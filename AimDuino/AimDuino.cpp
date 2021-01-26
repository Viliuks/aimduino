
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "GunData.h"
#include "ModifierData.h"
#include "Serial.h"
#include "Structs.h"

float sensitivity = 0.4f;
float fov = 75.f;

unsigned short port = 1;
bool shoot = false;
bool sentMouse = false;
bool sent = false;

Serial* SP;
std::string rctbl;
GunData::data selectedWeapon;
ModifierData::data selectedModifier;

std::map<unsigned short, GunData::data> weaponKeys{ {1, GunData::assault_rifle},
                                                   {2, GunData::mp5},
                                                   {3, GunData::m249},
                                                   {4, GunData::lr_rifle} };

std::map<unsigned short, ModifierData::data> modifierKeys{
    {0, ModifierData::none},         {1, ModifierData::silencer},
    {2, ModifierData::muzzle_boost}, {3, ModifierData::x8_scope},
    {4, ModifierData::x16_scope},    {5, ModifierData::muzzle_brake} };

Vector2D AngleConversion(Vector2D angles, float modifier)
{
    Vector2D pixel_return;
    pixel_return.x = (angles.x / (-0.03 * static_cast<double>(sensitivity) * 3.0 * (fov / 100.0))) * modifier;  //* 1.2;
    pixel_return.y = (angles.y / (-0.03 * static_cast<double>(sensitivity) * 3.0 * (fov / 100.0))) * modifier;  //* 1.2;
    return pixel_return;
}

std::string SetWeapon(GunData::data s, ModifierData::data mod)
{
    std::string rctbl = "2," + std::to_string(s.bullet_timeout * mod.timeOffset) + "," + std::to_string(s.bullet_amt);
    for (Vector2D vect : s.bullet_loc)
    {
        Vector2D v = AngleConversion(vect, mod.recoilMod);
        rctbl += ",";
        rctbl += std::to_string(v.x) + "," + std::to_string(v.y);
    }
    return rctbl;
}

void InterruptThread()
{
    while (true)
    {
        if ((GetKeyState(VK_LBUTTON) & 0x100))
        {
            if (shoot != true && (GetKeyState(VK_RBUTTON) & 0x100))
            {
                shoot = true;
                sentMouse = false;
            }
        }
        else
        {
            if (shoot != false)
            {
                shoot = false;
                sentMouse = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void SerialThread()
{
    char incomingData[256] = "";
    int dataLength = 255;
    int readResult = 0;
    while (SP->IsConnected())
    {
        if (!sent)
        {
            SP->WriteData(rctbl.c_str(), rctbl.size());
            sent = true;
        }
        if (!sentMouse)
        {
            std::string out = shoot ? "1,1" : "0,1";
            SP->WriteData(out.c_str(), rctbl.size());
            sentMouse = true;
        }
        readResult = SP->ReadData(incomingData, dataLength);
        incomingData[readResult] = 0;
         printf("%s", incomingData);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void PrintComSelect()
{
    printf("Input COM port for arduino: ");
    int tmpp;
    std::cin >> tmpp;
    if (std::cin.fail() || tmpp < 0 || tmpp > 256)
    {
        printf("Invalid COM port!\n");
        PrintComSelect();
    }
    std::wstring pcCommPort = L"\\\\.\\COM";
    pcCommPort += std::to_wstring(tmpp);
    SP = new Serial(pcCommPort.c_str());
    if (SP->IsConnected())
    {
        printf("We're connected\n");
    }
    else
    {
        printf("Unable to connect to COM%i\n", tmpp);
        PrintComSelect();
    }
}

void PrintWeaponSelect()
{
    printf("%s\n%s\n%s\n%s\n%s\n", "==== WEAPON SELECT ====", "1. Assault Rifle",
        "2. MP5", "3. M249", "4. LR");
    int weap = 0;
    std::cin >> weap;
    if (weap < 1 || weap > 4)
    {
        printf("Couldn't select weapon\n");
        PrintWeaponSelect();
    }
    for (auto& d : weaponKeys)
    {
        if (d.first == weap)
        {
            selectedWeapon = d.second;
            printf("Selected weapon -> %s\n", selectedWeapon.type.c_str());
            break;
        }
    }
}

void PrintModSelect()
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "==== MOD SELECT ====", "0. None",
        "1. Silencer", "2. Muzzle boost", "3. 8x scope", "4. 16x scope",
        "5. Muzzle brake");
    int mod = 0;
    std::cin >> mod;
    if (mod < 0 || mod > 5)
    {
        printf("Couldn't select modifier\n");
        PrintModSelect();
    }
    for (auto& m : modifierKeys)
    {
        if (m.first == mod)
        {
            selectedModifier = m.second;
            printf("Selected modifier -> %s\n", selectedModifier.type.c_str());
            break;
        }
    }
}

int main()
{
    std::string input;
    printf("Input your sensitivity (default 0.4): ");
    std::cin >> input;
    sensitivity = atof(input.c_str());
    printf("Input your FOV (default 75): ");
    std::cin >> input;
    fov = atof(input.c_str());

    PrintComSelect();
    PrintWeaponSelect();
    PrintModSelect();
    rctbl = SetWeapon(selectedWeapon, selectedModifier);

    std::thread interruptThread(InterruptThread);
    interruptThread.detach();
    std::thread serialThread(SerialThread);
    serialThread.detach();

    while (true)
    {
        //system("cls");
        printf("Current weapon: %s\n Current mod: %s\n",
            selectedWeapon.type.c_str(), selectedModifier.type.c_str());
        PrintWeaponSelect();
        PrintModSelect();
        rctbl = SetWeapon(selectedWeapon, selectedModifier);
        sent = false;
    }
}
