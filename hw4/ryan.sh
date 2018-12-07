#!/usr/bin/expect

spawn ./a.out

expect -re ".*: "
send "Ryan\n"
expect -re ".*: "
send "Stewart\n"
expect -re ".*: "
send "111-111-1111\n"
interact
