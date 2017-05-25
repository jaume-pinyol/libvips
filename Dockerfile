FROM amazonlinux:2017.03
MAINTAINER spt-edge@schibsted.com
ENV WORKDIRECTORY /work
ENV PKG_CONFIG_PATH $PKG_CONFIG_PATH:/usr/lib/pkgconfig/
COPY . ./libvips
RUN mkdir _resources
COPY _resources/install_libvips_alinux.sh _resources/
RUN yum install -y sudo
RUN sudo yum groupinstall -y "Development Tools"
RUN sudo yum install -y wget
RUN sudo yum install -y glib2-devel libxml2-devel gtk-doc libxml2-devel libpng-devel libtiff-devel libexif-devel libgsf-devel lcms-devel ImageMagick-devel gobject-introspection-devel libwebp-devel curl
RUN sudo yum install -y libpng-devel libxml2-devel
RUN sudo yum install -y libjpeg-turbo libjpeg-turbo-devel
RUN sudo yum update -y expat

RUN bash -c "source _resources/install_libvips_alinux.sh"

RUN rpm -qa | sort
RUN ldd /usr/lib/libvips.so
WORKDIR $WORKDIRECTORY
CMD ["/bin/bash"]
