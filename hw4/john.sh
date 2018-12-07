#!/usr/bin/expect

spawn ./a.out

expect -re ".*: "
send "John\n"
expect -re ".*: "
send "Cena\n"
expect -re ".*: "
send "123-456-7890\n"
interact
