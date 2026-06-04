#include "gui.h"
#include "../config.h"
#include "../utils/logger.h"

extern Logger logger;

// Callback per touch screen
static void touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
    // Implementare lettura touch da WT32-SC01
    data->state = LV_INDEV_STATE_REL;
}

GUIManager::GUIManager() : display(nullptr), touchpad(nullptr)
{
}

GUIManager::~GUIManager()
{
    if (display)
    {
        lv_disp_remove(display);
    }
}

void GUIManager::init()
{
    logger.info("Inizializzazione GUI Manager");
    
    // Inizializza LVGL
    lv_init();
    
    // TODO: Inizializza display driver per WT32-SC01
    // display = lv_disp_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    
    // TODO: Inizializza touchpad
    
    applyTheme();
    logger.info("GUI Manager inizializzato");
}

void GUIManager::update()
{
    if (display)
    {
        lv_task_handler();
    }
}

void GUIManager::handleInput()
{
    // Gestisci input touch
}

void GUIManager::showSplashScreen()
{
    logger.info("Visualizzazione splash screen");
    
    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), 0);
    
    // Logo/Titolo
    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "BMW F20\nDASHBOARD");
    lv_obj_set_style_text_color(title, lv_color_hex(0x1E90FF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_48, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -40);
    
    // Subtitle
    lv_obj_t* subtitle = lv_label_create(screen);
    lv_label_set_text(subtitle, "WT32-SC01 Plus");
    lv_obj_set_style_text_color(subtitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(subtitle, &lv_font_montserrat_16, 0);
    lv_obj_align(subtitle, LV_ALIGN_CENTER, 0, 40);
    
    // Loading spinner
    lv_obj_t* spinner = lv_spinner_create(screen, 1000, 60);
    lv_obj_set_size(spinner, 60, 60);
    lv_obj_align(spinner, LV_ALIGN_CENTER, 0, 80);
}

void GUIManager::showMainScreen()
{
    logger.info("Visualizzazione schermata principale");
    
    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(COLOR_BG), 0);
    
    // Griglia principale 2x2
    
    // RPM (alto sinistra)
    lv_obj_t* rpmContainer = lv_obj_create(screen);
    lv_obj_set_size(rpmContainer, 230, 140);
    lv_obj_align(rpmContainer, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(rpmContainer, lv_color_hex(0x2A2A2A), 0);
    lv_obj_set_style_border_color(rpmContainer, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_border_width(rpmContainer, 2, 0);
    lv_obj_set_style_border_opa(rpmContainer, LV_OPA_100, 0);
    
    lv_obj_t* rpmTitle = lv_label_create(rpmContainer);
    lv_label_set_text(rpmTitle, "RPM");
    lv_obj_set_style_text_color(rpmTitle, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_align(rpmTitle, LV_ALIGN_TOP_MID, 0, 5);
    
    rpmLabel = lv_label_create(rpmContainer);
    lv_label_set_text(rpmLabel, "0");
    lv_obj_set_style_text_color(rpmLabel, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_set_style_text_font(rpmLabel, &lv_font_montserrat_32, 0);
    lv_obj_align(rpmLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Velocità (alto destra)
    lv_obj_t* speedContainer = lv_obj_create(screen);
    lv_obj_set_size(speedContainer, 230, 140);
    lv_obj_align(speedContainer, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_bg_color(speedContainer, lv_color_hex(0x2A2A2A), 0);
    lv_obj_set_style_border_color(speedContainer, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_border_width(speedContainer, 2, 0);
    
    lv_obj_t* speedTitle = lv_label_create(speedContainer);
    lv_label_set_text(speedTitle, "VELOCITA'");
    lv_obj_set_style_text_color(speedTitle, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_align(speedTitle, LV_ALIGN_TOP_MID, 0, 5);
    
    speedLabel = lv_label_create(speedContainer);
    lv_label_set_text(speedLabel, "0 km/h");
    lv_obj_set_style_text_color(speedLabel, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_set_style_text_font(speedLabel, &lv_font_montserrat_32, 0);
    lv_obj_align(speedLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Temperatura (basso sinistra)
    lv_obj_t* tempContainer = lv_obj_create(screen);
    lv_obj_set_size(tempContainer, 230, 140);
    lv_obj_align(tempContainer, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_set_style_bg_color(tempContainer, lv_color_hex(0x2A2A2A), 0);
    lv_obj_set_style_border_color(tempContainer, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_border_width(tempContainer, 2, 0);
    
    lv_obj_t* tempTitle = lv_label_create(tempContainer);
    lv_label_set_text(tempTitle, "TEMP MOTORE");
    lv_obj_set_style_text_color(tempTitle, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_align(tempTitle, LV_ALIGN_TOP_MID, 0, 5);
    
    tempLabel = lv_label_create(tempContainer);
    lv_label_set_text(tempLabel, "0°C");
    lv_obj_set_style_text_color(tempLabel, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_set_style_text_font(tempLabel, &lv_font_montserrat_32, 0);
    lv_obj_align(tempLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Carburante (basso destra)
    lv_obj_t* fuelContainer = lv_obj_create(screen);
    lv_obj_set_size(fuelContainer, 230, 140);
    lv_obj_align(fuelContainer, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_style_bg_color(fuelContainer, lv_color_hex(0x2A2A2A), 0);
    lv_obj_set_style_border_color(fuelContainer, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_border_width(fuelContainer, 2, 0);
    
    lv_obj_t* fuelTitle = lv_label_create(fuelContainer);
    lv_label_set_text(fuelTitle, "CARBURANTE");
    lv_obj_set_style_text_color(fuelTitle, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_align(fuelTitle, LV_ALIGN_TOP_MID, 0, 5);
    
    fuelLabel = lv_label_create(fuelContainer);
    lv_label_set_text(fuelLabel, "0%");
    lv_obj_set_style_text_color(fuelLabel, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_set_style_text_font(fuelLabel, &lv_font_montserrat_32, 0);
    lv_obj_align(fuelLabel, LV_ALIGN_CENTER, 0, 0);
}

void GUIManager::showMenuScreen()
{
    logger.info("Visualizzazione menu");
}

void GUIManager::showConnectionError()
{
    logger.warn("Visualizzazione errore connessione");
    
    // TODO: Mostra popup errore connessione OBD2
}

void GUIManager::showSettingsScreen()
{
    logger.info("Visualizzazione impostazioni");
}

void GUIManager::updateMainScreen(uint16_t rpm, uint8_t speed, uint8_t coolantTemp,
                                 int8_t airTemp, uint8_t fuelLevel, float voltage)
{
    updateRPM(rpm);
    updateSpeed(speed);
    updateTemperature(coolantTemp);
    updateFuelLevel(fuelLevel);
}

void GUIManager::updateRPM(uint16_t rpm)
{
    if (rpmLabel)
    {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d", rpm);
        lv_label_set_text(rpmLabel, buffer);
    }
}

void GUIManager::updateSpeed(uint8_t speed)
{
    if (speedLabel)
    {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d km/h", speed);
        lv_label_set_text(speedLabel, buffer);
    }
}

void GUIManager::updateTemperature(uint8_t temp)
{
    if (tempLabel)
    {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d°C", temp);
        lv_label_set_text(tempLabel, buffer);
    }
}

void GUIManager::updateFuelLevel(uint8_t fuel)
{
    if (fuelLabel)
    {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d%%", fuel);
        lv_label_set_text(fuelLabel, buffer);
    }
}

void GUIManager::applyTheme()
{
    logger.info("Applicazione tema");
    
    // TODO: Configurare tema LVGL personalizzato
}