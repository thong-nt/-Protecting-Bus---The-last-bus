#include "logic.hh"
#include "QDebug"
#include <QtCore>

Logic::Logic()
{
}

void Logic::readData()
{
    CourseSide::OfflineReader Read_Json;
    offlinedata_ = Read_Json.readFiles(":/offlinedata/offlinedata/final_bus_liteN.json",":/offlinedata/offlinedata/full_stations_kkj3.json");
}

void Logic::FindRoute()
{
    try {
        Do_again:

        int ran = rand() % offlinedata_->buses.size();
        for (int i = 0; i < ran ; ++i)
        {
            std::list<std::shared_ptr<CourseSide::BusData>>::iterator it1 = offlinedata_->buses.begin();
            if (it1 != offlinedata_->buses.end())
                offlinedata_->buses.erase(it1);
            if (offlinedata_->buses.size() == 0)
                throw std::runtime_error("offlinedata_->buses have no items left");
        }

        if (offlinedata_->buses.front()->routeName.substr(0,10) != "Keskustori")
            goto Do_again;
    } catch (std::runtime_error const& error) {
        std::cerr << "Runtime_error: " << error.what() << std::endl;
    }
}

void Logic::Calculate_time()
{

    if (sec_ == 60)
    {
        min_++;
        sec_ = 0;
    }
    time_ = QTime(min_/60, min_ % 60, sec_);
    sec_++;
    qDebug() << time_;
    Logic::Check_time();
}

void Logic::control_Numb_Alien()
{
    if(number_alien < 5)
    {
        number_alien++;
    }
    emit sendNumAlien(number_alien);
    qDebug() << "Number Alien: " << number_alien;
}

void Logic::Check_time()
{
    emit sendTimer(time_);
    qDebug() << "void: " << time_;
}
