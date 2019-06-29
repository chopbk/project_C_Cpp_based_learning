# Cấu trúc bảng băm 

Cặp khóa-giá trị (items) sẽ được lưu trữ dưới dạng một `struct`

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

Bảng băm lưu trữ một mảng các con trỏ tới các item theo cấu trúc chi tiết dưới đây:

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```
## Khởi tạo và xóa

Chúng ta cần định nghĩa một hàm khởi tạo ban đầu cho mỗi biến `ht_item` (thành phần trong bảng băm). Hàm này sẽ cấp phát một đoạn bộ nhớ có kích thước của một `ht_item` và copy 2 chuỗi `k` và `v` vào một bộ nhớ mới qua hàm `strdup(const char* s)`. Hàm này là hàm static vì nó chỉ được gọi nội bộ.

```c
// hash_table.c
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
   /*strdup(const char *s) This function returns a pointer to a null-terminated byte 
   string, which is a duplicate of the string pointed to by s. The memory obtained is 
   done dynamically using malloc and hence it can be freed using free().*/
    return i;
}
```

Hàm chức năng tiếp theo tạo một bảng băm mới, `size` là số lượng item chúng ta có thể lữu trữ. Hiện tại nó có giá trị 53. Chúng ta sẽ mở rộng nó trong phần [Thay đổi kích thước bảng](/LearnC/write_a_hash_table/06-resizing). Bảng băm được khởi tạo thông qua hàm calloc để gán tất cả các giá trị ban đầu với giá trị NULL. Lúc này bảng băm là rỗng.

```c
// hash_table.c
ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}
```

Tiếp theo cần các hàm để xóa `ht_items` và `ht_hash_tables` thông qua hàm `free` để giải phóng các vùng nhớ đã cấp phát để tránh lỗi [memory
leaks](https://en.wikipedia.org/wiki/Memory_leak) khi chương trình đang hoạt động.

```c
// hash_table.c
//delete items (key-value)
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

//delete hash table
void ht_del_hash_table(ht_hash_table* ht) {
    //loop in all pointer items and call ht_del_item
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}
```
Trong hàm `main` sẽ có một đoạn để khai báo bảng băm và một đoạn xóa bảng băm

```c
// main.c
#include "hash_table.h"

int main() {
    //define new hash table
    ht_hash_table* ht = ht_new();
    ...
    //delete hash table
    ht_del_hash_table(ht);
}
```

Next section: [Các hàm băm](/LearnC/write_a_hash_table/03-hashing)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)