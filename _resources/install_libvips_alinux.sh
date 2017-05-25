#!/bin/bash
set -e

vips_version_minimum=8.4.5
vips_version_latest_major_minor=8.4
vips_version_latest_patch=5

install_libvips_from_source() {
  echo "Compiling libvips $vips_version_latest_major_minor.$vips_version_latest_patch from source"
  #curl -O http://www.vips.ecs.soton.ac.uk/supported/$vips_version_latest_major_minor/vips-$vips_version_latest_major_minor.$vips_version_latest_patch.tar.gz
  #tar zvxf vips-$vips_version_latest_major_minor.$vips_version_latest_patch.tar.gz
  cd ./libvips
  #cd vips-$vips_version_latest_major_minor.$vips_version_latest_patch
  # by default its O2
  make clean
  CFLAGS="-g -Wall" CXXFLAGS="-g -Wall" ./configure --enable-debug --disable-docs --disable-static --disable-introspection --disable-dependency-tracking --enable-cxx=yes --without-python --without-orc --without-fftw  $1
  sudo make
  sudo make install
  cd ..
  #sudo rm -rf vips-$vips_version_latest_major_minor.$vips_version_latest_patch
#  sudo rm vips-$vips_version_latest_major_minor.$vips_version_latest_patch.tar.gz
  sudo ldconfig
  echo "Installed libvips $vips_version_latest_major_minor.$vips_version_latest_patch"
}

echo "Installing libvips dependencies via yum"
#yum install -y sudo
#yum install -y wget
#sudo yum groupinstall -y "Development Tools"
#sudo yum install -y glib2-devel libxml2-devel gtk-doc libxml2-devel libpng-devel libtiff-devel libexif-devel libgsf-devel lcms-devel ImageMagick-devel gobject-introspection-devel libwebp-devel curl
#sudo yum install -y libpng-devel libxml2-devel
#sudo yum install -y libjpeg-turbo libjpeg-turbo-devel
#sudo yum update -y expat
install_libvips_from_source "--prefix=/usr"

#sudo sh -c "echo tsc > /sys/devices/system/clocksource/clocksource0/current_clocksource"

sleep 5
