#include <string>
#include <iostream>
#include <fstream>
#pragma once

struct PlayerData
{
    std::string playerName = "Kupo";

    private:
    std::string fileName = "PlayerData.txt";
public:
    void LoadData()
    {       
        std::cout<<"Loading Player Data!!!\n";
        std::ifstream pData;
        pData.open(fileName);
        if(pData.is_open())
        {
            while(!pData.eof())
            {
                std::getline(pData, playerName);
            }

        }
        else
        {
            std::cout<<"Couldn't Load Player Data!!!\n";
        }
    

        pData.close();
    }

    void SaveData()
    {
        std::cout<<"Saving Player Data!!!\n";
        std::ofstream pData;
        pData.open(fileName);
        if(pData.is_open())
        {
            pData << playerName << "\n";
        }
        else
        {
            std::cout<<"Couldn't Save Player Data!!!\n";
        }
        pData.close();

    }
};
