#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_memory_utils.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"
#include "lv_demos.h"

//==============================added start
#define USE_SQUARELINE 1
#if USE_SQUARELINE
#include "export/ui.h"

static uint8_t pic_num = 1;
//static void screen_img_num4event_handler(lv_obj_t * obj, lv_event_t event)
static void screen_img_num4event_handler(lv_event_t * e)
{
	//switch (event)
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
				pic_num ++;
				if(pic_num == 6) pic_num = 1;
				switch (pic_num)
				{
						case 1:
							lv_img_set_src(ui_Image4,&ui_img_pic001_png);
							break;
						case 2:
							lv_img_set_src(ui_Image4,&ui_img_pic002_png);
							break;
						case 3:
							lv_img_set_src(ui_Image4,&ui_img_pic003_png);
							break;
						case 4:
							lv_img_set_src(ui_Image4,&ui_img_pic004_png);
							break;
						case 5:
							lv_img_set_src(ui_Image4,&ui_img_pic005_png);
							break;		
						default:
							break;
				}
	}
		break;
	default:
		break;
	}
}
#endif
//==============================added end


void app_main(void)
{
    bsp_display_cfg_t cfg = {
        .lv_adapter_cfg = ESP_LV_ADAPTER_DEFAULT_CONFIG(),
        .rotation = ESP_LV_ADAPTER_ROTATE_270,
        .tear_avoid_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_TRIPLE_PARTIAL,
        .touch_flags = {
            .swap_xy = 1,
            .mirror_x = 0,
            .mirror_y = 1
        }};
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    bsp_display_lock(-1);

#if USE_SQUARELINE
//1280*800 
	ui_init();
	//lv_obj_set_event_cb(ui_Screen1, screen_img_num4event_handler);
	lv_obj_add_event_cb(ui_Screen1, screen_img_num4event_handler, LV_EVENT_ALL, NULL);
#else
    //lv_demo_music();
    //lv_demo_benchmark();
    lv_demo_widgets();
#endif

    bsp_display_unlock();
}