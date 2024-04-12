import torch
from models.crnn import CRNN


if __name__ == "__main__":
    
    model_path = "E:\\workspace\\weights\\crnn\\crnn.pth"    
    # output path
    onnx_file_path = "crnn.onnx"

    # define the model structure
    model = CRNN(32, 1, 37, 256)

    # load pretrained weights
    checkpoint = torch.load(model_path)
    
    # load to model
    model.load_state_dict(checkpoint)

    model.eval()

    # input shape
    batch_size = 1
    height = 32
    width = 100
    dummy_input = torch.randn(batch_size, 1, height, width)

    # export
    torch.onnx.export(
        model,
        dummy_input,
        onnx_file_path,
        input_names=["input"],
        output_names=["output"],
        opset_version=11,
        # dynamic_axes={
        #     "input": {0: "batch_size"},
        #     "output": {0: "batch_size"}
        # }
    )

    print(f"crnn export success to ONNX format: {onnx_file_path}")
