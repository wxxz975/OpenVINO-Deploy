#crnn Inference


### Download Model
download the model from the official [repo](https://github.com/meijieru/crnn.pytorch). or choice your own pretrain model to here.


### Export Pytorch Model to the ONNX format
1. Clone Official Repo
```bash
git clone https://github.com/meijieru/crnn.pytorch.git
```
2. Copy export_onnx.py to crnn directory
```bash
cp ./export_onnx.py <path/to/your/crnn/dir>
```
3. Change the model_path in the export_onnx.py file to the path of the crnn.pth model you downloaded

4. Export

```bash
python export_onnx.py
```

### Build & Run
```bash
cd <path/to/OpenVINO-Deploy>
mkdir build && cd build
make -j$(nproc)
crnn/crnn <path/to/your/model.onnx> <path/to/test/image>
```