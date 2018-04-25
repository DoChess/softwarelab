#!/bin/sh

echo "Installing dependencies"
apt-get install bison swig autoconf libtool automake alsa-oss libasound2 libasound2-dev pulseaudio libpulse-dev

echo "Executing sphinxbase configuration"
cd sphinxbase-5prealpha/
./autogen.sh 
./configure
make
make install

echo "Creating environment variables"
echo "export LD_LIBRARY_PATH=/usr/local/lib" >> /etc/ld.so.conf
echo "export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig" >> /etc/ld.so.conf

echo "Executing pocketsphinx configuration"
cd ..
cd pocketsphinx-5prealpha/
./autogen.sh 
make
make install

echo "DONE."
