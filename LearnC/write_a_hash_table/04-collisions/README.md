## Xử lý va chạm

Các hàm băm ánh xạ một lượng vô hạn đầu vào tới một lượng hữu hạn đầu ra. Các khóa đầu vào khác nhau sẽ ánh xạ tới một giá trị chỉ mục của bảng băm, dẫn tới việc xảy ra đụng độ trong bảng băm. Bảng băm phải triển khai một số phương pháp để xử lý các va chạm này.

Bảng băm của chúng sẽ xử lý đụng độ bằng `open addressing` với băm kép `double hashsing`. Băm kép sử dụng hai hàm băm để tính toán chỉ mục mà cặp key-value sẽ được lưu trữ sau `i` lần đụng độ.

Để tìm hiểu thêm về các cách xử lý đụng độ khác, tham khảo phần 7 
[Phụ lục: Các phương pháp xử lý đụng độ khác](/LearnC/write_a_hash_table/07-appendix).

## Băm kép

Sau khi `i` lần đụng độ, giá trị index sẽ được tính toán bằng 

```
index = (hash_a(string) + i * hash_b(string)) % num_buckets
```

Khi không xảy ra đụng độ, `i = 0`, vì vậy giá trị index sẽ chỉ được tính toán qua hàm 
`hash_a`. Nếu có đụng độ xảy ra, giá trị index sẽ được sửa đổi bằng hàm `hash_b`.

Sẽ có khả năng `hash_b` sẽ trả về 0, sẽ làm thành phần để tính toán thứ 2 thành 0. Điều này sẽ làm cho bảng băm sẽ cố gắng thêm một item vào cùng một chỗ trong bảng băm nhiều lần. Chúng ta có thể giảm thiểu điều này bằng cách thêm 1 vào kết quả của hàm băm thứ 2 để đảm bảo nó không bao giờ bằng 0. 

```
index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets
```

## Triển khai

```c
// hash_table.c
static int ht_get_hash(
    const char *s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt*(hash_b + 1)))%num_buckets;
}
```

Next section: [Các hàm sử dụng](/LearnC/write_a_hash_table/05-methods)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)
