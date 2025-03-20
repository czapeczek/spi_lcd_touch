#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include "driver/adc.h"

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
            // volt
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.volt = obj;
            lv_obj_set_pos(obj, 45, 42);
            lv_obj_set_size(obj, 150, 150);
            lv_arc_set_value(obj, 25);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // voltage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.voltage = obj;
            lv_obj_set_pos(obj, 80, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Text");
        }
    }
    
    tick_screen_main();
}

int32_t read_adc_voltage() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);

    // esp_adc_cal_characteristics_t adc_chars;
    // esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, &adc_chars);

    int raw_value = adc1_get_raw(ADC1_CHANNEL_7);
    // uint32_t voltage = esp_adc_cal_raw_to_voltage(raw_value, &adc_chars);

    //ESP_LOGI(TAG, "Reading adc");
     return raw_value;
}


void tick_screen_main() {
    int32_t voltage = read_adc_voltage(); // Get ADC voltage value
    
    // Map ADC value (0-4095) to arc range (10-40)
    int arc_value = 10 + (voltage * 30) / 4095;
    
    // Update the arc value
    lv_arc_set_value(objects.volt, arc_value);

    // Format text for label (max 32 characters)
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "V: %ld mV", voltage);
    printf(buffer);
    // Update the label text
    lv_label_set_text(objects.voltage, buffer);
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
