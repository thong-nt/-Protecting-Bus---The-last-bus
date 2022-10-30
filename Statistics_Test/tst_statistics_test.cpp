#include <QString>
#include <QtTest>
#include <QFile>
#include "statistics.hh"
#include <map>
#include <fstream>
#include <iostream>
#include <QCoreApplication>


class Statistics_Test : public QObject
{
    Q_OBJECT

public:
    Statistics_Test();
    ~Statistics_Test();

private slots:
    void test_Add_Stat();
    void test_Add_Stat_existed();
    void test_Save();
};

Statistics_Test::Statistics_Test()
{

}

Statistics_Test::~Statistics_Test()
{

}

void Statistics_Test::test_Add_Stat()
{
    Player_Statistics * player= new Player_Statistics();
    Statistics * AddrecordStat=new Statistics;
    std::string id="1234";
    std::string name="Minh";
    int score=100;
    player->ID=id;
    player->Name=name;
    player->score=score;

    AddrecordStat->Add_Stat(player->Name,player->Name,player->score);

    for(std::map<std::string, Player_Statistics*>::iterator i= AddrecordStat->listplayer.begin();i!=AddrecordStat->listplayer.end();i++){
        if(i->first==id){
            QCOMPARE(i->second->Name,player->Name);
            QCOMPARE(i->second->score,200);
        }
    }
}
void Statistics_Test::test_Add_Stat_existed()
{
    Player_Statistics * player= new Player_Statistics();
    Statistics * AddrecordStat=new Statistics;
    std::string id="1234";
    std::string name="Minh";
    int score=100;
    player->ID=id;
    player->Name=name;
    player->score=score;
    AddrecordStat->Add_Stat(player->ID,player->Name,player->score);
    player->score=200;
    AddrecordStat->Add_Stat(player->ID,player->Name,player->score);
    for(std::map<std::string, Player_Statistics*>::iterator i= AddrecordStat->listplayer.begin();i!=AddrecordStat->listplayer.end();i++){
        if(i->first==id){

            QCOMPARE(i->second->score,score);
        }
    }

}
void Statistics_Test::test_Save()
{
    Statistics * AddrecordStat= new Statistics();
    QString datapath = QCoreApplication::applicationDirPath();

    QFile file(datapath + "/Database.txt");
    bool opened = file.open(QIODevice::ReadOnly);
    QVERIFY(opened);

    std::string id="1234";
    std::string name="Minh";
    int score=100;
    AddrecordStat->Add_Stat(id,name,score);
    AddrecordStat->save_Database();

    std::map<std::string, Player_Statistics*> x;
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
                    x[parsed_data[0]] = player;
                }
            }
            file.close();
        }
    }
    for(std::map<std::string, Player_Statistics*>::iterator i= x.begin();i!=x.end();i++){
        if(i->first==id){
            QCOMPARE(i->second->Name,name);
            QCOMPARE(i->second->score,score);
        }
    }
}
QTEST_APPLESS_MAIN(Statistics_Test)

#include "tst_statistics_test.moc"
