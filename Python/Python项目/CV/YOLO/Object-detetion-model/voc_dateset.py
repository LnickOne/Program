import os
from PIL import Image
from torch.distributions import transform_to
from torch.utils.data import Dataset


class VOCDataset(Dataset):
    def __init__(self, image_folder, label_folder, transform, lable_tranform):
        self.image_folder = image_folder
        self.label_folder = label_folder
        self.transform = transform
        self.label_transform = lable_tranform
        self.image_names = os.listdir(self.image_folder)

    def __len__(self):
        return len(self.image_names)

    def __getitem__(self, index):
        image_name = self.image_names[index]
        image_path = os.path.join(self.image_folder, image_name)
        image = Image.open(image_path).convert("RGB")
        return image


if __name__ == "__main__":
    train_dataset = VOCDataset(
        r"/home/lnick/GitHub/Program/Python/Python项目/深度学习/CV/YOLO/DataSet/VOC/HelmetDataset-VOC/train/images",
        r"/home/lnick/GitHub/Program/Python/Python项目/深度学习/CV/YOLO/DataSet/VOC/HelmetDataset-VOC/train/labels",
        transform=None,
        lable_tranform=None,
    )
    print(len(train_dataset))
    print(train_dataset[11])
