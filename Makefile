all: build run

build:
		docker build . -t php-rootkit:latest
		
run:
		docker run -it -p 8080:80 php-rootkit:latest apache2-foreground

.PHONY: all build run
