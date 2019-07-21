# Các hàm API được sử dụng

Bảng băm của chúng ta được thực thi qua các API sau
```c
// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
```

## Insert

Để chèn một cặp khóa-giá trị mới, chúng ta cần lặp đi lặp lại việc tìm một chỉ mục mới để tìm kiếm một ô trống trong bảng băm. Sau đó chèn cặp khóa-giá trị trên vào chỉ mục tìm được và tăng giá trị `count` của bảng băm lên 1 đơn vị (một item mới đã được thêm vào). 
```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    } 
    ht->items[index] = item;
    ht->count++;
}
```

## Search

Việc tìm kiếm trong bảng băm cũng tương tự việc chèn vào, tuy nhiên trong mỗi vòng `while`, chúng ta sẽ kiểm tra cho đến khi `khóa` tìm được trong bảng băm trùng với `khóa` mà chúng ta đang tìm kiếm. Nếu vòng while chạm tới giá trị `NULL` trong bảng băm, hàm sẽ trả về `NULL` để chỉ ra rằng tìm thấy item trong bảng băm
```c
//hash_table.c

char *ht_search(ht_hash_table* ht, const char* key){
    int index = ht_get_hash(key, ht->size,0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL){
        if(strcmp(item->key, key) == 0){
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

## Delete 

Xóa giá trị trong bảng băm mà có mở rộng địa chỉ (open addressed) phức tạp hơn việc chèn và tìm kiếm. Item mà chúng ta muốn xóa có thể là một phần trong chuỗi xung đột. Việc xóa nó khỏi bảng sẽ làm ngắn chuỗi trên, và làm cho việc tìm kiếm item trong phần còn lại của chuỗi là không thể. Để xử lý điều trên, thay vì xóa hẳn item, chúng ta sẽ chỉ đánh dấu nó là đã xóa.

Chúng ta đánh dấu item là đã xóa bằng cách thay thế nó bằng một con trỏ tới một item toàn cục đại diện cho việc xóa item

```c
//hash_table.c
static ht_item HT_DELETED_ITEM = {NULL, NULL};

void ht_deleted(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL){
        if(item != &HT_DELETED_ITEM) {
            if(strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht_items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        i++;
    }
    ht->count--;
}
```

Sau khi xóa, chúng ta giảm giá trị count của bảng băm xuống 1 đơn vị.

Ngoài ra cần phải sửa đổi hàm `ht_insert` và `ht_search` để xem xét các vị trí xem có được đánh dấu là bị xóa hay chưa
- Khi thực hiện tìm kiếm, chúng ta sẽ nhảy qua node được đánh dấu là đã xóa
- Khi thực hiện chèn, nếu chạm tới một node được đánh dấu là đã xóa, chúng ta có thể chèn node mới vào đó.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
     // ...
    while (cur_item != NULL && cur_item != HT_DELETED_ITEM) {
        // ...
    }
    // ...
}
char* ht_search(ht_hash_table* ht, const char* key){
    //..
    while(item != NULL)
    {
         if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        // ...
    }
    // ...
}
```

## Update

Bảng băm của chúng ta hiện tại chưa hỗ trợ tính năng Update. Nếu chúng ta chèn hai item cùng một giá trị key, item thứ hai sẽ được chèn vào vị trí tiếp theo của bảng dựa theo kết quả của hàm băm. Khen thực hiện tìm kiếm theo khóa trên, item thứ 2 sẽ không bao giờ được tìm thấy mà sẽ chỉ trả về item thứ nhất.

Chúng ta có thể sửa đổi hàm `ht_insert` để xóa item trước đó để chèn item mới vào đó.
```c
//hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value)
{
    //..
    while (cur_item != NULL && cur_item != HT_DELETED_ITEM) {
        if(strcmp(cur_item->key, key) == 0) {
            ht_del_item(cur_item);
            ht->items[index] = item;
            return;
        }
        //...
    }
    //..
}
```

Next section: [Thay đổi kích thước bảng băm](/LearnC/write_a_hash_table/06-resizing)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)
