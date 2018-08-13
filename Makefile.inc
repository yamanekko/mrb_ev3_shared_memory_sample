# mrubyのパスを環境変数に設定するか、以下を使用してください
# MRUBY_PATH := /usr/local/mruby (ここにmrubyのパスをいれます)

APPL_LIBS += $(MRUBY_PATH)/build/EV3RT/lib/libmruby.a -lm
INCLUDES += -I$(MRUBY_PATH)/include
