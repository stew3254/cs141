#!/usr/bin/expect

spawn ./a.out

expect -re ".*: "
send "payrollData.txt\n"
expect -re ".*: "
send "data.xml\n"
interact

