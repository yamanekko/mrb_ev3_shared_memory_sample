#include "ev3api.h"
#include "syssvc/serial.h"	// for Bluetooth(log)
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/string.h"


#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

// LCDフォントサイズ
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

// メインタスク
void main_task(intptr_t unused)
{
	static mrb_state *mrb = NULL;
	mrb_value ret;

	mrb = mrb_open();
	struct RClass * ev3rt = mrb_class_get(mrb, "EV3RT");

	mrb_define_const(mrb, ev3rt, "TEST1_TASK_ID", mrb_fixnum_value(TEST1_TASK));
	mrb_define_const(mrb, ev3rt, "MAIN_TASK_ID", mrb_fixnum_value(MAIN_TASK));
	mrb_define_const(mrb, ev3rt, "TEST1_CYC_ID", mrb_fixnum_value(TEST1_CYC));

	#include "app_ruby.h"

	ret = mrb_load_irep (mrb, main_code);
	if(mrb->exc){
		if(!mrb_undef_p(ret)){
			ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
			ev3_lcd_draw_string("EV3way-ET ERR", 0, CALIB_FONT_HEIGHT*1);
			mrb_value s = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
			if (mrb_string_p(s)) {
				ev3_lcd_draw_string(RSTRING_PTR(s), 0, CALIB_FONT_HEIGHT*3);
				serial_wri_dat(SIO_PORT_BT, RSTRING_PTR(s), RSTRING_LEN(s));
			} else {
				ev3_lcd_draw_string("error unknown", 0, CALIB_FONT_HEIGHT*3);
			}
		}
	}
	mrb_close(mrb);
	ext_tsk();
}

// 周期ハンドラ
void cyclick_handler(intptr_t exinf) {
	wup_tsk(TEST1_TASK);
}

void test1_task(intptr_t exinf) {
	static mrb_state *mrb = NULL;
	mrb_value ret;
	mrb = mrb_open();

	struct RClass * ev3rt = mrb_class_get(mrb, "EV3RT");
	mrb_define_const(mrb, ev3rt, "TEST1_TASK_ID", mrb_fixnum_value(TEST1_TASK));
	mrb_define_const(mrb, ev3rt, "MAIN_TASK_ID", mrb_fixnum_value(MAIN_TASK));
	mrb_define_const(mrb, ev3rt, "TEST1_CYC_ID", mrb_fixnum_value(TEST1_CYC));

	#include "test1_ruby.h"

	ret = mrb_load_irep (mrb, test1_code);
	if(mrb->exc){
		if(!mrb_undef_p(ret)){
			ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
			ev3_lcd_draw_string("EV3way-ET ERR", 0, CALIB_FONT_HEIGHT*1);
			mrb_value s = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
			if (mrb_string_p(s)) {
				ev3_lcd_draw_string(RSTRING_PTR(s), 0, CALIB_FONT_HEIGHT*3);
				serial_wri_dat(SIO_PORT_BT, RSTRING_PTR(s), RSTRING_LEN(s));
			} else {
				ev3_lcd_draw_string("error unknown", 0, CALIB_FONT_HEIGHT*3);
			}
		}
	}
	mrb_close(mrb);
}

int _fini(void){
	return 0;
}
