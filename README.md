# Summary
STマイクロエレクトロニクス社のドローンキット「STEVAL-DRONE01」向けのソフト開発

# 使用機器

開発に使用するものを表1に示す。

<div style="text-align:center;">表1.使用機器</div>
| 使用機器       | 型格           | バージョン |
| -------------- | -------------- | ---------- |
| ドローンキット | STEVAL-DRONE01 | FCU001V1   |
| 安定化電源     |                |            |
| IDE            | STM32CubeIDE   | 1.0.2      |
| エミュレータ   | ST-LINK/V2     |            |
| FreeRTOS       | CMSIS_V2       | -          |

# Note

デバッグするときはバッテリを接続すること。

バッテリを接続しないと下記のエラーが発生しデバッガとの通信が切断される。

Target is not responding, retrying...