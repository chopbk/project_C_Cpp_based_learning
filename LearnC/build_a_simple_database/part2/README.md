# Part 2 - World’s Simplest SQL Compiler and Virtual Machine
![Kiến trúc SQL](https://cstack.github.io/db_tutorial/assets/images/arch2.gif)

Dựa vào [kiến trúc Sqlite](https://www.sqlite.org/arch.html), chúng ta có thể thấy Sqlite được chia thành 2 phần Front-end và Back-end. 
Trong đó phần xử lý lệnh SQL từ người dùng gồm Tokenizer - Parser và Code Generator.

Trong phần 2 này chúng ta sẽ xây dựng phần xử lý các câu lệnh SQL - phân tích cú pháp - chuyển đổi thành bytecode để đưa vào Virtual Machine và thực thi. Việc xử lý riêng biệt như thế này giúp Sqlite có một số lợi thế như 
giảm sự phức tạp của từng phần (VM sẽ không lo lắng về việc sai cú pháp)

Chúng ta sẽ sửa lại cấu trúc hàm `main` để hỗ trợ hai từ khóa mới trong việc xử lý lệnh người dùng: 
```c
int main(int argc, char* argv[]){
    InputBuffer * input_buffer = new_input_buffer();
    while(true){
        print_promt();
        read_input(input_buffer);
        
        if(input_buffer->buffer[0] == '.'){
            switch(do_meta_command(input_buffer)){
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command: '%s'\n"), input_buffer->buffer);
                    continue;
            }
        }
        Statement statement:
        switch(prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'. \n", input_buffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Executed.\n");
    }
}
```
Các câu lệnh non-SQL như `.exit` được gọi là "meta-commands". Chúng được bắt đầu bằng dấu chấm `'.', vì vậy chúng ta sẽ kiểm tra các lệnh tương tự như thế và xử lý trong một hàm riêng. 

Tiếp theo chúng ta thêm một hàm `prepare_statement()`  để chuyển đổi dòng lệnh đầu vào thành lệnh chức năng (prepared statement). 

Cuối cùng, chúng ta truyền `prepared statement` vào hàm `excute_statement()` để thực hiện chức năng của VM. 

Hai hàm về sẽ trả về kết quả SUCCESS hoặc UNRECOGNIZED như các giá trị ENUM sau đây
```c
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;
```
Tạm thời ở phần này chúng ta sẽ chỉ có 2 ENUM trả về như trên, nếu thất bại thì sẽ in ra lỗi và dấu nhắc mới để yêu cầu người dùng nhập lệnh mới. 

`do_meta_command()` chỉ là một hàm bao cho chức năng xử lý các lệnh meta như `.exit`, sau này chúng ta sẽ thêm nhiều lệnh xử lý hơn: 
```c
MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}
```
`prepared statement` hiện tại sẽ hỗ trợ hai tính năng gồm INSERT và SELECT, trong các bài viết tiếp, chúng ta sẽ viết thêm các truy vấn SQL khác
```c
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;
```
Vì vậy `hàm prepare_statement` cũng sẽ chỉ hỗ trợ các lệnh `insert` và `select` từ người dùng: 
```c
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if(strncmp(input_buffer->buffer. "insert", 6) == 0){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(strncmp(input_buffer->buffer. "select", 6) == 0){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}
```
Với việc tái cấu trúc này, chúng ta sẽ nhận ra hai từ khóa mới
```sh
~ ./db
db > insert foo bar
This is where we would do an insert.
Executed.
db > delete foo
Unrecognized keyword at start of 'delete foo'.
db > select
This is where we would do a select.
Executed.
db > .tables
Unrecognized command '.tables'
db > .exit
~
```
Với bài viết này, bộ khung của chúng ta đã bắt đầu hình thành, tuy nhiên vẫn chưa thể lưu trữ dữ liệu. Trong phần tiếp theo, chúng ta sẽ thực hiện việc thực thi các lệnh `insert` và `select`, tạo kho dữ liệu. 
Tham khảo file [sqlite.c](/LearnC/build_a_simple_database/part2/sqlite.c) trong cùng thư mục để xem toàn bộ phần mã nguồn của Part 2. 
## Phần tiếp theo
[Part 3 - An In-Memory, Append-Only, Single-Table Database](/LearnC/build_a_simple_database/part3/)

[Mục lục](/LearnC/build_a_simple_database/)