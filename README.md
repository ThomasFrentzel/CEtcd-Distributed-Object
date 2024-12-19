# CEtcd-Distributed-Object

**CEtcd-Distributed-Object** is a distributed object system that combines CORBA (Common Object Request Broker Architecture) with etcd-like functionality for managing key-value pairs.

## Description

This project implements a distributed object system called **CEtcd** (CORBA etcd), whose interface provides methods to manage key-value pairs in a distributed manner. The object supports operations such as inserting, retrieving, and deleting key-value pairs, along with handling errors through exceptions.

The object exposes the following methods:

| Method/Attribute | Description |
|------------------|-------------|
| `id`             | A read-only attribute representing the object's identifier (string). |
| `put(key, val)`  | Inserts a new key-value pair in the distributed object table. If the key already exists, it updates the value and returns `false`; otherwise, it returns `true`. |
| `get(key)`       | Returns the value associated with the specified key if it exists; otherwise, it throws an `InvalidKey` exception. |
| `del(key)`       | Removes the key and its associated value from the object table if they exist; otherwise, it throws an `InvalidKey` exception. |

Additionally, a client is developed to test all the operations of the distributed object.

---

## System Architecture

![architecture](https://github.com/user-attachments/assets/e44e06ef-f39d-48d0-9655-57710a5bbcc1)

---

## Files Overview

### `CEtcd.idl`

This file defines the interface for the distributed object, specifying the operations available (`put`, `get`, `del`) and the exceptions (`InvalidKey`).

```idl
exception InvalidKey {};

interface CEtcd {
    readonly attribute string id;
    boolean put(in string key, in string val);
    string get(in string key) raises(InvalidKey);
    void del(in string key) raises(InvalidKey);
};
```

### `CEtcdI.h` and `CEtcdI.cpp`

The **CEtcdI.h** and **CEtcdI.cpp** files provide the implementation of the **CEtcd** distributed object defined in `CEtcd.idl`. These files contain the logic to manage key-value pairs in the distributed object system.

- **CEtcdI.h** declares the `CEtcd_i` class, which implements the methods defined in `CEtcd.idl`. This file is responsible for the interface declarations and provides the structure of the distributed object.
- **CEtcdI.cpp** defines the methods of the `CEtcd_i` class, including the following operations:
  - **`id()`**: This method returns a custom identifier for the object, in this case, a hardcoded string `"customId"`.
  - **`put(key, val)`**: Inserts a new key-value pair or updates the value if the key already exists. It returns `true` when a new pair is inserted and `false` when an existing key's value is updated.
  - **`get(key)`**: Retrieves the value associated with the specified key. If the key doesn't exist, it throws an `InvalidKey` exception.
  - **`del(key)`**: Deletes the specified key-value pair if it exists. If the key doesn't exist, it throws an `InvalidKey` exception.

The data is managed in an internal `std::map<std::string, std::string> serverDb`, which acts as the storage for the key-value pairs. This class ensures that all operations (put, get, del) are performed in a distributed object environment using CORBA.

### How to Use

1. **Clone the Repository**: 
   ```bash
   git clone https://github.com/ThomasFrentzel/CEtcd-Distributed-Object
   ```
2. Make sure the etcd library is installed and properly configured on your machine for the client to interact with the distributed object system.
   
3. **Test with Client**: Run the provided client application to test the functionality:
   - Use `put(key, val)` to add or update key-value pairs.
   - Use `get(key)` to retrieve values by key.
   - Use `del(key)` to remove key-value pairs.
