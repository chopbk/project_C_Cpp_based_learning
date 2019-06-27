# Giới thiệu

Bảng băm là một cấu trúc dữ liệu mà cung cấp các hàm API để người dùng có thể dễ dàng sử dụng. Một bảng bảng bao gồm một mảng các nhóm dữ liệu, trong đó nó lưu theo cặp khóa-giá trị (key-value). Để xác định được vị trí mà cặp khóa-giá trị sẽ được lưu trữ, khóa sẽ được đưa qua một hàm băm. Hàm này sẽ trả về một giá trị nguyên dương và được sử dụng như một chỉ mục của cặp trong mảng cấu trúc trên. Khi mà chúng ta muốn lấy cặp khóa-giá trị, cần phải cung cấp khóa và sử dụng hàm băm để xác định chỉ mục trỏ tới vị trí đã lưu.

Việc sử dụng mảng để lưu trữ có độ phức tạp O(1), giúp cho bảng băm nhanh chóng lưu trữ và truy xuất dữ liệu

Bảng băm trong bài viết này áp dụng cho khóa là giá trị chuỗi, nhưng cách thức trong bài viết này có thể áp dụng cho các bảng băm sử dụng các cặp khóa-giá trị khác tùy ý. 

##API

Bảng băm trong bài viết này hỗ trợ các API sau
- `search(a,k)`: trả về giá trị `v` mà liên kết với khóa `k` hoặc `NULL` nếu khóa không tồn tại trong bảng
- `insert(a, k, v)`: lưu trữ cặp `k:v` trong mảng `a`.
- `delete(a, k)`: Xóa cặp `k:v` mà liên kết với khóa `k`, hoặc không làm gì nếu `k` không tồn tại trong bảng


## Code structure

Mã nguồn sẽ được đặt theo cấu trúc thư mục như sau

```
.
├── build
└── include
    ├── hash_table.h
    └── prime.h    
└── src
    ├── hash_table.c
    ├── prime.c
    ├── Makefile
```

`src` sẽ chứa mã nguồn, `include` chứa file header, `build` sẽ chứa file biên dịch

## Thuật ngữ 

Trong bài viết này, chúng ta sử dụng một số thuật ngữ sau đây:

- Associative array (Mảng liên kết): Một cấu trúc dữ liệu trừu tượng bao gồm một tập các cặp khóa - giá trị. Một mảng liên kết không thể chứa khóa trùng nhau nhưng mỗi khóa thì có thể ánh xạ đến nhiều hơn một giá trị trong tập đó. Cũng có thể gọi là `map`, `symbol table` hoặc `dictionary`

- Hash table (bảng băm): Một triển khai mảng liên kết và có thể ánh xạ các khóa thành giá trị thông qua các hàm băm để tính toán chỉ mục. Cũng có thể gọi là `hash map`, `map`, `hash` hoặc `dictionary`.

Bài tiếp theo: [Cấu trúc bảng băm](/LearnC/write_a_hash_table/02-hash-table)
[Nội dung bài viết](https://github.com/chopbk/project_C_Cpp_based_learning/tree/master/LearnC/write_a_hash_table#Nộidung)
