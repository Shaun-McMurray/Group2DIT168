# Group2DIT168
A self driving miniature vehicle built on OpenDaVINICI and OpenDLV.

## Introduction
The main goal of this project is to design, develop and test a self driving miniature vehicle which can communicate with other miniature vehicles and follow them based on the received data. In addition to following other vehicles, it will also have the ability to autonomously follow a lane. 

### GitHub layout description
The repository setup consists of a central repository, refered to as `origin`. The central repository consists of two main branches: `master` and `develop`. 
The `master` branch is a main branch which contains the source code in production-ready state. The `develop` branch is a main branch which contains the source code with latest integrated features. 

Once the source code in the `develop` branch contains stable and deliverable code, it should be merged into `master`. The repository may contain a number of supporting branches, which are used to develop new features. Supporting branches may branch off from and must be merged back into develop. 


![alt text][gitlayout]

[gitlayout]: https://raw.githubusercontent.com/Shaun-McMurray/Group2DIT168/master/documentation/GitHubLayout.png?token=AYDzFepkXWG_fnySxF0kTgjIEATQYVmhks5aku4UwA%3D%3D "GitHub layout"

Branching off from the `develop` branch:
```
git checkout -b myfeature develop
```
Merging a finished feature into the `develop` branch:
```
git checkout develop 			//switching to branch 'develop'
git merge --no-ff myfeature		//merging the branch
git branch -d myfeature		//deleting branch myfeature
git push origin develop 		//pushing changes
```

`master` and `develop` are protected branches to which changes can be pushed only through pull requests. Two members must review and approve the pull request before the changes are merged into the repository.

GitHub's issue tracker is used for task management.

## Getting started 
Following instructions will get you a copy of the project.

### Prerequisites
- [OpenDaVINCI](http://opendavinci.readthedocs.io/)
- [CMake](http://derekmolloy.ie/hello-world-introductions-to-cmake)
- [Docker](https://docs.docker.com/install/linux/docker-ce/ubuntu/)

### Cloning, Building, and Testing

To clone:
```
git clone https://github.com/Shaun-McMurray/Group2DIT168.git
```

To build:
```
cd build
cmake ..
make
```

When make is run a test runner is produced.
To test:
```
./DIT168-Runner
```

##Building and Testing with Docker

First pull the latest version:
```
docker pull sixonetwo/dit168:latest
```

Then to run the container:
```
docker run --rm -ti --net=host sixonetwo/dit168:latest
```

Tests are run during the build process, to run tests in docker, build a new docker image from the root project folder:
```
docker build -t yourtag .
```

To run your new built image:
```
docker run --rm -ti --net=host yourtag
```

##Building and Testing with Travis

When you are ready to commit changes to the project the build server will test and deploy your changes automatically.
First you can check if your build succeeds on Github by seeing a green checkmark next to your commit or in the slack channel #buildstatus
When your build succeeds your new Docker image is push to Docker Hub, to pull it:
```
docker pull sixonetwo/dit168:"your commit hash"
```


## Hardware used

\- BeagleBone Blue board\
\- RaspberryPi 3 model B board\
\- Battery [LiPo 7.4V 1200mAh 30C]\
\- Electronic Speed Control (ESC) unit [SKYRC Cheetah 60A Brushless ESC]\
\- Steering servo [Hitec Midi-Servo HS-5245MG]\
\- Motor [SKYRC Cheetah Brushless ESC]\
\- Ultrasonic sensors (front and rear) [Devantech SRF08]\
\- Infrared sensors (left and right) [Sharp GP2Y0A41SK0F]\
\- RaspberryPi Camera Module v2

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