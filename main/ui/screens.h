#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t* arcs[4];
extern lv_obj_t* labels[4];

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *volt_0;
    lv_obj_t *volt_1;
    lv_obj_t *volt_2;
    lv_obj_t *volt_3;
    lv_obj_t *p_0;
    lv_obj_t *p_1;
    lv_obj_t *p_2;
    lv_obj_t *p_3;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/