# CardGame
#注 由于笔记本分辨率（1920 * 1080）原因，游戏界面太长，无法看到下面的位置，所以展示的界面采用的是900 * 980分辨率。低分辨率、不修改level_1.json文件情况下，图片整体是不重叠的。  

#演示视频 https://github.com/user-attachments/assets/c9384702-1010-43be-8e18-d7555518f41f  

#对于可扩展性，可由以下步骤实现：  
1.level_1.json中添加新的卡片信息  
<img width="652" height="455" alt="level_1" src="https://github.com/user-attachments/assets/5585b392-fe31-4d45-98a7-f46861745e3e" />  
2.CardResConfig文件中，添加卡牌的资源获取方式，返回新添加卡牌类型的资源地址  
<img width="835" height="665" alt="CardResConfig" src="https://github.com/user-attachments/assets/8c83a91e-0273-4bd5-94a6-d541c8f9ae34" />  
3.CardModel中添加新的枚举类型  
<img width="642" height="691" alt="修改CardModel" src="https://github.com/user-attachments/assets/2c900d30-75ee-4dc6-98db-680daed06bd3" />  
4.CardView文件中添加新资源的加载方式，在CardView触摸绑定的回调函数中添加新的if分支，用于处理新类型，更改回退逻辑添加新的方法  
<img width="1301" height="382" alt="CardView" src="https://github.com/user-attachments/assets/db767b51-8ed3-4d19-8f9d-692c71c2c9d3" />  
<img width="923" height="325" alt="CardView_1" src="https://github.com/user-attachments/assets/b3d2e9b7-24ba-4502-ace3-444f43c3fae6" />  
5.在CardController中，为新类型添加处理方法，修改匹配逻辑  
<img width="1265" height="425" alt="CardController" src="https://github.com/user-attachments/assets/849d1d82-fcdb-4390-8189-d87ff5540fb9" />  

#项目整体介绍  
#GameController通过startGame方法，传入关卡的配置文件名，调用GameModelFromLevelGenerator::generateGameModel方法，解析level_1.json文件，将相应的数据加工为CardModel类型，放在LevelConfig对象的容器里（静态数据）。用返回的LevelConfig对象构造GameModel对象（存储运行时的游戏数据）。  

#调用GameModelFromLevelGenerator::generateGameView方法，传入GameModel对象构造GameView，GameView初始化的过程中构造一系列的CardView视图，为每一个CardView添加卡片触摸处理的回调函数；GameView上添加回退标签，绑定触摸事件。  

#CardView对象在初始化的过程中，加载相应的资源，生成CardManager对象，CardManager对象保存CardModel对象的引用和CardView对象的指针，将CardView的点击处理函数设置为CardManager的回调函数；CardManager对象初始化中在CardIdManagerMap中添加CardModel的id和对应Manager对象的映射关系（CardIdManagerMap为单例模式，可以通过该类，知道cardId，便可获得对应的CardManager对象和CardView对象，方便CardController中封装的卡片处理函数使用），另将每张CardView绑定相应的事件触摸点击事件。  

#匹配逻辑：通过回退栈顶状态的id和CardIdManagerMap中的映射关系，获得CardManager对象，再通过CardManager的CardModel引用获得face卡面面值，大一，或小一进行匹配成功。  




