## 双向链表

插入节点和删除节点的时间复杂度都是O(1),适合用于插入删除频繁的场合

## 几个重要的结构体

      // 双向链表的节点
      typedef struct listNode {
          struct listNode *prev;
          struct listNode *next;
          void *value;  // value存void指针
      } listNode;

      typedef struct listIter {
          listNode *next;
          int direction;
      } listIter;

      // 双向链表 list
      typedef struct list {
          listNode *head;  // 头部节点
          listNode *tail;  // 尾部节点
          void *(*dup)(void *ptr); // dup 方法
          void (*free)(void *ptr); // free 方法
          int (*match)(void *ptr, void *key); // match 方法
          unsigned long len;  // 链表长度
      } list;
