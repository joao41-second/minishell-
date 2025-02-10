#!/bin/bash
norminette | grep ".c" | grep ": OK" | cut -d':' -f1
