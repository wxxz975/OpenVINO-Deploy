# rt-detr Inference


## Quick Start

### Download Model
download the model from the ultralytics Release [website](https://github.com/ultralytics/assets/releases). or choice your own pretrain model to here.


### Export Pytorch Model to the ONNX format
1. Install ultralytics
```bash
pip install ultralytics
```

2. Export example

```bash
yolo export model=rtdetr-l.pt format=onnx opset=17 simplify=True
```
For detailed export parameters, please refer to the official [Docs](https://docs.ultralytics.com/modes/export/#arguments).

### Build & Run
```bash
cd <path/to/OpenVINO-Deploy>
mkdir build && cd build
make -j$(nproc)
yolov3/yolov3 <path/to/your/model.onnx> <path/to/test/image>
```