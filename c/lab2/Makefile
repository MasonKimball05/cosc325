# Makefile for Tiny BASIC Lexer
# Lab 2 - COSC 325

CC = gcc
CFLAGS = -Wall -std=c99
TARGET = front
SOURCE = front.c
INPUT = front.in

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean