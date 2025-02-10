#!/bin/bash
norminette | grep ".c" | grep ": OK" | cut -d':' -f1 | sed 's/$/  /' | sed 's/$/\//'
