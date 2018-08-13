# coding: utf-8

def log(logger, msg)
	value = logger.write(msg)
	if !value
		EV3RT::LCD.print("log error!!")
	else
		EV3RT::LCD.print("log ok")
	end
end

#for log
logger = EV3RT::Serial.new(EV3RT::SIO_PORT_BT)

# LCD 
led = EV3RT::LED.new()
# led.on(EV3RT::LED_ORANGE)

# 初期処理だけして寝かす
EV3RT::Task.active(EV3RT::TEST1_TASK_ID)
EV3RT::Task.sleep(100)

# 周期ハンドラを開始する
EV3RT::Task.start_cyclic(EV3RT::TEST1_CYC_ID)
EV3RT::Task.sleep(100)

counter = 0
loop do
	counter++
	# 共有変数の値を表示
	# val1はtest1タスクでカウントアップされている、val2はそのまま
	val1 = EV3RT::SharedMemory[1]
	val2 = EV3RT::SharedMemory[2]
	msg = "main_task val1:#{val1}, val2:#{val2}\r\n"
	log(logger, msg)
	# 共有変数の値を+1する
	EV3RT::SharedMemory[1] = val1 + 1
	EV3RT::SharedMemory[2] = val2 + 1
	EV3RT::Task.sleep(500)
end

# led.on(EV3RT::LED_RED)


