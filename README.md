## 五五开五子棋
+ 由c语言大作业简单修改而来。
+ 控制台界面五子棋，支持无禁手和有禁手（简单禁手）。以后可能加入图形界面。
+ 叫五五开是因为理论上黑棋是必胜的。
+ 大概能在1-3秒算5层，3-15秒算5-7层，限制了节点数3M。
+ 算杀模块有点慢，可能要等几秒，限制了节点数70k。
+ 地毯谱来自[棋软收藏站](http://game.onegreen.net/Soft/HTML/45951.html)。
### 编译运行
+ 请确保renjubook和主程序在同一路径下。
+ Windows: 推荐使用VS2015或以上版本，点开Renju.vcxproj即可，记得开O2优化
+ Linux: make。

### How to Run
+ Windows: Visual Studio >= 2015
+ Linux: make
+ please ensure that `renjubook` is in the same path with the executable program.