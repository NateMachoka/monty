#!/bin/bash

echo "push 42" > bytecodes/00.m
echo "push 123" >> bytecodes/00.m
echo "push -5" >> bytecodes/00.m
echo "pall" >> bytecodes/00.m
echo "push not_an_integer" >> bytecodes/00.m
echo "push" >> bytecodes/00.m
