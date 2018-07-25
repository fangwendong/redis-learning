## 重点关注的几点
* 1.字典相关的几个结构体

       dict由hash table存储key-value， hash table数组每一个元素存放dictEntry链接的链表头结点，dictEntry节点存放key-value

      typedef struct dictEntry {
          void *key;
          union {
              void *val;
              uint64_t u64;
              int64_t s64;
              double d;
          } v;
          struct dictEntry *next;
      } dictEntry;

      typedef struct dictht {
          dictEntry **table;  // 指向dictEntry数组的指针
          unsigned long size; //哈希表table的大小，初始化大小为4
          unsigned long sizemask;  // size - 1 ,用来对hash值求与计算获得index
          unsigned long used;   // 已经赋值了的数量
      } dictht;

      typedef struct dict {
          dictType *type; // 方法
          void *privdata;  // 保存key和value
          dictht ht[2];   //  hash table
          long rehashidx; // 如果rehashidx=-1表示没有进行rehash,如果如果rehashidx>-1，则表示正在进行rehash,搬运的位置是rehashidx
          int iterators; /* number of iterators currently running */
      } dict;
      
 * 2.动态扩容方法 int dictRehash(dict *d, int n) 
 
   为了对dictht进行动态扩容，rehash方法将ht[0]中的值搬n个到ht[1]中，
   分批次进行搬运，直到ht[0]中的值都搬到ht[1]上，再将ht[1]指针交给ht[0]，rehashidx=-1，完成此次rehash过程
   
 * 3.几个hash算法

         
