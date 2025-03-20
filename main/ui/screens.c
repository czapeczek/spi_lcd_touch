#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_scale_create(parent_obj);
            lv_obj_set_pos(obj, 38, 35);
            lv_obj_set_size(obj, 165, 164);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_OUTER);
            lv_scale_set_range(obj, 10, 40);
            lv_scale_set_total_tick_count(obj, 31);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_label_show(obj, true);
        }
        {
            // voltage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.voltage = obj;
            lv_obj_set_pos(obj, 45, 42);
            lv_obj_set_size(obj, 150, 150);
            lv_arc_set_value(obj, 25);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
