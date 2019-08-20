# Resizing

Hiện tại bảng băm của chúng ta đang dùng kích thước cố định, nếu có thêm nhiều item nữa được chèn vào thì bảng sẽ bị đầy, việc sử dụng kích thước cố định như vậy không được khuyến khích bởi: 
- Hiệu suất bảng băm giảm dần với tỷ lệ xung đột cao
- Bảng băm sẽ chỉ chứa được một số lượng item nhất định, nếu chúng ta muốn chèn thêm, tính năng insert sẽ thất bại

Để giảm thiểu các rủi ro trên, chúng ta có thể tăng kích thước của bảng băm khi kích thước bảng lớn và gần đầy. Dựa vào giá trị count được lưu trong struct, mỗi khi chèn hoặc xóa, chúng ta sẽ tính toán giá trị `load` - giá trị tỉ lệ của lượng bucket trên tổng số bucket. Nếu nó lớn hoặc bé hơn một giá trị nhất định, chúng ta sẽ tăng hoặc giảm giá trị kích thước bảng băm
- Tăng nếu load > 0.7
- Giảm nếu load < 0.1

Để thay đổ kích thước, chúng ta tạo một bảng băm lớn gấp rưỡi hoặc gaaspd dôi so với hiện tại và chèn tất cả các giá trị không bị xóa vào đó.

Kích thước mới phải là số nguyên tố gấp đôi hoặc một nửa kích thước hiện tại. chúng ta có thể tìm số nguyên tố bé nhất mà lớn hơn giá trị gấp đôi hoặc 1 nửa kích thước bảng băm hiện tại. 

Đầu tiên, định nghĩa các hàm để tìm số nguyên tố tiếp theo với 2 file, `prime.h` và `prime.c`
```c
// prime.h
int is_prime(const int x);
int next_prime(int x);
```
```c
// prime.c
#include <math.h>
#include "prime.h"

/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime(const int x) {
    if(x < 2){ return -1;}
    if(x < 4) {return 1;}
    if((x%2) == 0) {return 0;}
    for(int i = 3; i <= floor(sqrt((double)x)); i+= 2)){
        if((x % i) == 0){
            return 0;
        }
    }
    return 1;
}
/*
 * Return the next prime after x, or x if x is prime
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
```

Tiếp theo chúng ta sẽ cập nhật hàm `ht_new` để hỗ trợ việc tạo một bảng băm với kích thước nhất định. Chúng ta sẽ tạo một hàm mới `ht_new_sized`
```c
//hash_table.c
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}
ht_hash_table* ht_new(){
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}
```
Tiếp theo là hàm thay đổi kích thước, trong hàm này đầu tiên chúng ta sẽ kiểm tra giá trị kích thước có bé hơn giá trị `HT_INITIAL_BASE_SIZE` chúng ta sẽ khởi tạo một bảng băm mới với kích thước mong muốn. Tất cả các giá trị không NULL và không bị đánh dấu là đã xóa sẽ được chèn vào bảng mới.

```c
//hash_table.c
static void ht_resize(ht_hash_table* ht, const int base_size){
    if(base_size < HT_INITIAL_BASE_SIZE){
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}
```
Để đơn giản hơn trong việc thay đổi kích thước, định nghĩa hai hàm cho việc tăng và giảm
```c
// hash_table.c
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
```

Kiểm tra khi `load` của bảng băm khi thực hiện chèn hoặc xóa. 
```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    // ...
}


void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    // ...
}
```
Next section: [Phụ lục](/LearnC/write_a_hash_table/07-appendix)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)
