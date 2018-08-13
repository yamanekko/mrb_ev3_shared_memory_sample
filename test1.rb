# coding: utf-8

def log(logger, msg)
	value = logger.write(msg)
	if !value
		EV3RT::LCD.print("b log error!!")
	else
		EV3RT::LCD.print("b log ok")
	end
end

#for log
logger = EV3RT::Serial.new(EV3RT::SIO_PORT_BT)

counter = 0
# 初期処理が終わったら寝て周期タスクが開始するのを待つ
EV3RT::Task.sleep

loop do
	# 共有変数の値を表示
	val1 = EV3RT::SharedMemory[1]
	val2 = EV3RT::SharedMemory[2]
	msg = "test1_task val1:#{val1}, val2:#{val2}\r\n"
	log(logger, msg)

	# val1の方だけ共有変数の値を+1する
	EV3RT::SharedMemory[1] = val1 + 1

	EV3RT::Task.sleep
end #loop

