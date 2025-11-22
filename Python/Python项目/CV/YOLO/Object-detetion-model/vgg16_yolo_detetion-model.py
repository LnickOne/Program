import torch
import torchvision
from torch import nn
from torch.utils.data import dataset
from torchvision import transforms
from torchvision.models import vgg16
from yolo_dateset import YOLODataset


class VGG16Model(nn.Module):
    def __init__(self):
        super().__init__()
        self.feature_extractor = vgg16().features  # 只要特征提取部分，后面的就不要了
        self.fc_layer = nn.Sequential(
            nn.Flatten(),
            nn.Linear(512 * 14 * 14, 4096),
            nn.ReLU(),
            nn.Linear(4096, 1024),
            nn.ReLU(),
            nn.Linear(1024, 8), # 4个cordate +4个class
        )

    def forward(self, x):
        x = self.feature_extractor(x)
        x = self.fc_layer(x)
        return x


if __name__ == "__main__":
    model = VGG16Model()
    print(model)
    input = torch.randn(1, 3, 448, 448)
    output = model(input)
    print(output)
    print(output.shape)
    # 测试数据集
    # dataset = YOLODataset(
    #     r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/YOLO/HelmetDataset-YOLO-Train/images",
    #     r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/YOLO/HelmetDataset-YOLO-Train/labels",
    #     transforms.Compose([transforms.ToTensor(), transforms.Resize((512, 512))]),
    #     lable_tranform=None,
    # )
    # image, target = dataset[0]
    # output = model(image)
    # print(output.shape)
