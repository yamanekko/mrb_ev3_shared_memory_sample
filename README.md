# EV3RT用の共有メモリを使用したサンプルコード

TOPPERS/EV3RTの上で動作するmrubyは、タスクごとに別のmrubyVMが起動します。
そのため、複数タスクを実行する場合、タスク間でのデータ（変数）の共有ができません。
共有するにはいくつかの方法が考えられますが、ここではひとまず数値のみ共有できるようにしました。

* SharedMemory[1]は２つのタスクが交互に１を加算する例
* SharedMemory[2]はMain taskでインクリメントし、test1 taskは表示のみする例

Bluetoothでログを受信すると実行結果を確認できます。

