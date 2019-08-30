# Part 3 - An In-Memory, Append-Only, Single-Table Database
Hiện tại CSDL của chúng ta có một số giới hạn, trong phần này chúng ta sẽ bổ sung thêm với: 
- Hỗ trợ 2 hoạt động: insert một hàng và in tất cả các hàng.
- Chỉ nằm trong bộ nhớ (không lưu vào ổ điwã)
- Hỗ trợ một bảng mã hóa như dưới đây
|  Colume   |  Type       |
|   ---     |  ---        |
|    id     | interger    |
| username  | varchar(32) |
|   email   | varchar(255)|

Lệnh `insert` bây giờ sẽ dùng để lưu trữ người dùng và có cú pháp như sau:
``` sql
insert 1 cstack foo@bar.com
```
có nghĩa là trong code chúng ta phải sửa đổi hàm prepare_statement() để phân tích các đối số truyền vào cho hàm
```c
if(strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    int args_assigned = sscanf(
        input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
        statement->row_to_insert.username, statement->row_to_insert.email);
    )
    if(args_assigned < MAX_COL_TABLE){ //if number of args > max colume
        return PREPARE_SYNTAX_ERROR;
    }
    return PREPARE_SUCCESS;
}
...
```
Chúng ta sẽ định nghĩa cấu trúc dữ liệu `Row` để lưu trữ thông tin của một hàng
```c
#define MAX_COL_TABLE 3
#define COLUMN_EMAIL_SIZE 255
#define COLUMN_USERNAME_SIZE 32
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE]
} Row;

//Add Struct Row to Struct Statement
typedef struct{
    StatementType type;
    Row row_to_insert; //only used by insert statement
} Statement;
```
Bây giờ chúng ta cần xử lý dữ liệu đầu vào vào một số cấu trúc dữ liệu đại diện cho một bảng. Sqlite sử dụng B-trê để thực hiện tra cứu, chèn và xóa. Tuy nhiên trong phần này chúng ta sẽ chỉ sử dụng một thành phần đơn giản hơn, nhóm các hàng thành các page nhưng thay vì sắp xếp các page thành một cây, chúng ta sẽ chỉ sử dụng mảng để lưu trữ

Trước tiên chúng ta sẽ xác định đại diện của một hàng
```c
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
```
|  Colume   |  Size  | Offset Start
|   ---     |  ---   | ---    
|    id     |   4    | 0 
| username  |   32   | 4 
|   email   |  255   | 36
|   total   |  291   | 

```c
void serialize_row(Row source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id, ID_SIZE));
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}
void deserialize_row(void* source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
```
Tiếp theo định nghĩa một cấu trúc bảng để trỏ tới page của một hàng 
```c
const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROW_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROW_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;