#!/bin/sh
rm app_ruby.h
rm test1_ruby.h

/Users/yuri/git/mruby/bin/mrbc -g -Bmain_code -oapp_ruby.h app_ruby.rb
/Users/yuri/git/mruby/bin/mrbc -g -Btest1_code -otest1_ruby.h test1.rb

# mrbcで生成されたバイトコードに含まれている "extern const uint8_t" を消去するための暫定処理 
# mrubyが修正された場合は不要になる。残していても害はないはず
ruby delete_extern.rb

cd ..
make clean
make app=mrb_ev3_shared_memory_sample

# rename app ->shared_memory_sample すべて名前がappになるので、別の名前をつけてわかりやすくしておく
cp app shared_memory_sample
