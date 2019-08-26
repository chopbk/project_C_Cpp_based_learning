# How does a Database Work?
Qua loạt bài hướng dẫn này chúng ta có thể nắm được câu trả lời cho các câu hỏi sau
- Định dạng của dữ liệu lưu (trong bộ nhớ và trên đĩa)?
- Khi nào nó được chuyển từ bộ nhớ -> đĩa?
- Tại sao chỉ có 1 key cho mỗi bảng?
- Làm thế nào để quay trở lại (rolling back) một transaction work trước đó?
- Cách một chỉ mục (index) được định dạng?
- Khi nào và làm cách nào để xảy ra việc quét toàn bộ bảng?
- Định dạng của prepared statement được lưu?

Hay nói một cách ngắn hơn, chúng ta sẽ nắm rõ được làm cách nào mà cơ sở dữ liệt hoạt động.
Chúng ta sẽ xây dựng một bản sao của  `sqlite` từ C. 

# Nội Dung
- [Phần 1 - Introduction and Setting up the REPL](/LearnC/build_a_simple_database/part1/)
- [Phần 2 - World’s Simplest SQL Compiler and Virtual Machine](/LearnC/build_a_simple_database/part2/)
- [Phần 3 - An In-Memory, Append-Only, Single-Table Database](/LearnC/build_a_simple_database/part3/)
- [Phần 4 - Our First Tests (and Bugs)](/LearnC/build_a_simple_database/part4/)
- [Phần 5 - Persistence to Disk](/LearnC/build_a_simple_database/part5/)
- [Phần 6 - The Cursor Abstraction](/LearnC/build_a_simple_database/part6/)
- [Phần 7 - Introduction to the B-Tree](/LearnC/build_a_simple_database/part7/)
- [Phần 8 - B-Tree Leaf Node Format](/LearnC/build_a_simple_database/part8/)
- [Phần 9 - Binary Search and Duplicate Keys](/LearnC/build_a_simple_database/part9/)
- [Phần 10 - Splitting a Leaf Node](/LearnC/build_a_simple_database/part10/)
- [Phần 11 - Recursively Searching the B-Tree](/LearnC/build_a_simple_database/part11/)
- [Phần 12 - Scanning a Multi-Level B-Tree](/LearnC/build_a_simple_database/part12/)
- [Phần 13 - Updating Parent Node After a Split](/LearnC/build_a_simple_database/part13/)

# Tham Khảo
Bài viết được dịch lại từ [đây](https://cstack.github.io/db_tutorial/)