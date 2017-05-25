Failing Test
------------------


The test try to resize a 21000 x 14400 resolution to a 6k width image but it fails with a segmentation fault.
Depending on the environemnt it works or not, I've added a docker container where the test is currently failing.
Worth to say that I've tried with version *8.4.5*, *8.4.6* and *8.5.5* and I have the same issue in all the them.

From what I've figured out it is related to having a large file in disk, the resize is more than 100mb so vips uses disk to transform the image. If I increase the VIPS_DISK_THRESHOLD to fit in memory then it works fine.

I've traced the segfault to this line [https://github.com/jcupitt/libvips/blob/84270ce787f4d19859f1ceab8d8a9801a865a06a/libvips/iofuncs/vips.c#L608](vips.c line 608)

I'f I enable debug mode when compiling libvips then when running the test there is an error in [https://github.com/jcupitt/libvips/blob/84270ce787f4d19859f1ceab8d8a9801a865a06a/libvips/iofuncs/type.c#L1409](type.c line 1409)
`VIPS:ERROR:type.c:1409:vips_value_set_save_string: assertion failed: (G_VALUE_TYPE( value ) == VIPS_TYPE_SAVE_STRING)`

To locally build and run the test
```bash
g++ -std=c++11 -g -Wall resize-big-image.cpp `pkg-config vips-cpp --cflags --libs` -Wno-c++11-extensions -o resize
./bench-resize samples/twin-peaks.jpeg 
```

To run the test in the failing environment.
```bash
docker build -t not_working .
cd failing-test
./docker-test.sh

```

