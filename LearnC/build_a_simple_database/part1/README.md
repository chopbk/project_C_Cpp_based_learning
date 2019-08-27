# Part 1 - Introduction and Setting up the REPL
Trong phần này chúng ta sẽ tìm hiểu tổng quan về một Database và trả lời các câu hỏi ở phần mục lục. Để giả quyết những câu hỏi này, chúng ta sẽ viết một CSDL giống với sqlite (sqlite đơn giản hơn, ít tính năng hơn MySQL). Toàn bộ cơ sở dữ liệu được viết trong một tập tin duy nhất.
Trong phần này chúng ta sẽ thực hiện code để xử lý các lệnh từ người dùng khi sử dụng Sqlite
## Sqlite
Tài liệu về [Sqlite](https://www.sqlite.org/arch.html) có thể tham khảo tại đây
Dưới đây là mô hình của Sqlite

![Mô hình của Sqlite](https://cstack.github.io/db_tutorial/assets/images/arch1.gif)

Một truy vấn của người dùng sẽ đi qua các khối front-end để truy xuất hoặc sửa đổi dữ liệu
- tokenizer
- parser
- code generator

Đầu vào của front-end là các lệnh truy vấn SQL, đầu ra là `virtual machine bytecode` (Tạm hiểu là ngôn ngữ đã được biên dịch để sử dụng trên CSDL)

`backend` bao gồm các khối
- virtual machine
- B-tree
- pager
- os interface

**virtual machine** cơ bản là một khối chuyển đổi bytecode từ `front-end` như một lệnh để thực hiện các thao tác trên một, nhiều bảng hoặc chỉ mục. Các bảng và chỉ mục được lưu trữ trên một cấu trúc dữ liệu gọi là B-tree.
Mỗi **B-tree** bao gồm nhiều node. Mỗi node là có độ dài một trang(page). B-tree có thể truy xuất và lưu page vào ổ cứng bằng cách phát lệnh cho `pager`
**pager** nhận lệnh ghi hoặc đọc các page dữ liệu. Nó cũng giữ một bộ đệm của việc truy cập page dữ liệu gần đây trong bộ nhớ và xác định khi nào thì các page dữ liệu được ghi lại vào đĩa
**os interface** là lớp giao tiếp với hệ điều hành.

## Making a Simple REPL 
Đầu tiên chúng ta phải hiểu REPL là gì? 
REPL là viết tắt của Read Excute Print Loop (Đọc - Thực thi- In - Lặp) và nó biểu diễn môi trường máy tính như màn hình console trong Linux shell thực hiện các tác vụ mong muốn: 
- **Read**: Đọc cá thông tin input của người dùng
- **Excute**: Đánh giá các cấu trúc dữ liệu này.
- **Print**: In các kết quả.
- **Loop**: Lặp các dòng lệnh đến khi người dùng gõ ctrl-c hai lần.

Sqlite bắt đầu một vòng lặp read-excute-print-loop khi chúng ta bắt đầu khởi động (lệnh sqlite3) từ dòng lệnh
```sh
~ sqlite3
SQLite version 3.16.0 2016-11-04 19:09:39
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite> create table users (id int, username varchar(255), email varchar(255));
sqlite> .tables
users
sqlite> .exit
```
Để làm được điều này, hàm main sẽ phải có một vòng lặp vô hạn để in các dấu nhắc, lấy dòng lệnh từ terminal và xử lý dòng lệnh đầu vào
```c
int main(int argc, char *argv[]){
    InputBuffer * input_buffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
    }
}
```

Chúng ta định nghĩa `InputBuffer` là lớp bọc (wrapper) bên ngoài các dữ liệu mà cần lưu trữ để có thể tương tác với getline()
```c
typedef struct {
    char * buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer * new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer* ) malloc (sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}
```
Tiếp theo `print_promt()` in dấu nhắc tới người dùng sau khi đọc mỗi dòng của input
```c
void print_promt(){printf("db > ");}
```
Để đọc một dòng đầu vào, sử dụng getline()
```c 
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
```
- `lineptr`: một con trỏ trỏ tới biến mà chúng ta sử dụng để trỏ tới bộ đệm chứa dòng được đọc. `getline()` sẽ cấp phát bộ nhớ cho biến vì vậy nó nên được giải phóng sau khi sử dụng xong.
- `n`: một con trỏ trỏ tới biến chứa giá trị kích thước của buffer được cấp phát.
- `stream`: luồng đầu vào đọc dữ liệu
- `return value`: số byte đọc được, có thể sẽ bé hơn kích thước của buffer.

Sử dụng hàm `getline()` chúng ta sẽ lưu trữ lệnh vào `input_buffer->buffer` và kích thước của buffer được cấp phát vào `input_buffer->buffer_length`. Giá trị trả về được lưu trong `input_buffer->input_length`. 

`buffer` khởi tạo với giá trị `NULL`, vì vậy hàm `getline()` sẽ cấp phát đủ bộ nhớ để chứa đủ lệnh và làm `buffer` trỏ tới nó.
```c
void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = 
        getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    //ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    intput_buffer->buffer[bytes_read - 1] = 0;
}
```
Tiếp theo chúng ta cần định nghĩa một hàm giải phóng bộ nhớ mà đã được cấp phát bởi `getline()`
```c
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
```
Cuối cùng, chúng ta thực hiện phân tách và thực thi câu lện. Ở phần này chúng ta sẽ chỉ thực thi câu lệnh `.exit` để thực hiện thoát chương trình sqlite 
```c
if (strcmp(input_buffer->buffer, ".exit") == 0) {
  close_input_buffer(input_buffer);
  exit(EXIT_SUCCESS);
} else {
  printf("Unrecognized command '%s'.\n", input_buffer->buffer);
}
```

Build và chạy thử
``` sh
~ ./db
db > .tables
Unrecognized command '.tables'.
db > .exit
~
```
Như vậy chúng ta đã hoàn thành phần một với việc thực hiện cơ bản REPL, ở phần tiếp theo chúng ta sẽ bắt đầu phát triển các câu lệnh khác. Tham khảo file [sqlite.c](/LearnC/build_a_simple_database/part1/sqlite.c) trong cùng thư mục để xem toàn bộ phần mã nguồn của Part 1. 

## Phần tiếp theo
[Part 2 - World's Simplest SQL Compiler and Virtual Machine](/LearnC/build_a_simple_database/part2/)

[Mục lục](/LearnC/build_a_simple_database/)