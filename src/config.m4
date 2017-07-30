PHP_ARG_ENABLE(rootkit, whether to enable Rootkit support, [ --enable-rootkit   Enable Rootkit support])

if test "$PHP_ROOTKIT" = "yes"; then
  AC_DEFINE(HAVE_ROOTKIT, 1, [Whether you have Rootkit])
  PHP_NEW_EXTENSION(rootkit, rootkit.c rootkit_hook.c, $ext_shared)
fi