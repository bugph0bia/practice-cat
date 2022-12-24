# Makefile
.DEFAULT_GOAL := build

FLAGS = -ldflags="-s -w" -trimpath

fmt:
	go fmt
.PHONY: fmt

lint: fmt
	staticcheck
.PHONY: lint

vet: fmt
	go vet
.PHONY: vet

build: vet
	go mod tidy
	go build -o cat $(FLAGS)
.PHONY: build

clean:
	rm -r cat
.PHONY: clean

test: cat
	./test.sh
.PHONY: test