Packages installed
````
ImageMagick-6.7.8.9-15.21.amzn1.x86_64
ImageMagick-devel-6.7.8.9-15.21.amzn1.x86_64
apr-1.5.1-1.12.amzn1.x86_64
apr-util-1.4.1-4.17.amzn1.x86_64
audit-libs-2.6.5-3.28.amzn1.x86_64
autoconf-2.69-11.9.amzn1.noarch
automake-1.13.4-3.15.amzn1.noarch
avahi-libs-0.6.25-12.17.amzn1.x86_64
basesystem-10.0-4.9.amzn1.noarch
bash-4.2.46-20.36.amzn1.x86_64
bc-1.06.95-1.10.amzn1.x86_64
binutils-2.23.52.0.1-55.65.amzn1.x86_64
bison-2.7-4.11.amzn1.x86_64
boost-regex-1.53.0-14.21.amzn1.x86_64
busybox-1.19.3-2.11.amzn1.x86_64
byacc-1.9.20070509-7.8.amzn1.x86_64
bzip2-1.0.6-8.12.amzn1.x86_64
bzip2-devel-1.0.6-8.12.amzn1.x86_64
bzip2-libs-1.0.6-8.12.amzn1.x86_64
ca-certificates-2015.2.6-65.0.1.16.amzn1.noarch
cairo-1.12.14-6.8.amzn1.x86_64
chkconfig-1.3.49.3-2.14.amzn1.x86_64
coreutils-8.22-15.52.amzn1.x86_64
cpio-2.10-12.12.amzn1.x86_64
cpp48-4.8.3-9.111.amzn1.x86_64
cracklib-2.8.16-4.14.amzn1.x86_64
cracklib-dicts-2.8.16-4.14.amzn1.x86_64
crash-7.1.8-1.21.amzn1.x86_64
cscope-15.6-6.5.amzn1.x86_64
ctags-5.8-2.6.amzn1.x86_64
cups-libs-1.4.2-67.21.amzn1.x86_64
curl-7.51.0-4.73.amzn1.x86_64
cvs-1.11.23-16.9.amzn1.x86_64
cyrus-sasl-lib-2.1.23-13.16.amzn1.x86_64
dash-0.5.5.1-4.5.amzn1.x86_64
db4-4.7.25-18.11.amzn1.x86_64
db4-utils-4.7.25-18.11.amzn1.x86_64
dbus-libs-1.6.12-14.28.amzn1.x86_64
device-mapper-1.02.135-1.31.amzn1.x86_64
device-mapper-libs-1.02.135-1.31.amzn1.x86_64
diffstat-1.51-2.5.amzn1.x86_64
diffutils-3.3-4.15.amzn1.x86_64
docbook-dtds-1.0-51.8.amzn1.noarch
docbook-style-dsssl-1.79-10.7.amzn1.noarch
docbook-style-xsl-1.78.1-3.9.amzn1.noarch
docbook-utils-0.6.14-36.7.amzn1.noarch
doxygen-1.8.2-1.11.amzn1.x86_64
dracut-004-409.31.amzn1.noarch
dyninst-8.1.2-6.3.amzn1.x86_64
elfutils-0.163-3.18.amzn1.x86_64
elfutils-libelf-0.163-3.18.amzn1.x86_64
elfutils-libs-0.163-3.18.amzn1.x86_64
ethtool-3.15-2.27.amzn1.x86_64
expat-2.1.0-10.21.amzn1.x86_64
file-5.22-4.31.amzn1.x86_64
file-libs-5.22-4.31.amzn1.x86_64
filesystem-2.4.30-3.8.amzn1.x86_64
findutils-4.4.2-6.9.amzn1.x86_64
fipscheck-1.3.1-3.13.amzn1.x86_64
fipscheck-lib-1.3.1-3.13.amzn1.x86_64
flex-2.5.37-3.13.amzn1.x86_64
fontconfig-2.8.0-5.8.amzn1.x86_64
freetype-2.3.11-15.14.amzn1.x86_64
freetype-devel-2.3.11-15.14.amzn1.x86_64
gawk-3.1.7-10.10.amzn1.x86_64
gcc-4.8.3-3.20.amzn1.noarch
gcc-c++-4.8.3-3.20.amzn1.noarch
gcc-gfortran-4.8.3-3.20.amzn1.noarch
gcc48-4.8.3-9.111.amzn1.x86_64
gcc48-c++-4.8.3-9.111.amzn1.x86_64
gcc48-gfortran-4.8.3-9.111.amzn1.x86_64
gdb-7.6.1-64.33.amzn1.x86_64
gdbm-1.8.0-36.6.amzn1.x86_64
gettext-0.18.1.1-9.1.11.amzn1.x86_64
gettext-common-devel-0.18.1.1-9.1.11.amzn1.noarch
gettext-devel-0.18.1.1-9.1.11.amzn1.x86_64
gettext-libs-0.18.1.1-9.1.11.amzn1.x86_64
ghostscript-8.70-21.1.24.amzn1.x86_64
ghostscript-devel-8.70-21.1.24.amzn1.x86_64
ghostscript-fonts-5.50-23.2.7.amzn1.noarch
git-2.7.4-1.47.amzn1.x86_64
glib2-2.36.3-5.18.amzn1.x86_64
glib2-devel-2.36.3-5.18.amzn1.x86_64
glibc-2.17-157.169.amzn1.x86_64
glibc-common-2.17-157.169.amzn1.x86_64
glibc-devel-2.17-157.169.amzn1.x86_64
glibc-headers-2.17-157.169.amzn1.x86_64
gmp-6.0.0-11.16.amzn1.x86_64
gnupg2-2.0.28-1.30.amzn1.x86_64
gnutls-2.12.23-21.18.amzn1.x86_64
gobject-introspection-1.36.0-4.9.amzn1.x86_64
gobject-introspection-devel-1.36.0-4.9.amzn1.x86_64
gpg-pubkey-21c0f39f-56d0e29a
gpgme-1.4.3-5.15.amzn1.x86_64
grep-2.20-2.17.amzn1.x86_64
groff-1.22.2-8.11.amzn1.x86_64
groff-base-1.22.2-8.11.amzn1.x86_64
grubby-7.0.15-5.7.amzn1.x86_64
gtk-doc-1.19-2.11.amzn1.noarch
gzip-1.5-8.18.amzn1.x86_64
hardlink-1.0-10.4.amzn1.x86_64
hwdata-0.233-14.1.18.amzn1.noarch
indent-2.2.10-7.6.amzn1.x86_64
info-5.1-4.10.amzn1.x86_64
initscripts-9.03.49-1.35.amzn1.x86_64
intltool-0.41.0-1.1.5.amzn1.noarch
iproute-4.4.0-3.23.amzn1.x86_64
iptables-1.4.18-1.22.amzn1.x86_64
iputils-20121221-7.13.amzn1.x86_64
jasper-libs-1.900.1-16.9.amzn1.x86_64
jbigkit-libs-2.0-11.4.amzn1.x86_64
kbd-1.15-11.4.amzn1.x86_64
kbd-misc-1.15-11.4.amzn1.noarch
kernel-4.9.27-14.31.amzn1.x86_64
kernel-devel-4.9.27-14.31.amzn1.x86_64
kernel-headers-4.9.27-14.31.amzn1.x86_64
kexec-tools-2.0.0-273.11.amzn1.x86_64
keyutils-libs-1.5.8-3.12.amzn1.x86_64
kmod-14-10.10.amzn1.x86_64
kmod-libs-14-10.10.amzn1.x86_64
kpartx-0.4.9-72.8.amzn1.x86_64
krb5-libs-1.14.1-27.41.amzn1.x86_64
latrace-0.5.9-2.2.amzn1.x86_64
lcms-devel-1.19-1.8.amzn1.x86_64
lcms-libs-1.19-1.8.amzn1.x86_64
lcms2-2.6-2.5.amzn1.x86_64
lcms2-devel-2.6-2.5.amzn1.x86_64
less-436-13.12.amzn1.x86_64
libICE-1.0.6-1.4.amzn1.x86_64
libICE-devel-1.0.6-1.4.amzn1.x86_64
libSM-1.2.1-2.6.amzn1.x86_64
libSM-devel-1.2.1-2.6.amzn1.x86_64
libX11-1.6.0-2.2.12.amzn1.x86_64
libX11-common-1.6.0-2.2.12.amzn1.x86_64
libX11-devel-1.6.0-2.2.12.amzn1.x86_64
libXau-1.0.6-4.9.amzn1.x86_64
libXau-devel-1.0.6-4.9.amzn1.x86_64
libXdamage-1.1.3-4.7.amzn1.x86_64
libXext-1.3.2-2.1.10.amzn1.x86_64
libXext-devel-1.3.2-2.1.10.amzn1.x86_64
libXfixes-5.0.1-2.1.8.amzn1.x86_64
libXfont-1.4.5-5.12.amzn1.x86_64
libXrender-0.9.8-2.1.9.amzn1.x86_64
libXt-1.1.4-6.1.9.amzn1.x86_64
libXt-devel-1.1.4-6.1.9.amzn1.x86_64
libXxf86vm-1.1.3-2.1.9.amzn1.x86_64
libacl-2.2.49-6.11.amzn1.x86_64
libassuan-2.0.3-3.3.amzn1.x86_64
libattr-2.4.46-12.10.amzn1.x86_64
libblkid-2.23.2-33.28.amzn1.x86_64
libcap-2.16-5.5.8.amzn1.x86_64
libcap-ng-0.7.5-4.15.amzn1.x86_64
libcom_err-1.42.12-4.40.amzn1.x86_64
libcurl-7.51.0-4.73.amzn1.x86_64
libdrm-2.4.52-4.12.amzn1.x86_64
libdwarf-20130207-3.3.amzn1.x86_64
libedit-2.11-4.20080712cvs.1.6.amzn1.x86_64
libexif-0.6.21-5.6.amzn1.x86_64
libexif-devel-0.6.21-5.6.amzn1.x86_64
libffi-3.0.13-16.5.amzn1.x86_64
libffi-devel-3.0.13-16.5.amzn1.x86_64
libfontenc-1.0.5-2.6.amzn1.x86_64
libgcc48-4.8.3-9.111.amzn1.x86_64
libgcrypt-1.5.3-12.19.amzn1.x86_64
libgfortran-4.8.3-9.111.amzn1.x86_64
libgomp-4.8.3-9.111.amzn1.x86_64
libgpg-error-1.11-1.12.amzn1.x86_64
libicu-50.1.2-11.12.amzn1.x86_64
libidn-1.18-2.8.amzn1.x86_64
libidn2-0.16-1.2.amzn1.x86_64
libjpeg-turbo-1.2.90-5.14.amzn1.x86_64
libjpeg-turbo-devel-1.2.90-5.14.amzn1.x86_64
libmount-2.23.2-33.28.amzn1.x86_64
libmpc-1.0.1-3.3.amzn1.x86_64
libnih-1.0.1-7.8.amzn1.x86_64
libpciaccess-0.13.1-4.1.11.amzn1.x86_64
libpng-1.2.49-2.14.amzn1.x86_64
libpng-devel-1.2.49-2.14.amzn1.x86_64
libpsl-0.6.2-1.2.amzn1.x86_64
libpwquality-1.2.3-4.8.amzn1.x86_64
libquadmath-4.8.3-9.111.amzn1.x86_64
libquadmath48-devel-4.8.3-9.111.amzn1.x86_64
libselinux-2.1.10-3.22.amzn1.x86_64
libsepol-2.1.7-3.12.amzn1.x86_64
libserf-1.3.7-1.7.amzn1.x86_64
libssh2-1.4.2-2.13.amzn1.x86_64
libstdc++48-4.8.3-9.111.amzn1.x86_64
libstdc++48-devel-4.8.3-9.111.amzn1.x86_64
libtasn1-2.3-6.6.amzn1.x86_64
libtiff-4.0.3-27.29.amzn1.x86_64
libtiff-devel-4.0.3-27.29.amzn1.x86_64
libtool-2.4.2-20.4.8.3.31.amzn1.x86_64
libtool-ltdl-2.4.2-20.4.8.3.31.amzn1.x86_64
libudev-173-4.13.amzn1.x86_64
libunistring-0.9.3-6.1.amzn1.x86_64
libuser-0.60-7.23.amzn1.x86_64
libutempter-1.1.5-4.1.6.amzn1.x86_64
libuuid-2.23.2-33.28.amzn1.x86_64
libverto-0.2.5-4.9.amzn1.x86_64
libwebp-0.3.0-3.5.amzn1.x86_64
libwebp-devel-0.3.0-3.5.amzn1.x86_64
libwmf-lite-0.2.8.4-41.11.amzn1.x86_64
libxcb-1.11-2.21.amzn1.x86_64
libxcb-devel-1.11-2.21.amzn1.x86_64
libxml2-2.9.1-6.3.49.amzn1.x86_64
libxml2-devel-2.9.1-6.3.49.amzn1.x86_64
libxml2-python27-2.9.1-6.3.49.amzn1.x86_64
libxslt-1.1.28-5.12.amzn1.x86_64
ltrace-0.5-23.45svn.6.amzn1.x86_64
lua-5.1.4-4.1.9.amzn1.x86_64
lynx-2.8.6-27.7.amzn1.x86_64
lzo-2.08-1.5.amzn1.x86_64
m4-1.4.16-9.10.amzn1.x86_64
make-3.82-21.10.amzn1.x86_64
mdadm-3.2.6-7.32.amzn1.x86_64
mesa-dri-drivers-10.1.2-2.35.amzn1.x86_64
mesa-dri-filesystem-10.1.2-2.35.amzn1.x86_64
mesa-dri1-drivers-7.11-8.7.amzn1.x86_64
mesa-libGL-10.1.2-2.35.amzn1.x86_64
mingetty-1.08-5.9.amzn1.x86_64
mpfr-3.1.1-4.14.amzn1.x86_64
ncurses-5.7-4.20090207.14.amzn1.x86_64
ncurses-base-5.7-4.20090207.14.amzn1.x86_64
ncurses-libs-5.7-4.20090207.14.amzn1.x86_64
net-tools-1.60-110.10.amzn1.x86_64
nspr-4.11.0-1.37.amzn1.x86_64
nss-3.21.3-2.77.amzn1.x86_64
nss-softokn-3.16.2.3-14.4.39.amzn1.x86_64
nss-softokn-freebl-3.16.2.3-14.4.39.amzn1.x86_64
nss-sysinit-3.21.3-2.77.amzn1.x86_64
nss-tools-3.21.3-2.77.amzn1.x86_64
nss-util-3.21.3-1.1.51.amzn1.x86_64
openjade-1.3.2-36.5.amzn1.x86_64
openldap-2.4.40-12.30.amzn1.x86_64
opensp-1.5.2-12.1.5.amzn1.x86_64
openssh-6.6.1p1-33.66.amzn1.x86_64
openssh-clients-6.6.1p1-33.66.amzn1.x86_64
openssl-1.0.1k-15.99.amzn1.x86_64
p11-kit-0.18.5-2.3.amzn1.x86_64
p11-kit-trust-0.18.5-2.3.amzn1.x86_64
pam-1.1.8-12.33.amzn1.x86_64
patch-2.7.1-8.9.amzn1.x86_64
patchutils-0.3.1-3.1.5.amzn1.x86_64
pcre-8.21-7.7.amzn1.x86_64
perl-5.16.3-286.38.amzn1.x86_64
perl-Carp-1.26-244.5.amzn1.noarch
perl-Data-Dumper-2.145-3.5.amzn1.x86_64
perl-Encode-2.51-7.5.amzn1.x86_64
perl-Error-0.17020-2.9.amzn1.noarch
perl-Exporter-5.68-3.5.amzn1.noarch
perl-File-Path-2.09-2.5.amzn1.noarch
perl-File-Temp-0.23.01-3.5.amzn1.noarch
perl-Filter-1.49-3.5.amzn1.x86_64
perl-Getopt-Long-2.40-2.5.amzn1.noarch
perl-Git-2.7.4-1.47.amzn1.noarch
perl-HTTP-Tiny-0.033-3.6.amzn1.noarch
perl-PathTools-3.40-5.5.amzn1.x86_64
perl-Pod-Escapes-1.04-286.38.amzn1.noarch
perl-Pod-Perldoc-3.20-4.7.amzn1.noarch
perl-Pod-Simple-3.28-4.6.amzn1.noarch
perl-Pod-Usage-1.63-3.5.amzn1.noarch
perl-SGMLSpm-1.03ii-31.7.amzn1.noarch
perl-Scalar-List-Utils-1.27-248.5.amzn1.x86_64
perl-Socket-2.010-3.5.amzn1.x86_64
perl-Storable-2.45-3.5.amzn1.x86_64
perl-TermReadKey-2.30-20.9.amzn1.x86_64
perl-Test-Harness-3.28-3.6.amzn1.noarch
perl-Text-ParseWords-3.29-4.5.amzn1.noarch
perl-Text-Unidecode-0.04-20.7.amzn1.noarch
perl-Thread-Queue-3.02-2.5.amzn1.noarch
perl-Time-HiRes-1.9725-272.5.amzn1.x86_64
perl-Time-Local-1.2300-2.5.amzn1.noarch
perl-XML-Parser-2.41-10.9.amzn1.x86_64
perl-constant-1.27-2.5.amzn1.noarch
perl-libintl-1.20-12.7.amzn1.x86_64
perl-libs-5.16.3-286.38.amzn1.x86_64
perl-macros-5.16.3-286.38.amzn1.x86_64
perl-parent-0.225-244.5.amzn1.noarch
perl-podlators-2.5.1-3.8.amzn1.noarch
perl-threads-1.87-4.5.amzn1.x86_64
perl-threads-shared-1.43-6.5.amzn1.x86_64
pinentry-0.7.6-6.11.amzn1.x86_64
pixman-0.32.4-4.11.amzn1.x86_64
pkgconfig-0.27.1-2.7.amzn1.x86_64
popt-1.13-7.7.amzn1.x86_64
procps-3.2.8-30.14.amzn1.x86_64
psmisc-22.20-8.12.amzn1.x86_64
pth-2.0.7-9.3.7.amzn1.x86_64
python27-2.7.12-2.120.amzn1.x86_64
python27-beaker-1.5.4-10.6.amzn1.noarch
python27-chardet-2.0.1-7.7.amzn1.noarch
python27-iniparse-0.3.1-2.1.9.amzn1.noarch
python27-kitchen-1.1.1-5.6.amzn1.noarch
python27-libs-2.7.12-2.120.amzn1.x86_64
python27-mako-0.8.1-2.8.amzn1.noarch
python27-markupsafe-0.11-4.6.amzn1.x86_64
python27-paste-1.7.4-2.9.amzn1.noarch
python27-pyOpenSSL-0.10-2.8.amzn1.x86_64
python27-pycurl-7.19.0-17.12.amzn1.x86_64
python27-pygpgme-0.3-9.12.amzn1.x86_64
python27-pyliblzma-0.5.3-11.6.amzn1.x86_64
python27-pyxattr-0.5.0-1.6.amzn1.x86_64
python27-urlgrabber-3.10-8.16.amzn1.noarch
rcs-5.7-37.7.amzn1.x86_64
readline-6.2-9.14.amzn1.x86_64
rpm-4.11.3-21.75.amzn1.x86_64
rpm-build-4.11.3-21.75.amzn1.x86_64
rpm-build-libs-4.11.3-21.75.amzn1.x86_64
rpm-libs-4.11.3-21.75.amzn1.x86_64
rpm-python27-4.11.3-21.75.amzn1.x86_64
rsync-3.0.6-12.13.amzn1.x86_64
sed-4.2.1-10.10.amzn1.x86_64
setup-2.8.14-20.12.amzn1.noarch
sgml-common-0.6.3-33.5.amzn1.noarch
shadow-utils-4.1.4.2-13.10.amzn1.x86_64
shared-mime-info-1.1-9.8.amzn1.x86_64
snappy-1.0.5-1.1.amzn1.x86_64
source-highlight-3.1.6-4.2.amzn1.x86_64
sqlite-3.7.17-6.13.amzn1.x86_64
strace-4.8-11.16.amzn1.x86_64
subversion-1.9.5-1.56.amzn1.x86_64
subversion-libs-1.9.5-1.56.amzn1.x86_64
sudo-1.8.6p3-25.23.amzn1.x86_64
swig-2.0.10-4.24.amzn1.x86_64
sysctl-defaults-1.0-1.1.amzn1.noarch
system-release-2017.03-0.0.noarch
system-rpm-config-9.0.3-42.28.amzn1.noarch
systemtap-3.1-2.34.amzn1.x86_64
systemtap-client-3.1-2.34.amzn1.x86_64
systemtap-devel-3.1-2.34.amzn1.x86_64
systemtap-runtime-3.1-2.34.amzn1.x86_64
sysvinit-2.87-6.dsf.15.amzn1.x86_64
tar-1.26-31.22.amzn1.x86_64
texinfo-5.1-4.10.amzn1.x86_64
tzdata-2017b-1.69.amzn1.noarch
udev-173-4.13.amzn1.x86_64
unzip-6.0-4.10.amzn1.x86_64
upstart-0.6.5-13.3.13.amzn1.x86_64
urw-fonts-2.4-10.7.amzn1.noarch
util-linux-2.23.2-33.28.amzn1.x86_64
valgrind-3.10.0-16.14.amzn1.x86_64
vim-minimal-8.0.0503-1.45.amzn1.x86_64
wget-1.18-1.18.amzn1.x86_64
which-2.19-6.10.amzn1.x86_64
xml-common-0.6.3-33.5.amzn1.noarch
xorg-x11-font-utils-7.2-11.5.amzn1.x86_64
xorg-x11-proto-devel-7.7-9.10.amzn1.noarch
xz-5.1.2-12alpha.12.amzn1.x86_64
xz-devel-5.1.2-12alpha.12.amzn1.x86_64
xz-libs-5.1.2-12alpha.12.amzn1.x86_64
yum-3.4.3-150.68.amzn1.noarch
yum-metadata-parser-1.1.4-10.20.amzn1.x86_64
yum-plugin-ovl-1.1.31-40.29.amzn1.noarch
yum-plugin-priorities-1.1.31-40.29.amzn1.noarch
yum-utils-1.1.31-40.29.amzn1.noarch
zip-3.0-1.10.amzn1.x86_64
zlib-1.2.8-7.18.amzn1.x86_64
zlib-devel-1.2.8-7.18.amzn1.x86_64
````

