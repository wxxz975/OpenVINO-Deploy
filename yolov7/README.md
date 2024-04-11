# Yolov7 Inference



## Quick Start

### Download Model
download the model from the official [website](https://github.com/WongKinYiu/yolov7). or put your own pretrained model to here


### Export Pytorch Model to the ONNX format
1. Download the yolov7 repo to local
```bash
git clone https://github.com/WongKinYiu/yolov7 && cd yolov7
```

2. Export example


```bash
python export.py --weights <path/to/your/model.pt> --grid
```
For detailed export parameters, please refer to the official [code](https://github.com/WongKinYiu/yolov7/blob/main/export.py).

### Build & Run
```bash
cd <path/to/OpenVINO-Deploy>
mkdir build && cd build
make -j$(nproc)
yolov7/yolov7 <path/to/your/model.onnx> <path/to/test/image>
```




