/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* Node, List, and Iterator are the only data structures used currently. */


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

/* Functions implemented as macros */
#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l,m) ((l)->dup = (m))
#define listSetFreeMethod(l,m) ((l)->free = (m))
#define listSetMatchMethod(l,m) ((l)->match = (m))

#define listGetDupMethod(l) ((l)->dup)
#define listGetFree(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)


// 声明函数
/* Prototypes */
list *listCreate(void);   //  创建链表
void listRelease(list *list);  // 释放掉链表占用的内存
list *listAddNodeHead(list *list, void *value);   // 在list头部添加节点
list *listAddNodeTail(list *list, void *value);   // 在list尾部添加节点
list *listInsertNode(list *list, listNode *old_node, void *value, int after);   // 在list中插入节点,位置在 *old_node的前面或者后面
void listDelNode(list *list, listNode *node);  // 删除节点
listIter *listGetIterator(list *list, int direction); //迭代器
listNode *listNext(listIter *iter);  // 使用迭代器 *iter 遍历下一个节点
void listReleaseIterator(listIter *iter);   // 释放迭代器内存
list *listDup(list *orig);   // 复制链表
listNode *listSearchKey(list *list, void *key);  // 链表查找函数
listNode *listIndex(list *list, long index);    // 查找第n个节点
void listRewind(list *list, listIter *li);   // 获得从头部节点开始的迭代器
void listRewindTail(list *list, listIter *li);  // 获得从尾部节点开始的迭代器
void listRotate(list *list);

/* Directions for iterators */
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
