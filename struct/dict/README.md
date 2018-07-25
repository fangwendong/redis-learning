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
   
 * 3.使用到的几个hash算法
     

     1.针对int的hash函数
     
              unsigned int dictIntHashFunction(unsigned int key) {
                  key += ~(key << 15);
                  key ^= (key >> 10);
                  key += (key << 3);
                  key ^= (key >> 6);
                  key += ~(key << 11);
                  key ^= (key >> 16);
                  return key;
              }
       
     2.MurmurHash2算法
        
              unsigned int dictGenHashFunction(const void *key, int len) {
                  /* 'm' and 'r' are mixing constants generated offline.
                   They're not really 'magic', they just happen to work well.  */
                  uint32_t seed = dict_hash_function_seed;
                  const uint32_t m = 0x5bd1e995;
                  const int r = 24;

                  /* Initialize the hash to a 'random' value */
                  uint32_t h = seed ^len;

                  /* Mix 4 bytes at a time into the hash */
                  const unsigned char *data = (const unsigned char *) key;

                  // 长度大于等于4的情况
                  while (len >= 4) {
                      uint32_t k = *(uint32_t *) data;   // 4*8=32, 取4个字节当作uint32

                      k *= m;
                      k ^= k >> r;
                      k *= m;

                      h *= m;
                      h ^= k;

                      data += 4;
                      len -= 4;
                  }
     
                  /* Handle the last few bytes of the input array  */
                  // 剩下的长度小于4
                  switch (len) {
                      case 3:
                          h ^= data[2] << 16;
                      case 2:
                          h ^= data[1] << 8;
                      case 1:
                          h ^= data[0];
                          h *= m;
                  };

                  /* Do a few final mixes of the hash to ensure the last few
                   * bytes are well-incorporated. */
                  h ^= h >> 13;
                  h *= m;
                  h ^= h >> 15;

                  return (unsigned int) h;
              }
              
     3. djb hash算法
     
              unsigned int dictGenCaseHashFunction(const unsigned char *buf, int len) {
                  unsigned int hash = (unsigned int) dict_hash_function_seed;
                  while (len--)
                      hash = ((hash << 5) + hash) + (tolower(*buf++)); /* hash * 33 + c */
                  return hash;
              }
