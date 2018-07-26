* 动态字符串sds特性

 包含普通 char * 的特性，有个头部sdshdr包含sds的长度，类型，内存等信息。跟据不同的长度将sds分为5种类型，方便内存的扩充
 
* 宏的特殊用法

      struct __attribute__ ((__packed__)) sdshdr5 {
          unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
          char buf[];
      };
      struct __attribute__ ((__packed__)) sdshdr8 {
          uint8_t len; /* used */
          uint8_t alloc; /* excluding the header and null terminator */
          unsigned char flags; /* 3 lsb of type, 5 unused bits */
          char buf[];
      };
      struct __attribute__ ((__packed__)) sdshdr16 {
          uint16_t len; /* used */
          uint16_t alloc; /* excluding the header and null terminator */
          unsigned char flags; /* 3 lsb of type, 5 unused bits */
          char buf[];
      };
      struct __attribute__ ((__packed__)) sdshdr32 {
          uint32_t len; /* used */
          uint32_t alloc; /* excluding the header and null terminator */
          unsigned char flags; /* 3 lsb of type, 5 unused bits */
          char buf[];
      };
      struct __attribute__ ((__packed__)) sdshdr64 {
          uint64_t len; /* used */
          uint64_t alloc; /* excluding the header and null terminator */
          unsigned char flags; /* 3 lsb of type, 5 unused bits */
          char buf[];
      };

      // T=5 时 SDS_HDR_VAR(T,s) = struct sdshdr5 *sh = (void*)((s)-(sizeof(struct sdshdr##T)))
      #define SDS_HDR_VAR(T,s) struct sdshdr##T *sh = (void*)((s)-(sizeof(struct sdshdr##T)));
      #define SDS_HDR(T,s) ((struct sdshdr##T *)((s)-(sizeof(struct sdshdr##T))))
