# Group2DIT168
A self driving miniature vehicle built on OpenDaVINICI and OpenDLV.

## Introduction
The main goal of this project is to design, develop and test a self driving miniature vehicle which can communicate with other miniature vehicles and follow them based on the received data. 
The software architecture is based on Microservices. Used tools are deployed as Docker images.

### GitHub layout description
The repository setup consists of a central repository, refered to as `origin`. The central repository consists of two main branches: `master` and `develop`. 
The `master` branch is a main branch which contains the source code in production-ready state. The `develop` branch is a main branch which contains the source code with latest integrated features. 

Once the source code in the `develop` branch contains stable and deliverable code, it should be merged into `master`. The repository may contain a number of supporting branches, which are used to develop new features. Supporting branches may branch off from and must be merged back into develop. 

![alt text][gitlayout]

[gitlayout]: https://github.com/Shaun-McMurray/Group2DIT168/documentation/GitHubLayout.png "GitHub layout"

Branching off from the `develop` branch:
```
$ git checkout -b myfeature develop
```
Merging a finished feature into the `develop` branch:
```
$ git checkout develop 			//switching to branch 'develop'
$ git merge --no-ff myfeature		//merging the branch
$ git branch -d myfeature		//deleting branch myfeature
$ git push origin develop 		//pushing changes
```

`master` and `develop` are protected branches to which changes can be pushed only through pull requests. Two members must review and approve the pull request before the changes are merged into the repository.

GitHub's issue tracker is used for task management.

## Getting started 
Following instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- [OpenDaVINCI](http://opendavinci.readthedocs.io/)
- [CMake](http://derekmolloy.ie/hello-world-introductions-to-cmake)
- [Docker](https://docs.docker.com/install/linux/docker-ce/ubuntu/)

### Installing

### Running the tests

## Hardware used

\- BeagleBone Blue board\
\- RaspberryPi 3 model B board\
\- Battery [LiPo 7.4V 1200mAh 30C]\
\- Electronic Speed Control (ESC) unit [SKYRC Cheetah 60A Brushless ESC]\
\- Steering servo [Hitec Midi-Servo HS-5245MG]\
\- Motor [SKYRC Cheetah Brushless ESC]\
\- Ultrasonic sensors (front and rear) [Devantech SRF08]\
\- Infrared sensors (left and right) [Sharp GP2Y0A41SK0F]\
\- RaspberryPi Camera Module v2\

## Contributing
Please read our [Contributing.md](CONTRIBUTING.md) for more details. 

## Authors
- Gabriel Bulai
- Tim Jonasson
- Shaun McMurray
- Nina Uljanic

## Versioning
1.0.0 Nina Uljanic (2018-02-17)

## License
This project is lincesed under the MIT license. 

## Acknowledgments
- Christian Berger - professor
- Yue Kang - teaching assistant
- Jan Schroeder - teaching assistant
- Federico Giaimo - teaching assistant