Linked libs to libvips
````
linux-vdso.so.1 =>  (0x00007ffc34650000)
libz.so.1 => /lib64/libz.so.1 (0x00007ff4a39ee000)
libMagickCore.so.5 => /usr/lib64/libMagickCore.so.5 (0x00007ff4a3546000)
libpng12.so.0 => /usr/lib64/libpng12.so.0 (0x00007ff4a331f000)
libtiff.so.5 => /usr/lib64/libtiff.so.5 (0x00007ff4a30ad000)
libjpeg.so.62 => /usr/lib64/libjpeg.so.62 (0x00007ff4a2e5a000)
libgmodule-2.0.so.0 => /usr/lib64/libgmodule-2.0.so.0 (0x00007ff4a2c56000)
libxml2.so.2 => /usr/lib64/libxml2.so.2 (0x00007ff4a28ee000)
libgobject-2.0.so.0 => /usr/lib64/libgobject-2.0.so.0 (0x00007ff4a269f000)
libglib-2.0.so.0 => /usr/lib64/libglib-2.0.so.0 (0x00007ff4a2376000)
liblcms2.so.2 => /usr/lib64/liblcms2.so.2 (0x00007ff4a211e000)
libwebp.so.4 => /usr/lib64/libwebp.so.4 (0x00007ff4a1ecf000)
libexif.so.12 => /usr/lib64/libexif.so.12 (0x00007ff4a1c89000)
libstdc++.so.6 => /usr/lib64/libstdc++.so.6 (0x00007ff4a1984000)
libm.so.6 => /lib64/libm.so.6 (0x00007ff4a1682000)
libc.so.6 => /lib64/libc.so.6 (0x00007ff4a12bf000)
libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007ff4a10a9000)
libfreetype.so.6 => /usr/lib64/libfreetype.so.6 (0x00007ff4a0e0d000)
libfontconfig.so.1 => /usr/lib64/libfontconfig.so.1 (0x00007ff4a0bd7000)
libXext.so.6 => /usr/lib64/libXext.so.6 (0x00007ff4a09c5000)
libSM.so.6 => /usr/lib64/libSM.so.6 (0x00007ff4a07be000)
libICE.so.6 => /usr/lib64/libICE.so.6 (0x00007ff4a05a1000)
libX11.so.6 => /usr/lib64/libX11.so.6 (0x00007ff4a0266000)
libXt.so.6 => /usr/lib64/libXt.so.6 (0x00007ff4a0001000)
liblzma.so.5 => /usr/lib64/liblzma.so.5 (0x00007ff49fddc000)
libbz2.so.1 => /lib64/libbz2.so.1 (0x00007ff49fbcb000)
libgomp.so.1 => /usr/lib64/libgomp.so.1 (0x00007ff49f9b5000)
libpthread.so.0 => /lib64/libpthread.so.0 (0x00007ff49f798000)
libltdl.so.7 => /usr/lib64/libltdl.so.7 (0x00007ff49f58f000)
libjbig.so.2.0 => /usr/lib64/libjbig.so.2.0 (0x00007ff49f383000)
libdl.so.2 => /lib64/libdl.so.2 (0x00007ff49f17e000)
libffi.so.6 => /usr/lib64/libffi.so.6 (0x00007ff49ef76000)
/lib64/ld-linux-x86-64.so.2 (0x000055a093d7f000)
libexpat.so.1 => /lib64/libexpat.so.1 (0x00007ff49ed4c000)
libuuid.so.1 => /lib64/libuuid.so.1 (0x00007ff49eb48000)
libxcb.so.1 => /usr/lib64/libxcb.so.1 (0x00007ff49e92a000)
libXau.so.6 => /usr/lib64/libXau.so.6 (0x00007ff49e726000)
````

The file ./failing-test/packages-working-installed.txt contains a list of packages where everything works fine.



