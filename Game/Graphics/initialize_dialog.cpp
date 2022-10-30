#include "Graphics/initialize_dialog.hh"
#include "ui_initialize_dialog.h"
#include <QDebug>
#include <QMessageBox>

using namespace CourseSide;

Initialize_Dialog::Initialize_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Initialize_Dialog)
{
    ui->setupUi(this);
    Initialize_Dialog *dialog = this;
    dialog->resize(387,166);

    QPixmap bkgnd(":/Image/dark_bg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->OK_Button->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->Cancel_Button->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->title_LB->setStyleSheet("QLabel {border: none; color: white;}");
    ui->Driver_nameLB->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->ID_numLB->setStyleSheet("QLabel {border: none; color: white;}");
    ui->P2_checkBox->setStyleSheet("QCheckBox {border: none; color: white;}");

    ui->Driver_nameLB_2->setStyleSheet("QLabel {background-color : none; color: white;}");
    ui->Driver_nameLB_2->setDisabled(true);
    ui->ID_numLB_2->setStyleSheet("QLabel {border: none; color: white;}");
    ui->ID_numLB_2->setDisabled(true);

    stat = new Statistics();
}

Initialize_Dialog::~Initialize_Dialog()
{
    delete ui;
}

void Initialize_Dialog::Send_initail_data()
{
    Driver_Name = ui->DName_TB->text();
    Driver_ID = ui->ID_TB->text();
}

void Initialize_Dialog::on_OK_Button_clicked()
{
    Send_initail_data();

//    SimpleMainWindow* engine = new SimpleMainWindow();
//    QImage Tampere_map(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
//    engine->setSize(Tampere_map.width(),Tampere_map.height());
//    engine->setPicture(Tampere_map);
//    engine->Recieve_initail_data(Driver_Name,Driver_ID);
//    emit ingamemode(true);
//    this->close();
//    engine->show();
    if(!ui->P2_checkBox->isChecked())
    {
        if(ui->DName_TB->text() != "" && ui->ID_TB->text() != "")
        {
            Initialize_Dialog::startGame();
        }
        else
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, "Warning", "Please fill all information",QMessageBox::Ok);
        }
    }
    else
    {
        if(ui->DName_TB->text() == "" || ui->ID_TB->text() == "" || ui->ID_TB_2->text() == "" || ui->DName_TB_2->text() == "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, "Warning", "Please fill all information",QMessageBox::Ok);
        }
        else
        {
            Initialize_Dialog::startGame();
        }
    }

}

void Initialize_Dialog::startGame()
{
    GameplayWindow* engine = new GameplayWindow();
        QImage Tampere_map(":/Image/kartta_iso_1095x592.png");
        engine->setSize(Tampere_map.width(),Tampere_map.height());
        engine->setPicture(Tampere_map);
        engine->Recieve_initail_data(Driver_Name,Driver_ID);
        engine->AddrecordStat = stat;
        this->close();
        emit ingamemode(true);
        engine->ready_State(true);
        engine->show();
}

void Initialize_Dialog::quit()
{
    QCoreApplication::quit();
}

void Initialize_Dialog::on_P2_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        Initialize_Dialog *dialog = this;
        dialog->resize(387,166);
        ui->ID_numLB_2->setDisabled(true);
        ui->Driver_nameLB_2->setDisabled(true);
        ui->OK_Button->move(ui->OK_Button->x(),ui->OK_Button->y()/1.9);
        ui->Cancel_Button->move(ui->Cancel_Button->x(),ui->Cancel_Button->y()/1.9);
    }else if (arg1 == 2)
    {
        Initialize_Dialog *dialog = this;
        dialog->resize(387,166*1.8);
        ui->ID_numLB_2->setDisabled(false);
        ui->Driver_nameLB_2->setDisabled(false);
        ui->OK_Button->move(ui->OK_Button->x(),ui->OK_Button->y()*1.9);
        ui->Cancel_Button->move(ui->Cancel_Button->x(),ui->Cancel_Button->y()*1.9);
    }
}

void Initialize_Dialog::on_Cancel_Button_clicked()
{
    this->close();
}
