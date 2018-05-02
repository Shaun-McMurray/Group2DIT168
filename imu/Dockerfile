FROM arm32v7/debian:jessie-slim 
#MAINTAINER Group2

RUN apt-get update -q && \
    #apt install -y dirmngr software-properties-common && \
	apt-get install -y build-essential git && \    
    #apt-get install -y software-properties-common && \
    apt-get update -q && \
    #apt-get dist-upgrade -y && \
    apt-get install -y \ 
	sudo \
	wget && \ 
	#xz-utils && \
    apt-get clean -y && \
    apt-get autoclean -y && \
	apt-get autoremove -y && \
	wget https://cmake.org/files/v3.11/cmake-3.11.1.tar.gz && \
	tar -xf cmake-3.11.1.tar.gz && \
	cd cmake-3.11.1 && \
	./configure && \
	make DESTDIR=/usr/bin/cmake && \
	sudo make install && \
	export PATH=/usr/local/bin:$PATH && \
	cd ~/ && \
	wget https://launchpad.net/~chrberger/+archive/ubuntu/libcluon/+files/libcluon_0.0.80-1ppa1~xenial1_armhf.deb && \
	dpkg -i libcluon_0.0.80-1ppa1~xenial1_armhf.deb && \
	sudo apt-get install ./libcluon_0.0.80-1ppa1~xenial1_armhf.deb && \
	wget https://github.com/StrawsonDesign/Robotics_Cape_Installer/releases/download/v0.3.4/roboticscape_0.3.4_armhf.deb && \
	DEBIAN_FRONTEND=noninteractive dpkg -i roboticscape_0.3.4_armhf.deb 
	
#download StrawsonDesign Robotics Cape Library v. 0.3.4
#RUN wget https://github.com/StrawsonDesign/Robotics_Cape_Installer/releases/download/v0.3.4/roboticscape_0.3.4_armhf.deb

#RUN DEBIAN_FRONTEND=noninteractive dpkg -i roboticscape_0.3.4_armhf.deb

ENV APP_PATH /opt/sources
RUN mkdir -p $APP_PATH
WORKDIR $APP_PATH
COPY . $APP_PATH
RUN mkdir build -p && \

    cd build/ && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make
CMD ["./read_imu"]


#RUN rc_version
 
