from torch import nn


class YoloLoss(nn.Module):
    def __init__(self):
        super().__init__()
        # 位置损失使用MSE，分类损失使用交叉熵
        self.location_loss = nn.MSELoss()
        self.class_loss = nn.CrossEntropyLoss()

