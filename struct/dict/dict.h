/* Hash Tables Implementation.
 *
 * This file implements in-memory hash tables with insert/del/replace/find/
 * get-random-element operations. Hash tables will auto-resize if needed
 * tables of power of two in size are used, collisions are handled by
 * chaining. See the source code for more information... :)
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

#include <stdint.h>

#ifndef __DICT_H
#define __DICT_H

#define DICT_OK 0
#define DICT_ERR 1

/* Unused arguments generate annoying warnings... */
#define DICT_NOTUSED(V) ((void) V)

/*
 *dict由2个hash table存储key-value
 * hash table由 dictEntry链接的链表组成
 * dictEntry节点存放这key-value
 *
 */

// 存放k-v 链表节点
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


// dict的方法
typedef struct dictType {
    unsigned int (*hashFunction)(const void *key);   // 根据key计算hash值
    void *(*keyDup)(void *privdata, const void *key);   // 复制key
    void *(*valDup)(void *privdata, const void *obj);   // 复制value
    int (*keyCompare)(void *privdata, const void *key1, const void *key2); // 比较两个key
    void (*keyDestructor)(void *privdata, void *key);  // 销毁key
    void (*valDestructor)(void *privdata, void *obj);   // 销毁value
} dictType;

/* This is our hash table structure. Every dictionary has two of this as we
 * implement incremental rehashing, for the old to the new table. */
// hash table
typedef struct dictht {
    dictEntry **table;  // 指向dictEntry数组的指针
    unsigned long size; //哈希表table的大小，初始化大小为4
    unsigned long sizemask;  // size - 1 ,用来对hash值求与计算获得index
    unsigned long used;   // 已经赋值了的数量
} dictht;

// 字典
typedef struct dict {
    dictType *type; // 方法
    void *privdata;  // 保存key和value
    dictht ht[2];   //  hash table
    long rehashidx; /* rehashing not in progress if rehashidx == -1 */
    int iterators; /* number of iterators currently running */
} dict;

/* If safe is set to 1 this is a safe iterator, that means, you can call
 * dictAdd, dictFind, and other functions against the dictionary even while
 * iterating. Otherwise it is a non safe iterator, and only dictNext()
 * should be called while iterating. */
// 字典的迭代器
typedef struct dictIterator {
    dict *d;
    long index;
    int table, safe;
    dictEntry *entry, *nextEntry;
    /* unsafe iterator fingerprint for misuse detection. */
    long long fingerprint;
} dictIterator;

typedef void (dictScanFunction)(void *privdata, const dictEntry *de);

/* This is the initial size of every hash table */
#define DICT_HT_INITIAL_SIZE     4

/* ------------------------------- Macros ------------------------------------*/
#define dictFreeVal(d, entry) \
    if ((d)->type->valDestructor) \
        (d)->type->valDestructor((d)->privdata, (entry)->v.val)


// 宏定义 给dict的entry设置value
#define dictSetVal(d, entry, _val_) do { \
    if ((d)->type->valDup) \
        entry->v.val = (d)->type->valDup((d)->privdata, _val_); \
    else \
        entry->v.val = (_val_); \
} while(0)

#define dictSetSignedIntegerVal(entry, _val_) \
    do { entry->v.s64 = _val_; } while(0)

#define dictSetUnsignedIntegerVal(entry, _val_) \
    do { entry->v.u64 = _val_; } while(0)

#define dictSetDoubleVal(entry, _val_) \
    do { entry->v.d = _val_; } while(0)

#define dictFreeKey(d, entry) \
    if ((d)->type->keyDestructor) \
        (d)->type->keyDestructor((d)->privdata, (entry)->key)

#define dictSetKey(d, entry, _key_) do { \
    if ((d)->type->keyDup) \
        entry->key = (d)->type->keyDup((d)->privdata, _key_); \
    else \
        entry->key = (_key_); \
} while(0)


// 自定义的比较两个key的方法
#define dictCompareKeys(d, key1, key2) \
    (((d)->type->keyCompare) ? \
        (d)->type->keyCompare((d)->privdata, key1, key2) : \
        (key1) == (key2))

#define dictHashKey(d, key) (d)->type->hashFunction(key)
// key
#define dictGetKey(he) ((he)->key)                      //字典节点保存的 key
// value 四种形式
#define dictGetVal(he) ((he)->v.val)                    //字典节点he的一个对象值
#define dictGetSignedIntegerVal(he) ((he)->v.s64)       //字典节点he的64有符号整数值
#define dictGetUnsignedIntegerVal(he) ((he)->v.u64)     //字典节点he的64无符号整数值
#define dictGetDoubleVal(he) ((he)->v.d)                //字典节点he的浮点型数据

#define dictSlots(d) ((d)->ht[0].size+(d)->ht[1].size)
#define dictSize(d) ((d)->ht[0].used+(d)->ht[1].used)
#define dictIsRehashing(d) ((d)->rehashidx != -1)

/* API */
dict *dictCreate(dictType *type, void *privDataPtr); // 创建一个字典
int dictExpand(dict *d, unsigned long size);  // 扩大字典内存,从一个hash table变成2个
int dictAdd(dict *d, void *key, void *val);  // 往字典中加入 k-v
dictEntry *dictAddRaw(dict *d, void *key);   // 往字典中加入key
int dictReplace(dict *d, void *key, void *val); // 替换字典中k-v
dictEntry *dictReplaceRaw(dict *d, void *key);   // 单纯地加一个节点
int dictDelete(dict *d, const void *key);  //删除dict中的key,并且释放k-v
int dictDeleteNoFree(dict *d, const void *key);  //删除dict中的key,并且不释放k-v
void dictRelease(dict *d);  //删除整个字典
dictEntry * dictFind(dict *d, const void *key);   // 通过key查找节点,O(n) n为链表长度
void *dictFetchValue(dict *d, const void *key);  // 通过key获取value
int dictResize(dict *d);
dictIterator *dictGetIterator(dict *d);  //不安全的字典迭代器
dictIterator *dictGetSafeIterator(dict *d); // 安全的迭代器
dictEntry *dictNext(dictIterator *iter);    // 迭代下一个节点
void dictReleaseIterator(dictIterator *iter);  // 释放迭代器内存
dictEntry *dictGetRandomKey(dict *d);   // 随机地获取一个k-v
unsigned int dictGetSomeKeys(dict *d, dictEntry **des, unsigned int count);  // 随机地获取count个k-v,结果不一定有count个
void dictGetStats(char *buf, size_t bufsize, dict *d);
unsigned int dictGenHashFunction(const void *key, int len); // 根据key的长度采用不同的hash方法
unsigned int dictGenCaseHashFunction(const unsigned char *buf, int len);  // 计算hash的函数
void dictEmpty(dict *d, void(callback)(void*));  // 清空dict
void dictEnableResize(void); // set  dict_can_resize = 1;
void dictDisableResize(void); // set dict_can_resize = 0;
int dictRehash(dict *d, int n);
int dictRehashMilliseconds(dict *d, int ms);
void dictSetHashFunctionSeed(unsigned int initval);
unsigned int dictGetHashFunctionSeed(void);
unsigned long dictScan(dict *d, unsigned long v, dictScanFunction *fn, void *privdata);

/* Hash table types */
extern dictType dictTypeHeapStringCopyKey;
extern dictType dictTypeHeapStrings;
extern dictType dictTypeHeapStringCopyKeyValue;

#endif /* __DICT_H */
