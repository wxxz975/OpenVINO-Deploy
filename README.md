# OpenVINO-Deploy

OpenVINO-Deploy aims to implement popular AI models' inference deployment with OpenVINO written in C++, with a primary focus on object detection algorithms.

## Test Environment

1. OpenVINO 2023.3.0
2. OpenCV 4.2.0
3. Ubuntu 20.04

## Models

Following models are implemented.

|Name | Description|
|-|-|
|[yolov3](./yolov3/)| A fast and accurate real-time object detection algorithm that can detect multiple objects in an image or video stream with high efficiency.|
|[yolov5](./yolov5/)| A fast, accurate, and user-friendly real-time object detection algorithm.|
|[yolov7](./yolov7/)|  A cutting-edge real-time object detection model delivering exceptional accuracy and speed. |
|[yolov8](./yolov8/)| An enhanced YOLO object detection model with improved performance and flexibility.|
|[yolov9](./yolov9/)| Paper yolov9 Implement, Learning What You Want to Learn Using Programmable Gradient Information.|
|[rt-detr](./rtdetr/)| RT-DETR is a real-time object detection model that leverages transformers for efficient and accurate performance. |

<!-- |[detr](./detr/)| A transformer-based object detection model that directly predicts object bounding boxes and classes.| -->


## Quick Start

1. Clone this repo

```bash
git clone https://github.com/wxxz975/OpenVINO-Deploy.git
```

2. Create Build Directory

```bash
mkdir build && cd build
```
3. Build All
```bash
cmake .. && make -j$(nproc)
```

Then, you will find executable files for demos in this build directory.

---
***The onnx models exported by the experiment can be found on [BaiduCloud](https://pan.baidu.com/s/1vCOleM0AEdTaI3gF39bgxw?pwd=wxxz)***





## TODO List

- [x] yolov3
- [x] yolov3-spp
- [x] yolov3-tiny
- [ ] yolop
- [ ] yolov4
- [x] yolov5
- [x] yolov7
- [x] yolov8
- [x] yolov9
- [ ] detr
- [x] rt-detr
- [ ] ssd
- [ ] faster-rcnn

