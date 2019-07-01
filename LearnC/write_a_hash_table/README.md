# Write a hash table in C
Bài viết này là hướng dẫn triển khai một bảng băm sử dụng ngôn ngữ C. Bài viết mình tham khảo từ tutorial của [James Routley](https://twitter.com/james_routley), từ [Github](https://github.com/jamesroutley/write-a-hash-table)


[Bảng băm](https://en.wikipedia.org/wiki/Hash_table) là một trong những cấu trúc dữ liệu được sử dụng nhiều và hữu ích. Các tính năng chèn, tìm kiếm và xóa được thực hiện nhanh chóng và dễ dàng mở rộng giúp chúng ta giải quyết số lượng lớn các vấn đề trong các bài toán lập trình.

Trong bài viết này, chúng ta sẽ triển khai bảng băm với  ["open-addressed"](https://en.wikipedia.org/wiki/Open_addressing), ["double-hashed"](https://en.wikipedia.org/wiki/Double_hashing) sử dụng ngôn ngữ C. Sau khi đọc xong bài viết này, bạn sẽ nắm được
- Hiểu được về cách thức cấu trúc dữ liệu hoạt động 
- Nắm được khi nào thì sử dụng bảng băm, khi nào không sử dụng, và khi nào bảng băm có thể thất bại
- Tiếp xúc với mã nguồn C của bảng băm

Ngôn ngữ C là một ngôn ngữ tuyệt vời để viết một bảng băm, đây là ngôn ngữ cấp thấp, vì vậy bạn sẽ tiếp xúc sâu hơn với cách thức hoạt động ở mức ngôn ngữ máy.

Toàn bộ code của bài viết này vào khoảng 200 dòng code và sẽ tầm 1 đến 2 giờ để nắm bắt được.

# Nộidung 
1. [Giới thiệu](/LearnC/write_a_hash_table/01-introduction)
2. [Cấu trúc bảng băm](/LearnC/write_a_hash_table/02-hash-table)
3. [Các hàm băm](/LearnC/write_a_hash_table/03-hashing)
4. [Xử lý đụng độ](/LearnC/write_a_hash_table/04-collisions)
5. [Các hàm sử dụng](/LearnC/write_a_hash_table/05-methods)
6. [Thay đổi kích thước bảng](/LearnC/write_a_hash_table/06-resizing)
6. [Phụ lục: Các phương pháp xử lý đụng độ khác](/LearnC/write_a_hash_table/07-appendix)

# Tácgiả

Bài viết này được viết bởi [James Routley](https://twitter.com/james_routley),
blogs tại [routley.io](https://routley.io).