# Yolov9 Inference



## Quick Start

### Download Model
download the model from the official [website](https://github.com/WongKinYiu/yolov9). or choice your own pretrain model to here


### Export Pytorch Model to the ONNX format
1. Download the yolov9 repo to local
```bash
git clone https://github.com/WongKinYiu/yolov9 && cd yolov9
```

2. Export example


```bash
python export.py --weights <path/to/your/model.pt> --include onnx
```
For detailed export parameters, please refer to the official [code](https://github.com/WongKinYiu/yolov9/blob/main/export.py).

### Build & Run
```bash
cd <path/to/OpenVINO-Deploy>
mkdir build && cd build
make -j$(nproc)
yolov9/yolov9 <path/to/your/model.onnx> <path/to/test/image>
```




