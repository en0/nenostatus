# C Coding Standards

## General Guidelines
- **Consistency**: Be consistent. If a pattern is established, follow the pattern.
- **Descriptive Names**: Use meaningful names that describe the purpose of the variable, function, or type.

## Naming Conventions

### Variables
- Use **lowercase letters** with **underscores** to separate words.
  - Example: `int my_variable;`

### Constants
- Use **uppercase letters** with **underscores** to separate words.
  - Example: `#define MAX_SIZE 100`

### Functions
- Use **lowercase letters** with **underscores**.
  - Example: `void calculate_sum(int a, int b);`

### Types (typedefs)
- Use **CamelCase** for typedefs, starting with an uppercase letter.
  - Example: 
    ```c
    typedef unsigned long long BigSize;
    ```

### Structures
- Use **CamelCase** for struct names, starting with an uppercase letter.
- Always use typedefs when possible.
  - Example: 
    ```c
    typedef struct MyStruct {
        int value;
    } MyStruct;
    ```

### Enumerations
- Use **uppercase letters** with **underscores** for enumeration constants.
- Always use typedefs when possible.
  - Example:
    ```c
    typedef enum {
        STATUS_OK,
        STATUS_ERROR,
        STATUS_PENDING
    } Status;
    ```

### Macros
- Use **uppercase letters** with **underscores** for macro names.
  - Example: `#define SUM(a,b) (a+b)`

