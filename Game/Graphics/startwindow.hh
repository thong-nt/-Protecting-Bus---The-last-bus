#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

/**
  * @file
  * @brief Defines a class that handling the start window of the game.
  */

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QImage>
#include <QMediaPlayer>
#include "Graphics/initialize_dialog.hh"
#include <QKeyEvent>

/**
 * @brief StartWindow is a class, which provides methods handling the start window of the game
 *
 * The class provides methods that using push button to start the initialize_dialog, score leaderboard, quit the game
 * and checkbox to mute/unmute the background sound.
 *
 */

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor
     * @post initialize the startwindow with size, setting its background, background image of a bus, title of the window, background music,
     * 1 checkbox to mute/unmute the game,
     * 4 push buttons to start the dialog before starting the game, how to play, leaderboard and quit the game.
     * @param parent: QWidget object
     */
    explicit StartWindow(QWidget *parent = nullptr);
    /**
     * @brief Default destructor
     * @post deallocate StartWindow object
     */
    ~StartWindow();

public slots:
    /**
     * @brief Function that stop the background music and close StartWindow window .
     * @pre -
     * @post Exception guarantee: nothrow.
     */
    void closeMenu(bool);

private slots:
    /**
     * @brief Function that open the initialize_dialog window .
     * @pre -
     * @post Exception guarantee: nothrow.
     */

    void on_startButton_clicked();
    /**
     * @brief Function that stop the background music.
     * @pre -
     * @post Exception guarantee: nothrow.
     */

    void on_Mute_checkBox_stateChanged(int arg1);
    /**
     * @brief Function that showing the score leaderboard of recent players .
     * @pre -
     * @post CLose the bus image, replace with a widget contain label which is set to player's place, their name and score.
     * .Exception guarantee: nothrow.
     */

    void on_LDBButton_clicked();

private:
    Ui::StartWindow *ui;
    QMediaPlayer *back_sound;
    bool checkLB;
};

#endif // STARTWINDOW_HH
