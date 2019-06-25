# 1 – What are key-value stores, and why implement one?
Trong phần này, mình sẽ mô tả ngắn key-value stores là gì. Sau đó tôi sẽ giải thích lý do phía sau dự án này và cuối cùng là làm sáng tỏ mục đích chính của key-value store mà chúng ta đang cần thực hiện. Dưới đây là một số mục mà sẽ được trình bày ở phần 1.
1.1 – Cái nhìn tổng quan về key-value
1.2 – Lưu trữ khóa-giá trị và CSDL quan hệ
1.3 – Tại sao thực hiện triển khai key-value stores
1.4 – Kế hoạch tiếp theo


## 1.1 – Cái nhìn tổng quan về key-value

Key-value stores (Lưu trữ khóa-giá trị) là một trong các dạng CSDL đơn giản nhất. Hầu hết các ngôn ngữ lập trình sử dụng việc lưu trữ khóa giá trị trên bộ nhớ. 'map container' của C++ STL là một lưu trữ khóa giá trị, giống như HashMap của Java, kiểu 'dictionary' trong Python. Lưu trữ khóa-giá trị được chia sẻ ra bên ngoài theo các hình thức giao tiếp sau:
- Get (key): Lấy các dữ liệu trước đó đã được lưu dưới định danh "key", hoặc không thành công nếu không tìm thấy dữ liệu tương ứng với "key"
- Set (key,value): Lưu "value" trong bộ nhớ dưới định dang của "key", sau đó chúng ta có thể truy cập với việc sử dụng "key" tương ứng. Nếu trước đó đã có dữ liệu tương ứng với "key", dữ liệu đó sẽ được thay thế
- Delete(key): Xóa dữ liệu được lưu qua "key" (nếu có)

Việc lưu trữ khóa-giá trị có thể thực hiện bằng cách sử dụng hash table, self-balancing tree (B-trees hoặc Red-black tree). Trong trường hợp dữ liệu quá lớn so với bộ nhớ hoặc dữ liệu phải được duy trì trong trường hợp hệ thống gặp sự cố, chúng ta phải sử dụng file system.

Lưu trữ khóa-giá trị là một phần trong [NoSQL](https://en.wikipedia.org/wiki/NoSQL) - tập hợp lại tất cả hệ thống cơ sở dữ liệu mà không sử dụng tất cả các khái niệm được tạo bởi cơ sở dữ liệu quan hệ truyền thống. Trong đó: 
- Không sử dụng bất kỳ ngôn ngữ truy vấn SQL 
- Có thể không cung cấp hỗ trợ đầy đủ của mô hình [ACID](https://en.wikipedia.org/wiki/ACID) (gồm atomicity, consistency, isolation, durability - nguyên tử - nhất quán - độc lập  và vững bền)
- Có thể cung cấp một kiến trúc phân tán, chịu lỗi (hệ thống có khả năng tiếp tục hoạt động mà không bị gián đoạn khi một hoặc nhiều thành phần nó bị sự cố)



