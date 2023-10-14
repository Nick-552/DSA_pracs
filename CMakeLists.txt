cmake_minimum_required(VERSION 3.26)
project(DSA_pracs)

set(CMAKE_CXX_STANDARD 23)

add_executable (main main.cpp)
add_executable(ex1 ex1.cpp)
add_executable (ex2 ex2.cpp
        Note.h Note.cpp
)
add_executable (ex3 ex3.cpp
        BankAccount.cpp BankAccounts.cpp
        ex1.cpp
)