FROM php:7.1-apache
MAINTAINER Jaime Lopez "jaime@0xbaaad.com"

# Puts the rootkit's code into the container
COPY src/ /module
WORKDIR /module

# Compiles and configures the rootkit module...
RUN phpize
RUN ./configure --enable-rootkit
RUN make && make install

RUN echo 'extension=rootkit.so' >> /usr/local/etc/php/conf.d/docker-php-ext-rootkit.ini

COPY www/ /var/www/html/