#include "statistics.hh"
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

Statistics::Statistics()
{
    Statistics::read_Database(QCoreApplication::applicationDirPath() + "/Database.txt");
    Statistics::Sort();
}

Statistics::~Statistics()
{
    while (!listplayer.empty()) {
        Player_Statistics *player_to_be_gone = listplayer.begin()->second;
        listplayer.erase(listplayer.begin());
        delete player_to_be_gone;
    }
}

void Statistics::Add_Stat(std::string Name, std::string ID, int score)
{
    if (listplayer.find(ID) != listplayer.end()) //Find info
        {
            listplayer[ID]->score = score;
        }
        else // Cant find info
        {
            Player_Statistics *player = new Player_Statistics();
            player->ID = ID;
            player->Name = Name;
            player->score = score;
            listplayer[ID] = player;
    }
}

void Statistics::save_Database()
{
    QString datapath = QCoreApplication::applicationDirPath();

    QFile file(datapath + "/Database.txt");
    if(file.exists())
    {
        if(file.open(QIODevice::WriteOnly))
        {
            save_data:
            QTextStream stream(&file);
            for(auto findit = listplayer.cbegin(); findit != listplayer.cend(); ++findit)
            {
                stream << QString::fromStdString(findit->first) << ";" << QString::fromStdString(findit->second->Name) <<";"<<
                          QString::number(findit->second->score) <<"\n";
            }
            file.close();
        }
    }
    else
    {
        file.open(QIODevice::NewOnly);
        file.close();
        goto save_data;
    }
}

void Statistics::read_Database(QString fileName)
{
    QString data;
    QFile file(fileName);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                std::string line = in.readLine().toStdString();
                if(line.empty() || line[0] == '#')
                {
                    continue;
                }
                std::string tmp = line;
                std::vector<std::string> parsed_data;
                size_t pos = 0;
                while (true)
                {
                    pos = tmp.find(";");
                    parsed_data.push_back(tmp.substr(0, pos));
                    if(pos == std::string::npos){break;}
                    tmp = tmp.substr(pos+1);
                }
                if( parsed_data.size() == 3 )
                {
                    Player_Statistics *player = new Player_Statistics();
                    player->ID = parsed_data[0];
                    player->Name = parsed_data[1];
                    player->score = stoi(parsed_data[2]);
                    listplayer[parsed_data[0]] = player;
                }
            }
            file.close();
        }
    }
    else
    {
        file.open(QIODevice::NewOnly);
        file.close();
    }
}

void Statistics::Sort()
{

    for(auto findit = listplayer.cbegin(); findit != listplayer.cend(); ++findit)
    {
        leaders.insert(std::make_pair(findit->second->score,findit->second));
    }
}

void Statistics::print()
{
     for(auto findit = leaders.cbegin(); findit != leaders.cend(); ++findit)
    {
        qDebug() << QString::fromStdString(findit->second->Name) << "," << findit->first;
    }
}
