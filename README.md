# oop_final_-reupload-
2024 reupload
這份專題是物件導向程式設計的期末專題，專題的內容需用到物件導向的三大觀念「封裝」、「繼承」、「多型」，

因此誕生了這份作品《別踩尖刺兒》！

《別踩尖刺兒》是一款參考了steam上一款名為《超級雞馬》的派對遊戲而做出來的遊戲，遊戲內容主要是讓玩家們由左邊快速的通關到右邊的旗幟，

在過程中可以放置一些陷阱，像是冰塊、蜘蛛網、砲彈之類的來阻止其他人前進，但同樣的也要注意，這些陷阱也會害到自己！

# 開啟遊戲
![GITHUB](https://github.com/czsczsczs2/oop_project/blob/master/OOP_Photo/interface.png)


# 選角畫面
![GITHUB](https://github.com/czsczsczs2/oop_project/blob/master/OOP_Photo/md_images/select.jpg)


# 放置陷阱
![GITHUB](https://github.com/czsczsczs2/oop_project/blob/master/OOP_Photo/md_images/trap.jpg)


# 遊戲中
![GITHUB](https://github.com/czsczsczs2/oop_project/blob/master/OOP_Photo/md_images/gaming.jpg)


# 結束畫面
![GITHUB](https://github.com/czsczsczs2/oop_project/blob/master/OOP_Photo/md_images/victory.jpg)

**DEMO影片**
https://youtu.be/wR0NvpHaOCs


# 待改進
1.畫面看起來還是很卡，不知道是動畫不夠多張還是其他原因導致畫面不順

2.code的內容大多數不工整，且不精確

3.並未使用git作為版控，導致merge極度的困難

4.server端沒有一個防範調封包的時候的狀況處理

5.陷阱道具數量太少

---------**以下心得**-----------

這一次算是我第一次跟團隊一起製作一個專案，大家都被分到不同的負責工作

我是負責網路連線的部分的，我真的覺得網路連線的這個過程，極度的難處理

一開始再做初版的連線的時候，只能一台連進來server，

我完全不知道發生什麼事了，於是東測西測了一個晚上之後，才把4人連線的方法弄出來，

但這還是個開始，當開始正式要使用到連線部分的時候，發現封包沒法依我們想要的型態傳輸，於是乎又搞了好幾個小時去研究如何傳輸其他的資料型態，

接著下一個災難，**掉封包**，這也是我最沒有辦法的一部分，因為我完全不知道封包從哪開始掉的也不知道從哪開始debug，於是我想到了電腦網路所教的TCP，讓client和server透過特定的值來確認連線狀況，這個方法雖然有用，但有時候關鍵的封包還是會掉，我也就放棄處理它了，畢竟掉關鍵封包的機率不高(ﾟ∀ﾟ)，還有一堆拎拎叩叩的網路相關的東西我就不贅述了。

總體來說，我覺得我這次做的這些事情大概有80%都跟物件導向沒有關係，我反而有種是再複習電腦網路所教的知識，並加以運用到我的專題上面，
某種意義上來說，好像也不錯，不過剩下20%就是真的去幫忙其他人處理UI和判定部份的問題了

經過這一次的團隊經驗和專題製作的經驗過後，我想應該對這些有初步的認識了，希望我下一次能做出更好的作品


**2021/01/24**

