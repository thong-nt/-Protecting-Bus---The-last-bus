#ifndef INITIALIZE_DIALOG_H
#define INITIALIZE_DIALOG_H
/**
  * @file
  * @brief Defines a class that contains methods for handling Dialog that when the player start the game, it obtain
  * the player's name and id, then the player can proceed to gameplay window by clicking start button, or quit
  * the Dialog by clicking cancel, also a checkbox for 2nd player.
  */

#include <QDialog>
#include "Graphics/startwindow.hh"
#include "Graphics/gameplaywindow.hh"
#include "statistics.hh"
/**
 * @brief Initialize_Dialog is a class, which provides methods handling Dialog to obtain player's information
 *
 * The class provides methods that receive data from the user input to line edits, OK push button to start the game, Cancel
 * push button to close the Dialog, checkbox for initialize 2nd player, start the gameplay window.
 *
 */
namespace Ui {
class Initialize_Dialog;
}

    class Initialize_Dialog : public QDialog
    {
        Q_OBJECT

    public:
        QString Driver_Name,Driver_ID;
        /**
         * @brief Default constructor
         * @post initialize the Dialog with size of 387*166, setting its background, 2 line edit for player input info,
         * 2 push buttons to start the game or close the Dialog.
         * @param parent: QWidget object
         */
        explicit Initialize_Dialog(QWidget *parent = nullptr);
        /**
         * @brief Default destructor
         * @post deallocate Initialize_Dialog object
         */
        ~Initialize_Dialog();
        /**
         * @brief Function setting the Driver_Name and Driver_ID variables.
         * @pre -
         * @post Exception guarantee: nothrow.
         */
         void Send_initail_data();
         Statistics * stat;

    signals:
         /**
          * @brief signal emitted the gameplay window has started
          * @param true if the gameplay window has started
          */
         void ingamemode(bool);
         void sendStat(Statistics *);

    private slots:
         /**
          * @brief Function when clicking the OK push button.
          * @pre -
          * @post If either Line edits is empty, throw a warning.
          * Else receiving player's info,the game start with starting gameplaywindow,either the player check the 2nd player checkbox.
          * Exception guarantee: strong.
          */
        void on_OK_Button_clicked();
        /**
         * @brief Function to close the entire game.
         * @pre -
         * @post Exception guarantee: nothrow.
         */
        void quit();
        /**
         * @brief Function to collect information of player 1 and 2 which depend on mode.
         * @pre -
         * @post Exception guarantee: strong.
         */
        void on_P2_checkBox_stateChanged(int arg1);
        /**
         * @brief Function to close the Dialog.
         * @pre -
         * @post Exception guarantee: nothrow.
         */
        void on_Cancel_Button_clicked();
        /**
         * @brief Function to call the gameplaywindow.
         * @pre -
         * @post Create the gameplaywindow object, set the size and picture of the map of Tampere, receive data from the user input
         * and close the Dialog.
         * Exception guarantee: nothrow.
         */
        void startGame();

    private:
        Ui::Initialize_Dialog *ui;
    };
#endif // INITIALIZE_DIALOG_H
