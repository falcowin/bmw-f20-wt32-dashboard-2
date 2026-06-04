#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl.h>

class GUIManager
{
public:
    GUIManager();
    ~GUIManager();

    // Inizializzazione
    void init();
    void update();
    void handleInput();

    // Schermate
    void showSplashScreen();
    void showMainScreen();
    void showMenuScreen();
    void showConnectionError();
    void showSettingsScreen();

    // Aggiornamento dati
    void updateMainScreen(uint16_t rpm, uint8_t speed, uint8_t coolantTemp, 
                         int8_t airTemp, uint8_t fuelLevel, float voltage);
    void updateRPM(uint16_t rpm);
    void updateSpeed(uint8_t speed);
    void updateTemperature(uint8_t temp);
    void updateFuelLevel(uint8_t fuel);

private:
    lv_disp_t* display;
    lv_indev_t* touchpad;
    
    // Elementi GUI
    lv_obj_t* mainScreen;
    lv_obj_t* rpmLabel;
    lv_obj_t* speedLabel;
    lv_obj_t* tempLabel;
    lv_obj_t* fuelLabel;
    lv_obj_t* voltageLabel;
    lv_obj_t* rpmGauge;
    lv_obj_t* speedGauge;
    
    // Funzioni private
    void createMainScreen();
    void createGauges();
    void createMenuButtons();
    void applyTheme();
};

#endif // GUI_H