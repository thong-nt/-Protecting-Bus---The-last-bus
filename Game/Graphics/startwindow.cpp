#include "startwindow.hh"
#include "ui_startwindow.h"
#include "QDebug"
#include "startwindow.hh"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/Image/UFO_chasing_bg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->centralwidget->setFixedSize(bkgnd.width(),bkgnd.height());

    QPixmap pixbus(":/Image/bus.png");
    pixbus = pixbus.scaled(this->size(), Qt::KeepAspectRatio);
    ui->Bus_ImageLB->setPixmap(pixbus.scaled(ui->Bus_ImageLB->width(),ui->Bus_ImageLB->height(),Qt::KeepAspectRatio));
    ui->Bus_ImageLB->move(500,300);

    QPixmap pixtitle(":/Image/Title_name.png");
    pixtitle = pixtitle.scaled(this->size(), Qt::KeepAspectRatio);
    ui->titleLB->setPixmap(pixtitle.scaled(ui->titleLB->width(),ui->titleLB->height(),Qt::KeepAspectRatio));
    ui->titleLB->move(ui->titleLB->x(),ui->titleLB->y());

    QPixmap pixStitle(":/Image/StartMenu.png");
    pixStitle = pixStitle.scaled(this->size(), Qt::KeepAspectRatio);
    ui->StartMLB->setPixmap(pixStitle.scaled(ui->StartMLB->width(),ui->StartMLB->height(),Qt::KeepAspectRatio));
    ui->StartMLB->move(ui->StartMLB->x()+25,ui->StartMLB->y()+35);

    back_sound = new QMediaPlayer();
    back_sound->setMedia(QUrl("qrc:/Media/intro.mp3"));
    back_sound->play();

    ui->startButton->move(ui->startButton->x(),ui->startButton->y()+20);
    ui->startButton->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->LDBButton->move(ui->LDBButton->x(),ui->LDBButton->y()+20);
    ui->LDBButton->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->HTPButton->move(ui->HTPButton->x(),ui->HTPButton->y()+20);
    ui->HTPButton->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->exitButton->move(ui->exitButton->x(),ui->exitButton->y()+20);
    ui->exitButton->setStyleSheet("QPushButton {background-color: #A3C1DA; color: white;}");
    ui->Mute_checkBox->setStyleSheet("QCheckBox {border: none; color: white;}");

    checkLB = false;

    QString datapath = QCoreApplication::applicationDirPath();
    QFile file(datapath + "/Database.txt");
    if(!file.exists())
    {
        file.open(QIODevice::NewOnly);
        file.close();
    }
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::closeMenu(bool a)
{
    if (a == true)
    {
        back_sound->stop();
        this->close();
    }
}

void StartWindow::on_startButton_clicked()
{
    ui->Bus_ImageLB->setVisible(true);
    ui->verticalLayoutWidget->close();
    Initialize_Dialog *dialog = new Initialize_Dialog();
    connect(dialog,&Initialize_Dialog::ingamemode,this,&StartWindow::closeMenu);
    dialog->exec();
}

void StartWindow::on_Mute_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        back_sound->setMuted(false);
    }else if (arg1 == 2)
    {
        back_sound->setMuted(true);
    }
}

void StartWindow::on_LDBButton_clicked()
{
    int count = 1;
    ui->Bus_ImageLB->setVisible(false);
    ui->verticalLayoutWidget->show();
    if (checkLB == false)
    {
       Statistics *LeadersBoard = new Statistics();
       for(auto findit = LeadersBoard->leaders.cbegin(); findit != LeadersBoard->leaders.cend(); ++findit)
       {
           if (count == 11)
               break;

           QLabel *label = new QLabel(this);
           label->setFrameStyle(QFrame::Shadow_Mask | QFrame::NoFrame);
           label->setText(QString::number(count) + ". " + QString::fromStdString(findit->second->Name) + " " + QString::number(findit->second->score));
           label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
           QFont f( "Wide Latin", 12, QFont::Bold);
           label->setFont(f);
           label->setStyleSheet("QLabel {background-color : none; color: white;}");
           ui->verticalLayout->addWidget(label);
           count++;
           checkLB = true;
       }
    }

}
