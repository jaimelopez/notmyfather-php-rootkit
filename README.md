# NotMyFather PHP Rootkit
NotMyFather is just a PHP extension as a rootkit proof of concept.

In this PoC I just hooked the `hash()` and `md5()` PHP's original methods which will print into STDOUT some debug messages, but you can play with the code implementing whatever functionality you want.

You can read more about the whole history in the entry that I published on my blog: [You Are Not My Father: PHP Rootkit](https://www.0xbaaad.com/2017/07/you-are-not-my-father-php-rootkit)

# Usage
In this same repository you have a Docker container ready to run and test.

You can use the Makefile that is provided here as well.

    A simple way to see it running is just typing: make which will build a new image
    for the container and will prepare and start the instance of apache with php,
    compiling the rootkit and doing all for you.

The instance has a small PHP application which just calls the hooked methods in order to see how the rootkit works (take a look at php code in `/www/index.php`)

    Once the container will be up you can visit `http://localhost:8080` with the browser.

The debug messages will be shown thru the same console from where you run the container.

## Folders and files
- `/src`        contains the rootkit source code
- `/www`        there is the php application code
- `Dockerfile`  definition of the docker container (here is defined the module compilation)
- `Makefile`    builds and start an instance of the container with all ready to check