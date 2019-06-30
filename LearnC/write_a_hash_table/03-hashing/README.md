# Hash function

Trong phần này, chúng ta sẽ tiếp tục với hàm băm

Hàm băm được lựa chọn phải

- Có đầu vào là một chuỗi string và trả về một số từ `0` tới `m`, trong đó `m` là độ dài mong muốn của bảng băm
- Hàm băm phải trả về số sao cho có sự phân phối đồng đều trong khoảng mong muốn, để tránh việc các giá trị khóa khác nhau nhưng lại trả về một giá trị index giống nhau. Nếu không thì sẽ dẫn tới tỷ lệ va chạm cao hơn, làm giảm hiệu năng của bảng băm

## Thuật toán

Chúng ta sẽ sử dụng một hàm băm chuỗi được mô tả bằng đoạn mã giả dưới đây: 
```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i]))
    hash = hash % num_buckets
    return hash
```

Hàm băm này gồm 2 bước

1. Chuyển đổi string thành một số có giá trị lớn
2. Giảm kích thước của số nguyên thành một số nằm trong khoảng cho phép (độ dài của bảng băm) bằng phép `mod` `m`

Giá trị `a` phải là một số nguyên tố lớn hơn kích thước bảng chữ cái. Chúng đang băm chuỗi ASCII với kích thước là 128. Vì vậy cần chọn giá trị `a` lớn hơn 128 (Ví dụ như 153...).

Hàm `char_code` là hàm trả về một số nguyên mà đại diện cho chữ cái (mã ký tự ASCII), dưới đây là ví dụ một hàm băm với chuỗi `cat`, `a` = 153, kích thước bảng băm là 53

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```
Nếu thay đổi giá trị `a` thì chúng ta sẽ có một hàm băm khác.

```
hash("cat", 163, 53) = 3
```

## Triển khai

```c
// hash_table.c
static int ht_hash(const char* s, const int prime_num, const int hash_size) {
    long hash = 0;
    const int len_s = strlen(s);
    for(int i = 0; i < len_s; i++) {
        hash += (long)pow(prime_num,len_s - (i+1)) * s[i];
        hash = hash%hash_size;
    }
    return (int)hash;
}
```

##Ngoại lệ

Một hàm băm lý tưởng sẽ luôn luôn trả về một phân phối đồng đều. Tùy nhiên, đối với bầy kỳ một hàm băm nào cũng đều tồn tại các đầu vào không mong muốn và kết quả sẽ trả về cùng một giá trị sau khi băm. Để tìm được các đầu vào này cần phải thử một lượng lớn đầu vào chạy qua hàm băm. Tất cả các đầu vào mà cho ra một giá trị giống nhau được gọi là tập bệnh lý (pathological set).

Việc tồn tại tập bệnh lý này có nghĩa là không có hàm băm nào hoàn hảo cho tất cả dữ liệu đầu vào cả. Điều tốt nhất chúng ta cần làm là tạo một hàm băm mà hoạt động tốt cho tập dữ liệu mong muốn.

Dữ liệu không mong muốn cũng gây ra một số vấn đề bảo mật. Nếu người dùng gọi các hàm chức năng qua tập các khóa gây ra các vấn đề va chạm, việc tìm kiếm sẽ mất nhiều thời gian hơn (`O(n)`) so với bình thường (`O(1)`). Đều này có thể gây ra việc từ chối dịch vụ trong các hệ thống sử dụng bảng băm như DNS và một số dịch vụ web nhất định.

Bài tiếp theo: [Xử lý va chạm](/LearnC/write_a_hash_table/04-collisionsg)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)



