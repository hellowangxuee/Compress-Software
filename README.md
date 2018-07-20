# Compress-Software

文件压缩系统采用C++编写，使用map、vector、priority_queue、pair对数据进行操作，根据字符出现的概率来充当权值构建哈夫曼树，采用自底向上的编码方式，解压时可根据构造的哈夫曼树从根扫描至叶节点。
