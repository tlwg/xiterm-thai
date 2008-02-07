#!/bin/sh

set -x

# autoconf2.50 is the diverted name when installed with autoconf2.13
# at the same time on Debian. We prefer autoconf2.50.

if autoheader2.50 --version </dev/null >/dev/null; then
  autoheader2.50
else
  autoheader
fi

if autoconf2.50 --version </dev/null >/dev/null; then
  autoconf2.50
else
  autoconf
fi

